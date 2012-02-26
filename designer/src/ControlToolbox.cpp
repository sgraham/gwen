
#include "ControlToolbox.h"
#include "ControlFactory/ControlFactory.h"


GWEN_CONTROL_CONSTRUCTOR( ControlToolbox )
{
	SetWidth( 150 );
	SetMargin( Margin( 5, 5, 5, 5 ) );
	SetText( "Controls" );

	for ( ControlFactory::List::iterator it = ControlFactory::GetList().begin(); it != ControlFactory::GetList().end(); ++it )
	{
		ControlFactory::Base* pControlFactory = *it;

		Controls::Button* pButton = new Controls::Button( this );
		pButton->SetSize( 32, 32 );
		pButton->Dock( Pos::Top );
		pButton->DragAndDrop_SetPackage( true, "ControlButton", pControlFactory, false );
		pButton->SetText( pControlFactory->Name() );
	}
}
