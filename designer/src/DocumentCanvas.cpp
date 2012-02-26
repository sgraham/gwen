#include "DocumentCanvas.h"
#include "ControlFactory/ControlFactory.h"

GWEN_CONTROL_CONSTRUCTOR( DocumentCanvas )
{
	SetShouldDrawBackground( true );
}


void DocumentCanvas::Render( Gwen::Skin::Base* skin )
{
	skin->DrawGenericPanel( this );
}

bool DocumentCanvas::DragAndDrop_CanAcceptPackage( Gwen::DragAndDrop::Package* pPackage )
{
	return pPackage->name == "ControlButton";
}

bool DocumentCanvas::DragAndDrop_HandleDrop( Gwen::DragAndDrop::Package* pPackage, int x, int y )
{
	Gwen::Point pPos = CanvasPosToLocal( Gwen::Point( x, y ) );

	Controls::Base* pDroppedOn = GetControlAt( pPos.x, pPos.y );
	if ( !pDroppedOn ) pDroppedOn = this;

	pPos = pDroppedOn->CanvasPosToLocal( Gwen::Point( x, y ) );
	

	if ( pPackage->name == "ControlButton" )
	{
		ControlFactory::Base* pControlFactory = static_cast<ControlFactory::Base*>(pPackage->userdata);
		Controls::Base* pControl = pControlFactory->CreateInstance( pDroppedOn );
		pControl->SetPos( pPos );

		return true;
	}

	return false;
}