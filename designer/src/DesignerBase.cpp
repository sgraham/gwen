#include "DesignerBase.h"

GWEN_CONTROL_CONSTRUCTOR( DesignerBase )
{
	Dock( Pos::Fill );

	CreateMenu();
	CreateDocumentHolder();

	new Controls::StatusBar( this, "StatusBar" );

	NewDocument();
}


void DesignerBase::CreateMenu()
{
	Controls::MenuStrip* pStrip = new Controls::MenuStrip( this );
	pStrip->Dock( Pos::Top );

	// File
	{
		Gwen::Controls::MenuItem* pRoot = pStrip->AddItem( "File" );

		pRoot->GetMenu()->AddItem( "New", "img/menu/new.png", "Ctrl + N" )->SetAction( this, &ThisClass::NewDocument );
		pRoot->GetMenu()->AddItem( "Close", "img/menu/close.png" )->SetAction( this, &ThisClass::CloseDocument );
	}
}

void DesignerBase::CreateDocumentHolder()
{
	m_DocumentHolder = new Controls::TabControl( this );
	m_DocumentHolder->Dock( Pos::Fill );
	m_DocumentHolder->SetMargin( Margin( -1, 2, -1, -1 ) );
}

void DesignerBase::NewDocument()
{
	Controls::TabButton* pButton = m_DocumentHolder->AddPage( L"Untitled Design" );
	pButton->SetImage( "img/document_normal.png" );
	Base* pPage = pButton->GetPage();

	pButton->OnPress();
}

void DesignerBase::CloseDocument()
{
	Controls::TabButton* pButton = m_DocumentHolder->GetCurrentButton();
	if ( !pButton ) return;

	m_DocumentHolder->RemovePage( pButton );
	pButton->DelayedDelete();
}