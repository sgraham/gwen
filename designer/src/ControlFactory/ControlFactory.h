
#pragma once

#include "Gwen/Gwen.h"
#include "ControlFactory.h"


namespace ControlFactory
{
	class Property 
	{
		public:

			typedef std::list<Property*> List;

			virtual Gwen::String			Name() = 0;
			virtual Gwen::String			Description() = 0;

			virtual Gwen::UnicodeString		GetValue( Gwen::Controls::Base* ctrl ) = 0;
			virtual void					SetValue( Gwen::Controls::Base* ctrl, const Gwen::UnicodeString& str ) = 0;
	};

	class Base
	{
		public:

			Base();

			virtual Gwen::String Name() = 0;
			virtual Gwen::String BaseName() = 0;

			virtual Gwen::Controls::Base* CreateInstance( Gwen::Controls::Base* parent ) = 0;

			Base* GetBaseFactory();
			void AddProperty( Property* pProp );

			const Property::List& Properties(){ return m_Properties; }

		protected:

			Property::List	m_Properties;
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

#define GWEN_CONTROL_FACTORY_PROPERTY( _name_, _description_ )\
	public:\
	Gwen::String Name() { return #_name_; }\
	Gwen::String Description() { return _description_; }
