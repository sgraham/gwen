/*
	GWEN
	Copyright (c) 2012 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_WINDOWCLOSEBUTTON_H
#define GWEN_CONTROLS_WINDOWCLOSEBUTTON_H

#include "Gwen/Gwen.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/Dragger.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/ResizableControl.h"
#include "Gwen/Controls/Modal.h"
#include "Gwen/Skin.h"


namespace Gwen 
{
	namespace Controls
	{
		class GWEN_EXPORT WindowCloseButton : public Button
		{
			GWEN_CONTROL_INLINE( WindowCloseButton, Button )
			{
				m_pWindow = NULL;
			}

			virtual void Render( Skin::Base* skin );
			virtual void SetWindow( Controls::Base* p );

			protected:

			Controls::Base* m_pWindow;
		};
	}
}

#endif
