
#include "ControlFactory.h"

namespace ControlFactory
{
	List& GetList()
	{
		static List list;
		return list;
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

		return NULL;
	}

	void Base::SetControlValue( Gwen::Controls::Base* ctrl, const Gwen::String& name, const Gwen::UnicodeString& str )
	{
		Property* pProp = GetProperty( name );
		if ( !pProp ) return;

		pProp->SetValue( ctrl, str );
	}
}