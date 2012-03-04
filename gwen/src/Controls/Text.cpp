/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Controls/Text.h"
#include "Gwen/Skin.h"
#include "Gwen/Utility.h"

using namespace Gwen;
using namespace Gwen::ControlsInternal;

GWEN_CONTROL_CONSTRUCTOR( Text )
{
	m_Font = NULL;
	m_ColorOverride = Color( 255, 255, 255, 0 );
	m_Color = GetSkin()->Colors.Label.Default;
	SetMouseInputEnabled( false );
	SetWrap( false );
}

Text::~Text()
{
	// NOTE: This font doesn't need to be released
	// Because it's a pointer to another font somewhere.
}

void Text::Layout( Skin::Base* skin )
{
	if ( m_bTextChanged )
	{
		RefreshSize();
		m_bTextChanged = false;
	}
}

Gwen::Font* Text::GetFont()
{
	return m_Font;
}

void Text::SetFont( Gwen::Font* pFont )
{
	if ( m_Font == pFont ) return;

	m_Font = pFont;
	m_bTextChanged = true;
	Invalidate();
}

void Text::SetString( const TextObject& str )
{ 
	if ( m_String == str ) return;

	m_String = str.GetUnicode(); 
	m_bTextChanged = true;
	Invalidate();
}

void Text::Render( Skin::Base* skin )
{
	if ( m_bWrap ) return;
	if ( Length() == 0 || !GetFont() ) return;

	if ( m_ColorOverride.a == 0 )
		skin->GetRender()->SetDrawColor( m_Color );
	else
		skin->GetRender()->SetDrawColor( m_ColorOverride );

	skin->GetRender()->RenderText( GetFont(), Gwen::Point( GetPadding().left, GetPadding().top ), m_String.GetUnicode() );
}

Gwen::Point Text::GetCharacterPosition( int iChar )
{
	if ( Length() == 0 || iChar == 0 )
	{
		return Gwen::Point( 1, 0 );
	}

	UnicodeString sub = m_String.GetUnicode().substr( 0, iChar );
	Gwen::Point p = GetSkin()->GetRender()->MeasureText( GetFont(), sub );
	
	if ( p.y >= m_Font->size )
		p.y -= m_Font->size;

	return p;
}

int Text::GetClosestCharacter( Gwen::Point p )
{
	int iDistance = 4096;
	int iChar = 0;

	for ( size_t i=0; i<m_String.GetUnicode().length()+1; i++ )
	{
		Gwen::Point cp = GetCharacterPosition( i );
		int iDist = abs(cp.x - p.x) + abs(cp.y - p.y); // this isn't proper

		if ( iDist > iDistance ) continue;

		iDistance = iDist;
		iChar = i;
	}

	return iChar;
}

void Text::OnScaleChanged()
{
	Invalidate();
}

void Text::RefreshSize()
{
	if ( m_bWrap )
	{
		return RefreshSizeWrap();
	}

	if ( !GetFont() )
	{
		Debug::AssertCheck( 0, "Text::RefreshSize() - No Font!!\n" );
		return;
	}

	Gwen::Point p( 1, GetFont()->size );

	if ( Length() > 0 )
	{
		p = GetSkin()->GetRender()->MeasureText( GetFont(), m_String.GetUnicode() );
	}

	p.x += GetPadding().left + GetPadding().right;
	p.y += GetPadding().top + GetPadding().bottom;

	if ( p.x == Width() && p.y == Height() ) 
		return;

	SetSize( p.x, p.y );
	InvalidateParent();
	Invalidate();
}

void SplitWords(const Gwen::UnicodeString &s, wchar_t delim, std::vector<Gwen::UnicodeString> &elems) 
{
	Gwen::UnicodeString str;

	for ( int i=0; i<s.length(); i++ )
	{
		if ( s[i] == L'\n' )
		{
			if ( !str.empty() ) elems.push_back( str );
			elems.push_back( L"\n" );
			str.clear();
			continue;
		}

		if ( s[i] == L' ' )
		{
			elems.push_back( str );
			str.clear();
		}

		str += s[i];
	}
}

void Text::RefreshSizeWrap()
{
	RemoveAllChildren();

	std::vector<Gwen::UnicodeString> words;
	SplitWords( GetText().GetUnicode(), L' ', words );

	if ( !GetFont() )
	{
		Debug::AssertCheck( 0, "Text::RefreshSize() - No Font!!\n" );
		return;
	}

	Point pFontSize = GetSkin()->GetRender()->MeasureText( GetFont(), L" " );

	int w = GetParent()->Width();
	int x = 0, y = 0;

	std::vector<Gwen::UnicodeString>::iterator it = words.begin();
	for ( it; it != words.end(); ++it )
	{
		if ( (*it)[0] == L'\n' )
		{
			y += pFontSize.y;
			x = 0;
			continue;
		}

		Text* t = new Text( this );
		t->SetFont( GetFont() );
		t->SetString( *it );
		t->RefreshSize();

		if ( x + t->Width() > w )
		{
			y += pFontSize.y;
			x = 0 - pFontSize.x;
		}

		t->SetPos( x, y );

		x += t->Width();
	}

	// Size to children height and parent width
	{
		Point childsize = ChildrenSize();
		SetSize( w, childsize.y );
	}

	InvalidateParent();
	Invalidate();
}