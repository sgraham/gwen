/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Controls/WindowCloseButton.h"
#include "Gwen/Controls/ImagePanel.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Modal.h"

using namespace Gwen;
using namespace Gwen::Controls;
using namespace Gwen::ControlsInternal;

namespace Gwen
{
	void Controls::WindowCloseButton::Render( Skin::Base* skin )
	{
		if ( !m_pWindow ) return;

		skin->DrawWindowCloseButton( this, IsDepressed() && IsHovered(), IsHovered() && ShouldDrawHover(), !m_pWindow->IsOnTop() );
	}

	void Controls::WindowCloseButton::SetWindow( Gwen::Controls::Base* p ) 
	{ 
		m_pWindow = p; 
	}


}