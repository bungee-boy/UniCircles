#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "circle.h"
#include "main.h"

using namespace std;  // Namespaces
using namespace std::this_thread;
using namespace std::chrono;

int gScreenWidth{ 1800 };  // Screen dimensions
int gScreenHeight{ 990 };
int gTimeDelayMS{ 10 };  // Delay to slow things down
bool gCollision = true;  // Control collision


int main()
{	
	sf::RenderWindow window(sf::VideoMode(gScreenWidth, gScreenHeight), "Circles");  // Initialise window
	sf::CircleShape circleShape(0);  // Load circles class
	sf::Font basicFont;  // Load font class
	if (!basicFont.loadFromFile("basic.ttf")) {  // Load font
		return 0;
	}
	sf::Text text25("This is a test", basicFont, 25);  // Create text instance of basicFont, size 25
	text25.setColor({ 255, 255, 255, 255 });  // Set font colour
	text25.setPosition(gScreenWidth / 2, gScreenHeight / 2);  // Set font position

	srand(time(NULL));  // Random seed set to time

	int numCircles = 20; // Number of circles
	vector<Circle> Circles;  // Create empty vector of circles
	Circles.resize(numCircles);
	for (int i = 0; i < Circles.size(); i++)  // Fill vector with circles
		Circles[i] = Circle();
	

	while(window.isOpen()) {
		sleep_for(milliseconds(gTimeDelayMS));  // Window FPS
		window.clear();  // Clear window between frames

		sf::Event event;  // Window events
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:  // If window close
				window.close();  // Exit window
				break;
			default:  // Pass
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && numCircles > 1) {  // Right click
			numCircles -= 1;  // Remove circle
			Circles.pop_back();
			cout << "Removed a circle." << endl;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {  // Middle click
			gCollision = !gCollision;  // Toggle collision
			cout << "Toggled collision." << endl;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && numCircles < 200) {  // Left click
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
			
			Circles[i].Draw(window);  // Draw circles
		}

		text25.setString(("Number of circles: " + numCircles));  // Update amount of circles
		window.draw(text25);  // Draw text to window

		window.display();  // Display window
	}

	return 0;
}
