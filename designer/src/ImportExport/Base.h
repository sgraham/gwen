
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"
#include "ControlFactory/ControlFactory.h"

using namespace Gwen;

namespace Gwen
{
	namespace ImportExport 
	{
		class Base
		{
			public:

				Base();

				virtual Gwen::String Name() = 0;

				virtual bool CanImport() = 0;
				virtual void Import( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename ) = 0;

				virtual bool CanExport() = 0;
				virtual void Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename ) = 0;

			public:
				
				typedef std::list<ImportExport::Base*> List;
				static List& GetList();
				static Base* Find( Gwen::String strName );

			protected:

		};

		namespace Tools
		{
			ControlList GetExportableChildren( Gwen::Controls::Base* pRoot );
		}
	}
}
