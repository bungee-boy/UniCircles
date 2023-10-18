/*
    Start shape drawing file
*/

#include <iostream>
#include "Framework.h"

// Variables with global scope - do not rename them, feel free to change values though

// Screen dimensions
int gScreenWidth{800};
int gScreenHeight{600};

// Delay to slow things down
int gTimeDelayMS{10};

using namespace std;

int main()
{
	cout << "Hello circles" << endl;

	while(UpdateFramework())
	{
		// Draws a circle at 100,200 with radius 20
		DrawCircle(100,200,20);	
	}

	cout << "Bye bye" << endl;

	return 0;
}
