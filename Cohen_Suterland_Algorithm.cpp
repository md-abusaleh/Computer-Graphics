#include <GL/glut.h>
#include <iostream>

#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

float xmin = -50, ymin = -50, xmax = 50, ymax = 50;

int computeRegionCode(float x, float y) {
    int code = 0;
    if (x < xmin) code |= LEFT;
    if (x > xmax) code |= RIGHT;
    if (y < ymin) code |= BOTTOM;
    if (y > ymax) code |= TOP;
    return code;
}

void cohenSutherlandLineClipAndDraw(float x0, float y0, float x1, float y1) {
    int code0 = computeRegionCode(x0, y0);
    int code1 = computeRegionCode(x1, y1);
    bool accept = false;

    while (true) {
        if ((code0 | code1) == 0) {
            accept = true;
            break;
        }
        else if (code0 & code1) {
            break;
        }
        else {
            int codeOut;
            float x, y;

            codeOut = code0 ? code0 : code1;

            if (codeOut & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            }
            else if (codeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            }
            else if (codeOut & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            }
            else if (codeOut & LEFT) {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (codeOut == code0) {
                x0 = x;
                y0 = y;
                code0 = computeRegionCode(x0, y0);
            }
            else {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1);
            }
        }
    }

    if (accept) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    cohenSutherlandLineClipAndDraw(-60, -20, 80, 60);

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100, 100, -100, 100);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("212-15-4082");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}