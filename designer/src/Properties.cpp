#include "Properties.h"
#include "DocumentCanvas.h"
#include "ControlFactory/ControlFactory.h"

GWEN_CONTROL_CONSTRUCTOR( Properties )
{
	SetSize( 200, 200 );

	m_Props = new Controls::PropertyTree( this );
	m_Props->Dock( Pos::Fill );


}

void Properties::WatchCanvas( DocumentCanvas* pCanvas )
{
	m_pCanvas = pCanvas;
	//m_pCanvas->onChildAdded.Add( this, &ThisClass::OnCanvasChildAdded );

}
