#include "Base.h"

using namespace ImportExport;

BaseImportExport::BaseImportExport()
{

}

void BaseImportExport::Import( const Gwen::String& strFilename )
{
	
}

void BaseImportExport::Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename )
{
	Gwen::Debug::Msg( "Saving To.. %s\n", strFilename.c_str() );
}