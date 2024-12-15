#include "pch.h"
#include "InputManager.h"

void InputManager::Init(HWND InHwnd)
{
	Hwnd = InHwnd;
	States.resize(KEY_TYPE_COUNT, EKeyState::NONE);
}

void InputManager::Update()
{
	HWND hwnd = ::GetActiveWindow();
	if (Hwnd != hwnd)
	{
		for (uint32 Key = 0; Key < KEY_TYPE_COUNT; Key++)
			States[Key] = EKeyState::NONE;

		return;
	}

	BYTE AsciiKeys[KEY_TYPE_COUNT] = {};
	if (::GetKeyboardState(AsciiKeys) == false)
		return;

	for (uint32 Key = 0; Key < KEY_TYPE_COUNT; Key++)
	{
		if (AsciiKeys[Key] & 0x80)
		{
			EKeyState& State = States[Key];

			if (State == EKeyState::PRESS || State == EKeyState::DOWN)
				State = EKeyState::PRESS;
			else
				State = EKeyState::DOWN;
		}
		else
		{
			EKeyState& State = States[Key];

			if (State == EKeyState::PRESS || State == EKeyState::DOWN)
				State = EKeyState::UP;
			else
				State = EKeyState::NONE;
		}
	}

	::GetCursorPos(&MousePos);
	::ScreenToClient(Hwnd, &MousePos);
}