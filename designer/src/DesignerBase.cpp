#include "DesignerBase.h"
#include "Document.h"
#include "ControlToolbox.h"
#include "ImportExport/Base.h"

GWEN_CONTROL_CONSTRUCTOR( DesignerBase )
{
	Dock( Pos::Fill );

	CreateMenu();
	CreateToolBar();
	CreateControlToolbox();
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

		pRoot->GetMenu()->AddItem( "Open", "img/menu/open.png", "Ctrl + O" )->SetAction( this, &ThisClass::OpenDocument );
		pRoot->GetMenu()->AddItem( "Save", "img/menu/save.png", "Ctrl + S" )->SetAction( this, &ThisClass::SaveDocument );

		pRoot->GetMenu()->AddItem( "Close", "img/menu/close.png" )->SetAction( this, &ThisClass::CloseDocument );
	}
}

void DesignerBase::CreateToolBar()
{
	Controls::ToolBarStrip* pStrip = new Controls::ToolBarStrip( this );
	pStrip->Dock( Pos::Top );

	pStrip->Add( "New Document", "img/menu/new.png" )->onPress.Add( this, &ThisClass::NewDocument );

	//pStrip->Add( "Open", "img/menu/open.png" )->onPress.Add( this, &ThisClass::OpenDocument );
	//pStrip->Add( "Save", "img/menu/save.png" )->onPress.Add( this, &ThisClass::SaveDocument );
}

void DesignerBase::CreateControlToolbox()
{
	ControlToolbox* pControlBox = new ControlToolbox( this );
	pControlBox->Dock( Pos::Left );
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

	Document* doc = new Document( pButton->GetPage(), "Document" );
	doc->Initialize( pButton );

	pButton->OnPress();
}

void DesignerBase::CloseDocument()
{
	Controls::TabButton* pButton = m_DocumentHolder->GetCurrentButton();
	if ( !pButton ) return;

	m_DocumentHolder->RemovePage( pButton );
	pButton->DelayedDelete();
}

void DesignerBase::OpenDocument()
{
	//Document* doc = CurrentDocument();
	//if ( !doc ) return;
}

void DesignerBase::SaveDocument()
{
	Document* doc = CurrentDocument();
	if ( !doc ) return;

	doc->DoSave( &m_DefaultImportExport );
}

Document* DesignerBase::CurrentDocument()
{
	Controls::TabButton* pButton = m_DocumentHolder->GetCurrentButton();
	if ( !pButton ) return NULL;

	Document* doc = gwen_cast<Document>(pButton->GetPage()->FindChildByName( "Document" ));
	if ( !doc ) return NULL;

	return doc;
}