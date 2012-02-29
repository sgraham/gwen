
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
}