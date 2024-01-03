#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "circle.h"

using namespace std;

extern int gWidth;
extern int gHeight;


Circle::Circle() {  // Circle constructor
	pos.x = rand() % gWidth - 22 + 1;
	pos.y = rand() % gHeight - 22 + 1;
	dir.x = rand() % 8 + 1;
	dir.y = rand() % 8 + 1;
	size = rand() % 20 + 15;  // Random 15 - 20
	cout << "Created circle" << endl;
}

Circle::~Circle() {  // Circle deconstructor
	cout << "Removed circle" << endl;
}

void Circle::Move() {  // Circle move
	pos.x += dir.x;
	pos.y += dir.y;
	// Bounce off edges of the screen
	if (pos.x <= 0) {  // Left
		pos.x = 0;
		dir.x = -dir.x;
	}
	else if (pos.x >= gWidth - (size * 2)) {  // Right
		pos.x = gWidth - (size * 2);
		dir.x = -dir.x;
	}

	if (pos.y <= 0) {  // Top
		pos.y = 0;
		dir.y = -dir.y;
	}
	else if (pos.y >= gHeight - (size * 2)) {  // Bottom
		pos.y = gHeight - (size * 2);
		dir.y = -dir.y;
	}
}

void Circle::Draw(sf::RenderWindow& window) {  // Draw circle
	sf::CircleShape circle;  // Create circle
	circle.setRadius(size);  // Set radius
	circle.setPosition(pos.x, pos.y);  // Set position
	circle.setFillColor({ colour.r, colour.g, colour.b, colour.a });  // Set colour
	window.draw(circle);  // Draw to screen
}

void Collide(Circle& a, Circle& b) {  // Collision between circles
	F_Pos dist;  // Float position
	dist.x = a.getPos().x - b.getPos().x;
	dist.y = a.getPos().y - b.getPos().y;
	float totalDist = dist.x * dist.x + dist.y * dist.y;  // Use pythagorus theorum
	if (totalDist > 10000) { // Do not consider collision if circles are > 10,000 away from each other (optimisation)
		return;
	}
	float collision = a.getSize() * a.getSize() + b.getSize() * b.getSize();  // Calculate collision ^ 2 rather than sqrt(dist) as faster (optimisation)
	// cout << "Size: " << a.getSize() << " " << b.getSize() << " Dist: " << totalDist << " Coll: " << collision << endl;  // Debug output
	if (totalDist <= collision) {  // If collided...
		Pos tempDir{ a.getDir().x, a.getDir().y };  // Exchange directions to simulate elastic collision
		a.setDir(b.getDir());
		b.setDir(tempDir);
	}
}
