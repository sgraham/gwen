#include "Hierarchy.h"
#include "DocumentCanvas.h"
#include "ControlFactory/ControlFactory.h"

GWEN_CONTROL_CONSTRUCTOR( Hierarchy )
{
	SetSize( 200, 200 );

	m_Tree = new Controls::TreeControl( this );
	m_Tree->Dock( Pos::Fill );
}

void Hierarchy::WatchCanvas( DocumentCanvas* pCanvas )
{
	m_pCanvas = pCanvas;
	m_pCanvas->onChildAdded.Add( this, &ThisClass::OnCanvasChildAdded );

	CompleteRefresh();
}

void Hierarchy::CompleteRefresh()
{
	m_Tree->Clear();

	UpdateNode( m_Tree, m_pCanvas );

	m_Tree->ExpandAll();
}

void Hierarchy::UpdateNode( Controls::TreeNode* pNode, Controls::Base* pControl )
{	
	Controls::TreeNode* pChildNode = NULL;

	if ( m_pCanvas == pControl )
	{
		pChildNode = pNode->AddNode( "Canvas" );
		pChildNode->SetImage( "img/document_normal.png" );
	}
	else if ( !pControl->UserData.Exists( "ControlFactory" ) )
	{
		pChildNode = pNode;
	}
	else
	{
		Gwen::String strName = pControl->GetName();
		if ( strName == "" ) strName = "[" + Gwen::String( pControl->GetTypeName() ) + "]";

		pChildNode = pNode->AddNode( strName );
		pChildNode->SetImage( "img/controls/" + Gwen::String(pControl->GetTypeName()) + ".png" );
	}


	for ( int i=0; i<pControl->NumChildren(); i++ )
	{
		UpdateNode( pChildNode, pControl->GetChild( i ) );
	}
}

void Hierarchy::OnCanvasChildAdded( Event::Info info )
{
	
	info.Control;

	Debug::Msg( "Document Added\n" );

	CompleteRefresh();
}