
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class DocumentCanvas;

class Properties : public Controls::Base 
{
	GWEN_CONTROL( Properties, Controls::Base );

		void WatchCanvas( DocumentCanvas* pCanvas );

	protected:

		DocumentCanvas*				m_pCanvas;
		Controls::PropertyTree*		m_Props;


};