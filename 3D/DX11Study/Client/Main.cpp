#include "pch.h"

#include "01. TriangleDemo.h"
#include "02. QuadDemo.h"
#include "03. ConstBufferDemo.h"
#include "04. CameraDemo.h"
#include "05. TextureDemo.h"
#include "06. SamplerDemo.h"
#include "07. HeightMapDemo.h"
#include "08. NormalDemo.h"
#include "09. MeshDemo.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	FGameDesc Desc;
	Desc.AppName = L"DX11Study";
	Desc.hInstance = hInstance;
	Desc.bVSync = false;
	Desc.hwnd = NULL;
	Desc.Width = 800;
	Desc.Height = 600;
	Desc.ClearColor = FColor(0.5f, 0.5f, 0.5f, 0.5f);
	Desc.App = make_shared<FCameraDemo>();

	GAME->Run(Desc);

	return 0;
}