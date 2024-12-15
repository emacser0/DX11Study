#pragma once

struct FGameDesc
{
	std::shared_ptr<class IExecute> App = nullptr;
	std::wstring AppName = L"GameCoding";
	HINSTANCE hInstance = 0;
	HWND hwnd = 0;
	float Width = 800;
	float Height = 600;
	bool bVSync = false;
	bool bWindowed = true;
	Color ClearColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
};

class FGame
{
	DECLARE_SINGLE(FGame);
public:
	WPARAM Run(FGameDesc& InDesc);

	FGameDesc& GetGameDesc() { return Desc; }

private:
	ATOM MyRegisterClass();
	BOOL InitInstance(int cmdShow);

	void Update();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	
private:
	FGameDesc Desc;
};

