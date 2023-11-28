#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include "circle.h"
#include "main.h"

using namespace std;  // Namespaces
using namespace std::this_thread;
using namespace std::chrono;

int gScreenWidth{1800};  // Screen dimensions
int gScreenHeight{990};
int gTimeDelayMS{10};  // Delay to slow things down
bool gCollision = true;  // Control collision

sf::RenderWindow gWindow(sf::VideoMode(gScreenWidth, gScreenHeight), "Circles");  // Initialise window
sf::CircleShape gCircleShape(0);


int main()
{
	srand(time(NULL));  // Random seed set to time

	int numCircles = 20; // Number of circles
	vector<Circle> Circles;  // Create empty vector of circles
	Circles.resize(numCircles);
	for (int i = 0; i < Circles.size(); i++)  // Fill vector with circles
		Circles[i] = Circle();
	

	while(gWindow.isOpen()) {
		sleep_for(milliseconds(gTimeDelayMS));  // Window FPS
		gWindow.clear();  // Clear window between frames

		sf::Event event;  // Window events
		while (gWindow.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:  // If window close
				gWindow.close();  // Exit window
				break;
			default:  // Pass
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {  // Right click
			numCircles -= 1;  // Remove circle
			Circles.pop_back();
			cout << "Removed a circle." << endl;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {  // Middle click
			gCollision = !gCollision;  // Toggle collision
			cout << "Toggled collision." << endl;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && numCircles >= 1) {  // Left click
			Circles.push_back(Circle());  // Add circle
			numCircles += 1;
			cout << "Added a new circle." << endl;
		}

		for (int i = 0; i < numCircles; i++) {  // For each circle
			Circles[i].Move();  // Move circles

			if (gCollision) {  // Collision between circles
				for (int j = i + 1; j < numCircles; j++)
					Collide(Circles[i], Circles[j]);
			}
			
			Circles[i].Draw(gWindow);  // Draw circles
		}

		gWindow.display();  // Draw to window
	}

	return 0;
}
