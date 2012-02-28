#include "Document.h"
#include "DocumentCanvas.h"
#include "Hierarchy.h"

class DocumentInner : public Gwen::Controls::ScrollControl
{
	GWEN_CONTROL_INLINE( DocumentInner, Gwen::Controls::ScrollControl )
	{

	}

	void Render( Gwen::Skin::Base* skin )
	{
		skin->GetRender()->SetDrawColor( Color( 255, 255, 255, 255 ) );
		skin->GetRender()->DrawFilledRect( GetRenderBounds() );
	}

	void RenderOver( Gwen::Skin::Base* skin )
	{
		skin->GetRender()->SetDrawColor( Color( 90, 90, 90, 255 ) );
		skin->GetRender()->DrawLinedRect( GetRenderBounds() );
	}
};

GWEN_CONTROL_CONSTRUCTOR( Document )
{
	Dock( Pos::Fill );
	SetPadding( Padding( 1, 1, 1, 1 ) );

	DocumentInner* pInner = new DocumentInner( this );
	pInner->Dock( Pos::Fill );

	m_pCanvas = new DocumentCanvas( pInner );
	m_pCanvas->SetSize( 400, 300 );
	m_pCanvas->SetPos( 5, 5 );

	Hierarchy* pHierarchy = new Hierarchy( this );
	pHierarchy->Dock( Pos::Right );
	pHierarchy->SetMargin( Margin( 4, 0, 0, 0 ) );
	pHierarchy->WatchCanvas( m_pCanvas );
	
}

void Document::Initialize( Controls::TabButton* pTab )
{

}

