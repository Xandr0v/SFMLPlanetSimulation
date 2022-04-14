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

}


void Window::update()
{
	sf::Event event;
	sf::Clock clock;

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
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseWheelScrolled:
			if (event.mouseWheel.x > 0)
			{
				this->zoomFactor /= zoomSpeed;
			} 
			else if (event.mouseWheel.x < 0)
			{
				this->zoomFactor *= zoomSpeed;
			}
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				window.close();
				break;
			}
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
