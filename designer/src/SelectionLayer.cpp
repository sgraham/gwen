#include "SelectionLayer.h"
#include "Cage.h"

GWEN_CONTROL_CONSTRUCTOR( SelectionLayer )
{
	SetShouldDrawBackground( true );
}

void SelectionLayer::ClearSelection()
{
	RemoveAllChildren();
}

void SelectionLayer::AddSelection( Controls::Base* pControl )
{
	Cage* pCage = new Cage( this );
	pCage->Setup( pControl );
}

void SelectionLayer::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( !bDown ) return;

	Gwen::Point pPos = GetParent()->CanvasPosToLocal( Gwen::Point( x, y ) );
	
	SetMouseInputEnabled( false );
	Controls::Base* pCtrl = GetParent()->GetControlAt( pPos.x, pPos.y );
	SetMouseInputEnabled( true );

	if ( !pCtrl || pCtrl == GetParent() ) return;

	if ( !Gwen::Input::IsShiftDown() )
	{
		ClearSelection();
	}

	AddSelection( pCtrl );
}