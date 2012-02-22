#include "Gwen/Gwen.h"
#include "Gwen/Controls.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Renderers/DirectX9.h"

int main()
{
	Gwen::Renderer::DirectX9	renderer;
	Gwen::Skin::TexturedBase	skin( &renderer );

	Gwen::Controls::WindowCanvas window_canvas( -1, -1, 700, 500, &skin, "GWEN Designer" );

	skin.Init( "img/DesignerSkin.png" );

	while ( !window_canvas.WantsQuit() )
	{
		window_canvas.DoThink();
	}
}