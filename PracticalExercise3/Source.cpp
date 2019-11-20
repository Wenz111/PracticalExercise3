#include <Windows.h>
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical Exercise 3"

int question = 0;
int numberOfBladeOption = 1;
float xvalue = 0.0f;
float yvalue = 0.0f;
float angleRotate = 0.0f;
float speed_step_angle = 0.05f;
float center_x = 0.0f;
float center_y = 0.1f;

float xcolor = 58.0f / 255.0f;
float ycolor = 39.0f / 255.0f;
float zcolor = 16.0f / 255.0f;

float cloudMoveX = 0.5f;
float cloudMoveY = 0.0f;
float cloud2MoveX = -1.5f;
float cloud2MoveY = 0.0f;

void drawSunRay() {
	glBegin(GL_QUADS);
	glVertex2f(-0.4f, 0.8f);
	glVertex2f(-0.15f, 0.8f);
	glVertex2f(-0.15f, 0.7f);
	glVertex2f(-0.4f, 0.7f);
	glEnd();
}

void drawCloud() {
	float cx1 = 0.4, cy1 = 0.8, cx2 = 0.0, cy2 = 0.0;
	float cangle = 0.0;
	float cradius = 0.1;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(209.0f / 255.0f, 219.0f / 255.0f, 254.0f / 255.0f);
	glVertex2f(cx1, cy1);

	for (cangle = 0; cangle <= 360; cangle += 0.2) {
		cx2 = cx1 + cos(cangle) * cradius;
		cy2 = cy1 + sin(cangle) * cradius;
		glVertex2f(cx2, cy2);
	}
	glEnd();
}

void drawCompleteCloud() {
	drawCloud();

	glPushMatrix();
	glTranslatef(0.1f, 0.05f, 0.0f);
	drawCloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2f, 0.0f, 0.0f);
	drawCloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1f, -0.05f, 0.0f);
	drawCloud();
	glPopMatrix();
}

void drawWindMillBlade() {
	
	glColor3f(xcolor, ycolor, zcolor);
	// Windmill Blade 1 Top
	glBegin(GL_QUADS);
	glVertex2f(0.025f, 0.6f);
	glVertex2f(0.025f, 0.1f);
	glVertex2f(-0.025f, 0.1f);
	glVertex2f(-0.025f, 0.6f);
	glEnd();

	// Blade 1 Left Design
	glPushMatrix();
	glTranslatef(-0.05f, 0.0f, 0.0f);
	glRotatef(5.0f, 0.0f, 0.0, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.015f, 0.6f);
	glVertex2f(0.015f, 0.2f);
	glVertex2f(-0.015f, 0.2f);
	glVertex2f(-0.015f, 0.6f);
	glEnd();
	glPopMatrix();

	// Blade 1 Right Design
	glPushMatrix();
	glTranslatef(0.05f, 0.0f, 0.0f);
	glRotatef(-5.0f, 0.0f, 0.0, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.015f, 0.6f);
	glVertex2f(0.015f, 0.2f);
	glVertex2f(-0.015f, 0.2f);
	glVertex2f(-0.015f, 0.6f);
	glEnd();
	glPopMatrix();

	// Blade 1 Top design
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2f(-0.1f, 0.6f);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.1f, 0.57f);
	glVertex2f(-0.1f, 0.57f);
	glEnd();
	glPopMatrix();

	// Blade 1 Middle 2 design
	glPushMatrix();
	glTranslatef(0.0f, -0.1f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.1f, 0.6f);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.1f, 0.57f);
	glVertex2f(-0.1f, 0.57f);
	glEnd();
	glPopMatrix();

	// Blade 1 Middle design
	glPushMatrix();
	glTranslatef(0.0f, -0.2f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.1f, 0.6f);
	glVertex2f(0.1f, 0.6f);
	glVertex2f(0.1f, 0.57f);
	glVertex2f(-0.1f, 0.57f);
	glEnd();
	glPopMatrix();

	// Blade 1 Bottom design
	glPushMatrix();
	glTranslatef(0.0f, -0.3f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.08f, 0.6f);
	glVertex2f(0.08f, 0.6f);
	glVertex2f(0.08f, 0.57f);
	glVertex2f(-0.08f, 0.57f);
	glEnd();
	glPopMatrix();

	// End of Blade 1
}

void drawFourBlade() {
	// Draw Blade 1
	drawWindMillBlade();


	// Draw Blade 2 (Left)
	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 2

	// Draw Blade 3 (Right)
	glPushMatrix();
	glTranslatef(-0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 3

	// Draw Blade 4 (Down)
	glPushMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4
}

void drawSixBlade() {
	// Draw Six Blade
// Draw Blade 1
	drawWindMillBlade();

	// Draw Blade 2 (Left)
	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 2

	// Draw Blade 2.5 (Top Left)
	glPushMatrix();
	glTranslatef(0.05f, -0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(0.03f, 0.07f, 0.0f);
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 2.5

	// Draw Blade 3 (Right)
	glPushMatrix();
	glTranslatef(-0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 3

	// Draw Blade 4.5 (Bottom Right)
	glPushMatrix();
	glTranslatef(-0.06f, 0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	glPushMatrix();
	glRotatef(-140.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4.5

	// Draw Blade 4 (Down)
	glPushMatrix();
	glTranslatef(0.0f, 0.23f, 0.0f);
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4
}

void drawEightBlade() {
	// Draw Eight Blade
// Draw Blade 1
	drawWindMillBlade();

	// Draw Blade 2 (Left)
	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 2

	// Draw Blade 2.5 (Top Left)
	glPushMatrix();
	glTranslatef(0.05f, -0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(0.03f, 0.07f, 0.0f);
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 2.5

	// Draw Blade 3 (Right)
	glPushMatrix();
	glTranslatef(-0.1f, 0.1f, 0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 3

	// Draw Blade 4.5 (Bottom Left)
	glPushMatrix();
	glTranslatef(0.06f, 0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	glPushMatrix();
	glRotatef(140.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4.5

	// Draw Blade 3.5 (Top Right)
	glPushMatrix();
	glTranslatef(-0.05f, -0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(-0.03f, 0.07f, 0.0f);
	glPushMatrix();
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 3.5

	// Draw Blade 4.5 (Bottom Right)
	glPushMatrix();
	glTranslatef(-0.06f, 0.05f, 0.0f);
	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0f);
	glPushMatrix();
	glRotatef(-140.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4.5

	// Draw Blade 4 (Down)
	glPushMatrix();
	glTranslatef(0.0f, 0.23f, 0.0f);
	glPushMatrix();
	glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
	drawWindMillBlade();
	glPopMatrix();
	glPopMatrix();
	// End of Blade 4
}

void drawWindmill() {
	glClearColor(133.0f / 255.0f, 183.0f / 255.0f, 108.0f / 255.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	// Design Background
	glBegin(GL_QUADS);
	glColor3f(35.0f / 255.0f, 31.0f / 255.0f, 24.0f / 255.0f);
	glVertex2f(-1.0f, -0.8f);
	glVertex2f(1.0f, -0.8f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();

	// Draw Sun
	float x1 = -0.9, y1 = 0.9, x2 = 0.0, y2 = 0.0;
	float angle = 0.0;
	float radius = 0.4;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(248.0f / 255.0f, 249.0f / 255.0f, 159.0f / 255.0f);
	glVertex2f(x1, y1);

	for (angle = 0; angle <= 360; angle += 0.2) {
		x2 = x1 + cos(angle) * radius;
		y2 = y1 + sin(angle) * radius;
		glVertex2f(x2, y2);
	}
	glEnd();

	// Draw Sun Ray 1 (Top)
	glPushMatrix();
	glTranslatef(0.0f, 0.2f, 0.0f);
	glPushMatrix();
	glRotatef(5.0f, 0.0f, 0.0f, 1.0f);
	drawSunRay();
	glPopMatrix();
	glPopMatrix();

	// Draw Sun Ray 2
	glPushMatrix();
	glTranslatef(-0.55f, -0.15f, 0.0f);
	glPushMatrix();
	glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
	drawSunRay();
	glPopMatrix();
	glPopMatrix();

	// Draw Sun Ray 3
	glPushMatrix();
	glTranslatef(0.0f, 0.1f, 0.0f);
	glPushMatrix();
	glTranslatef(-0.13f, 0.2f, 0.0f);
	glPushMatrix();
	glTranslatef(-0.9f, -0.5f, 0.0f);
	glPushMatrix();
	glRotatef(-55.0f, 0.0f, 0.0f, 1.0f);
	drawSunRay();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	// Draw Sun Ray 4
	glPushMatrix();
	glTranslatef(-0.1f, 0.68f, 0.0f);
	glPushMatrix();
	glRotatef(95.0f, 0.0f, 0.0f, 1.0f);
	drawSunRay();
	glPopMatrix();
	glPopMatrix();

	// Draw Moving Cloud -0.4 to 0.3
	glPushMatrix();
	cloudMoveX -= 0.0001f;
	glTranslatef(cloudMoveX, cloudMoveY, 0.0f);
	drawCompleteCloud();
	glPopMatrix();

	// Draw Moving Cloud -0.4 to 0.3
	glPushMatrix();
	cloud2MoveX += 0.0001f;
	cloud2MoveY = -0.3f;
	glTranslatef(cloud2MoveX, cloud2MoveY, 0.0f);
	drawCompleteCloud();
	glPopMatrix();

	// Windmill Body
	glBegin(GL_QUADS);
	glColor3f(132.0f / 255.0f, 115.0f / 255.0f, 107.0f / 255.0f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.5f, -0.8f);
	glVertex2f(-0.5f, -0.8f);
	glVertex2f(-0.2f, 0.1f);
	glEnd();

	// Windmill First Bottom Section
	glBegin(GL_QUADS);
	glColor3f(163.0f / 255.0f, 146.0f / 255.0f, 124.0f / 255.0f);
	glVertex2f(-0.43f, -0.6f);
	glVertex2f(0.43f, -0.6f);
	glColor3f(35.0f / 255.0f, 31.0f / 255.0f, 24.0f / 255.0f);
	glVertex2f(0.5f, -0.8f);
	glVertex2f(-0.5f, -0.8f);
	glEnd();

	// Windmill Second Middle Section
	glBegin(GL_QUADS);
	glColor3f(163.0f / 255.0f, 146.0f / 255.0f, 124.0f / 255.0f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(0.27f, -0.1f);
	glVertex2f(-0.27f, -0.1f);
	glVertex2f(-0.2f, 0.1f);
	glEnd();

	// Middle Body
	glBegin(GL_QUADS);
	glColor3f(132.0f / 255.0f, 115.0f / 255.0f, 107.0f / 255.0f);
	glVertex2f(0.1f, 0.3f);
	glVertex2f(0.2f, 0.1f);
	glVertex2f(-0.2f, 0.1f);
	glVertex2f(-0.1f, 0.3f);
	glEnd();

	// Windmill Third Top Section
	glBegin(GL_QUADS);
	glColor3f(163.0f / 255.0f, 146.0f / 255.0f, 124.0f / 255.0f);
	glVertex2f(0.07f, 0.35f);
	glVertex2f(-0.07f, 0.35f);
	glVertex2f(-0.1f, 0.3f);
	glVertex2f(0.1f, 0.3f);
	glEnd();

	// Top Body
	glBegin(GL_QUADS);
	glColor3f(132.0f / 255.0f, 115.0f / 255.0f, 107.0f / 255.0f);
	glVertex2f(-0.07f, 0.38f);
	glVertex2f(0.07f, 0.38f);
	glVertex2f(0.07f, 0.35f);
	glVertex2f(-0.07f, 0.35f);
	glEnd();

	// Spinning Windmill Algorithm
	glPushMatrix();
	glTranslatef(center_x, center_y, 0.0f);
	glRotatef(angleRotate, 0.0f, 0.0f, 1.0f);
	angleRotate += speed_step_angle;
	glTranslatef(-center_x, -center_y, 0.0f);

	// Windmill Center Quads Section
	glBegin(GL_QUADS);
	glColor3f(196.0f / 255.0f, 174.0f / 255.0f, 144.0f / 255.0f);
	glVertex2f(0.05f, 0.15f);
	glVertex2f(0.05f, 0.05f);
	glVertex2f(-0.05f, 0.05f);
	glVertex2f(-0.05f, 0.15f);
	glEnd();

	// Draw Blade switch case
	switch (numberOfBladeOption)
	{
	case 1:
		drawFourBlade();
		break;
	case 2:
		drawSixBlade();
		break;
	case 3:
		drawEightBlade();
		break;
	default:
		break;
	}

	// Spinning Algorithm
	glPopMatrix();
}

void displayTwoInteractiveRectangle() {
	glClearColor(199.0f / 255.0f, 157.0f / 255.0f, 112.0f / 255.0f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(-xvalue, yvalue, 0.0f);
	// Draw Left Quads
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.15f, 0.1f);
	glVertex2f(0.15f, 0.1f);
	glVertex2f(0.15f, -0.1f);
	glVertex2f(-0.15f, -0.1f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(xvalue, -yvalue, 0.0f);
	// Draw Right Quads
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.15f, 0.1f);
	glVertex2f(0.15f, 0.1f);
	glVertex2f(0.15f, -0.1f);
	glVertex2f(-0.15f, -0.1f);
	glEnd();
	glPopMatrix();
}

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			break;
		}
		if (wParam == 0x31) {
			// Press key 1 -> display question 1
			question = 1;
			xvalue = 0.0f;
			yvalue = 0.0f;
			break;
		}
		if (wParam == VK_LEFT) {
			// Left key press -> x axis + 0.0001f
			xvalue = 0.0001f;
			break;
		}
		if (wParam == VK_RIGHT) {
			// Right key press -> x axis + 0.0001f
			xvalue = 0.0001f;
			break;
		}
		if (wParam == VK_UP) {
			// Up key press -> y axis + 0.0001f
			yvalue = 0.0001f;
			break;
		}
		if (wParam == VK_DOWN) {
			// Up key press -> y axis + 0.0001f
			yvalue = 0.0001f;
			break;
		}
		if (wParam == VK_SPACE) {
			// Space key press -> reset object to White and locate at centre
			xvalue = 0.0f;
			yvalue = 0.0f;
			xcolor = 58.0f / 255.0f;
			ycolor = 39.0f / 255.0f;
			zcolor = 16.0f / 255.0f;
			cloudMoveX = 0.5f;
			cloudMoveY = 0.0f;
			cloud2MoveX = -1.5f;
			cloud2MoveY = 0.0f;
			break;
		}
		if (wParam == 0x4F) {
			// Press key O -> Increase or Decrease Windmill Spin
			speed_step_angle += 0.05f;
			break;
		}
		if (wParam == 0x50) {
			// Press key P -> Increase or Decrease Windmill Spin
			speed_step_angle -= 0.05f;
			break;
		}
		if (wParam == 0x49) {
			// Press key I -> Clockwise or AntiClockwise Windmill Spin
			angleRotate *= -1.0f;
			speed_step_angle *= -1.0f;
			break;
		}
		if (wParam == 0x55) {
			// Press key U -> Stop Windmill Spin
			speed_step_angle = 0.0f;
			break;
		}
		if (wParam == 0x4A) {
			// Press key J -> Change Windmill Blade Color (Light Blue)
			xcolor = 4.0f / 255.0f;
			ycolor = 160.0f / 255.0f;
			zcolor = 233.0f / 255.0f;
			break;
		}
		if (wParam == 0x4B) {
			// Press key K -> Change Windmill Blade Color (Light Red)
			xcolor = 229.0f / 255.0f;
			ycolor = 0.0f / 255.0f;
			zcolor = 91.0f / 255.0f;
			break;
		}
		if (wParam == 0x4C) {
			// Press key L -> Change Windmill Blade Color (Turquoise)
			xcolor = 116.0f / 255.0f;
			ycolor = 168.0f / 255.0f;
			zcolor = 165.0f / 255.0f;
			break;
		}
		if (wParam == 0x4D) {
			// Press key M -> Change Number of Windmill Blade
			numberOfBladeOption += 1;
			if (numberOfBladeOption > 3) {
				numberOfBladeOption = 1;
			}
			break;
		}
		if (wParam == 0x32) {
			// Press key 2 -> Display Windmill
			question = 2;
			break;
		}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	switch (question)
	{
	case 1:
		displayTwoInteractiveRectangle();
		// Move Left Right Algorithm
		if (xvalue > 0.0f) {
			xvalue += 0.0001f;
			if (xvalue > 0.5f) {
				xvalue = 0.5f;
			}
		}

		// Move Up Down Algorithm
		if (yvalue > 0.0f) {
			yvalue += 0.0001f;
			if (yvalue > 0.5f) {
				yvalue = 0.5f;
			}
		}
		break;
	case 2:
		drawWindmill();
		break;
	default:
		break;
	}

	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------