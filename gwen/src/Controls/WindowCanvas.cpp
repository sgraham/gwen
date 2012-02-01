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
#include "Gwen/Controls/WindowCloseButton.h"

#ifndef GWEN_NO_ANIMATION
#include "Gwen/Anim.h"
#endif

using namespace Gwen::Controls;

WindowCanvas::WindowCanvas( int x, int y, int w, int h, Gwen::Skin::Base* pSkin, const Gwen::String& strWindowTitle ) : BaseClass( NULL )
{
	m_bQuit = false;

	// Centering the window on the desktop
	{
		int dw, dh;
		Gwen::Platform::GetDesktopSize( dw, dh );

		if ( x < 0 ) x = (dw - w) * 0.5;
		if ( y < 0 ) y = (dh - h) * 0.5;
	}

	m_pOSWindow = Gwen::Platform::CreatePlatformWindow( x, y, w, h, strWindowTitle );
	m_WindowPos  = Gwen::Point( x, y );

	pSkin->GetRender()->InitializeContext( this );
	pSkin->GetRender()->Init();
	m_pSkinChange = pSkin;
	
	SetSize( w, h );

	m_TitleBar = new Gwen::ControlsInternal::Dragger( this );
		m_TitleBar->SetHeight( 24 );
		m_TitleBar->SetPadding( Padding( 0, 0, 0, 0 ) );
		m_TitleBar->SetMargin( Margin( 0, 0, 0, 4 ) );
		m_TitleBar->Dock( Pos::Top );
		m_TitleBar->SetDoMove( false );
		m_TitleBar->onDragged.Add( this, &WindowCanvas::Dragger_Moved );
		m_TitleBar->OnDragStart.Add( this, &WindowCanvas::Dragger_Start );

	m_Title = new Gwen::Controls::Label( m_TitleBar );
		m_Title->SetAlignment( Pos::Left | Pos::CenterV );
		m_Title->SetText( strWindowTitle );
		m_Title->Dock( Pos::Fill );
		m_Title->SetPadding( Padding( 8, 0, 0, 0 ) );
		m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive );

	Gwen::Controls::WindowCloseButton* pButton = new Gwen::Controls::WindowCloseButton( m_TitleBar );
		pButton->SetText( "" );
		pButton->SetSize( 24, 24 );
		pButton->Dock( Pos::Right );
		pButton->SetMargin( Margin( 0, 0, 6, 0 ) );
		pButton->onPress.Add( this, &WindowCanvas::CloseButtonPressed );
		pButton->SetTabable( false );
		pButton->SetName( "closeButton" );
		pButton->SetWindow( this );

	m_Sizer = new Gwen::ControlsInternal::Dragger( this );
		m_Sizer->SetSize( 16, 16 );
		m_Sizer->SetDoMove( false );
		m_Sizer->onDragged.Add( this, &WindowCanvas::Sizer_Moved );
		m_Sizer->OnDragStart.Add( this, &WindowCanvas::Dragger_Start );
		m_Sizer->SetCursor( Gwen::CursorType::SizeNWSE );
}

WindowCanvas::~WindowCanvas()
{
	DestroyWindow();
}

void* WindowCanvas::GetWindow()
{
	return m_pOSWindow;
}

void WindowCanvas::Layout( Skin::Base* skin )
{
	m_Sizer->BringToFront();
	Align::AlignRight(  m_Sizer );
	Align::AlignBottom( m_Sizer );

	BaseClass::Layout( skin );
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

		render->SetClipRegion( GetRenderBounds() );
		render->SetRenderOffset( Gwen::Point( X() * -1, Y() * -1 ) );
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

void WindowCanvas::Render( Skin::Base* skin )
{
	bool bHasFocus = IsOnTop();

	if ( bHasFocus )
		m_Title->SetTextColor( GetSkin()->Colors.Window.TitleActive );
	else
		m_Title->SetTextColor( GetSkin()->Colors.Window.TitleInactive );

	skin->DrawWindow( this, m_TitleBar->Bottom(), bHasFocus );
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


void WindowCanvas::Dragger_Start()
{
	Gwen::Platform::GetCursorPos( m_HoldPos );	

	m_HoldPos.x -= m_WindowPos.x;
	m_HoldPos.y -= m_WindowPos.y;
}

void WindowCanvas::Dragger_Moved()
{
	Gwen::Point p;
	Gwen::Platform::GetCursorPos( p );	

	SetPos( p.x - m_HoldPos.x, p.y - m_HoldPos.y );
}

void WindowCanvas::SetPos( int x, int y )
{
	int w, h;
	Gwen::Platform::GetDesktopSize( w, h );
	y = Gwen::Clamp( y, 0, h );

	m_WindowPos.x = x;
	m_WindowPos.y = y;

	Gwen::Platform::SetBoundsPlatformWindow( m_pOSWindow, x, y, Width(), Height() );
}

void WindowCanvas::CloseButtonPressed()
{
	InputQuit();
}

bool WindowCanvas::IsOnTop()
{
	return Gwen::Platform::HasFocusPlatformWindow( m_pOSWindow );
}


void WindowCanvas::Sizer_Moved()
{
	Gwen::Point p;
	Gwen::Platform::GetCursorPos( p );	

	int w = (p.x) - m_WindowPos.x;
	int h = (p.y) - m_WindowPos.y;

	w = Clamp( w, 100, 9999 );
	h = Clamp( h, 100, 9999 );

	Gwen::Platform::SetBoundsPlatformWindow( m_pOSWindow, m_WindowPos.x, m_WindowPos.y, w, h );
	GetSkin()->GetRender()->ResizedContext( this, w, h );
	this->SetSize( w, h );

	BaseClass::DoThink();
	RenderCanvas();
}