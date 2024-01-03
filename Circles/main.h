#pragma once

int gWidth{ 1800 };  // Screen dimensions
int gHeight{ 990 };
int gFps{ 10 };  // Delay to slow things down
bool gCollision = true;  // Control collision

enum class EInput {  // Enum for mouse input
	eNone,
	eLmb,
	eRmb,
	eMmb
};

int main();  // Main function
