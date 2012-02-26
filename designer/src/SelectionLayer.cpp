#include "SelectionLayer.h"

GWEN_CONTROL_CONSTRUCTOR( SelectionLayer )
{
	SetShouldDrawBackground( true );
}

void SelectionLayer::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( !bDown ) return;

	Gwen::Point pPos = GetParent()->CanvasPosToLocal( Gwen::Point( x, y ) );
	
	SetMouseInputEnabled( false );
	Controls::Base* pCtrl = GetParent()->GetControlAt( pPos.x, pPos.y );
	SetMouseInputEnabled( true );


	if ( !pCtrl || pCtrl == GetParent() ) return;

	pCtrl->DelayedDelete();
}