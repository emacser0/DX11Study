#include "pch.h"

#include "01. TriangleDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	FGameDesc desc;
	desc.AppName = L"DX11Study";
	desc.hInstance = hInstance;
	desc.bVSync = false;
	desc.hwnd = NULL;
	desc.Width = 800;
	desc.Height = 600;
	desc.ClearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	desc.App = make_shared<FTriangleDemo>();

	GAME->Run(desc);

	return 0;
}