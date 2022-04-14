#include "Planet.h"
typedef sf::Vector2<double> Vector2d;
double dt;
double scale;

//default constructor
Planet::Planet(planetData pl)
{
	vel = { 0 ,0 };

	pos = pl.pos;
	vel = pl.vel;
	radius = pl.radius;
	mass = pl.mass;
	sf::Color col = pl.col;

	sf::CircleShape shape;
	shape.setPosition(pos.x / scale, pos.y / scale);
	shape.setRadius(radius / scale);
	shape.setOrigin(radius / scale, radius / scale);
	shape.setFillColor(col);
	this->shape = shape;
}


//update current position, multiplying by the speed of time
void Planet::update()
{
	
	vel += acc * dt;
	pos += vel * dt;
	shape.setPosition(pos.x / scale, pos.y / scale);
	acc = { 0, 0 };
	
}


//drawing object using sf::CircleShape
void Planet::draw(sf::RenderWindow& window)
{
	window.draw(shape);
	
	
	
	
}

Vector2d Planet::getPos()
{
	return pos / scale;
}



//calculate gravitational force between unique pairs of planets
void Planet::gravityCalc(std::vector<Planet>& planetArray)
{

	std::vector<Planet>::iterator it;
	bool hit = true;
	while(hit)
	{
		[&]
		{
			int plCount = planetArray.size();
			for (int i = 0; i < plCount; i++) 
			{
				for (int j = i + 1; j < plCount; j++)
				{

					Planet& pl1 = planetArray[i];
					Planet& pl2 = planetArray[j];
					Vector2d deltaPos = pl2.pos - pl1.pos;
					double R = pythagor(deltaPos);
					if (R < pl1.radius + pl2.radius)
					{
						planetData pl3;

						pl3.pos = ((pl1.pos + pl2.pos) / 2.0 + deltaPos / pythagor(deltaPos) * (pl2.radius / pl1.radius) );
						pl3.vel = (pl1.vel * pl1.mass + pl2.vel * pl2.mass) / (pl1.mass + pl2.mass);
						pl3.radius = pythagor(pl1.radius, pl2.radius);
						pl3.mass = pl1.mass + pl2.mass;
						pl3.col = sf::Color::Green;

						planetArray.push_back(Planet(pl3));

						// i always bigger than j
						planetArray.erase(planetArray.begin() + i);
						planetArray.erase(planetArray.begin() + j - 1);

						hit = true;
						return;
					}
					//if statement ends
				}
			}
			//unique planet pairs loop ends

			//if R > pl1.radius + pl2.radius for each pairs of planets we can quit while loop
			hit = false;
			
		}();
	}
	//collision detection ends

	int plCount = planetArray.size();
	for (int i = 0; i < plCount; i++)
	{
		for (int j = i + 1; j < plCount; j++)
		{
			Planet& pl1 = planetArray[i];
			Planet& pl2 = planetArray[j];

			Vector2d deltaPos = pl1.pos - pl2.pos;
			double R = pythagor(deltaPos);
			Vector2d Fvar = -G * deltaPos / pow(R, 3);
			pl1.acc += Fvar * pl2.mass;
			pl2.acc -= Fvar * pl1.mass;		
		}
	}



}

void Planet::planetLines(std::vector<Planet>& planetArray, sf::RenderWindow& window)
{
	int plCount = planetArray.size();
	for (int i = 0; i < plCount; i++)
	{
		for (int j = i + 1; j < plCount; j++)
		{
			Planet& pl1 = planetArray[i];
			Planet& pl2 = planetArray[j];
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(pl1.pos / scale), sf::Color::White),
				sf::Vertex(sf::Vector2f(pl2.pos / scale), sf::Color::White)
			};
			window.draw(line, 2, sf::Lines);
		}
	}

}






