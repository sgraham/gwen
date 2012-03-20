
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"
#include "ImportExport/Base.h"

using namespace Gwen;

class Document;

/*

	The base panel

*/

class DesignerBase : public Controls::Base 
{
	GWEN_CONTROL( DesignerBase, Controls::Base );

	protected:

		void CreateMenu();
		void CreateToolBar();
		void CreateDocumentHolder();
		void CreateControlToolbox();

		void NewDocument();
		void CloseDocument();
		void OpenDocument();
		void DoOpenDocument( Event::Info info );
		void SaveDocument();
		void SaveAsDocument();
		

		Document* CurrentDocument();


		Controls::TabControl*			m_DocumentHolder;
};