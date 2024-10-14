#include<windows.h>
#include <GL/glut.h>


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);	// Set display window colour to black

    glMatrixMode(GL_PROJECTION);		// Set projection parameters
    gluOrtho2D(-300.0, 300.0, -300.0, 300.0);
}

void drawShapes(void)
{
    glClear(GL_COLOR_BUFFER_BIT);	// Clear display window

    //Set colour to black
    glColor3f(0.396, 0.851, 0.169);
    //Adjust the point size
    glPointSize(10.0);

    // Draw a couple of points

    //Set colour to blue
    glColor3f(0, 1, 0);

    // Draw a filled triangle
    glBegin(GL_POLYGON);//first
    glVertex2i(-30, 130);
    glVertex2i(0, 200);
    glVertex2i(30, 130);
    glVertex2i(100, 100);
    glVertex2i(30, 70);

    glVertex2i(0, 0);
    glVertex2i(-30, 70);
    glVertex2i(-100, 100);







    glEnd();
    glColor3f(1, 1, 1);

    // Draw a filled triangle
    glBegin(GL_POLYGON);//second
    glVertex2i(70, 30);
    glVertex2i(100, 100);
    glVertex2i(130, 30);
    glVertex2i(200, 0);
    glVertex2i(130, -30);

    glVertex2i(100, -100);
    glVertex2i(70, -30);
    glVertex2i(0, 0);







    glEnd();
    glColor3f(0, 0, 1);

    // Draw a filled triangle
    glBegin(GL_POLYGON);//third
    glVertex2i(-30, -70);
    glVertex2i(0, 0);
    glVertex2i(30, -70);
    glVertex2i(100, -100);
    glVertex2i(30, -130);

    glVertex2i(0, -200);
    glVertex2i(-30, -130);
    glVertex2i(-100, -100);
    glVertex2i(-30, -70);







    glEnd();
    glColor3f(1, 0, 0);

    // Draw a filled triangle
    glBegin(GL_POLYGON);//4th
    glVertex2i(-130, 30);
    glVertex2i(-100, 100);
    glVertex2i(-70, 30);
    glVertex2i(0, 0);
    glVertex2i(-70, -30);

    glVertex2i(-100, -100);
    glVertex2i(-130, -30);
    glVertex2i(-200, 0);







    glEnd();
    glFlush();	// Process all OpenGL routines

}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);						// Initalise GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// Set display mode

    glutInitWindowPosition(100, 100);				// Set window position
    glutInitWindowSize(350, 350);					// Set window size
    glutCreateWindow("MD ABU SALEH ");	// Create display window

    init();							// Execute initialisation procedure
    glutDisplayFunc(drawShapes);		// Send graphics to display window
    glutMainLoop();					// Display everything and wait

    return 0;
}
