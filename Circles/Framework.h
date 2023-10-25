#if !defined(FRAMEWORK_H)
#define FRAMEWORK_H

bool UpdateFramework();
void DrawCircle(int x,int y, int radius);
void ChangeColour(unsigned char red, unsigned char green,
	unsigned char blue, unsigned char alpha = 255);

enum class EButton
{
	eLeft,
	eRight,
	eMiddle
};

bool IsButtonPressed(EButton whichButton);
void GetMousePosition(int &x, int &y);

// The extern keyword allows these globals to be accessed anywhere
extern int gScreenWidth;
extern int gScreenHeight;

#endif
