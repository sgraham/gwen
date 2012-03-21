#include "DocumentCanvas.h"
#include "Gwen/Util/ControlFactory.h"
#include "SelectionLayer.h"

GWEN_CONTROL_CONSTRUCTOR( DocumentCanvas )
{
	SetShouldDrawBackground( true );

	m_SelectionLayer = new SelectionLayer( this );
	m_SelectionLayer->onSelectionChanged.Add( this, &ThisClass::OnSelectionChanged );
	m_SelectionLayer->onPropertiesChanged.Add( this, &ThisClass::OnPropertiesChanged );

	ControlFactory::Base* pControlFactory = Gwen::ControlFactory::Find( "DesignerCanvas" );
	UserData.Set( "ControlFactory", pControlFactory );
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
	return pPackage->name == "ControlSpawn";
}

bool DocumentCanvas::DragAndDrop_HandleDrop( Gwen::DragAndDrop::Package* pPackage, int x, int y )
{
	Gwen::Point pPos = CanvasPosToLocal( Gwen::Point( x, y ) );

	m_SelectionLayer->SetHidden( true );
	Controls::Base* pDroppedOn = GetControlAt( pPos.x, pPos.y );
	m_SelectionLayer->SetHidden( false );

	if ( !pDroppedOn ) pDroppedOn = this;

	pPos = pDroppedOn->CanvasPosToLocal( Gwen::Point( x, y ) );
	

	if ( pPackage->name == "ControlSpawn" )
	{
		ControlFactory::Base* pControlFactory = static_cast<ControlFactory::Base*>(pPackage->userdata);
		Controls::Base* pControl = pControlFactory->CreateInstance( pDroppedOn );
		pControl->SetPos( pPos );
		pControl->SetMouseInputEnabled( true );

		pControl->UserData.Set( "ControlFactory", pControlFactory );
		onChildAdded.Call( this, Event::Information( pControl ) );

		return true;
	}

	return false;
}

void DocumentCanvas::SelectControls( ControlList& CtrlList )
{
	m_SelectionLayer->ClearSelection();

	for ( ControlList::List::const_iterator it = CtrlList.list.begin(); it != CtrlList.list.end(); ++it )
	{
		m_SelectionLayer->AddSelection( (*it) );
	}
}

void DocumentCanvas::OnSelectionChanged( Event::Info info )
{
	onSelectionChanged.Call( this, info );
}

void DocumentCanvas::OnPropertiesChanged( Event::Info info )
{
	onPropertiesChanged.Call( this, info );
}