#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>

using namespace std::chrono;
typedef sf::Vector2<double> Vector2d;

struct planetData
{
	Vector2d pos;
	Vector2d vel;
	float radius;
	float mass;
	sf::Color col;
};
namespace m
{
	template<typename T>
	void print(T x)
	{
		std::cout << x << "\n";
	}

	template<typename T>
	void print(T x, T y)
	{
		std::cout << x << " " << y << "\n";
	}

	template<typename T>
	void print(sf::Vector2<T> v)
	{
		std::cout << v.x << " " << v.y << "\n";
	}
}
int hash(int n);


template <typename T>
T pythagor(T a, T b)
{
	return sqrt(pow(a, 2) + pow(b, 2));
}

template <typename T>
T pythagor(sf::Vector2<T> v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

