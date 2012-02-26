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

	if ( pPackage->name == "ControlButton" )
	{
		ControlFactory::Base* pControlFactory = static_cast<ControlFactory::Base*>(pPackage->userdata);
		Controls::Base* pControl = pControlFactory->CreateInstance( this );
		pControl->SetPos( pPos );

		return true;
	}

	return false;
}