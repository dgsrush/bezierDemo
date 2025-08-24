#pragma once

#include<SFML/Graphics.hpp>

typedef enum ButtonState { PRESSED,HELD,RELEASED,NONE } ButtonState;

class InputMgr
{
public:
	InputMgr();
	~InputMgr();
	void initMouse();
	void initKeyboard();
	void update(int mz);

	void getMouseXY(int *x, int *y);
	void getMouseXYZ(int *x, int *y, int *z);
	ButtonState getMouseButtonState(int);
	bool isMouseOver();

	ButtonState getKeyState(int);

	void mouseClear();
	void kbClear();
	void clear();

	bool kbLeftReleased();
	bool kbRightReleased();
	bool kbUpReleased();
	bool kbDownReleased();
	bool kbHomeReleased();
	bool kbEndReleased();
	bool kbSpaceReleased();
	bool kbEscapePressed();
	bool kbKeyReleased(int);
	bool kbF1Released();
	bool kbF12Released();
	bool kbEnterReleased();
	bool mouseLeftReleased();
	bool mouseRightReleased();

	bool kbLeftDown();
	bool kbRightDown();
	bool kbUpDown();
	bool kbDownDown();

	bool mouseLeftDown();
	bool mouseRightDown();

private:
	bool bm;
	bool bk;
	int mz;

	bool mb[sf::Mouse::Button::ButtonCount];
	bool mbLast[sf::Mouse::Button::ButtonCount];

	int kb[sf::Keyboard::Key::KeyCount];
	int kbLast[sf::Keyboard::Key::KeyCount];
};
