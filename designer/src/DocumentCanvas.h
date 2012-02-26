
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class DocumentCanvas : public Controls::Base 
{
	GWEN_CONTROL( DocumentCanvas, Controls::Base );

	virtual void Render( Gwen::Skin::Base* skin );

	protected:
};