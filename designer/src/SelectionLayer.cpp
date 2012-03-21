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
