#include "DocumentCanvas.h"
#include "DragBox.h"

GWEN_CONTROL_CONSTRUCTOR( DocumentCanvas )
{
	SetShouldDrawBackground( true );
}


void DocumentCanvas::Render( Gwen::Skin::Base* skin )
{
	skin->DrawGenericPanel( this );
}