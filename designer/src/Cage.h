
#pragma once

#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"

using namespace Gwen;

class Cage : public Controls::Base 
{
	GWEN_CONTROL( Cage, Controls::Base );

		void Setup( Controls::Base* pControl );

		virtual void Render( Gwen::Skin::Base* skin );
		virtual void PostLayout( Skin::Base* skin );

	protected:

		Controls::Base*		m_Control;
		int					m_iBorder;

};