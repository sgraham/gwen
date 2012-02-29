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
	m_pCanvas->onSelectionChanged.Add( this, &ThisClass::OnCanvasSelectionChanged );
	//m_pCanvas->onChildAdded.Add( this, &ThisClass::OnCanvasChildAdded );

}


void Properties::OnCanvasSelectionChanged( Event::Info info )
{
	m_Props->Clear();

	for ( ControlList::List::const_iterator it = info.ControlList.list.begin(); it != info.ControlList.list.end(); ++it )
	{
		AddPropertiesFromControl( *it );
	}

	m_Props->ExpandAll();
}

void Properties::AddPropertiesFromControl( Controls::Base* pControl )
{
	ControlFactory::Base* cf = pControl->UserData.Get<ControlFactory::Base*>( "ControlFactory" );

	while ( cf )
	{
		Controls::Properties* properties = m_Props->Find( cf->Name() );

		if ( !properties ) properties = m_Props->Add( cf->Name() );

		ControlFactory::Property::List::const_iterator it = cf->Properties().begin();
		ControlFactory::Property::List::const_iterator itEnd = cf->Properties().end();
		for ( it; it != itEnd; ++it )
		{
			Controls::PropertyRow* row = properties->Find( (*it)->Name() );
			if ( !row )
			{
				properties->Add( (*it)->Name(), (*it)->GetValue( pControl ) );
			}
			else
			{
				if ( row->GetProperty()->GetPropertyValue().GetUnicode() != (*it)->GetValue( pControl ) )
				{
					row->GetProperty()->SetPropertyValue( "different" );
				}
			}
			
		}


		cf = cf->GetBaseFactory();
	}
}