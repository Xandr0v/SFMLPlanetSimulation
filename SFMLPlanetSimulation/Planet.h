#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include "constants.h"
#include "functions.h"
typedef sf::Vector2<double> Vector2d;



class Planet
{
	sf::CircleShape shape;
	

	Vector2d pos, vel, acc;
	double radius;
	double mass;
	static double dt;
	static double scale;
	

public:
	Planet(planetData pl);
	void update();
	void draw(sf::RenderWindow& window);
	Vector2d getPos();
	static void gravityCalc(std::vector<Planet>& planetArray);
	static void planetLines(std::vector<Planet>& planetArray, sf::RenderWindow& window);
	
	
};
