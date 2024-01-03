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
	Circle();  // Constructor
	~Circle();  // Destructor
	Pos getPos() { return pos; }  // Get & Set functions
	void setPos(Pos newPos) { pos = newPos; }
	Pos getDir() { return dir; }
	void setDir(Pos newDir) { dir = newDir; }
	int getSize() { return size; }
	void setSize(int newSize) { size = newSize; }
	void Move();  // Updates position
	void Draw(sf::RenderWindow& window);  // Draws the circle to given window
private:
	Pos pos;
	Pos dir;
	int size;
	Colour colour;
};

void Collide(Circle& a, Circle& b);  // Calculates collisions between 2 circles
