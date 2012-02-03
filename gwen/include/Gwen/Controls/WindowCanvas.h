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
#include "Gwen/Controls/Dragger.h"
#include "Gwen/Controls/Label.h"

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

				virtual void Render( Skin::Base* skin );

				virtual void SetPos( int x, int y );
				virtual bool IsOnTop();

				virtual void Layout( Skin::Base* skin );


			protected:

				virtual void RenderCanvas();
				virtual void DestroyWindow();

				virtual void CloseButtonPressed();

				virtual void Dragger_Start();
				virtual void Dragger_Moved();
				virtual void Sizer_Moved();

				void*		m_pOSWindow;
				bool		m_bQuit;

				Gwen::Skin::Base*			m_pSkinChange;

				ControlsInternal::Dragger*	m_TitleBar;
				ControlsInternal::Dragger*	m_Sizer;
				Gwen::Controls::Label*		m_Title;


				Gwen::Point		m_WindowPos;
				Gwen::Point		m_HoldPos;

		};
	}
}
#endif
