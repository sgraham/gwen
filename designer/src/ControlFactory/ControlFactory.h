
#pragma once

#include "Gwen/Gwen.h"
#include "ControlFactory.h"


namespace ControlFactory
{
	class Base
	{
		public:

			Base();

			virtual Gwen::String Name() = 0;
			virtual Gwen::String BaseName() = 0;

			virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent ) = 0;

		protected:

	};
	
	typedef std::list< ControlFactory::Base* > List;
	List& GetList();
}

#define GWEN_CONTROL_FACTORY_CONSTRUCTOR( ThisName, BaseName )\
	typedef BaseName BaseClass;\
	typedef ThisName ThisClass;\
	ThisName()

#define GWEN_CONTROL_FACTORY( ThisName ) \
	static ThisName ThisName##_Instance;