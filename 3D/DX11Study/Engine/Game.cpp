#include "pch.h"
#include "Game.h"
#include "IExecute.h"

WPARAM FGame::Run(FGameDesc& InDesc)
{
	Desc = InDesc;
	assert(Desc.App != nullptr);

	MyRegisterClass();

	if (!InitInstance(SW_SHOWNORMAL))
		return FALSE;
		
	GRAPHICS->Init(Desc.hwnd);
	TIME->Init();
	INPUT->Init(Desc.hwnd);
	
	Desc.App->Init();

	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			Update();
		}
	}

	return msg.wParam;
}


ATOM FGame::MyRegisterClass()
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Desc.hInstance;
	wcex.hIcon = ::LoadIcon(NULL, IDI_WINLOGO);
	wcex.hCursor = ::LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = Desc.AppName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

BOOL FGame::InitInstance(int cmdShow)
{
	RECT windowRect = { 0, 0, Desc.Width, Desc.Height };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	Desc.hwnd = CreateWindowW(Desc.AppName.c_str(), Desc.AppName.c_str(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, Desc.hInstance, nullptr);

	if (!Desc.hwnd)
		return FALSE;

	::ShowWindow(Desc.hwnd, cmdShow);
	::UpdateWindow(Desc.hwnd);

	return TRUE;
}

LRESULT CALLBACK FGame::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProc(handle, message, wParam, lParam);
	}
}

void FGame::Update()
{
	TIME->Update();
	INPUT->Update();

	GRAPHICS->RenderBegin();

	Desc.App->Update();
	Desc.App->Render();

	GRAPHICS->RenderEnd();
}

