
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

namespace ImportExport 
{
	class  BaseImportExport
	{
		public:

			BaseImportExport();

			virtual bool CanImport(){ return true; }
			virtual void Import( const Gwen::String& strFilename );

			virtual bool CanExport(){ return true; }
			virtual void Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename );

		protected:

	};
}
