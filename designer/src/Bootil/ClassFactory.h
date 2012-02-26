#pragma once
#include "Bootil/Bootil.h"

/*

Usage:

In your Base Classes header:

	ClassFactory_Declare( MyFactory, MyBaseClass );

	In your Base Classes class definition:

		ClassFactor_Base( MyBaseClass );

In your Base Classes body:

	ClassFactory_Define( MyFactory, MyBaseClass );



Then register derived classes using

	ClassFactory_RegisterEx( MyFactory, MyBaseClass, MyDerivedClass, 0, "Name Of Class", "Description Of Class" )

or

	ClassFactory_Register( MyFactory, MyBaseClass, MyDerivedClass, "Name Of Class" )



To Create a class

	ClassFactory()->Create( "Name Of Class" )

*/

namespace Bootil 
{
	namespace Utility
	{

		template <class TBase> class CClassFactory;

		template <class TBase>
		class ClassFactoryWorker
		{
			public:

				virtual int GetCategory() = 0;
				virtual std::string GetDescription() = 0;
				virtual std::string GetName() = 0;
				virtual TBase Create() = 0;
		};

		template <class TBase>
		class CClassFactory
		{
			public:

				typedef std::map< std::string, ClassFactoryWorker< TBase >* > List;

				void Register( ClassFactoryWorker< TBase >* worker, const BString& strName, int iCategory )
				{
					m_Lists[iCategory][strName] = worker;
				}

				void UnRegister( const BString& strName )
				{
					UnRegister( 0, strName );
				}

				void UnRegister( int iType, const BString& strName )
				{
					m_List.erase( strName );
				}

				int GetCount( int iType = 0 )
				{
					return m_Lists[iType].size();
				}

				BString	GetDescription( int iType, int iNumber )
				{
					List::iterator i = m_Lists[iType].begin();
					while ( i != m_Lists[iType].end() )
					{
						if (iNumber == 0)
							return i->second->GetDescription();

						--iNumber;
						++i;
					}

					return "";
				}

				TBase Create( const BString& strName ) { return Create( 0, strName ); }
				TBase Create( int iType, const BString& strName )
				{
					List::iterator i = m_Lists[iType].find( strName );
					if ( i == m_Lists[iType].end() ) return NULL;

					return i->second->Create();
				}

				TBase Create( int iNumber ) { return Create( 0, iNumber ); }
				TBase Create( int iType, int iNumber )
				{
					List::iterator i = m_Lists[iType].begin();
					while ( i != m_Lists[iType].end() )
					{
						if (iNumber == 0)
							return i->second->Create();
						--iNumber;
						++i;
					}

					return NULL;
				}


				std::map< unsigned int, List> m_Lists;
		};
	}
}

#define ClassFactory_Declare( _name_, _baseclass_ )\
	Bootil::Utility::CClassFactory<_baseclass_*>* Get##_name_();


#define ClassFactory_Define( _name_, _baseclass_ )\
	Bootil::Utility::CClassFactory<_baseclass_*>* Get##_name_()\
{\
	static Bootil::Utility::CClassFactory<_baseclass_*> obj;\
	return &obj;\
}

#define ClassFactor_Base( _baseclass_ )\
	Bootil::Utility::ClassFactoryWorker<_baseclass_*>* m_pMyClassFactory;\
	void SetClassFactory( Bootil::Utility::ClassFactoryWorker<_baseclass_*>* cf ){ m_pMyClassFactory = cf; }\
	Bootil::Utility::ClassFactoryWorker<_baseclass_*>* GetClassFactory(){ return m_pMyClassFactory; }\



#define ClassFactory( _name_ ) (Get##_name_())


#define ClassFactory_RegisterEx( _factoryname_, _baseclass_, _thisclass_, _iCategoryID_, _name_, _description_ )\
class CF_##_baseclass_##_thisclass_ : public Bootil::Utility::ClassFactoryWorker<_baseclass_*>\
{\
public:\
	CF_##_baseclass_##_thisclass_( int iCocks ) { Get##_factoryname_()->Register( this, _name_, _iCategoryID_ ); }\
	virtual int GetCategory(){ return _iCategoryID_; }\
	virtual BString GetDescription(){ return _description_; }\
	virtual BString GetName(){ return _name_; }\
	virtual _baseclass_* Create(){ _baseclass_* ptr = new _thisclass_(); ptr->SetClassFactory( this ); return ptr; }\
};\
	static CF_##_baseclass_##_thisclass_ g_CF_##_baseclass_##_thisclass_( 23 );

#define ClassFactory_Register( _factoryname_, _baseclass_, _thisclass_, _name_ )\
	ClassFactory_RegisterEx( _factoryname_, _baseclass_, _thisclass_, 0, _name_, "" )