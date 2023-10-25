/*
    Start shape drawing file
*/

#include <iostream>
#include <vector>
#include "Framework.h"

// Variables with global scope - do not rename them, feel free to change values though

// Screen dimensions
int gScreenWidth{1800};
int gScreenHeight{990};

// Delay to slow things down
int gTimeDelayMS{10};

using namespace std;

int main()
{
	cout << "Hello circles" << endl;
	srand(time(NULL));  // Random seed set to time

	int numCircles = 20; // Number of circles
	bool collisionEnabled = true;  // Enable collision
	struct Circle {  // Circle type
		int pos[2];
		int dir[2];
		int size;
		unsigned char colour[4];
		bool move;
	};

	vector<Circle> Circles;  // Create empty vector of circles
	Circles.resize(numCircles);

	for (int i = 0; i < Circles.size(); i++) {  // Fill vector with randomised circles
		Circles[i].pos[0] = rand() % gScreenWidth - 22 + 1;
		Circles[i].pos[1] = rand() % gScreenHeight - 22 + 1;
		Circles[i].dir[0] = rand() % 8 + 1;
		Circles[i].dir[1] = rand() % 8 + 1;
		Circles[i].size = rand() % 15 + 10;
		Circles[i].colour[0] = rand() % 255 + 1;
		Circles[i].colour[1] = rand() % 255 + 1;
		Circles[i].colour[2] = rand() % 255 + 1;
		Circles[i].colour[3] = 255; // rand() % 255 + 10;
		Circles[i].move = true;
	}
	

	while(UpdateFramework())
	{
		if (IsButtonPressed(EButton::eRight)) {  // Add circle on right click
			Circle newCircle;
			newCircle.pos[0] = rand() % gScreenWidth - 22 + 1;
			newCircle.pos[1] = rand() % gScreenHeight - 22 + 1;
			newCircle.dir[0] = rand() % 8 + 1;
			newCircle.dir[1] = rand() % 8 + 1;
			newCircle.size = rand() % 15 + 10;
			newCircle.colour[0] = rand() % 255 + 1;
			newCircle.colour[1] = rand() % 255 + 1;
			newCircle.colour[2] = rand() % 255 + 1;
			newCircle.colour[3] = 255; // rand() % 255 + 10;
			newCircle.move = true;
			cout << "Added a new circle." << endl;
			numCircles += 1;  // Add to Circles
			Circles.push_back(newCircle);
		}
		if (IsButtonPressed(EButton::eMiddle)) {
			collisionEnabled = !collisionEnabled;
			cout << "Toggled collision." << endl;
		}

		for (int i = 0; i < numCircles; i++) {
			if (Circles[i].move) {  // Move circles
				Circles[i].pos[0] += Circles[i].dir[0];
				Circles[i].pos[1] += Circles[i].dir[1];

				if (Circles[i].pos[0] <= 0) {  // Bounce off edges of the screen
					Circles[i].pos[0] = 0;
					Circles[i].dir[0] = -Circles[i].dir[0];
				}
				else if (Circles[i].pos[0] >= gScreenWidth - (Circles[i].size * 2)) {
					Circles[i].pos[0] = gScreenWidth - (Circles[i].size * 2);
					Circles[i].dir[0] = -Circles[i].dir[0];
				}

				if (Circles[i].pos[1] <= 0) {
					Circles[i].pos[1] = 0;
					Circles[i].dir[1] = -Circles[i].dir[1];
				}
				else if (Circles[i].pos[1] >= gScreenHeight - (Circles[i].size * 2)) {
					Circles[i].pos[1] = gScreenHeight - (Circles[i].size * 2);
					Circles[i].dir[1] = -Circles[i].dir[1];
				}
			}

			if (collisionEnabled) {
				for (int b = i + 1; b < numCircles; b++) {  // Collision between circles
					float distx = Circles[i].pos[0] - Circles[b].pos[0];
					float disty = Circles[i].pos[1] - Circles[b].pos[1];
					float dist = distx * distx + disty * disty;  // Use pythagorus theorum

					float collision = Circles[i].size + Circles[b].size;
					collision *= collision;  // Calculate collision^2 rather than sqrt(dist) as faster

					if (dist < collision) {
						Circles[i].dir[0] = -Circles[i].dir[0];
						Circles[i].dir[1] = -Circles[i].dir[1];
						Circles[b].dir[0] = -Circles[b].dir[0];
						Circles[b].dir[1] = -Circles[b].dir[1];
					}
				}
			}

			ChangeColour(Circles[i].colour[0], Circles[i].colour[1], Circles[i].colour[2], Circles[i].colour[3]);  // Draw circles
			DrawCircle(Circles[i].pos[0], Circles[i].pos[1], Circles[i].size);
		}
	}

	cout << "Bye bye" << endl;

	return 0;
}
