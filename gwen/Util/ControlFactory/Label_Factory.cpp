
#include "Gwen/Util/ControlFactory.h"
#include "Gwen/Controls.h"

using namespace Gwen;

namespace Property 
{
	class Text: public ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( Text, "The text, or label of the control" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return gwen_cast<Controls::Label>(ctrl)->GetText().GetUnicode();
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			gwen_cast<Controls::Label>(ctrl)->SetText( str );
		}

	};

	class Font: public ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( Font, "The font name" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return gwen_cast<Controls::Label>(ctrl)->GetFont()->facename;
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			if ( str == L"" ) return;

			Gwen::Font* pFont = gwen_cast<Controls::Label>(ctrl)->GetFont();

			gwen_cast<Controls::Label>(ctrl)->SetFont( str, pFont->size, pFont->bold );
		}

	};

	class FontSize: public ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( FontSize, "The font size" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return Gwen::Utility::Format( L"%i", (int) gwen_cast<Controls::Label>(ctrl)->GetFont()->size );
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			int size;
			if ( swscanf( str.c_str(), L"%i", &size ) != 1 ) return;

			Gwen::Font* pFont = gwen_cast<Controls::Label>(ctrl)->GetFont();
			if ( size == pFont->size ) return;

			gwen_cast<Controls::Label>(ctrl)->SetFont( pFont->facename, size, pFont->bold );
		}

	};

	class FontBold: public ControlFactory::PropertyBool
	{
		GWEN_CONTROL_FACTORY_PROPERTY( FontBold, "The font bold" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			if ( gwen_cast<Controls::Label>(ctrl)->GetFont()->bold ) return True;
			return False;
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			bool bTrue = (str == True);

			Gwen::Font* pFont = gwen_cast<Controls::Label>(ctrl)->GetFont();
			if ( bTrue == pFont->bold ) return;

			gwen_cast<Controls::Label>(ctrl)->SetFont( pFont->facename, pFont->size, bTrue ? true : false );
		}

	};

	class Wrap: public ControlFactory::PropertyBool
	{
		GWEN_CONTROL_FACTORY_PROPERTY( Wrap, "Wrap the text" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			if ( gwen_cast<Controls::Label>(ctrl)->Wrap() ) return True;
			return False;
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			bool bTrue = (str == True);

			if ( bTrue == gwen_cast<Controls::Label>(ctrl)->Wrap() ) return;

			gwen_cast<Controls::Label>(ctrl)->SetWrap( bTrue );
		}

	};

}

class Label_Factory : public Gwen::ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Label_Factory, ControlFactory::Base )
		{
			AddProperty( new Property::Text() );
			AddProperty( new Property::Wrap() );	
			AddProperty( new Property::Font() );
			AddProperty( new Property::FontSize() );
			AddProperty( new Property::FontBold() );			
		}

		virtual Gwen::String Name(){ return "Label"; }
		virtual Gwen::String BaseName(){ return "Base"; }

		virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent )
		{
			Gwen::Controls::Label* pControl = new Gwen::Controls::Label( parent );
			pControl->SetSize( 100, 20 );
			pControl->SetText( "New Label" );
			return pControl;
		}
};

GWEN_CONTROL_FACTORY( Label_Factory );