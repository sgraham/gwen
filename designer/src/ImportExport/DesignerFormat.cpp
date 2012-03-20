
#include "ImportExport/Base.h"
#include "Bootil/Bootil.h"


class DesignerFormat : public Gwen::ImportExport::Base
{
	public:

		DesignerFormat();

		virtual Gwen::String Name(){ return "Designer"; }

		virtual bool CanImport(){ return true; }
		virtual void Import( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename );

		virtual bool CanExport(){ return true; }
		virtual void Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename );

		void ExportToTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree );
		void ImportFromTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree );

};

DesignerFormat g_DesignerFormat;


DesignerFormat::DesignerFormat()
{
	
}

void DesignerFormat::Import( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename )
{
	Bootil::BString strContents;

	if ( !Bootil::File::Read( strFilename, strContents ) )
		return;

	Bootil::Data::Tree tree;
	Bootil::Data::Json::Import( tree, strContents );

	ImportFromTree( pRoot, tree );
	//Debug::Msg( "%s\n", strContents.c_str() );

}

void DesignerFormat::ImportFromTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree )
{

	if ( tree.HasChild( "Children" ) )
	{
		Bootil::Data::Tree& ChildrenObject = tree.GetChild( "Children" );

		BOOTIL_FOREACH( c, ChildrenObject.Children(), Bootil::Data::Tree::List )
		{
			Bootil::BString strType = c->GetValue( "Type" );

			ControlFactory::Base* pFactory = ControlFactory::Find( strType );
			if ( !pFactory ) continue;

			Gwen::Controls::Base* pControl = pFactory->CreateInstance( pRoot );
			if ( !pControl ) continue;

			pControl->SetMouseInputEnabled( true );
			pControl->UserData.Set( "ControlFactory", pFactory );

			if ( c->HasChild( "Properties" ) )
			{
				Bootil::Data::Tree& Properties = c->GetChild( "Properties" );
				BOOTIL_FOREACH( p, Properties.Children(), Bootil::Data::Tree::List )
				{
					pFactory->SetControlValue( pControl, p->GetKey(), Bootil::String::Convert::ToWide( p->GetValue() ) );
				}
			}
		}
	}
}

void DesignerFormat::Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename )
{
	Bootil::Data::Tree tree;

	ExportToTree( pRoot, tree );

	Bootil::BString strOutput;
	if ( Bootil::Data::Json::Export( tree, strOutput, true ) )
	{
		Bootil::File::Write( strFilename, strOutput );
	}
}

void DesignerFormat::ExportToTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree )
{
	Bootil::Data::Tree* me = &tree;

	if ( pRoot->GetTypeName() == "DocumentCanvas" )
	{
		
	}
	else
	{
		me = &tree.AddChild();
		me->SetChild( "Type", pRoot->GetTypeName() );

		//
		// Set properties from the control factory
		//
		if ( pRoot->UserData.Exists( "ControlFactory" ) )
		{
			Bootil::Data::Tree& props = me->AddChild( "Properties" );
			ControlFactory::Base* pCF = pRoot->UserData.Get<ControlFactory::Base*>( "ControlFactory" );
			while ( pCF )
			{
				ControlFactory::Property::List::const_iterator it = pCF->Properties().begin();
				ControlFactory::Property::List::const_iterator itEnd = pCF->Properties().end();
				for ( it; it != itEnd; ++it )
				{
					props.SetChild( (*it)->Name(), Gwen::Utility::UnicodeToString( (*it)->GetValue( pRoot ) ).c_str() );
				}

				pCF = pCF->GetBaseFactory();
			}
		}
	}
	
	ControlList list = ImportExport::Tools::GetExportableChildren( pRoot );

	if ( !list.list.empty() )
	{
		Bootil::Data::Tree& children = me->AddChild( "Children" );

		ControlList::List::iterator it = list.list.begin();
		ControlList::List::iterator itEnd = list.list.end();
		while( it != itEnd )
		{
			ExportToTree( *it, children );
			++it;
		}
	}
}