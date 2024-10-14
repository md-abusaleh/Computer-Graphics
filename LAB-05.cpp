#include <GL/glut.h>
#include <windows.h>

void drawCircle(int radius) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    while (x <= y) {
        glBegin(GL_POLYGON);
        // Point 1
        glVertex2d(x, y);
        // Point 2
        glVertex2d(-x, -y);
        // Point 3
        glVertex2d(y, x);
        // Point 4
        glVertex2d(-y, -x);
        // Point 5
        glVertex2d(-x, y);
        // Point 6
        glVertex2d(x, -y);
        // Point 7
        glVertex2d(-y, x);
        // Point 8
        glVertex2d(y, -x);

        if (d < 0) {
            x++;
            d += 2 * x + 1;
        }
        else {
            x++;
            y--;
            d += 2 * x - 2 * y + 1;
        }
    }

    glEnd();
}

void drawRectangle() {
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2d(-150, -100);
    glVertex2d(150, -100);
    glVertex2d(150, 100);
    glVertex2d(-150, 100);
    glEnd();
}
void drawstand() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2d(-150, -200);
    glVertex2d(-160, -200);
    glVertex2d(-160, 120);
    glVertex2d(-150, 120);
    glEnd();

}
void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.0f);
    glVertex2d(-120, -200);
    glVertex2d(-180, -200);
    glVertex2d(-180, -180);
    glVertex2d(-120, -180);

    glEnd();

}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle();
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(60);
    drawstand();
    ground();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("MD ABU SALEH");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-200, 200, -200, 200);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
