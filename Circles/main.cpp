#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include "circle.h"
#include "main.h"

using namespace std;  // Include namespaces
using namespace std::this_thread;
using namespace std::chrono;

int main()
{
	sf::RenderWindow window(sf::VideoMode(gWidth, gHeight), "Circles");  // Initialise window
	sf::CircleShape circleShape(0);  // Load circles class
	sf::Font basicFont;  // Load font class
	if (!basicFont.loadFromFile("basic.ttf"))  // Load custom font
		return 0;

	srand(time(NULL));  // Random seed set to time

	EInput lastInput{ EInput::eNone };  // Make enum for inputs

	int numCircles = 20; // Number of circles
	vector<Circle*> Circles;  // Create empty vector of pointers to circles
	Circles.resize(numCircles);
	for (int i = 0; i < Circles.size(); i++)  // Fill vector with circles
		Circles[i] = new Circle();  // Create circle using pointers

	sf::Color colWhite({ 255, 255, 255, 255 });
	sf::Color colGrey({ 180, 180, 180, 255 });
	// Controls title
	sf::Text txtControlTitle("Controls:", basicFont);  // Create text instance of basicFont, size 25
	txtControlTitle.setFillColor(colWhite);  // Set font colour
	txtControlTitle.setPosition(0, 0);  // Set font position
	// Controls
	sf::Text txtControls("Increase: [LMB]\nDecrease: [RMB]\nToggle collision: [MMB]\nSpeed: [Scroll]", basicFont, 20);
	txtControls.setFillColor(colGrey);
	txtControls.setPosition(0, 35);
	// Stats title
	sf::Text txtStatsTitle("Stats:", basicFont);
	txtStatsTitle.setFillColor(colWhite);
	txtStatsTitle.setPosition(0, 150);
	// Speed
	sf::Text txtSpeed("Speed: " + to_string(10 - gFps), basicFont, 20);
	txtSpeed.setFillColor(colGrey);
	txtSpeed.setPosition(0, 185);
	// NumCircles
	sf::Text txtNumCircles("Circles: " + to_string(numCircles), basicFont, 20);
	txtNumCircles.setFillColor(colGrey);
	txtNumCircles.setPosition(0, 210);
	// Collision
	sf::Text txtCollision(gCollision ? "Collision: On" : "Collision: Off", basicFont, 20);
	txtCollision.setFillColor(colGrey);
	txtCollision.setPosition(0, 235);

	while(window.isOpen()) {  // Main loop
		sleep_for(milliseconds(gFps));  // Window FPS
		window.clear();  // Clear window between frames

		sf::Event event;  // Window events
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:  // If window close
				window.close();  // Exit window
				break;
			case sf::Event::MouseWheelScrolled:  // Mouse scroll
				if (gFps > 1 || event.mouseWheelScroll.delta < 0) {
					gFps -= event.mouseWheelScroll.delta;
					txtSpeed.setString("Speed: " + to_string(10 - gFps));
				}
			default:  // Pass
				break;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {  // Right click
			if (numCircles > 1) {
				lastInput = EInput::eRmb;
				numCircles -= 1;  // Remove circle
				delete Circles[numCircles];
				Circles.pop_back();
				txtNumCircles.setString("Circles: " + to_string(numCircles));  // Update amount of circles
			}
			
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {  // Middle click
			if (lastInput != EInput::eMmb) {
				lastInput = EInput::eMmb;  // Update last key
				gCollision = !gCollision;  // Toggle collision
				txtCollision.setString(gCollision ? "Collision: On" : "Collision: Off");
				cout << "Toggled collision." << endl;
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {  // Left click
			if (numCircles < 200) {
				lastInput = EInput::eLmb;
				Circles.push_back(new Circle());  // Add circle using pointers
				numCircles += 1;
				txtNumCircles.setString("Circles: " + to_string(numCircles));  // Update amount of circles
			}
		}
		else  // Default last key to none
			lastInput = EInput::eNone;

		for (int circA = 0; circA < numCircles; circA++) {  // For each circle
			(*Circles[circA]).Move();  // Move circles (dereference first)

			if (gCollision) {  // Collision between circles
				for (int circB = circA + 1; circB < numCircles; circB++)
					Collide(*Circles[circA], *Circles[circB]);  // Dereference as circles is using pointers
			}
			
			(*Circles[circA]).Draw(window);  // Draw circles (dereference first)
		}

		window.draw(txtControlTitle);  // Draw text to window
		window.draw(txtControls);
		window.draw(txtStatsTitle);
		window.draw(txtSpeed);
		window.draw(txtNumCircles);
		window.draw(txtCollision);
		
		window.display();  // Display window
	}

	return 0;
}
