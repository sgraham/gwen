
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class DocumentCanvas;

class Hierarchy : public Controls::Base 
{
	GWEN_CONTROL( Hierarchy, Controls::Base );

		void WatchCanvas( DocumentCanvas* pCanvas );

	protected:

		void CompleteRefresh();
		void UpdateNode( Controls::TreeNode* pNode, Controls::Base* pControls );

		void OnCanvasChildAdded( Event::Info info );

		DocumentCanvas*			m_pCanvas;
		Controls::TreeControl*	m_Tree;

};