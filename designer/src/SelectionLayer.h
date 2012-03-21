
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class SelectionLayer : public Controls::Base 
{
	GWEN_CONTROL( SelectionLayer, Controls::Base );

	virtual void OnMouseClickLeft( int x, int y, bool bDown );

	virtual void ClearSelection();
	virtual void AddSelection( Controls::Base* pControl );
	virtual void RemoveSelection(  Controls::Base* pControl );

	Event::Caller onSelectionChanged;
	Event::Caller onPropertiesChanged;
	Event::Caller onHierachyChanged;

	protected:

		void OnCageMoving( Event::Info info );
		void OnControlDragged( Event::Info info );
		void OnCagePressed( Event::Info info );

		ControlList	m_Selected;

};