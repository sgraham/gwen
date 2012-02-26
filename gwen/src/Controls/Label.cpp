/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Utility.h"

using namespace Gwen;
using namespace Gwen::Controls;

GWEN_CONTROL_CONSTRUCTOR( Label )
{
	m_Text = new ControlsInternal::Text( this );
	m_Text->SetFont( GetSkin()->GetDefaultFont() );

	SetMouseInputEnabled( false );
	SetBounds( 0, 0, 100, 10 );
	SetAlignment( Gwen::Pos::Left | Gwen::Pos::Top );
}

void Label::PostLayout( Skin::Base* /*skin*/ )
{
	m_Text->Position( m_iAlign );
}

void Label::SetAlignment( int iAlign )
{ 
	if ( m_iAlign == iAlign ) return;

	m_iAlign = iAlign;
	Invalidate();
}

void Label::SetText( const TextObject& str, bool bDoEvents )
{ 
	if ( m_Text->GetText() == str.GetUnicode() ) return;

	m_Text->SetString( str );
	Redraw();

	if ( bDoEvents )
		OnTextChanged();
}

void Label::SizeToContents()
{
	m_Text->SetPos( m_Padding.left, m_Padding.top );
	m_Text->RefreshSize();

	SetSize( m_Text->Width() + m_Padding.left + m_Padding.right, m_Text->Height() + m_Padding.top + m_Padding.bottom );
}

Gwen::Point Label::GetCharacterPosition( int iChar )
{ 
	Gwen::Point p = m_Text->GetCharacterPosition( iChar );
	p.x += m_Text->X();
	p.y += m_Text->Y();

	return p;
}