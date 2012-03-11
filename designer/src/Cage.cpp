
#include "Cage.h"

GWEN_CONTROL_CONSTRUCTOR( Cage )
{
	m_Control = NULL;
	m_iBorder = 5;
}

void Cage::Render( Gwen::Skin::Base* skin )
{
	Rect bounds = GetRenderBounds();

	bounds.x += m_iBorder;
	bounds.y += m_iBorder;
	bounds.w -= m_iBorder * 2;
	bounds.h -= m_iBorder * 2;

	skin->GetRender()->SetDrawColor( Color( 255, 255, 255, 100 ) );
	skin->GetRender()->DrawFilledRect( bounds );

	skin->GetRender()->SetDrawColor( Color( 255, 0, 0, 255 ) );
	skin->GetRender()->DrawLinedRect( bounds );
	bounds.x -= 1; bounds.y -= 1; bounds.w += 2; bounds.h += 2; 
	skin->GetRender()->DrawLinedRect( bounds );
}

void Cage::PostLayout( Skin::Base* skin )
{
	if ( !m_Control ) return;

	Point canvaspos = m_Control->LocalPosToCanvas();
	Point parentpos = GetParent()->CanvasPosToLocal( canvaspos );

	parentpos.x -= m_iBorder;
	parentpos.y -= m_iBorder;

	SetPos( parentpos );

	Point size = m_Control->GetSize();
	size.x += m_iBorder * 2;
	size.y += m_iBorder * 2;

	SetSize( size );
}

void Cage::Setup( Controls::Base* pControl )
{
	m_Control = pControl;
}

void Cage::SetDepressed( bool b )
{
	BaseClass::SetDepressed( b );

	m_DragPoint = m_Control->GetPos();
}

void Cage::OnMouseMoved( int x, int y, int deltaX, int deltaY )
{
	if ( !IsDepressed() ) return;

	m_DragPoint += Point( deltaX, deltaY );

	Point pos = m_DragPoint;

	pos.x = ((int)((float)pos.x / 10.0f)) * 10;
	pos.y = ((int)((float)pos.y / 10.0f)) * 10;

	pos -= m_Control->GetPos();

	Event::Information info;
	info.Point = pos;
	onMoved.Call( this, info );
}