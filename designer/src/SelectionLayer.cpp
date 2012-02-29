#include "SelectionLayer.h"
#include "Cage.h"

GWEN_CONTROL_CONSTRUCTOR( SelectionLayer )
{
	SetShouldDrawBackground( true );
}

void SelectionLayer::ClearSelection()
{
	m_Selected.Clear();
	RemoveAllChildren();
	Redraw();
}

void SelectionLayer::AddSelection( Controls::Base* pControl )
{
	Cage* pCage = new Cage( this );
	pCage->Setup( pControl );

	m_Selected.Add( pControl );

	Redraw();
}

void SelectionLayer::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( !bDown ) return;

	Gwen::Point pPos = GetParent()->CanvasPosToLocal( Gwen::Point( x, y ) );
	
	SetMouseInputEnabled( false );
	Controls::Base* pCtrl = GetParent()->GetControlAt( pPos.x, pPos.y );
	SetMouseInputEnabled( true );

	if ( !Gwen::Input::IsShiftDown() )
	{
		ClearSelection();
	}

	if ( pCtrl && pCtrl != GetParent() )
	{
		AddSelection( pCtrl );
	}

	Event::Information info;
	info.ControlList = m_Selected;

	onSelectionChanged.Call( this, info );
}