#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include "planet.h"
#include "Trace.h"
#include "functions.h"
#include "Window.h"

typedef sf::Vector2<double> Vector2d;

Window w(1000, 1000, "PlanetSimulationV2", 60);
Window w1(1000, 1000, "PlanetSimulationV2", 60);
sf::RenderWindow& window = w.window;

//earth radius = 6 371 km
//earth mass = 5.97E024 kg
//earth density 5515 kg/mmm

double Planet::dt = 3600 * 10;
double Planet::scale = 1000000;




int main()
{
	std::vector<Planet> planetArray;
	std::vector<Trace> traceArray;
	planetData pl;
	double scale = 1000000;


	//sun
	pl.pos = Vector2d(0, 0) * scale;
	pl.vel = Vector2d(0, 0) * scale;
	pl.radius = 696.0 * scale;
	pl.mass = 2E30;
	pl.col = sf::Color(255, 207, 72);

	planetArray.push_back(Planet(pl));


	//earth
	pl.pos = Vector2d( 150000, 0 ) * scale;
	pl.vel = Vector2d( 0, -0.03 ) * scale;
	pl.radius = 6.371 * scale;
	pl.mass = 6E24;
	pl.col = sf::Color(0, 50, 255);

	planetArray.push_back(Planet(pl));



	/*int plCount = 1;
	for (int i = 0; i < plCount; i++)
	{
		planetData pl;
		float randSp = 1;
		float squareSide = 50.f;
		sf::Vector2f spawnZone = { squareSide, squareSide };

		pl.pos = sf::Vector2f(hash(spawnZone.x) - spawnZone.x / 2.f + w.size.x / 2.f, hash(spawnZone.y) - spawnZone.y / 2.f + w.size.y / 2.f);
		pl.vel = sf::Vector2f(hash(randSp) - randSp / 2, hash(randSp) - randSp / 2);
		
		pl.radius = 6.371f;
		pl.mass = 5.97E024;
		pl.col = sf::Color::White;
		planetArray.push_back(Planet(pl));
	}*/

	




	
	while (window.isOpen())
	{
		Planet::gravityCalc(planetArray);




		/*sf::RectangleShape rect(sf::Vector2f(50, 50));
		rect.setOrigin(sf::Vector2f(25, 25));
		rect.setFillColor(sf::Color::Blue);
		rect.setPosition(0, 0);
		window.draw(rect);*/

		
		for (Planet& planet : planetArray)
		{
			planet.update();
			planet.draw(window);
			planet.draw(w1.window);
			/*traceArray.push_back(Trace(planet.getPos(), 300));*/
		}
		
		Planet::planetLines(planetArray, window);
		Planet::planetLines(planetArray, w1.window);
		w1.camPos = sf::Vector2f(planetArray[1].getPos().x, planetArray[1].getPos().y);

		/*for (Trace& trace : traceArray)
		{
			trace.update();
			trace.draw(window);
		}*/
		
		
		w1.update();
		w.update();
	}
	return 0;
}