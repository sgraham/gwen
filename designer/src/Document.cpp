#include "Document.h"
#include "DocumentCanvas.h"

GWEN_CONTROL_CONSTRUCTOR( Document )
{
	Dock( Pos::Fill );
	SetPadding( Padding( 1, 1, 1, 1 ) );

	m_pCanvas = new DocumentCanvas( this );
	m_pCanvas->SetSize( 400, 300 );
	m_pCanvas->SetPos( 5, 5 );
}

void Document::Initialize( Controls::TabButton* pTab )
{

}

void Document::Render( Gwen::Skin::Base* skin )
{
	skin->GetRender()->SetDrawColor( Color( 255, 255, 255, 255 ) );
	skin->GetRender()->DrawFilledRect( GetRenderBounds() );


}

void Document::RenderOver( Gwen::Skin::Base* skin )
{
	skin->GetRender()->SetDrawColor( Color( 90, 90, 90, 255 ) );
	skin->GetRender()->DrawLinedRect( GetRenderBounds() );
}