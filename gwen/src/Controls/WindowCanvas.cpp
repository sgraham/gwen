/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/


#include "Gwen/Gwen.h"
#include "Gwen/Controls/WindowCanvas.h"
#include "Gwen/Skin.h"
#include "Gwen/Controls/Menu.h"
#include "Gwen/DragAndDrop.h"
#include "Gwen/ToolTip.h"

#ifndef GWEN_NO_ANIMATION
#include "Gwen/Anim.h"
#endif

using namespace Gwen::Controls;


WindowCanvas::WindowCanvas( int x, int y, int w, int h, Gwen::Skin::Base* pSkin, const Gwen::String& strWindowTitle ) : BaseClass( NULL )
{
	m_bQuit = false;

	m_pOSWindow = Gwen::Platform::CreatePlatformWindow( x, y, w, h, strWindowTitle );

	pSkin->GetRender()->InitializeContext( this );
	pSkin->GetRender()->Init();
	m_pSkinChange = pSkin;
	
	SetSize( w, h );
}

WindowCanvas::~WindowCanvas()
{
	DestroyWindow();
}

void* WindowCanvas::GetWindow()
{
	return m_pOSWindow;
}

void WindowCanvas::DoThink()
{
	RenderCanvas();
	Platform::MessagePump( m_pOSWindow, this );
	BaseClass::DoThink();
}

void WindowCanvas::RenderCanvas()
{
	Gwen::Renderer::Base* render = m_Skin->GetRender();

	render->BeginContext( this );
	render->Begin();

		RecurseLayout( m_Skin );

		render->SetClipRegion( GetBounds() );
		render->SetRenderOffset( Gwen::Point( 0, 0 ) );
		render->SetScale( Scale() );

		if ( m_bDrawBackground )
		{
			render->SetDrawColor( m_BackgroundColor );
			render->DrawFilledRect( GetRenderBounds() );
		}

		DoRender( m_Skin );

		DragAndDrop::RenderOverlay( this, m_Skin );

		ToolTip::RenderToolTip( m_Skin );

		render->EndClip();

	render->End();
	render->EndContext( this );

	render->PresentContext( this );
}

void WindowCanvas::DoMessages()
{

}

void WindowCanvas::DestroyWindow()
{
	if ( m_pOSWindow )
	{
		GetSkin()->GetRender()->ShutdownContext( this );
		Gwen::Platform::DestroyPlatformWindow( m_pOSWindow );
		m_pOSWindow = NULL;
	}
}

bool WindowCanvas::InputQuit()
{
	m_bQuit = true;
	return true;
}

Skin::Base* WindowCanvas::GetSkin( void )
{
	if ( m_pSkinChange )
	{
		SetSkin( m_pSkinChange );
		m_pSkinChange = NULL;
	}

	return BaseClass::GetSkin();
}