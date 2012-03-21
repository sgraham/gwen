
#include "Gwen/Util/ControlFactory.h"
#include "Gwen/Controls.h"

using namespace Gwen;

namespace Property
{
	class ControlName : public Gwen::ControlFactory::Property 
	{
		GWEN_CONTROL_FACTORY_PROPERTY( ControlName, "The control's name" );

		UnicodeString GetValue( Controls::Base* ctrl )
		{
			return Utility::Format( L"%S", ctrl->GetName().c_str() );
		}

		void SetValue( Controls::Base* ctrl, const UnicodeString& str )
		{
			ctrl->SetName( Gwen::Utility::UnicodeToString( str ) );
		}
	};

	class Position : public Gwen::ControlFactory::Property 
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

	class Size: public Gwen::ControlFactory::Property 
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

		int	NumberCount(){ return 2; };

		float GetNumber( Controls::Base* ctrl, int i )
		{ 
			if ( i == 0 ) return ctrl->X();
			return ctrl->Y();
		};

		void SetNumber( Controls::Base* ctrl, int i, float f )
		{
			if ( i == 0 ) return ctrl->SetPos( f, ctrl->Y() );
			ctrl->SetPos( ctrl->X(), f );
		};
	};
}


class Base_Factory : public Gwen::ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Base_Factory, Gwen::ControlFactory::Base )
		{
			AddProperty( new Property::Position() );
			AddProperty( new Property::Size() );
			AddProperty( new Property::ControlName() );
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