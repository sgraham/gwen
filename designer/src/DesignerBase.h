
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

/*

	The base panel

*/

class DesignerBase : public Controls::Base 
{
	GWEN_CONTROL( DesignerBase, Controls::Base );

	protected:

		void CreateMenu();
		void CreateDocumentHolder();

		void NewDocument();
		void CloseDocument();


		Controls::TabControl*		m_DocumentHolder;

};