#include <Polycode.h>
#include "TetrisApp.h"
#include "PolycodeView.h"
#include "windows.h"


using namespace Polycode;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PolycodeView *view = new PolycodeView(hInstance, nCmdShow, L"Polycode Template");
	TetrisApp *app = new TetrisApp(view);

	MSG Msg;
	do {
		if(PeekMessage(&Msg, NULL, 0,0,PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	} while(app->Update());
	return Msg.wParam;
}