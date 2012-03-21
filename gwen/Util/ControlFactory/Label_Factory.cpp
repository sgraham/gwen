
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
}

class Label_Factory : public Gwen::ControlFactory::Base
{
	public:

		GWEN_CONTROL_FACTORY_CONSTRUCTOR( Label_Factory, ControlFactory::Base )
		{
			AddProperty( new Property::Text() );
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