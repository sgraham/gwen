
#include "ControlFactory.h"
#include "Gwen/Controls.h"

class Label_Factory : public ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Label_Factory, ControlFactory::Base )
		{

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