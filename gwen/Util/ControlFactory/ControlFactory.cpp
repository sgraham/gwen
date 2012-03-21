
#include "Gwen/Util/ControlFactory.h"

namespace Gwen 
{
namespace ControlFactory
{

	void InitializeControls()
	{
		//
		// This sucks, but I don't think it's possible to get the factory method working
		// inside a static lib without some shady unportable compiler capers
		//
		DECLARE_GWEN_CONTROL_FACTORY( Base_Factory );
		DECLARE_GWEN_CONTROL_FACTORY( Label_Factory );
		DECLARE_GWEN_CONTROL_FACTORY( Button_Factory );
		DECLARE_GWEN_CONTROL_FACTORY( TextBox_Factory );
		DECLARE_GWEN_CONTROL_FACTORY( CheckBox_Factory );
		DECLARE_GWEN_CONTROL_FACTORY( MenuStrip_Factory );
		
		

		DECLARE_GWEN_CONTROL_FACTORY( DesignerCanvas_Factory );

		
	}


	List& GetList()
	{
		static List list;
		static bool Initialized = false;

		if ( !Initialized )
		{
			Initialized = true;
			InitializeControls();			
		}

		return list;
	}

	ControlFactory::Base* Find( const Gwen::String& name )
	{
		for ( ControlFactory::List::iterator it = ControlFactory::GetList().begin(); it != ControlFactory::GetList().end(); ++it )
		{
			if ( (*it)->Name() == name )
			{
				return *it;
			}
		}

		return NULL;
	}

	Base::Base()
	{
		GetList().push_back( this );
	}

	void Base::AddProperty( Property* pProp )
	{
		m_Properties.push_back( pProp );
	}

	Base* Base::GetBaseFactory()
	{
		for ( ControlFactory::List::iterator it = ControlFactory::GetList().begin(); it != ControlFactory::GetList().end(); ++it )
		{
			if ( (*it)->Name() == BaseName() )
			{
				return *it;
			}
		}

		return NULL;
	}

	Property* Base::GetProperty( const Gwen::String& name )
	{
		ControlFactory::Property::List::const_iterator it = Properties().begin();
		ControlFactory::Property::List::const_iterator itEnd = Properties().end();
		for ( it; it != itEnd; ++it )
		{
			if ( (*it)->Name() != name ) continue;

			return *it;
		}

		Base* pBase = GetBaseFactory();
		if ( !pBase ) return NULL;

		return pBase->GetProperty( name );
	}

	void Base::SetControlValue( Gwen::Controls::Base* ctrl, const Gwen::String& name, const Gwen::UnicodeString& str )
	{
		Property* pProp = GetProperty( name );
		
		if ( !pProp )
		{
			Base* pBase = GetBaseFactory();
			if ( !pBase ) return;

			return pBase->SetControlValue( ctrl, name, str );
		}

		pProp->SetValue( ctrl, str );
	}
}
}