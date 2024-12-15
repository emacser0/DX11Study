#pragma once

enum class EKeyType
{
	UP = VK_UP,
	DOWN = VK_DOWN,
	LEFT = VK_LEFT,
	RIGHT = VK_RIGHT,

	W = 'W',
	A = 'A',
	S = 'S',
	D = 'D',

	Q = 'Q',
	E = 'E',
	Z = 'Z',
	C = 'C',

	KEY_1 = '1',
	KEY_2 = '2',
	KEY_3 = '3',
	KEY_4 = '4',

	LBUTTON = VK_LBUTTON,
	RBUTTON = VK_RBUTTON,
};

enum class EKeyState
{
	NONE,
	PRESS,
	DOWN,
	UP,
	END
};

enum
{
	KEY_TYPE_COUNT = static_cast<int32>(UINT8_MAX + 1),
	KEY_STATE_COUNT = static_cast<int32>(EKeyState::END),
};

class InputManager
{
	DECLARE_SINGLE(InputManager);

public:
	void Init(HWND InHwnd);
	void Update();

	bool GetButton(EKeyType InKey) { return GetState(InKey) == EKeyState::PRESS; }
	bool GetButtonDown(EKeyType InKey) { return GetState(InKey) == EKeyState::DOWN; }
	bool GetButtonUp(EKeyType InKey) { return GetState(InKey) == EKeyState::UP; }
	
	const POINT& GetMousePos() { return MousePos; }

private:
	inline EKeyState GetState(EKeyType InKey) { return States[static_cast<uint8>(InKey)]; }

private:
	HWND Hwnd;
	std::vector<EKeyState> States;
	POINT MousePos = {};
};

