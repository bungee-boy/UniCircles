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
	Circle();
	Pos getPos();
	void setPos(Pos newPos);
	Pos getDir();
	void setDir(Pos newDir);
	int getSize();
	void setSize(int newSize);
	void Move();
	void Draw(sf::RenderWindow& window);
private:
	Pos pos;
	Pos dir;
	int size;
	Colour colour;
};

void Collide(Circle& a, Circle& b);
