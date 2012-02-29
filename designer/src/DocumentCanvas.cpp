#include "DocumentCanvas.h"
#include "ControlFactory/ControlFactory.h"
#include "SelectionLayer.h"

GWEN_CONTROL_CONSTRUCTOR( DocumentCanvas )
{
	SetShouldDrawBackground( true );

	m_SelectionLayer = new SelectionLayer( this );
}


void DocumentCanvas::Render( Gwen::Skin::Base* skin )
{
	skin->DrawGenericPanel( this );
}

void DocumentCanvas::PostLayout( Skin::Base* skin )
{
	m_SelectionLayer->BringToFront();
	m_SelectionLayer->SetBounds( 0, 0, Width(), Height() );
}

bool DocumentCanvas::DragAndDrop_CanAcceptPackage( Gwen::DragAndDrop::Package* pPackage )
{
	return pPackage->name == "ControlButton";
}

bool DocumentCanvas::DragAndDrop_HandleDrop( Gwen::DragAndDrop::Package* pPackage, int x, int y )
{
	Gwen::Point pPos = CanvasPosToLocal( Gwen::Point( x, y ) );

	m_SelectionLayer->SetMouseInputEnabled( false );
	Controls::Base* pDroppedOn = GetControlAt( pPos.x, pPos.y );
	m_SelectionLayer->SetMouseInputEnabled( true );

	if ( !pDroppedOn ) pDroppedOn = this;

	pPos = pDroppedOn->CanvasPosToLocal( Gwen::Point( x, y ) );
	

	if ( pPackage->name == "ControlButton" )
	{
		ControlFactory::Base* pControlFactory = static_cast<ControlFactory::Base*>(pPackage->userdata);
		Controls::Base* pControl = pControlFactory->CreateInstance( pDroppedOn );
		pControl->SetPos( pPos );
		pControl->SetMouseInputEnabled( true );

		pControl->UserData.Set( "ControlFactory", pControlFactory );
		onChildAdded.Call( this, Event::Information( pControl ) );

		ControlFactory::Base* pCF = pControl->UserData.Get<ControlFactory::Base*>( "ControlFactory" );

		return true;
	}

	return false;
}
