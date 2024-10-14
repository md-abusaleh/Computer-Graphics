#include <windows.h>
#include <GL/glut.h>


void renderLine() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    gluOrtho2D(-500, 500, -500, 500);
    glClear(GL_COLOR_BUFFER_BIT);

    int r = 200;
    int x = 0;
    int y = r;
    int p = 1 - r;



    for (int x = 0; x < y; x++) {

        if (p < 0) {

            p = p + (2 * x) + 1;
        }
        else {

            y = y - 1;
            p = p + 2 * (x - y) + 1;
        }
        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2i(x, y);
        glVertex2i(x, -y);
        glVertex2i(-x, y);
        glVertex2i(-x, -y);
        glVertex2i(y, x);
        glVertex2i(y, -x);
        glVertex2i(-y, x);
        glVertex2i(-y, -x);

    }

    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("MD ABU SALEH");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);

    glutDisplayFunc(renderLine);
    glutMainLoop();
    return 0;
}

