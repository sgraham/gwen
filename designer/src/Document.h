
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class DocumentCanvas;

class Document : public Controls::Base 
{
	GWEN_CONTROL( Document, Controls::Base );

		virtual void Initialize( Controls::TabButton* pTab );

		virtual void Render( Gwen::Skin::Base* skin );
		virtual void RenderOver( Gwen::Skin::Base* skin );

	protected:

		Controls::TabButton*	m_pTab;
		DocumentCanvas*			m_pCanvas;
};