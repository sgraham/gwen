
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class SelectionLayer;

class DocumentCanvas : public Controls::Base 
{
	GWEN_CONTROL( DocumentCanvas, Controls::Base );

	virtual void Render( Gwen::Skin::Base* skin );
	virtual void PostLayout( Skin::Base* skin );

	virtual bool DragAndDrop_CanAcceptPackage( Gwen::DragAndDrop::Package* pPackage );
	virtual bool DragAndDrop_HandleDrop( Gwen::DragAndDrop::Package* pPackage, int x, int y );

	Event::Caller	onChildAdded;
	Event::Caller	onChildRemoved;

	protected:

		SelectionLayer*	m_SelectionLayer;
};