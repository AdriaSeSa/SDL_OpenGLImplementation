#pragma once
#define MAX_KEYS 300
#define MAX_MOUSE_BUTTONS 5

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP,
	KEY_ERROR
};

class InputManager
{
public:

	static InputManager* GetInstance();

	static void ReleaseInstance();

	void UpdateInput();

	KEY_STATE GetKey(unsigned int id) const
	{
		return (id < MAX_KEYS) ? keyboard[id] : KEY_ERROR;
	}

	KEY_STATE GetMouseButton(unsigned int id) const
	{
		return (id < MAX_MOUSE_BUTTONS) ? mouse_buttons[id] : KEY_ERROR;
	}
private:
	InputManager();

	~InputManager();

	static InputManager* instance;

public:

	int mouse_x = 0;
	int mouse_y = 0;

	int mouse_wheel_y = 0;

private:
	KEY_STATE* keyboard = nullptr;
	KEY_STATE mouse_buttons[MAX_MOUSE_BUTTONS] = { KEY_STATE::KEY_DOWN };
};

