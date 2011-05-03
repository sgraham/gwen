#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls/Label.h"

using namespace Gwen;

class Label : public GUnit
{
	public:

	GWEN_CONTROL_INLINE( Label, GUnit )
	{
		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( "Normal Label" );
			label->SizeToContents();
			label->SetPos( 10, 10 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Chinese: 久有归天愿 终过鬼门关" );
			label->SizeToContents();
			label->SetPos( 10, 30 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Japanese: 生むぎ　生ごめ　生たまご" );
			label->SizeToContents();
			label->SetPos( 10, 50 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Korean: 극지탐험　협회결성　체계적　연구" );
			label->SizeToContents();
			label->SetPos( 10, 70 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Hindi: ये अनुच्छेद हिन्दी में है।" );
			label->SizeToContents();
			label->SetPos( 10, 90 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Arabic: الآن لحضور المؤتمر الدولي" );
			label->SizeToContents();
			label->SetPos( 10, 110 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Coloured Text" );
			label->SetTextColor( Gwen::Color( 0, 0, 255, 255 ) );
			label->SizeToContents();
			label->SetPos( 10, 130 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Coloured Text With Alpha" );
			label->SetTextColor( Gwen::Color( 0, 0, 255, 100 ) );
			label->SizeToContents();
			label->SetPos( 10, 150 );
		}

		{
			//
			// Note that when using a custom font, this font object has to stick around
			// for the lifetime of the label. Rethink, or is that ideal?
			//
			m_Font.facename = L"Comic Sans MS";
			m_Font.size = 25;

			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Custom Font (Comic Sans 25)" );
			label->SetFont( &m_Font );
			label->SizeToContents();
			label->SetPos( 10, 170 );
		}

		{
			Gwen::Controls::Label* label = new Gwen::Controls::Label( this );
			label->SetText( L"Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n\nLorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." );
			label->SizeToContents();
			label->SetBounds( 300, 10, 150, 500 );
		}

	}

	Gwen::Font	m_Font;
};



DEFINE_UNIT_TEST( Label, L"Label" );