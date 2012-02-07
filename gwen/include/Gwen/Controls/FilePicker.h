/*
	GWEN
	Copyright (c) 2012 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_FILEPICKER_H
#define GWEN_CONTROLS_FILEPICKER_H

#include "Gwen/BaseRender.h"
#include "Gwen/Controls/Dialogs/FileOpen.h"
#include "Gwen/Controls/TextBox.h"


namespace Gwen 
{
	namespace Controls
	{
		class GWEN_EXPORT FilePicker : public Controls::Base
		{
			public:

				GWEN_CONTROL_INLINE( FilePicker, Controls::Base )
				{
					m_Button = new Controls::Button( this );
					m_Button->Dock( Pos::Right );
					m_Button->SetMargin( Margin( 2, 0, 0, 0 ) );
					m_Button->SetText( ".." );
					m_Button->SetSize( 20, 20 );
					m_Button->onPress.Add( this, &FilePicker::OnBrowse );

					m_TextBox = new Controls::TextBox( this );
					m_TextBox->Dock( Pos::Fill );

					this->SetSize( 100, 20 );

					SetFileType( "Any Type | *.*" );
				}

				void SetFileType( const Gwen::String& string ) { m_FileType = string; }

				void SetFileName( const Gwen::String& string )
				{
					m_TextBox->SetText( string );
					m_TextBox->MoveCaretToEnd();
					onFileChanged.Call( this );
				}

				const Gwen::TextObject& GetFileName()
				{
					return m_TextBox->GetText();
				}

				void OnBrowse()
				{
					Gwen::Dialogs::FileOpen( true, "Name", "Start Path", m_FileType, this, &FilePicker::SetFileName );
				}

				virtual TextObject GetValue(){ return GetFileName(); }

				Event::Caller	onFileChanged;

			private:

				Controls::TextBox*	m_TextBox;
				Controls::Button*	m_Button;

				String				m_FileType;

		};
	}

}
#endif
