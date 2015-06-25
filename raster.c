#define true 1
#define false 0
#define SW 800
#define SH 400

// Size of pixel in pixels
#define SZPIX 3
// { -lessblurry ; +moreblurry }
#define ALIASBLUR  0.38f

/* modified by Jon McCormack from: */
/* E. Angel, Interactive Computer Graphics */
/* A Top-Down Approach with OpenGL, Third Edition */
/* Addison-Wesley Longman, 2003 */
/* <OpenGL/glut.h> Windows...? */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void PutPixel(int x, int y)
{
	glVertex2f(x*SZPIX - SZPIX/2, y*SZPIX-SZPIX/2);
}


void PutCircle(unsigned int x0, unsigned int y0, unsigned int radius, int thickness)
{
    int f = 1 - radius;
    int ddF_x = 0;
    int ddF_y = -2 * radius;
    int x = 0;
    int y = radius;
 
    PutPixel(x0, y0 + radius);
    PutPixel(x0, y0 - radius);
    PutPixel(x0 + radius, y0);
    PutPixel(x0 - radius, y0);
 
    while(x < y) 
    {
        if(f >= 0) 
        {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x + 1;   

	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 + x + (i - thickness/2);
		int cy = y0 + y + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR) );
		PutPixel(cx, cy);
	} 
	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 - x + (i - thickness/2);
		int cy = y0 + y + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
        for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 + x + (i - thickness/2);
		int cy = y0 - y + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 - x + (i - thickness/2);
		int cy = y0 - y + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
        for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 + y + (i - thickness/2);
		int cy = y0 + x + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 - y + (i - thickness/2);
		int cy = y0 + x + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 + y + (i - thickness/2);
		int cy = y0 - x + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
	for (int i = 0; i < thickness; i++)
	for (int j = 0; j < thickness; j++)
	{
		int cx = x0 - y + (i - thickness/2);
		int cy = y0 - x + (j - thickness/2);
		glColor4f(1, 1, 1, (1.0f / thickness) * ( sqrt(i*i + j*j) * ALIASBLUR ) );
		PutPixel(cx, cy);
	} 
    }
}



void AALine(int x0, int y0, int x1, int y1, int thick) {
 
  float m = ((float)y1 - (float)y0) / ((float)x1 - (float)x0);
  float b = (float)y0 - m*(float)x0;
	

  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  int err = (dx>dy ? dx : -dy)/2, e2;
 
  for(;;){

    // Get formula of line for anti-aliasing 
    float distY = fabs( y0 - (m*(float)x0 + b));
    float distX = fabs( x0 - ( (y0-b)/m ) );
    float dist = sqrt(distY*distY + distX*distX);
    printf("%f\r\n", dist);
    glColor4f(1,1,1,1.0f - dist*ALIASBLUR);
	
    PutPixel(x0,y0);

    for (int i = 0; i < thick; i++)
    {
    	for (int j = 0; j < thick; j++)
	{
		float offs = i - (thick/2);
		distY = fabs( y0 - (m*(float)x0 + b+offs));
    		distX = fabs( x0 - ( (y0-b)/m + offs) );
    		dist = sqrt(distY*distY + distX*distX);
		glColor4f(1,1,1, 1.0f - dist*ALIASBLUR);

		PutPixel(x0 + offs, y0 + offs);
	}
    }

    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}


void display(void)
{
/* clear window */
glClear(GL_COLOR_BUFFER_BIT);

/* Draw grid */
glBegin(GL_LINES);
	glColor4f(1, 1, 1, 0.1f);
	// Vertical
	for (int i = 0; i < SW / SZPIX; i++)
	{
		glVertex2f(i*SZPIX, 0);
		glVertex2f(i*SZPIX, SH);
	}
	// Horizontal
	for (int i = 0; i < SH / SZPIX; i++)
	{
		glVertex2f(0, i*SZPIX);
		glVertex2f(SW, i*SZPIX);
	}
glEnd();

/* Draw pixels */
glPointSize(SZPIX);
glColor4f(1, 1, 1, 1);
glBegin(GL_POINTS);
	PutCircle(10, 20, 30, 2);
	AALine(30, 30, 40,20, 4);
glEnd();

/* flush GL buffers */
glFlush();
}
void init()
{
/* set clear color to black */
glClearColor (0.0, 0.0, 0.0, 0.0);
/* set fill color to white */
glColor3f(1.0, 1.0, 1.0);
/* set up standard orthogonal view with clipping */
/* box as cube of side 2 centered at origin */
/* This is default view and these statement could be removed */
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
glOrtho(0, SW, 0, SH, -1.0, 1.0);

glEnable(GL_BLEND);
glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
int main(int argc, char** argv)
{
/* Initialize mode and open a window in upper left corner of screen */
/* Window title is name of program (arg[0]) */
glutInit(&argc,argv);
glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(SW,SH);
glutInitWindowPosition(0,0);
glutCreateWindow("simple");
glutDisplayFunc(display);
init();
glutMainLoop();
}
