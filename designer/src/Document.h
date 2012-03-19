
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

		virtual void DoSaveAs( ImportExport::BaseImportExport* exporter );
		virtual void DoSave( ImportExport::BaseImportExport* exporter );
		

	protected:

		void DoSaveFromDialog( Event::Info info );

		Controls::TabButton*	m_pTab;
		DocumentCanvas*			m_pCanvas;

		Gwen::String			m_strFilename;

		ImportExport::BaseImportExport*		m_Exporter;
		ImportExport::BaseImportExport*		m_Importer;
};