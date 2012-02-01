/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_PLATFORM_H
#define GWEN_PLATFORM_H

#include "Gwen/Structures.h"
#include "Gwen/Events.h"

namespace Gwen
{
	namespace Platform
	{
		//
		// Set the system cursor to iCursor
		// Cursors are defined in Structures.h
		//
		GWEN_EXPORT void SetCursor( unsigned char iCursor );

		//
		// Used by copy/paste
		//
		GWEN_EXPORT UnicodeString GetClipboardText();
		GWEN_EXPORT bool SetClipboardText( const UnicodeString& str );

		//
		// Needed for things like double click
		//
		GWEN_EXPORT float GetTimeInSeconds();

		//
		// System Dialogs ( Can return false if unhandled )
		//
		GWEN_EXPORT bool FileOpen( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionStr fnCallback );
		GWEN_EXPORT bool FileSave( const String& Name, const String& StartPath, const String& Extension, Gwen::Event::Handler* pHandler, Event::Handler::FunctionStr fnCallback );

		//
		// Window Creation
		//
		GWEN_EXPORT void* CreatePlatformWindow( int x, int y, int w, int h, const Gwen::String& strWindowTitle );
		GWEN_EXPORT void DestroyPlatformWindow( void* pPtr );
		GWEN_EXPORT void MessagePump( void* pWindow, Gwen::Controls::Canvas* ptarget );
	}

}
#endif
