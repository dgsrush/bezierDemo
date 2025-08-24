#include"InputMgr.h"

extern sf::RenderWindow window;

InputMgr::InputMgr()
{
	bm = false;
	bk = false;
	mz = 0;
	for(int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mb[i] = false;
		mbLast[i] = false;
	}
	for(int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		kb[i] = 0;
		kbLast[i] = 0;
	}
}

InputMgr::~InputMgr() {}

void InputMgr::initMouse() { bm = true; }
void InputMgr::initKeyboard() { bk = true; }

void InputMgr::mouseClear()
{
	mz = 0;
	for(int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
	{
		mb[i] = false;
		mbLast[i] = false;
	}
}

void InputMgr::kbClear()
{
	for(int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
	{
		kb[i] = 0;
		kbLast[i] = 0;
	}
}

void InputMgr::clear()
{
	mouseClear();
	kbClear();
}

void InputMgr::getMouseXY(int *x, int *y)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);
	*x = mouse.x;
	*y = mouse.y;
}

void InputMgr::getMouseXYZ(int *x, int *y, int *z)
{
	getMouseXY(x, y);
	*z = mz;
}

bool InputMgr::isMouseOver()
{
	return window.hasFocus(); //is this what we want?
}

void InputMgr::update(int mousez)
{
	if(bm)
	{
		mz = mousez;
		for(int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
		{
			mbLast[i] = mb[i];
			mb[i] = false;
		}
		if(window.hasFocus())
		{
			for(int i = 0; i < sf::Mouse::Button::ButtonCount; i++)
			{
				if(sf::Mouse::isButtonPressed((sf::Mouse::Button)i))
					mb[i] = true;
			}
		}
		else
			mouseClear();
	}
	if(bk)
	{
		for(int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
		{
			kbLast[i] = kb[i];
			kb[i] = 0;
		}
		if(window.hasFocus())
		{
			for(int i = 0; i < sf::Keyboard::Key::KeyCount; i++)
			{
				if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
					kb[i] = 1;
			}
		}
		else
			kbClear();
	}
}

ButtonState InputMgr::getMouseButtonState(int i)
{
	if(!bm) return NONE;
	if(i < 0 || i >= sf::Mouse::Button::ButtonCount) return NONE;
	if(!mbLast[i] &&  mb[i]) return PRESSED;
	if( mbLast[i] &&  mb[i]) return HELD;
	if( mbLast[i] && !mb[i]) return RELEASED;
	return NONE;
}

ButtonState InputMgr::getKeyState(int i)
{
	if(!bk) return NONE;
	if(i < 0 || i >= sf::Keyboard::Key::KeyCount) return NONE;
	if(!(kbLast[i]) &&  (kb[i])) return PRESSED;
	if( (kbLast[i]) &&  (kb[i])) return HELD;
	if( (kbLast[i]) && !(kb[i])) return RELEASED;
	return NONE;
}

bool InputMgr::kbLeftReleased() { return (getKeyState(sf::Keyboard::Left) == ButtonState::RELEASED); }
bool InputMgr::kbRightReleased() { return (getKeyState(sf::Keyboard::Right) == ButtonState::RELEASED); }
bool InputMgr::kbUpReleased() { return (getKeyState(sf::Keyboard::Up) == ButtonState::RELEASED); }
bool InputMgr::kbDownReleased() { return (getKeyState(sf::Keyboard::Down) == ButtonState::RELEASED); }
bool InputMgr::kbHomeReleased() { return (getKeyState(sf::Keyboard::Home) == ButtonState::RELEASED); }
bool InputMgr::kbEndReleased() { return (getKeyState(sf::Keyboard::End) == ButtonState::RELEASED); }
bool InputMgr::kbSpaceReleased() { return (getKeyState(sf::Keyboard::Space) == ButtonState::RELEASED); }
bool InputMgr::kbEscapePressed() { return (getKeyState(sf::Keyboard::Escape) == ButtonState::PRESSED); }
bool InputMgr::kbKeyReleased(int key) { return (getKeyState(key) == ButtonState::RELEASED); }
bool InputMgr::kbF1Released() { return (getKeyState(sf::Keyboard::F1) == ButtonState::RELEASED); }
bool InputMgr::kbF12Released() { return (getKeyState(sf::Keyboard::F12) == ButtonState::RELEASED); }
bool InputMgr::kbEnterReleased() { return (getKeyState(sf::Keyboard::Enter) == ButtonState::RELEASED); }
bool InputMgr::mouseLeftReleased() { return (getMouseButtonState(sf::Mouse::Button::Left) == ButtonState::RELEASED); }
bool InputMgr::mouseRightReleased() { return (getMouseButtonState(sf::Mouse::Button::Right) == ButtonState::RELEASED); }

bool InputMgr::mouseLeftDown() { return (getMouseButtonState(sf::Mouse::Button::Left) == ButtonState::HELD); }
bool InputMgr::mouseRightDown() { return (getMouseButtonState(sf::Mouse::Button::Right) == ButtonState::HELD); }

bool InputMgr::kbLeftDown()  { return (getKeyState(sf::Keyboard::Left) == ButtonState::HELD); }
bool InputMgr::kbRightDown() { return (getKeyState(sf::Keyboard::Right) == ButtonState::HELD); }
bool InputMgr::kbUpDown()    { return (getKeyState(sf::Keyboard::Up) == ButtonState::HELD); }
bool InputMgr::kbDownDown()  { return (getKeyState(sf::Keyboard::Down) == ButtonState::HELD); }
