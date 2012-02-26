
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


}