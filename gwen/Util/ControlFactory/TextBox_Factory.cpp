
#include "Gwen/Util/ControlFactory.h"
#include "Gwen/Controls.h"

class TextBox_Factory : public Gwen::ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( TextBox_Factory, Gwen::ControlFactory::Base )
		{

		}

		virtual Gwen::String Name(){ return "TextBox"; }
		virtual Gwen::String BaseName(){ return "Label"; }

		virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent )
		{
			Gwen::Controls::TextBox* pControl = new Gwen::Controls::TextBox( parent );
			pControl->SetSize( 100, 20 );
			pControl->SetText( "" );
			return pControl;
		}
};


GWEN_CONTROL_FACTORY( TextBox_Factory );