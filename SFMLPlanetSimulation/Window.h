#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <iostream>
#include "constants.h"
struct Window
{
	sf::RenderWindow window;
	sf::View view;
	sf::Vector2f camPos;
	sf::Vector2f size;
	float camAngle;
	float zoomFactor;
	float camSpeed;
	float camRotationSpeed;
	float zoomSpeed;
	sf::Event event;
	sf::Clock clock;
	bool isPressed;
	bool isReleased;

	

	Window(int x, int y, std::string title, int FPS);
	void update();
	sf::Vector2f getMousePos();

	void viewMove(sf::Vector2f vel);
	void viewRotate(float angle);
	void viewSetZoom(float factor);
	
	
	
};
	


