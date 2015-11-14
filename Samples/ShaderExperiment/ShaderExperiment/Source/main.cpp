#include "AppInclude.h"
#include "WonderApp.h"
#include "Renderer/SilhouetteRenderer.h"

int main(int argc, char* argv[])
{
	// Create application
	WonderApp application;

	Configuration* confPtr = Configuration::GetPtr();

	// Set canvas size
	size2f canvasSize;
	canvasSize.set(1920.0f, 1080.0f);
	Configuration::GetPtr()->SetCanvasSize(&canvasSize);

	// Set canvas mode
	Configuration::GetPtr()->SetCanvasMode(CanvasMode::CanvasModeAspectFit);

	// Set canvas color
	Configuration::GetPtr()->SetCanvasColor(3, 113, 156, 255);

	// Set renderer
	Configuration::GetPtr()->SetRendererType(Configuration::Renderertype::RENDERER_TYPE_USER_DEFINED);
	WonderPtr<SilhouetteRenderer> renderer;
	renderer.Create();
	Configuration::GetPtr()->SetUserDefinedRenderer(renderer.Ptr());

	// Build it up
	return BuildWonderlandUp(argc, argv, &application);
}
