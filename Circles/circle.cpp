#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "circle.h"

using namespace std;

extern int gScreenWidth;
extern int gScreenHeight;


Circle::Circle() {  // Circle constructor
	pos.x = rand() % gScreenWidth - 22 + 1;
	pos.y = rand() % gScreenHeight - 22 + 1;
	dir.x = rand() % 8 + 1;
	dir.y = rand() % 8 + 1;
	size = rand() % 15 + 10;
}

void Circle::Move() {  // Circle move
	pos.x += dir.x;
	pos.y += dir.y;

	if (pos.x <= 0) {  // Bounce off edges of the screen
		pos.x = 0;
		dir.x = -dir.x;
	}
	else if (pos.x >= gScreenWidth - (size * 2)) {
		pos.x = gScreenWidth - (size * 2);
		dir.x = -dir.x;
	}

	if (pos.y <= 0) {
		pos.y = 0;
		dir.y = -dir.y;
	}
	else if (pos.y >= gScreenHeight - (size * 2)) {
		pos.y = gScreenHeight - (size * 2);
		dir.y = -dir.y;
	}
}

void Circle::Draw(sf::RenderWindow& window) {  // Circle draw
	sf::CircleShape circle;  // Create circle
	circle.setRadius(size);  // Set radius
	circle.setPosition(pos.x, pos.y);  // Set position
	circle.setFillColor({ colour.r, colour.g, colour.b, colour.a });
	window.draw(circle);  // Draw to screen
}

void Collide(Circle& a, Circle& b) {  // Collision between circles
	F_Pos dist;
	dist.x = a.pos.x - b.pos.x;
	dist.y = a.pos.y - b.pos.y;
	float totalDist = dist.x * dist.x + dist.y * dist.y;  // Use pythagorus theorum

	float collision = a.size + b.size;
	collision *= collision;  // Calculate collision^2 rather than sqrt(dist) as faster

	if (totalDist < collision) {
		a.dir.x = -a.dir.x, a.dir.y = -a.dir.y;
		b.dir.x = -b.dir.x, b.dir.y = -b.dir.y;
	}
}
