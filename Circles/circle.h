#pragma once

struct Pos {
	int x = 0, y = 0;
};

struct F_Pos {
	float x = 0, y = 0;
};

struct Colour {
	unsigned char r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1, a = 255;
};

class Circle {
public:
	Pos pos;
	Pos dir;
	int size;
	Colour colour;
	Circle();
	void Move();
	void Draw(sf::RenderWindow& window);
};

void Collide(Circle& a, Circle& b);