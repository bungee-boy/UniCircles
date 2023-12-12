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

Pos Circle::getPos() { return pos; }
void Circle::setPos(Pos newPos) { pos = newPos; }

Pos Circle::getDir() { return dir; }
void Circle::setDir(Pos newDir) { dir = newDir; }

int Circle::getSize() { return size; }
void Circle::setSize(int newSize) { size = newSize; }

void Circle::Move() {  // Circle move
	pos.x += dir.x;
	pos.y += dir.y;

	if (pos.x <= 0) {  // Bounce off edges of the screen
		pos.x = 0;
		dir.x = -dir.x;
	}
	else if (pos.x >= gWidth - (size * 2)) {
		pos.x = gWidth - (size * 2);
		dir.x = -dir.x;
	}

	if (pos.y <= 0) {
		pos.y = 0;
		dir.y = -dir.y;
	}
	else if (pos.y >= gHeight - (size * 2)) {
		pos.y = gHeight - (size * 2);
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
	F_Pos dist;  // Float position
	dist.x = a.getPos().x - b.getPos().x;
	dist.y = a.getPos().y - b.getPos().y;
	float totalDist = dist.x * dist.x + dist.y * dist.y;  // Use pythagorus theorum
	if (totalDist > 10000) {
		return;
	}
	float collision = a.getSize() * a.getSize() + b.getSize() * b.getSize();  // Calculate collision ^ 2 rather than sqrt(dist) as faster
	// cout << "Size: " << a.getSize() << " " << b.getSize() << " Dist: " << totalDist << " Coll: " << collision << endl;
	if (totalDist <= collision) {  // If collided...
		cout << endl;
		Pos tempDir{ a.getDir().x, a.getDir().y };  // Exchange directions to simulate elastic collision
		a.setDir(b.getDir());
		b.setDir(tempDir);
	}
}
