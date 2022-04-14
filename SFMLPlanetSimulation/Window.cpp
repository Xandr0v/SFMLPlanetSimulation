#include "Window.h"

Window::Window(int x, int y, std::string title, int FPS)
{

	size = sf::Vector2f(x, y);
	zoomFactor = 200.f;
	camAngle = 0.f;
	camSpeed = 10.f;
	camRotationSpeed = 2.f;
	zoomSpeed = 1.1;

	//window creating
	window.create(sf::VideoMode(x, y), title);

	//setting view
	sf::View view = window.getDefaultView();
	view.setCenter(size.x / 2.f, size.y / 2.f);
	view.setSize(size.x * zoomFactor, -size.y * zoomFactor);
	window.setView(view);
	window.setFramerateLimit(FPS);

	sf::Event event;
	sf::Clock clock;
}




void Window::update()
{
	isPressed = false;
	isReleased = false;

	//view setting
	view.setCenter(camPos);
	view.setRotation(camAngle);
	view.setSize(size.x * zoomFactor, -size.y * zoomFactor);
	window.setView(view);

	//displaying and clock
	window.display();
	window.clear();
	clock.restart();

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) { window.close(); }
		if (event.type == sf::Event::MouseButtonPressed) { isPressed = true; }
		if (event.type == sf::Event::MouseButtonReleased) { isReleased = true; }
		if (event.type == sf::Event::MouseWheelScrolled)
		{
			if (event.mouseWheel.x > 0) { this->zoomFactor /= zoomSpeed; }
			else if (event.mouseWheel.x < 0) { this->zoomFactor *= zoomSpeed; }
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)	{ window.close(); }
		}
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		viewMove(sf::Vector2f(0, camSpeed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		viewMove(sf::Vector2f(0, -camSpeed));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		viewMove(sf::Vector2f(camSpeed, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		viewMove(sf::Vector2f(-camSpeed, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		viewRotate(camRotationSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		viewRotate(-camRotationSpeed);
	}
}



sf::Vector2f Window::getMousePos()
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	/*pos.y = size.y - pos.y;*/
	sf::Vector2f wpos = window.mapPixelToCoords(pos);
	return wpos;
}




void Window::viewMove(sf::Vector2f vel)
{
	vel *= zoomFactor;

	sf::Vector2f direction;
	direction.x = camAngle / radian;
	direction.y = (camAngle + 90) / radian;

	sf::Vector2f angleVel;
	angleVel.x = cosf(direction.x) * vel.x + cosf(direction.y) * vel.y;
	angleVel.y = sinf(direction.x) * vel.x + sinf(direction.y) * vel.y;

	camPos += angleVel;
}

void Window::viewRotate(float angle)
{
	camAngle += angle;
}

void Window::viewSetZoom(float factor)
{
	zoomFactor += factor;
}
