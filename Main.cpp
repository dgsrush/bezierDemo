#include<SFML/Graphics.hpp>
#include"InputMgr.h"
#include<cmath>

sf::RenderWindow window;
InputMgr inp;
int mx = 0, my = 0;
int pointMove = -1;
sf::Vector2f p[] = { {300.f, 300.f}, {400.f, 200.f}, {500.f, 250.f}, {600.f, 400.f} };
int pCur = 0;
int numSegments = 100;
sf::VertexArray lines(sf::Lines, numSegments);
sf::CircleShape circle1(4), circle2(4);
bool calcType = true;

void quit() { window.close(); }

void setupWindow()
{
	int ww = 1024; int wh = 768;
	sf::VideoMode videoMode(ww, wh);
	window.create(videoMode, "Bezier/CatmullRom Demo", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	window.setPosition(sf::Vector2i(desktop.width / 2 - ww / 2, desktop.height / 2 - wh / 2 - 13));
}

bool mouseInCircle(int i)
{
	if(i < 0 || i > 3) return false;
	double dist = std::sqrt(std::pow(mx - p[i].x, 2) + std::pow(my - p[i].y, 2));
	return (dist < 5.0);
}

/////

float catmullRomGetT(float t, float alpha, const sf::Vector2f &p0, const sf::Vector2f &p1)
{
	sf::Vector2f d  = p1 - p0;
	float a = d.x * d.x + d.y * d.y;
	float b = std::pow(a, alpha * 0.5f);
	return (b + t);
}

float catmullRomLerp(float v0, float v1, float t)
{
	return (1.0f - t) * v0 + t * v1;
}

sf::Vector2f calcCatmullRomPoint(const sf::Vector2f &p0, const sf::Vector2f &p1,
								 const sf::Vector2f &p2, const sf::Vector2f &p3,
								 float t, float alpha = 0.5f)
{
	float t0 = 0.0f;
	float t1 = catmullRomGetT(t0, alpha, p0, p1);
	float t2 = catmullRomGetT(t1, alpha, p1, p2);
	float t3 = catmullRomGetT(t2, alpha, p2, p3);
	t = catmullRomLerp(t1, t2, t);
	sf::Vector2f a1 = (t1 - t) / (t1 - t0) * p0 + (t - t0) / (t1 - t0) * p1;
	sf::Vector2f a2 = (t2 - t) / (t2 - t1) * p1 + (t - t1) / (t2 - t1) * p2;
	sf::Vector2f a3 = (t3 - t) / (t3 - t2) * p2 + (t - t2) / (t3 - t2) * p3;
	sf::Vector2f b1 = (t2 - t) / (t2 - t0) * a1 + (t - t0) / (t2 - t0) * a2;
	sf::Vector2f b2 = (t3 - t) / (t3 - t1) * a2 + (t - t1) / (t3 - t1) * a3;
	sf::Vector2f c  = (t2 - t) / (t2 - t1) * b1 + (t - t1) / (t2 - t1) * b2;
	return c;
}

/////

sf::Vector2f calcBezierPoint(const sf::Vector2f &p0, const sf::Vector2f &p1,
							 const sf::Vector2f &p2, const sf::Vector2f &p3,
							 float t)
{
	sf::Vector2f ret;
	float pp = (1.0f - t);
	ret.x = pp * pp * pp * p0.x + 3 * pp * pp * t * p1.x + 3 * pp * t * t * p2.x + t * t * t * p3.x;
	ret.y = pp * pp * pp * p0.y + 3 * pp * pp * t * p1.y + 3 * pp * t * t * p2.y + t * t * t * p3.y;
	return ret;
}

/////

void recalcCurve()
{
	lines.clear();
	std::vector<sf::Vector2f> points;
	for(int i = 0; i <= numSegments; i++)
	{
		float t = static_cast<float>(i) / numSegments;
		if(calcType)
			points.push_back(calcBezierPoint(p[0], p[1], p[2], p[3], t));
		else
			points.push_back(calcCatmullRomPoint(p[0], p[1], p[2], p[3], t));
	}
	for(int i = 0; i < numSegments; i++)
	{
		sf::Vertex v1, v2;
		v1.position = points[i];
		v2.position = points[i + 1];
		v1.color = sf::Color::Yellow;
		v2.color = sf::Color::Yellow;
		lines.append(v1);
		lines.append(v2);
	}
	circle1.setPosition(sf::Vector2f(p[pCur].x - 3.0f, p[pCur].y - 3.0f));
}

void init()
{
	window.display();
	inp.initKeyboard();
	inp.initMouse();
    circle1.setFillColor(sf::Color::Red);
    circle1.setOutlineThickness(1);
    circle2.setFillColor(sf::Color::Blue);
    circle2.setOutlineThickness(1);
	recalcCurve();
}

void inputFunc()
{
	if(inp.kbEscapePressed()) quit();
	inp.getMouseXY(&mx, &my);

	if(inp.kbF1Released())
	{
		calcType = !calcType;
		recalcCurve();
	}

	if(inp.kbSpaceReleased())
	{
		pCur++;
		if(pCur == 4) pCur = 0;
		recalcCurve();
	}

	if(inp.kbLeftDown())       { p[pCur].x -= 2.0f; recalcCurve(); }
	else if(inp.kbRightDown()) { p[pCur].x += 2.0f; recalcCurve(); }
	if(inp.kbUpDown())         { p[pCur].y -= 2.0f; recalcCurve(); }
	else if(inp.kbDownDown())  { p[pCur].y += 2.0f; recalcCurve(); }

	if(inp.mouseLeftDown() && pointMove < 0)
	{
		for(int i = 0; i < 4; i++)
		{
			if(mouseInCircle(i))
			{
				pointMove = i;
				break;
			}
		}
	}

	if(inp.mouseLeftReleased())
		pointMove = -1;

	if(pointMove >= 0)
	{
		p[pointMove].x = mx;
		p[pointMove].y = my;
		recalcCurve();
	}
}

void frameFunc()
{
	window.draw(lines);
	for(int i = 0; i < 4; i++)
	{
		circle2.setPosition(sf::Vector2f(p[i].x - 3.0f, p[i].y - 3.0f));
		window.draw(circle2);
	}
	window.draw(circle1);
}

int main()
{
	setupWindow();
	init();
	int mousez;
	sf::Color clear(12, 123, 220);
	while(window.isOpen())
	{
		sf::Event event;
		mousez = 0;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				quit();
			else if(event.type == sf::Event::MouseWheelMoved)
    			mousez = event.mouseWheel.delta;
		}
		inp.update(mousez);
		inputFunc();
		window.clear(clear);
		frameFunc();
		window.display();
	}
	return 0;
}
