#include <windows.h> 
#include <GL/glut.h> 

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black
    gluOrtho2D(0, 100, 0, 100); // Set up orthographic projection
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the shapes in white
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glVertex2d(10, 50);
    glVertex2d(10, 60);
    glVertex2d(15, 60);
    glVertex2d(15, 55);
    glVertex2d(20, 55);
    glVertex2d(20, 60);
    glVertex2d(25, 60);
    glVertex2d(25, 55);
    glVertex2d(30, 55);
    glVertex2d(30, 60);
    glVertex2d(35, 60);
    glVertex2d(35, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glVertex2d(10, 50);
    glVertex2d(10, 55);
    glVertex2d(35, 55);
    glVertex2d(35, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glVertex2d(17, 50);
    glVertex2d(17, 30);
    glVertex2d(27, 30);
    glVertex2d(27, 50);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glVertex2d(10, 20);
    glVertex2d(17, 30);
    glVertex2d(27, 30);
    glVertex2d(35, 20);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f); // Set color to white
    glVertex2d(5, 20);
    glVertex2d(40, 20);
    glVertex2d(40, 15);
    glVertex2d(5, 15);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("MD ABU SALEH");
    glutInitWindowSize(420, 420);
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
