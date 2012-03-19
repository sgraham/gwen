#include "Base.h"

using namespace Gwen;
using namespace ImportExport;


ImportExport::Base::List & ImportExport::Base::GetList()
{
	static ImportExport::Base::List list;
	return list;
}

ImportExport::Base* ImportExport::Base::Find( Gwen::String strName )
{
	ImportExport::Base::List::iterator it = GetList().begin();
	ImportExport::Base::List::iterator itEnd = GetList().end();

	while ( it != itEnd )
	{
		if ( (*it)->Name() == strName ) return (*it);

		++it;
	}

	return NULL;
}

Base::Base()
{
	GetList().push_back( this );
}


namespace Gwen{
namespace ImportExport {
namespace Tools{

	ControlList GetExportableChildren( Gwen::Controls::Base* pRoot )
	{
		ControlList list;

		for ( int i=0; i<pRoot->NumChildren(); i++ )
		{
			Gwen::Controls::Base* pBaseChild = pRoot->GetChild( i );
			if  ( !pBaseChild ) continue;
			if ( !pBaseChild->UserData.Exists( "ControlFactory" ) ) continue;

			list.Add( pBaseChild );
		}

		return list;
	}

}}}