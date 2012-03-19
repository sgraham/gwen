
#include "ImportExport/Base.h"
#include "Bootil/Bootil.h"


class DesignerFormat : public Gwen::ImportExport::Base
{
	public:

		DesignerFormat();

		virtual Gwen::String Name(){ return "Designer"; }

		virtual bool CanImport(){ return true; }
		virtual void Import( const Gwen::String& strFilename );

		virtual bool CanExport(){ return true; }
		virtual void Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename );

		void AddToTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree );

};

DesignerFormat g_DesignerFormat;


DesignerFormat::DesignerFormat()
{
	
}

void DesignerFormat::Import( const Gwen::String& strFilename )
{
	
}

void DesignerFormat::Export( Gwen::Controls::Base* pRoot, const Gwen::String& strFilename )
{
	Bootil::Data::Tree tree;

	ControlList list = ImportExport::Tools::GetExportableChildren( pRoot );
	if ( !list.list.empty() )
	{
		BOOTIL_FOREACH( a, list.list, ControlList::List )
		{
			AddToTree( *a, tree );
		}
	}

	Bootil::BString strOutput;
	if ( Bootil::Data::Json::Export( tree, strOutput, true ) )
	{
		Debug::Msg( "JSON!\n%s\n", strOutput.c_str() );
		Bootil::File::Write( strFilename, strOutput );
	}

	Debug::Msg( "DEsigner Format Exporting.. %s\n", strFilename.c_str() );
}

void DesignerFormat::AddToTree( Gwen::Controls::Base* pRoot, Bootil::Data::Tree& tree )
{
	Bootil::Data::Tree& me = tree.AddChild();

	{
		me.SetChild( "Type", pRoot->GetTypeName() );

		if ( pRoot->UserData.Exists( "ControlFactory" ) )
		{
			Bootil::Data::Tree& props = me.AddChild( "properties" );
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
		Bootil::Data::Tree& children = me.AddChild( "Children" );

		ControlList::List::iterator it = list.list.begin();
		ControlList::List::iterator itEnd = list.list.end();
		while( it != itEnd )
		{
			AddToTree( *it, children );
			++it;
		}
	}
}