#include <windows.h>
#include <GL/glut.h>

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(0, 900, 0, 900);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2d(200, 200);
    glVertex2d(600, 200);
    glVertex2d(600, 600);
    glVertex2d(200, 600);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2d(200, 600);
    glVertex2d(600, 600);
    glVertex2d(400, 700);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(250, 400);
    glVertex2d(300, 400);
    glVertex2d(300, 450);
    glVertex2d(250, 450);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2d(500, 400);
    glVertex2d(550, 400);
    glVertex2d(550, 450);
    glVertex2d(500, 450);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 255);
    glVertex2d(350, 200);
    glVertex2d(450, 200);
    glVertex2d(450, 470);
    glVertex2d(350, 470);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Simple Square");
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}