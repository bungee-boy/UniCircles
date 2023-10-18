/*
    Start shape drawing file
*/

#include <iostream>
#include "Framework.h"

// Variables with global scope - do not rename them, feel free to change values though

// Screen dimensions
int gScreenWidth{1000};
int gScreenHeight{1000};

// Delay to slow things down
int gTimeDelayMS{10};

using namespace std;

int main()
{
	cout << "Hello circles" << endl;

	srand(time(NULL));

	const int numCircles = 20;
	int posx[numCircles];
	int posy[numCircles];
	int dirx[numCircles];
	int diry[numCircles];
	int size[numCircles];
	unsigned char cols[numCircles][4];

	for (int i = 0; i < numCircles; i++) {
		posx[i] = rand() % gScreenWidth - 22 + 1;
		posy[i] = rand() % gScreenHeight - 22 + 1;
		dirx[i] = rand() % 8 + 1;
		diry[i] = rand() % 8 + 1;
		size[i] = rand() % 15 + 10;
		cols[i][0] = rand() % 255 + 1;
		cols[i][1] = rand() % 255 + 1;
		cols[i][2] = rand() % 255 + 1;
		cols[i][3] = rand() % 255 + 10;
	}
	

	while(UpdateFramework())
	{
		for (int a = 0; a < numCircles; a++) {  // Collision between circles
			for (int b = a + 1; b < numCircles; b++) {
				float distx = posx[a] - posx[b];
				float disty = posy[a] - posy[b];
				float dist = distx * distx + disty * disty;  // Use pythagorus theorum

				float collision = size[a] + size[b];
				collision *= collision;  // Calculate collision^2 rather than sqrt(dist) as faster

				if (dist < collision) {
					dirx[a] = -dirx[a];
					dirx[b] = -dirx[b];
					diry[a] = -diry[a];
					diry[b] = -diry[b];
				}
			}
		}

		for (int i = 0; i < numCircles; i++) {  // Draw circles
			ChangeColour(cols[i][0], cols[i][1], cols[i][2]);
			DrawCircle(posx[i], posy[i], size[i]);
			posx[i] += dirx[i];
			posy[i] += diry[i];

			if (posx[i] <= 0) {  // Bounce off edges of the screen
				posx[i] = 0;
				dirx[i] = -dirx[i];
			}
			else if (posx[i] >= gScreenWidth - (size[i] * 2)) {
				posx[i] = gScreenWidth - (size[i] * 2);
				dirx[i] = -dirx[i];
			}

			if (posy[i] <= 0) {
				posy[i] = 0;
				diry[i] = -diry[i];
			}
			else if (posy[i] >= gScreenHeight - (size[i] * 2)) {
				posy[i] = gScreenWidth - (size[i] * 2);
				diry[i] = -diry[i];
			}
		}
	}

	cout << "Bye bye" << endl;

	return 0;
}
