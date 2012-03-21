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
	pCage->onMoved.Add( this, &ThisClass::OnControlDragged );
	pCage->onPress.Add( this, &ThisClass::OnCagePressed );
	pCage->onMoving.Add( this, &ThisClass::OnCageMoving );

	m_Selected.Add( pControl );

	Redraw();
}

void SelectionLayer::RemoveSelection( Controls::Base* pControl )
{
	m_Selected.Remove( pControl );

	for ( int i=0; i<pControl->NumChildren(); i++ )
	{
		Cage* pCage = gwen_cast<Cage>( pControl->GetChild( i ) );
		if  (!pCage ) continue;

		if ( pCage->Target() == pControl )
			pCage->DelayedDelete();
	}

	Redraw();
}

void SelectionLayer::OnMouseClickLeft( int x, int y, bool bDown )
{
	if ( !bDown ) return;

	Gwen::Point pPos = GetParent()->CanvasPosToLocal( Gwen::Point( x, y ) );
	
	SetMouseInputEnabled( false );
	Controls::Base* pCtrl = GetParent()->GetControlAt( pPos.x, pPos.y );
	SetMouseInputEnabled( true );

	bool bPanelsWereSelected = !m_Selected.list.empty();


	if ( !Gwen::Input::IsShiftDown() )
	{
		ClearSelection();
	}

	if ( pCtrl )
	{
			if ( pCtrl == GetParent() )
			{
				//
				// We only select the canvas if no other panels were selected before
				//
				if ( !bPanelsWereSelected )
					AddSelection( pCtrl );
			}
			else
			{
				AddSelection( pCtrl );
			}
	}

	Event::Information info;
	info.ControlList = m_Selected;

	onSelectionChanged.Call( this, info );
}

void SelectionLayer::OnControlDragged( Event::Info info )
{
	for ( ControlList::List::const_iterator it = m_Selected.list.begin(); it != m_Selected.list.end(); ++it )
	{
		Controls::Base* pControl = (*it);
		pControl->MoveBy( info.Point.x, info.Point.y );
	}

	Event::Information inf;
		inf.ControlList = m_Selected;
	onPropertiesChanged.Call( this, inf );
}

void SelectionLayer::OnCagePressed( Event::Info info )
{
	Cage* pCage = gwen_cast<Cage>( info.ControlCaller );
	if ( !pCage ) return;

	RemoveSelection( pCage->Target() );
	pCage->DelayedDelete();	

	// Let everything else know the selection changed
	{
		Event::Information info;
		info.ControlList = m_Selected;
		onSelectionChanged.Call( this, info );
	}
}

void SelectionLayer::OnCageMoving( Event::Info info )
{
	//
	// Convert the passed canvas pos to a pos local to the canvas
	//
	Gwen::Point pPos = GetParent()->CanvasPosToLocal( info.Point );
	
	// Hide all of the selected panels, and this selecion layer
	{
		for ( ControlList::List::const_iterator it = m_Selected.list.begin(); it != m_Selected.list.end(); ++it )
		{
			(*it)->SetHidden( true );
		}

		SetHidden( true );
	}

	// Find out which control is under our cursor
	Controls::Base* pCtrl = GetParent()->GetControlAt( pPos.x, pPos.y );

		
	bool bHierachyChanged = false;

	// Show all the hidden panels
	{
		SetHidden( false );
		for ( ControlList::List::const_iterator it = m_Selected.list.begin(); it != m_Selected.list.end(); ++it )
		{
			(*it)->SetHidden( false );

			// If the panel we're dragging doesn't have the parent thats underneath
			// then make it have it. Tweak positions so they're the same
			if ( pCtrl != (*it)->GetParent() )
			{
				Gwen::Point pPos = (*it)->LocalPosToCanvas();
				(*it)->SetParent( pCtrl );
				(*it)->SetPos( pCtrl->CanvasPosToLocal( pPos ) );
				bHierachyChanged = true;
			}
		}
	}

	//
	// If any parents changed then fire an event to update the tree
	//
	if ( bHierachyChanged )
	{
		onHierachyChanged.Call( this );
	}

}
