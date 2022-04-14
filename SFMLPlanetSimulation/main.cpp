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
sf::RenderWindow& window = w.window;

//earth radius = 6 371 km
//earth mass = 5.97E024 kg
//earth density 5515 kg/mmm

double Planet::dt = 3600;
double Planet::scale = 1000000;




int main()
{
	std::vector<Planet> planetArray;
	std::vector<Trace> traceArray;
	double scale = Planet::scale;


	//sun
	planetArray.push_back(Planet(
		Vector2d(0, 0) * scale,
		Vector2d(0, 0) * scale,
		696.0 * scale * 100,
		2E30,
		sf::Color(255, 207, 72)
	));
	


	//earth
	/*planetArray.push_back(Planet(
		Vector2d(150000, 0) * scale,
		Vector2d( 0, -0.03 ) * scale,
		6.371 * scale * 100,
		6E24,
		sf::Color(0, 50, 255)
	));*/



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

	



	bool mouseState = false;

	sf::Vector2f mouseWPos;
	sf::Vector2f mouseWPosRelease;
	while (window.isOpen())
	{
		Planet::gravityCalc(planetArray);

		if (w.isPressed)
		{
			mouseState = true;
			mouseWPos = w.getMousePos();
			
		}
		else if (w.isReleased)
		{
			mouseState = false;
			mouseWPosRelease = w.getMousePos();
			sf::Vector2f deltaWPos = mouseWPosRelease - mouseWPos;
			
			planetArray.push_back(Planet(
				Vector2d(mouseWPos.x, mouseWPos.y) * scale,
				Vector2d(deltaWPos.x, deltaWPos.y),
				6.371 * scale * 500,
				6E24,
				sf::Color(0, 50, 255)
			));

		}
		if (mouseState)
		{
			mouseWPosRelease = w.getMousePos();
			sf::Vertex line[] =
			{
				sf::Vertex(mouseWPos, sf::Color::Red),
				sf::Vertex(mouseWPosRelease, sf::Color::Blue)
			};
			window.draw(line, 2, sf::Lines);
		}
		

		/*Planet::planetLines(planetArray, window);*/
		for (Planet& planet : planetArray)
		{
			planet.update();
			planet.draw(window);
			
			/*traceArray.push_back(Trace(planet.getPos(), 500));*/
		}
		
		
		

		/*for (int i = 0; i < traceArray.size(); i++)
		{
			Trace& trace = traceArray[i];
			trace.update();
			trace.draw(window);
			if (trace.isDead())
			{
				traceArray.erase(traceArray.begin() + i);
			}
		}*/
		
		
		
		w.update();
	}
	return 0;
}