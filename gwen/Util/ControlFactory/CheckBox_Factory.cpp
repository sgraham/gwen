
#include "Gwen/Util/ControlFactory.h"
#include "Gwen/Controls.h"

class CheckBox_Factory : public ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( CheckBox_Factory, ControlFactory::Base )
		{

		}

		virtual Gwen::String Name(){ return "CheckBox"; }
		virtual Gwen::String BaseName(){ return "Button"; }

		virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent )
		{
			Gwen::Controls::CheckBox* pControl = new Gwen::Controls::CheckBox( parent );
			return pControl;
		}
};


GWEN_CONTROL_FACTORY( CheckBox_Factory );