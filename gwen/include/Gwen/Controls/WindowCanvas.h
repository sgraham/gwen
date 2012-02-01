/*
	GWEN
	Copyright (c) 2012 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_WINDOWCANVAS_H
#define GWEN_CONTROLS_WINDOWCANVAS_H

#include "Gwen/Controls/Base.h"
#include "Gwen/InputHandler.h"
#include "Gwen/WindowProvider.h"

namespace Gwen 
{
	namespace Controls
	{
		class GWEN_EXPORT WindowCanvas : public Canvas, public Gwen::WindowProvider
		{
			public:

				typedef Controls::Canvas BaseClass;

				WindowCanvas( int x, int y, int w, int h, Gwen::Skin::Base* pRenderer, const Gwen::String& strWindowTitle = "" );
				~WindowCanvas();

				virtual void DoThink();
				
				virtual bool WantsQuit(){ return m_bQuit; }

				// Gwen::WindowProvider
				virtual void* GetWindow();
				virtual bool InputQuit();

				Skin::Base* GetSkin( void );

			protected:

				virtual void DoMessages();
				virtual void RenderCanvas();
				virtual void DestroyWindow();

				void*		m_pOSWindow;
				bool		m_bQuit;

				Gwen::Skin::Base*	m_pSkinChange;

		};
	}
}
#endif
