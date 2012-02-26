
#include "ControlFactory.h"
#include "Gwen/Controls.h"

class Button_Factory : public ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Button_Factory, ControlFactory::Base )
		{

		}

		virtual Gwen::String Name(){ return "Button"; }
		virtual Gwen::String BaseName(){ return "Label"; }

		virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent )
		{
			Gwen::Controls::Button* pControl = new Gwen::Controls::Button( parent );
			pControl->SetSize( 100, 20 );
			pControl->SetText( "New Button" );
			return pControl;
		}
};


GWEN_CONTROL_FACTORY( Button_Factory );