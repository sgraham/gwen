
#include "ControlFactory.h"
#include "Gwen/Controls.h"

using namespace Gwen;

namespace Property
{
	class Position : public ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( Position, "Sets the position of the control" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return Utility::Format( L"%i %i", ctrl->X(), ctrl->Y() );
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			int x, y;
			if ( swscanf( str.c_str(), L"%i %i", &x, &y ) != 2 ) return;
			ctrl->SetPos( x, y );
		}
	};

	class Size: public ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( Size, "The with and height of the control" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return Utility::Format( L"%i %i", ctrl->Width(), ctrl->Height() );
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			int w, h;
			if ( swscanf( str.c_str(), L"%i %i", &w, &h ) != 2 ) return;
			ctrl->SetSize( w, h );
		}
	};
}


class Base_Factory : public ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Base_Factory, ControlFactory::Base )
		{
			AddProperty( new Property::Position() );
			AddProperty( new Property::Size() );
		}

		virtual Gwen::String Name(){ return "Base"; }
		virtual Gwen::String BaseName(){ return ""; }

		virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent )
		{
			Gwen::Controls::Base* pControl = new Gwen::Controls::Base( parent );
			pControl->SetSize( 100, 100 );
			return pControl;
		}
};


GWEN_CONTROL_FACTORY( Base_Factory );