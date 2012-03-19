
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"
#include "ImportExport/Base.h"

using namespace Gwen;

class DocumentCanvas;

class Document : public Controls::Base 
{
	GWEN_CONTROL( Document, Controls::Base );

		virtual void Initialize( Controls::TabButton* pTab );

		virtual void DoSaveAs( ImportExport::Base* exporter );
		virtual void DoSave( ImportExport::Base* exporter );
		

	protected:

		void DoSaveFromDialog( Event::Info info );

		Controls::TabButton*	m_pTab;
		DocumentCanvas*			m_pCanvas;

		Gwen::String			m_strFilename;

		ImportExport::Base*		m_Exporter;
		ImportExport::Base*		m_Importer;
};