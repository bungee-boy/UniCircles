
// SFML header file for graphics, there are also ones for Audio, Window, System and Network
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

extern int gScreenWidth;
extern int gScreenHeight;

sf::RenderWindow gWindow(sf::VideoMode(gScreenWidth, gScreenHeight), "C++ Framework");
sf::CircleShape gCircleShape(20, 64);

extern int x;
extern int y;

extern int gTimeDelayMS;

using namespace std::this_thread;
using namespace std::chrono;

bool UpdateFramework()
{
	static bool init{ true };

    if (!gWindow.isOpen())
      return false;

	if (init)
	{
		gCircleShape.setFillColor(sf::Color::Red);
		init = false;
	}

    // Handle any pending SFML events
    // These cover keyboard, mouse,joystick etc.
    sf::Event event;
    while (gWindow.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          gWindow.close();
        break;
        default:
          break;
      }
    }

    // Get the window to display its contents
    gWindow.display();

    sleep_for(milliseconds(gTimeDelayMS));

    // We must clear the winint timeDelayMS;dow each time round the loop
    gWindow.clear();

    // draw our circle shape to the window
   // gWindow.draw(gRedCircleShape);

    return true;
}

void ChangeColour(unsigned char red, unsigned char green, 
	unsigned char blue, unsigned char alpha = 255)
{
	gCircleShape.setFillColor({ red,green,blue,alpha });
}

void DrawCircle(int x,int y, int radius)
{
    gCircleShape.setPosition((float)x,(float)y);
    gCircleShape.setRadius((float)radius);
    // draw our circle shape to the window
    gWindow.draw(gCircleShape);
}

