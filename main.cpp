#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <time.h>

#define PI 3.14159265358979323846

#define MAX_RAIN_DROPS 1000
//rain
typedef struct {
    float x, y;
    float speed;
} RainDrop;

RainDrop rainDrops[MAX_RAIN_DROPS];

int scenary = 1; // Variable to track the current scene

int direction =1;
float shiftX = 0;
float shiftY = 0;

float planeX = 0;
float planeSpeed = 2;
bool planeFacingRight = false;

float cloud1X =1000;
float cloud2X =0;

float birdX = 780;

float fishX = 500;
float fishSpeed =1;
bool fishFacingLeft = true; // Indicates if the fish is facing left

float boatX = 480;
float boatSpeed =1;

float busX = 1000;

float carX = 0;
/*
float circleY[15] = {305, 310, 315, 320, 325, 305, 310, 315, 320, 325, 305, 310, 315, 320, 325};
float circleX[15] = {860, 860, 865, 870, 875, 900, 900, 905, 910, 915, 940, 940, 945, 950, 955};
float speed = 0.5;
float x_increment = 0.1;*/

void circle360(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}
void circle0to160(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i =0; i <=180; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void circle90to270(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 90; i <= 270; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void circle180to360(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 180; i <= 360; i++)
    {
        float angle = i * 3.1416 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}


void drawCircleOutline1(float radiusX, float radiusY, float posX, float posY)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.14159f / 180;
        glVertex2f(posX + cos(angle) * radiusX, posY + sin(angle) * radiusY);
    }
    glEnd();
}

void drawCircleOutline(float centerX, float centerY, float radius, int numSegments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments); // Angle for each segment
        float x = radius * cosf(theta); // Calculate x-coordinate
        float y = radius * sinf(theta); // Calculate y-coordinate
        glVertex2f(x + centerX, y + centerY); // Vertex for the circle's outline
    }
    glEnd();
}
void drawHalfCircleOutline(float centerX, float centerY, float radius, int numSegments)
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= numSegments / 2; i++)   // Only draw half of the circle
    {
        float theta = PI * float(i) / float(numSegments / 2);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + centerX, y + centerY);
    }
    glEnd();
}
void drawHalfCircleOutline2(float rx, float ry, float cx, float cy)
{
    int num_segments = 100; // Number of segments used to draw the outline
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= num_segments; ++i)
    {
        float theta = M_PI + (M_PI * i) / num_segments; // Angle from 180 to 360 degrees
        float x = cx + rx * cos(theta);
        float y = cy + ry * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
void drawHalfCircleOutline3(GLfloat radiusX, GLfloat radiusY, GLfloat cx, GLfloat cy)
{
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 180; i++)
    {
        float angle = i * PI / 180;
        float x = radiusX * cos(angle);
        float y = radiusY * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}
/*
void steamcircle(float radius, float cx, float cy)
{
    int num_segments = 100;
    float theta = 2.0f * 3.1415926f / float(num_segments);
    float c = cosf(theta);
    float s = sinf(theta);
    float t;
    float x = radius;
    float y = 0;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; i++)
    {
        glVertex2f(x + cx, y + cy);
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}
*/


// Function to draw a star
void drawStar(float cx, float cy, float radius) {
    //glColor3f(0.788, 0.286, 0.227); // Gold color for the star
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 10; i++) {
        float angle = i * M_PI / 5.0;
        float dx = (i % 2 == 0) ? radius * cosf(angle) : (radius / 2.0) * cosf(angle);
        float dy = (i % 2 == 0) ? radius * sinf(angle) : (radius / 2.0) * sinf(angle);
        glVertex2f(cx + dx, cy + dy);
    }
    glEnd();
}
/*// Function to draw a swim ring
void drawSwimRing(float cx, float cy, float outerRadius, float innerRadius, int segments) {
    // Draw the outer circle
    glColor3f(1, 0.894, 0.098); // Orange color
    circle360(outerRadius, segments, cx, cy);

    // Draw the inner circle with the background color to create the hole
    glColor3f(0.961, 0.757, 0.447); // Sky blue background
    circle360(innerRadius, segments, cx, cy);
}
*/

void cars()
{

    //car
    //sky car

    glPushMatrix();
    glTranslatef(carX, 0,0);

    glColor3f(1,1,1);
    circle360(3,3,230,480);
    glBegin(GL_QUADS);
    glColor3f(0.137, 0.639, 0.62);
    glVertex2i(140,470);
    glVertex2i(220,470);
    glVertex2i(210,510);
    glVertex2i(150,510);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(140,470);
    glVertex2i(220,470);
    glVertex2i(210,510);
    glVertex2i(150,510);
    glVertex2i(140,470);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.137, 0.639, 0.62);
    glVertex2i(130,470);
    glVertex2i(230,470);
    glVertex2i(230,490);
    glVertex2i(130,490);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,470);
    glVertex2i(230,470);
    glVertex2i(230,490);
    glVertex2i(130,490);
    glVertex2i(130,470);
    glEnd();

    //car window
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(152,492);
    glVertex2i(175,492);
    glVertex2i(175,505);
    glVertex2i(155,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(152,492);
    glVertex2i(175,492);
    glVertex2i(175,505);
    glVertex2i(155,505);
    glVertex2i(152,492);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(185,492);
    glVertex2i(208,492);
    glVertex2i(205,505);
    glVertex2i(185,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(185,492);
    glVertex2i(208,492);
    glVertex2i(205,505);
    glVertex2i(185,505);
    glVertex2i(185,492);
    glEnd();

    glColor3f(0,0,0);
    circle360(10,10,160,470);
    glColor3f(1,1,1);
    circle360(5,5,160,470);
    glColor3f(0,0,0);
    circle360(10,10,200,470);
    glColor3f(1,1,1);
    circle360(5,5,200,470);

    //red car

    glColor3f(1,1,1);
    circle360(3,3,350,480);
    glBegin(GL_QUADS);
    glColor3f(0.753, 0.031, 0.031);
    glVertex2i(260,470);
    glVertex2i(340,470);
    glVertex2i(330,510);
    glVertex2i(270,510);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(260,470);
    glVertex2i(340,470);
    glVertex2i(330,510);
    glVertex2i(270,510);
    glVertex2i(260,470);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.753, 0.031, 0.031);
    glVertex2i(250,470);
    glVertex2i(350,470);
    glVertex2i(350,490);
    glVertex2i(250,490);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,470);
    glVertex2i(350,470);
    glVertex2i(350,490);
    glVertex2i(250,490);
    glVertex2i(250,470);
    glEnd();


    //car window
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(272,492);
    glVertex2i(295,492);
    glVertex2i(295,505);
    glVertex2i(275,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(272,492);
    glVertex2i(295,492);
    glVertex2i(295,505);
    glVertex2i(275,505);
    glVertex2i(272,492);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(305,492);
    glVertex2i(328,492);
    glVertex2i(325,505);
    glVertex2i(305,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(305,492);
    glVertex2i(328,492);
    glVertex2i(325,505);
    glVertex2i(305,505);
    glVertex2i(305,492);
    glEnd();

    //car wheel
    //for blue car
    glColor3f(0,0,0);
    circle360(10,10,280,470);
    glColor3f(1,1,1);
    circle360(5,5,280,470);
    //for red car
    glColor3f(0,0,0);
    circle360(10,10,320,470);
    glColor3f(1,1,1);
    circle360(5,5,320,470);

    glPopMatrix();
    carX += 1.5; // Move cars to the right
    if (carX > 1000)
    {
        carX = -500;
    }
    glutPostRedisplay();
}
void schoolbus()
{

    //school bus
    glPushMatrix();
    glTranslatef(busX, 0,0);

    glBegin(GL_QUADS);
    glColor3f(0.914, 0.659, 0.078);
    glVertex2i(30,400);
    glVertex2i(180,400);
    glVertex2i(180,460);
    glVertex2i(30,460);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(30,400);
    glVertex2i(180,400);
    glVertex2i(180,460);
    glVertex2i(30,460);
    glVertex2i(30,400);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.914, 0.659, 0.078);
    glVertex2i(0,400);
    glVertex2i(30,400);
    glVertex2i(30,430);
    glVertex2i(0,430);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(0,400);
    glVertex2i(30,400);
    glVertex2i(30,430);
    glVertex2i(0,430);
    glVertex2i(0,400);
    glEnd();

    //bus window1
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex2i(10,430);
    glVertex2i(30,430);
    glVertex2i(30,452);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(10,430);
    glVertex2i(30,430);
    glVertex2i(30,452);
    glVertex2i(10,430);
    glEnd();

    //bus window2
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(70,438);
    glVertex2i(90,438);
    glVertex2i(90,452);
    glVertex2i(70,452);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(70,438);
    glVertex2i(90,438);
    glVertex2i(90,452);
    glVertex2i(70,452);
    glVertex2i(70,438);
    glEnd();
    //bus window3
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(100,438);
    glVertex2i(120,438);
    glVertex2i(120,452);
    glVertex2i(100,452);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(100,438);
    glVertex2i(120,438);
    glVertex2i(120,452);
    glVertex2i(100,452);
    glVertex2i(100,438);
    glEnd();
    //bus window4
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(130,438);
    glVertex2i(150,438);
    glVertex2i(150,452);
    glVertex2i(130,452);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,438);
    glVertex2i(150,438);
    glVertex2i(150,452);
    glVertex2i(130,452);
    glVertex2i(130,438);
    glEnd();

    //bus door
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2i(35,410);
    glVertex2i(55,410);
    glVertex2i(55,445);
    glVertex2i(35,445);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(40,410);
    glVertex2i(50,410);
    glVertex2i(50,440);
    glVertex2i(40,440);
    glEnd();
    //bus wheel
    //for outer portion black
    glColor3f(0,0,0);
    circle360(10,10,30,400);
    circle360(10,10,70,400);
    circle360(10,10,120,400);
    circle360(10,10,150,400);
    //for inner portion black
    glColor3f(1,1,1);
    circle360(5,5,30,400);
    circle360(5,5,70,400);
    circle360(5,5,120,400);
    circle360(5,5,150,400);

    //truck
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2i(800, 400);
    glVertex2i(950, 400);
    glVertex2i(950, 420);
    glVertex2i(800, 420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(800, 400);
    glVertex2i(950, 400);
    glVertex2i(950, 420);
    glVertex2i(800, 420);
    glVertex2i(800, 400);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.976, 0.718, 0.714);
    glVertex2i(855, 420);
    glVertex2i(950, 420);
    glVertex2i(950, 480);
    glVertex2i(855, 480);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(855, 420);
    glVertex2i(950, 420);
    glVertex2i(950, 480);
    glVertex2i(855, 480);
    glVertex2i(855, 420);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.129, 0.678, 0.91);
    glVertex2i(800, 420);
    glVertex2i(850, 420);
    glVertex2i(850, 460);
    glVertex2i(810, 460);
    glVertex2i(800, 415);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(800, 420);
    glVertex2i(850, 420);
    glVertex2i(850, 460);
    glVertex2i(810, 460);
    glVertex2i(800, 415);
    glVertex2i(800, 420);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(805, 420);
    glVertex2i(830, 420);
    glVertex2i(830, 447);
    glVertex2i(813, 447);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(805, 420);
    glVertex2i(830, 420);
    glVertex2i(830, 447);
    glVertex2i(813, 447);
    glVertex2i(805, 420);
    glEnd();

    glColor3f(0,0,0);
    circle360(15,15,825,400);
    circle360(15,15,875,400);
    circle360(15,15,915,400);
    glColor3f(1,1,1);
    circle360(10,10,825,400);
    circle360(10,10,875,400);
    circle360(10,10,915,400);


    glPopMatrix();
    busX -= 2.5; // Move bus to the left
    if (busX < -1000)
    {
        busX = 1000;
    }

    glutPostRedisplay();

}

void boat()
{
    glPushMatrix();
    glTranslatef(boatX, 0, 0);

    // Boat hull
    glColor3f(0.329, 0.8, 0.816);
    circle180to360(80, 50, 680, 180);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    drawHalfCircleOutline2(80, 50, 680, 180);


    // Boat body
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(600, 180);
    glVertex2i(760, 180);
    glVertex2i(760, 190);
    glVertex2i(600, 190);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(600, 180);
    glVertex2i(760, 180);
    glVertex2i(760, 190);
    glVertex2i(600, 190);
    glVertex2i(600, 180);
    glEnd();

    // Boat sails
    glBegin(GL_TRIANGLES);
    glColor3f(0.992, 0.082, 0.09);
    glVertex2i(683, 200);
    glVertex2i(683, 280);
    glVertex2i(740, 200);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(683, 200);
    glVertex2i(683, 280);
    glVertex2i(740, 200);
    glVertex2i(683, 200);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.675, 0.404);
    glVertex2i(677, 200);
    glVertex2i(677, 280);
    glVertex2i(620, 200);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(677, 200);
    glVertex2i(677, 280);
    glVertex2i(620, 200);
    glVertex2i(677, 200);
    glEnd();

    // Boat mast
    //glColor3f(0.29, 0.569, 0.894);
    //circle360(10, 40, 680, 240);

    glBegin(GL_QUADS);
    glColor3f(0.431, 0.294, 0.141);
    glVertex2i(677, 180);
    glVertex2i(683, 180);
    glVertex2i(683, 290);
    glVertex2i(677, 290);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(677, 180);
    glVertex2i(683, 180);
    glVertex2i(683, 290);
    glVertex2i(677, 290);
    glVertex2i(677, 180);
    glEnd();




    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.286, 0.502, 0.89);
    glVertex2i(560,130);
    glVertex2i(800,130);

    glVertex2i(580,120);
    glVertex2i(630,120);

    glVertex2i(650,120);
    glVertex2i(700,120);

    glVertex2i(720,120);
    glVertex2i(770,120);

    glVertex2i(610,110);
    glVertex2i(660,110);

    glVertex2i(690,110);
    glVertex2i(740,110);

    glVertex2i(620,100);
    glVertex2i(730,100);

    glEnd();
    glPopMatrix();

    // Update boat position
    boatX += boatSpeed; // Move boat based on current speed
    if (boatX > 1000 || boatX < -100)
    {
        boatSpeed = -boatSpeed; // Reverse direction
    }

    // Request to redraw the scene
    glutPostRedisplay();
}

void fish()
{

    glPushMatrix();
    glTranslatef(fishX, 0, 0);

    if (!fishFacingLeft)
    {
        glTranslatef(500, 0, 0); // Translate to pivot point
        glScalef(-1, 1, 1); // Mirror the fish along the y-axis
        glTranslatef(-500, 0, 0); // Translate back
    }
    //fish1
    glColor3f(1, 0.196, 0.204);
    circle90to270(10,15,430,40);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.196, 0.204);
    glVertex2i(430,30);
    glVertex2i(438,32);
    glVertex2i(440,22);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(430,30);
    glVertex2i(438,32);
    glVertex2i(440,22);
    glVertex2i(430,30);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.196, 0.204);
    glVertex2i(430,50);
    glVertex2i(438,48);
    glVertex2i(440,58);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(430,50);
    glVertex2i(438,48);
    glVertex2i(440,58);
    glVertex2i(430,50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.196, 0.204);
    glVertex2i(460,28);
    glVertex2i(460,52);
    glVertex2i(440,40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(460,28);
    glVertex2i(460,52);
    glVertex2i(440,40);
    glVertex2i(460,28);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.969, 0.824, 0.314);
    glVertex2i(430,28);
    glVertex2i(430,52);
    glVertex2i(450,40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(430,28);
    glVertex2i(430,52);
    glVertex2i(450,40);
    glVertex2i(430,28);
    glEnd();

    glColor3f(1,1,1);
    circle360(2,2,425,45);
    glColor3f(0,0,0);
    circle360(1,1,425,45);

    //fish2
    glColor3f(1, 0.725, 0.267);
    circle90to270(10,15,480,75);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.725, 0.267);
    glVertex2i(480,65);
    glVertex2i(480,75);
    glVertex2i(490,62);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(480,65);
    glVertex2i(480,75);
    glVertex2i(490,62);
    glVertex2i(480,65);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.725, 0.267);
    glVertex2i(480,85);
    glVertex2i(480,75);
    glVertex2i(490,88);
    glVertex2i(480,85);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(480,85);
    glVertex2i(480,75);
    glVertex2i(490,88);
    glVertex2i(480,85);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.055, 0.38, 0.569);
    glVertex2i(480,62);
    glVertex2i(480,88);
    glVertex2i(495,75);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(480,62);
    glVertex2i(480,88);
    glVertex2i(495,75);
    glVertex2i(480,62);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0.725, 0.267);
    glVertex2i(495,75);
    glVertex2i(505,65);
    glVertex2i(505,85);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(495,75);
    glVertex2i(505,65);
    glVertex2i(505,85);
    glVertex2i(495,75);
    glEnd();

    glColor3f(1,1,1);
    circle360(2,2,475,80);
    glColor3f(0,0,0);
    circle360(1,1,475,80);


    //fish3
    glColor3f(0.757, 0.29, 0.773);
    circle90to270(15,20,510,40);
    glBegin(GL_TRIANGLES);
    glColor3f(0.757, 0.29, 0.773);
    glVertex2i(510,30);
    glVertex2i(518,35);
    glVertex2i(520,20);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(510,30);
    glVertex2i(518,35);
    glVertex2i(520,20);
    glVertex2i(510,30);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.757, 0.29, 0.773);
    glVertex2i(510,50);
    glVertex2i(518,45);
    glVertex2i(520,60);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(510,50);
    glVertex2i(518,45);
    glVertex2i(520,60);
    glVertex2i(510,50);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.757, 0.29, 0.773);
    glVertex2i(540,40);
    glVertex2i(555,25);
    glVertex2i(555,55);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(540,40);
    glVertex2i(555,25);
    glVertex2i(555,55);
    glVertex2i(540,40);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.996, 0.941, 0.145);
    glVertex2i(510,25);
    glVertex2i(510,55);
    glVertex2i(540,40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(510,25);
    glVertex2i(510,55);
    glVertex2i(540,40);
    glVertex2i(510,25);
    glEnd();

    glColor3f(1,1,1);
    circle360(3,3,500,45);
    glColor3f(0,0,0);
    circle360(2,2,500,45);

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.286, 0.502, 0.89);
    glVertex2i(570,60);
    glVertex2i(620,60);

    glVertex2i(640,60);
    glVertex2i(680,60);

    glVertex2i(580,50);
    glVertex2i(640,50);

    glVertex2i(660,50);
    glVertex2i(710,50);

    glVertex2i(570,40);
    glVertex2i(630,40);

    glVertex2i(660,40);
    glVertex2i(710,40);

    glVertex2i(570,30);
    glVertex2i(620,30);

    glVertex2i(630,30);
    glVertex2i(680,30);

    glEnd();

    glPopMatrix();
// Update fish position
    fishX += fishSpeed;
    if (fishX > 1000)
    {
        fishSpeed = -fishSpeed;
        fishFacingLeft = true; // Fish is now facing right
    }
    else if (fishX < -100)
    {
        fishSpeed = -fishSpeed;
        fishFacingLeft = false; // Fish is now facing left
    }

    // Request to redraw the scene
    glutPostRedisplay();

}

void cloud1()
{
    //cloud
    glPushMatrix();
    glTranslatef(cloud1X, 0,0);
    glColor3f(1,1,1);
    //cloud 1
    circle360(50,40,80,850);
    circle360(50,40,120,850);
    circle360(40,40,100,830);
    circle360(40,40,100,870);
    glPopMatrix();
    cloud1X += 0.30f; // Move cars to the right
    if (cloud1X > 1000.0f)
    {
        cloud1X = -500.0f;
    }
    glutPostRedisplay();
}

void cloud2()
{

    glPushMatrix();
    glTranslatef(cloud2X, 0,0);
    //cloud2
    glColor3f(1,1,1);
    circle360(40,30,310,900);
    circle360(40,30,390,900);
    circle360(30,30,350,930);
    circle360(30,30,350,870);
    circle360(30,30,320,880);
    circle360(30,30,370,930);
    circle360(30,30,370,880);
    circle360(30,30,320,930);
    //cloud 3
    circle360(50,40,530,830);
    circle360(50,40,570,830);
    circle360(40,40,550,810);
    circle360(40,40,550,850);

    glPopMatrix();
    cloud2X -= 0.30f; // Move bus to the left
    if (cloud2X < -1000.0f)
    {
        cloud2X = 1000.0f;
    }

    glutPostRedisplay();

}
void bird()
{
    //bird

    glPushMatrix();
    glTranslatef(birdX, 0,0);

    glBegin(GL_QUADS);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(810,780);
    glVertex2f(820,780);
    glVertex2f(820,790);
    glVertex2f(810,790);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(840,790);
    glVertex2f(850,790);
    glVertex2f(850,800);
    glVertex2f(840,800);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(820,810);
    glVertex2f(830,810);
    glVertex2f(830,820);
    glVertex2f(820,820);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(850,820);
    glVertex2f(860,820);
    glVertex2f(860,830);
    glVertex2f(850,830);
    glEnd();

    glLineWidth(3.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(800,780);
    glVertex2f(820,780);
    glVertex2f(820,780);
    glVertex2f(820,800);

    glVertex2f(830,790);
    glVertex2f(850,790);
    glVertex2f(850,790);
    glVertex2f(850,810);

    glVertex2f(810,810);
    glVertex2f(830,810);
    glVertex2f(830,810);
    glVertex2f(830,830);

    glVertex2f(840,820);
    glVertex2f(860,820);
    glVertex2f(860,820);
    glVertex2f(860,840);

    glEnd();

    glPopMatrix();
    birdX -= 2; // Move bus to the left
    if (birdX < -900)
    {
        birdX = 1000;
    }

    glutPostRedisplay();

}
void plane()
{
    glPushMatrix();
    glTranslatef(planeX, 0, 0);

    if (planeFacingRight)
    {
        glTranslatef(110, 0, 0); // Translate to pivot point
        glScalef(-1, 1, 1); // Mirror the plane along the y-axis
        glTranslatef(-110, 0, 0); // Translate back
    }

    //plane
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.271, 0.741, 0.929);
    glVertex2i(0,950);
    glVertex2i(80,950);

    glVertex2i(-30,940);
    glVertex2i(30,940);

    glVertex2i(-40,930);
    glVertex2i(20,930);

    glVertex2i(-30,920);
    glVertex2i(30,920);

    glVertex2i(-40,910);
    glVertex2i(20,910);

    glVertex2i(-30,900);
    glVertex2i(30,900);

    glVertex2i(10,890);
    glVertex2i(80,890);

    glVertex2i(-20,880);
    glVertex2i(90,880);

    glEnd();

    glLineWidth(2.0);

    glColor3f(0.867, 0.149, 0.224);
    circle360(40,18,140,915);
    glColor3f(0,0,0);
    drawCircleOutline1(40,18,140,915);

    glBegin(GL_QUADS);
    glColor3f(0.047, 0.369, 0.576);
    glVertex2i(100,930);
    glVertex2i(130,940);
    glVertex2i(90,970);
    glVertex2i(80,960);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(100,930);
    glVertex2i(130,940);
    glVertex2i(90,970);
    glVertex2i(80,960);
    glVertex2i(100,930);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.867, 0.149, 0.224);
    glVertex2i(50,900);
    glVertex2i(170,900);
    glVertex2i(130,950);
    glVertex2i(50,930);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(170,900);
    glVertex2i(50,900);
    glVertex2i(50,930);
    glVertex2i(130,950);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.867, 0.149, 0.224);
    glVertex2i(50,900);
    glVertex2i(40,900);
    glVertex2i(20,930);
    glVertex2i(40,940);
    glVertex2i(50,930);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(50,900);
    glVertex2i(40,900);
    glVertex2i(20,930);
    glVertex2i(40,940);
    glVertex2i(50,930);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.047, 0.369, 0.576);
    glVertex2i(100,900);
    glVertex2i(150,900);
    glVertex2i(110,860);
    glVertex2i(90,860);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(100,900);
    glVertex2i(150,900);
    glVertex2i(110,860);
    glVertex2i(90,860);
    glVertex2i(100,900);
    glEnd();



    glColor3f(1,1,1);
    circle0to160(15,20,130,930);
    circle360(5,5,70,920);
    circle360(5,5,90,920);
    circle360(5,5,110,920);


    glPopMatrix();
// Update plane position
    planeX += planeSpeed;
    if (planeX > 1000)
    {
        planeSpeed = -planeSpeed;
        planeFacingRight = true; // Plane is now facing right
    }
    else if (planeX < -300)
    {
        planeSpeed = -planeSpeed;
        planeFacingRight = false; // Plane is now facing left
    }

    // Request to redraw the scene
    glutPostRedisplay();
}

















void cars1()
{

    //car



    //sky car

    glPushMatrix();
    glTranslatef(carX, 0,0);

    //carlight

    glBegin(GL_TRIANGLES);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(220, 480);
glVertex2i(250, 470);
glVertex2i(250, 490);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(340, 480);
glVertex2i(380, 470);
glVertex2i(380, 490);
glEnd();


glColor3f(0.667, 0.667, 0.667); // Darkened color for white
circle360(3, 3, 230, 480);

glBegin(GL_QUADS);
glColor3f(0.055, 0.255, 0.247); // Darkened color for blue
glVertex2i(140, 470);
glVertex2i(220, 470);
glVertex2i(210, 510);
glVertex2i(150, 510);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(140, 470);
glVertex2i(220, 470);
glVertex2i(210, 510);
glVertex2i(150, 510);
glVertex2i(140, 470);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.055, 0.255, 0.247); // Darkened color for blue
glVertex2i(130, 470);
glVertex2i(230, 470);
glVertex2i(230, 490);
glVertex2i(130, 490);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 470);
glVertex2i(230, 470);
glVertex2i(230, 490);
glVertex2i(130, 490);
glVertex2i(130, 470);
glEnd();

// Car window
glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(152, 492);
glVertex2i(175, 492);
glVertex2i(175, 505);
glVertex2i(155, 505);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(152, 492);
glVertex2i(175, 492);
glVertex2i(175, 505);
glVertex2i(155, 505);
glVertex2i(152, 492);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(185, 492);
glVertex2i(208, 492);
glVertex2i(205, 505);
glVertex2i(185, 505);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(185, 492);
glVertex2i(208, 492);
glVertex2i(205, 505);
glVertex2i(185, 505);
glVertex2i(185, 492);
glEnd();

glColor3f(0, 0, 0);
circle360(10, 10, 160, 470);
glColor3f(0.667, 0.667, 0.667); // Darkened color for white
circle360(5, 5, 160, 470);
glColor3f(0, 0, 0);
circle360(10, 10, 200, 470);
glColor3f(0.667, 0.667, 0.667); // Darkened color for white
circle360(5, 5, 200, 470);

// Red car
glColor3f(0.667, 0.667, 0.667); // Darkened color for white
circle360(3, 3, 350, 480);
glBegin(GL_QUADS);
glColor3f(0.482, 0.015, 0.015); // Darkened color for red
glVertex2i(260, 470);
glVertex2i(340, 470);
glVertex2i(330, 510);
glVertex2i(270, 510);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(260, 470);
glVertex2i(340, 470);
glVertex2i(330, 510);
glVertex2i(270, 510);
glVertex2i(260, 470);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.482, 0.015, 0.015);
    glVertex2i(250,470);
    glVertex2i(350,470);
    glVertex2i(350,490);
    glVertex2i(250,490);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,470);
    glVertex2i(350,470);
    glVertex2i(350,490);
    glVertex2i(250,490);
    glVertex2i(250,470);
    glEnd();


    //car window
    glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
    glVertex2i(272,492);
    glVertex2i(295,492);
    glVertex2i(295,505);
    glVertex2i(275,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(272,492);
    glVertex2i(295,492);
    glVertex2i(295,505);
    glVertex2i(275,505);
    glVertex2i(272,492);
    glEnd();

    glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
    glVertex2i(305,492);
    glVertex2i(328,492);
    glVertex2i(325,505);
    glVertex2i(305,505);
    glEnd();
    glLineWidth(1.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(305,492);
    glVertex2i(328,492);
    glVertex2i(325,505);
    glVertex2i(305,505);
    glVertex2i(305,492);
    glEnd();

    //car wheel
    //for blue car
    glColor3f(0,0,0);
    circle360(10,10,280,470);
    glColor3f(1,1,1);
    circle360(5,5,280,470);
    //for red car
    glColor3f(0,0,0);
    circle360(10,10,320,470);
    glColor3f(1,1,1);
    circle360(5,5,320,470);

    glPopMatrix();
    carX += 2; // Move cars to the right
    if (carX > 1000)
    {
        carX = -500;
    }
    glutPostRedisplay();
}
void schoolbus1()
{

    //school bus
    glPushMatrix();
    glTranslatef(busX, 0,0);

    //buslight

    glBegin(GL_TRIANGLES);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(5, 415);
glVertex2i(-35, 425);
glVertex2i(-35, 405);
glEnd();


glBegin(GL_QUADS);
glColor3f(0.471, 0.337, 0.039); // Darkened color
glVertex2i(30, 400);
glVertex2i(180, 400);
glVertex2i(180, 460);
glVertex2i(30, 460);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(30, 400);
glVertex2i(180, 400);
glVertex2i(180, 460);
glVertex2i(30, 460);
glVertex2i(30, 400);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.471, 0.337, 0.039); // Darkened color
glVertex2i(0, 400);
glVertex2i(30, 400);
glVertex2i(30, 430);
glVertex2i(0, 430);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(0, 400);
glVertex2i(30, 400);
glVertex2i(30, 430);
glVertex2i(0, 430);
glVertex2i(0, 400);
glEnd();

// Bus window 1
glBegin(GL_TRIANGLES);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(10, 430);
glVertex2i(30, 430);
glVertex2i(30, 452);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(10, 430);
glVertex2i(30, 430);
glVertex2i(30, 452);
glVertex2i(10, 430);
glEnd();

// Bus window 2
glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(70, 438);
glVertex2i(90, 438);
glVertex2i(90, 452);
glVertex2i(70, 452);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(70, 438);
glVertex2i(90, 438);
glVertex2i(90, 452);
glVertex2i(70, 452);
glVertex2i(70, 438);
glEnd();
// Bus window 3
glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(100, 438);
glVertex2i(120, 438);
glVertex2i(120, 452);
glVertex2i(100, 452);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(100, 438);
glVertex2i(120, 438);
glVertex2i(120, 452);
glVertex2i(100, 452);
glVertex2i(100, 438);
glEnd();
// Bus window 4
glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(130, 438);
glVertex2i(150, 438);
glVertex2i(150, 452);
glVertex2i(130, 452);
glEnd();
glLineWidth(1.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 438);
glVertex2i(150, 438);
glVertex2i(150, 452);
glVertex2i(130, 452);
glVertex2i(130, 438);
glEnd();

// Bus door
glBegin(GL_QUADS);
glColor3f(0, 0, 0); // Dark color for door
glVertex2i(35, 410);
glVertex2i(55, 410);
glVertex2i(55, 445);
glVertex2i(35, 445);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(40, 410);
glVertex2i(50, 410);
glVertex2i(50, 440);
glVertex2i(40, 440);
glEnd();

// Bus wheel
glColor3f(0, 0, 0);
circle360(10, 10, 30, 400);
circle360(10, 10, 70, 400);
circle360(10, 10, 120, 400);
circle360(10, 10, 150, 400);
glColor3f(0.667, 0.667, 0.667); // Darkened color for white
circle360(5, 5, 30, 400);
circle360(5, 5, 70, 400);
circle360(5, 5, 120, 400);
circle360(5, 5, 150, 400);

    // Truck

    //trucklight
glBegin(GL_TRIANGLES);
glColor3f(0.878, 0.863, 0.698); // Light yellow
glVertex2i(805, 415);
glVertex2i(765, 425);
glVertex2i(765, 405);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.2, 0.2, 0.2); // Darkened color for truck body
glVertex2i(800, 400);
glVertex2i(950, 400);
glVertex2i(950, 420);
glVertex2i(800, 420);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(800, 400);
glVertex2i(950, 400);
glVertex2i(950, 420);
glVertex2i(800, 420);
glVertex2i(800, 400);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.686, 0.5, 0.497); // Darkened color for truck cabin
glVertex2i(855, 420);
glVertex2i(950, 420);
glVertex2i(950, 480);
glVertex2i(855, 480);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(855, 420);
glVertex2i(950, 420);
glVertex2i(950, 480);
glVertex2i(855, 480);
glVertex2i(855, 420);
glEnd();


glBegin(GL_POLYGON);
glColor3f(0.071, 0.386, 0.52); // Darkened color for truck trailer
glVertex2i(800, 420);
glVertex2i(850, 420);
glVertex2i(850, 460);
glVertex2i(810, 460);
glVertex2i(800, 415);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(800, 420);
glVertex2i(850, 420);
glVertex2i(850, 460);
glVertex2i(810, 460);
glVertex2i(800, 415);
glVertex2i(800, 420);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.878, 0.863, 0.698); // Light yellow
// Darkened color for window
glVertex2i(805, 420);
glVertex2i(830, 420);
glVertex2i(830, 447);
glVertex2i(813, 447);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(805, 420);
glVertex2i(830, 420);
glVertex2i(830, 447);
glVertex2i(813, 447);
glVertex2i(805, 420);
glEnd();

glColor3f(0, 0, 0);
circle360(15, 15, 825, 400); // Darkened color for wheels
circle360(15, 15, 875, 400);
circle360(15, 15, 915, 400);
glColor3f(0.8, 0.8, 0.8); // Darkened color for wheel hub
circle360(10, 10, 825, 400);
circle360(10, 10, 875, 400);
circle360(10, 10, 915, 400);

    glPopMatrix();
    busX -= 2; // Move bus to the left
    if (busX < -1000)
    {
        busX = 1000;
    }

    glutPostRedisplay();

}

void boat1()
{
    glPushMatrix();
    glTranslatef(boatX, 0, 0);

    // Boat hull
glColor3f(0.129, 0.314, 0.322); // Darkened color for hull
circle180to360(80, 50, 680, 180);
glLineWidth(2.0);
glColor3f(0, 0, 0);
drawHalfCircleOutline2(80, 50, 680, 180);

// Boat body
glBegin(GL_QUADS);
glColor3f(0.8, 0.8, 0.8); // Lightened color for body
glVertex2i(600, 180);
glVertex2i(760, 180);
glVertex2i(760, 190);
glVertex2i(600, 190);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(600, 180);
glVertex2i(760, 180);
glVertex2i(760, 190);
glVertex2i(600, 190);
glVertex2i(600, 180);
glEnd();

// Boat sails
glBegin(GL_TRIANGLES);
glColor3f(0.749, 0.063, 0.07); // Darkened color for sails
glVertex2i(683, 200);
glVertex2i(683, 280);
glVertex2i(740, 200);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(683, 200);
glVertex2i(683, 280);
glVertex2i(740, 200);
glVertex2i(683, 200);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.8, 0.54, 0.322); // Darkened color for sails
glVertex2i(677, 200);
glVertex2i(677, 280);
glVertex2i(620, 200);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(677, 200);
glVertex2i(677, 280);
glVertex2i(620, 200);
glVertex2i(677, 200);
glEnd();

// Boat mast
glBegin(GL_QUADS);
glColor3f(0.215, 0.147, 0.069); // Darkened color for mast
glVertex2i(677, 180);
glVertex2i(683, 180);
glVertex2i(683, 290);
glVertex2i(677, 290);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(677, 180);
glVertex2i(683, 180);
glVertex2i(683, 290);
glVertex2i(677, 290);
glVertex2i(677, 180);
glEnd();

// Waves
glLineWidth(4.0);
glBegin(GL_LINES);
glColor3f(0.057, 0.1, 0.178); // Darkened color for waves
glVertex2i(560, 130);
glVertex2i(800, 130);

glVertex2i(580, 120);
glVertex2i(630, 120);

glVertex2i(650, 120);
glVertex2i(700, 120);

glVertex2i(720, 120);
glVertex2i(770, 120);

glVertex2i(610, 110);
glVertex2i(660, 110);

glVertex2i(690, 110);
glVertex2i(740, 110);

glVertex2i(620, 100);
glVertex2i(730, 100);
glEnd();

    glPopMatrix();

    // Update boat position
    boatX += boatSpeed; // Move boat based on current speed
    if (boatX > 1000 || boatX < -100)
    {
        boatSpeed = -boatSpeed; // Reverse direction
    }

    // Request to redraw the scene
    glutPostRedisplay();
}

void fish1()
{

    glPushMatrix();
    glTranslatef(fishX, 0, 0);

    if (!fishFacingLeft)
    {
        glTranslatef(500, 0, 0); // Translate to pivot point
        glScalef(-1, 1, 1); // Mirror the fish along the y-axis
        glTranslatef(-500, 0, 0); // Translate back
    }
    // Fish body
glColor3f(0.545, 0.106, 0.110); // Darkened color for fish body
circle90to270(10, 15, 430, 40);

// Fish fins
glBegin(GL_TRIANGLES);
glColor3f(0.545, 0.106, 0.110); // Darkened color for fins
glVertex2i(430, 30);
glVertex2i(438, 32);
glVertex2i(440, 22);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(430, 30);
glVertex2i(438, 32);
glVertex2i(440, 22);
glVertex2i(430, 30);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.545, 0.106, 0.110); // Darkened color for fins
glVertex2i(430, 50);
glVertex2i(438, 48);
glVertex2i(440, 58);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(430, 50);
glVertex2i(438, 48);
glVertex2i(440, 58);
glVertex2i(430, 50);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.545, 0.106, 0.110); // Darkened color for fins
glVertex2i(460, 28);
glVertex2i(460, 52);
glVertex2i(440, 40);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(460, 28);
glVertex2i(460, 52);
glVertex2i(440, 40);
glVertex2i(460, 28);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.522, 0.318, 0.127); // Darkened color for fins
glVertex2i(430, 28);
glVertex2i(430, 52);
glVertex2i(450, 40);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(430, 28);
glVertex2i(430, 52);
glVertex2i(450, 40);
glVertex2i(430, 28);
glEnd();

// Eye
glColor3f(0.4, 0.4, 0.4); // Darkened color for eye
circle360(2, 2, 425, 45);
glColor3f(0, 0, 0);
circle360(1, 1, 425, 45);
// Fish body
glColor3f(0.467, 0.302, 0.157); // Darkened color for fish body
circle90to270(10, 15, 480, 75);

// Fish fins
glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.302, 0.157); // Darkened color for fins
glVertex2i(480, 65);
glVertex2i(480, 75);
glVertex2i(490, 62);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(480, 65);
glVertex2i(480, 75);
glVertex2i(490, 62);
glVertex2i(480, 65);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.302, 0.157); // Darkened color for fins
glVertex2i(480, 85);
glVertex2i(480, 75);
glVertex2i(490, 88);
glVertex2i(480, 85);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(480, 85);
glVertex2i(480, 75);
glVertex2i(490, 88);
glVertex2i(480, 85);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.039, 0.235, 0.349); // Darkened color for fins
glVertex2i(480, 62);
glVertex2i(480, 88);
glVertex2i(495, 75);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(480, 62);
glVertex2i(480, 88);
glVertex2i(495, 75);
glVertex2i(480, 62);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.302, 0.157); // Darkened color for fins
glVertex2i(495, 75);
glVertex2i(505, 65);
glVertex2i(505, 85);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(495, 75);
glVertex2i(505, 65);
glVertex2i(505, 85);
glVertex2i(495, 75);
glEnd();

// Eye
glColor3f(0.4, 0.4, 0.4); // Darkened color for eye
circle360(2, 2, 475, 80);
glColor3f(0, 0, 0);
circle360(1, 1, 475, 80);

// Fish body
glColor3f(0.467, 0.18, 0.467); // Darkened color for fish body
circle90to270(15, 20, 510, 40);

// Fish fins
glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.18, 0.467); // Darkened color for fins
glVertex2i(510, 30);
glVertex2i(518, 35);
glVertex2i(520, 20);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(510, 30);
glVertex2i(518, 35);
glVertex2i(520, 20);
glVertex2i(510, 30);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.18, 0.467); // Darkened color for fins
glVertex2i(510, 50);
glVertex2i(518, 45);
glVertex2i(520, 60);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(510, 50);
glVertex2i(518, 45);
glVertex2i(520, 60);
glVertex2i(510, 50);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.467, 0.18, 0.467); // Darkened color for fins
glVertex2i(540, 40);
glVertex2i(555, 25);
glVertex2i(555, 55);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(540, 40);
glVertex2i(555, 25);
glVertex2i(555, 55);
glVertex2i(540, 40);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.863, 0.812, 0.106); // Darkened color for fins
glVertex2i(510, 25);
glVertex2i(510, 55);
glVertex2i(540, 40);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(510, 25);
glVertex2i(510, 55);
glVertex2i(540, 40);
glVertex2i(510, 25);
glEnd();

// Eye
glColor3f(1, 1, 1); // Adjusted color for eye
circle360(3, 3, 500, 45);
glColor3f(0, 0, 0);
circle360(2, 2, 500, 45);

// Fish lines
glLineWidth(4.0);
glBegin(GL_LINES);
glColor3f(0.057, 0.1, 0.178); // Adjusted color for lines
glVertex2i(570, 60);
glVertex2i(620, 60);

glVertex2i(640, 60);
glVertex2i(680, 60);

glVertex2i(580, 50);
glVertex2i(640, 50);

glVertex2i(660, 50);
glVertex2i(710, 50);

glVertex2i(570, 40);
glVertex2i(630, 40);

glVertex2i(660, 40);
glVertex2i(710, 40);

glVertex2i(570, 30);
glVertex2i(620, 30);

glVertex2i(630, 30);
glVertex2i(680, 30);
glEnd();


    glPopMatrix();
// Update fish position
    fishX += fishSpeed;
    if (fishX > 1000)
    {
        fishSpeed = -fishSpeed;
        fishFacingLeft = true; // Fish is now facing right
    }
    else if (fishX < -100)
    {
        fishSpeed = -fishSpeed;
        fishFacingLeft = false; // Fish is now facing left
    }

    // Request to redraw the scene
    glutPostRedisplay();

}


void bird1()
{
    //bird

    glPushMatrix();
    glTranslatef(birdX, 0,0);

    glBegin(GL_QUADS);
glColor3f(0.055, 0.055, 0.055); // Dark gray
glVertex2f(810,780);
glVertex2f(820,780);
glVertex2f(820,790);
glVertex2f(810,790);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.055, 0.055, 0.055); // Dark gray
glVertex2f(840,790);
glVertex2f(850,790);
glVertex2f(850,800);
glVertex2f(840,800);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.055, 0.055, 0.055); // Dark gray
glVertex2f(820,810);
glVertex2f(830,810);
glVertex2f(830,820);
glVertex2f(820,820);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.055, 0.055, 0.055); // Dark gray
glVertex2f(850,820);
glVertex2f(860,820);
glVertex2f(860,830);
glVertex2f(850,830);
glEnd();

glLineWidth(3.0);
glBegin(GL_LINES);

glColor3f(0.055, 0.055, 0.055); // Dark gray
glVertex2f(800,780);
glVertex2f(820,780);
glVertex2f(820,780);
glVertex2f(820,800);

glVertex2f(830,790);
glVertex2f(850,790);
glVertex2f(850,790);
glVertex2f(850,810);

glVertex2f(810,810);
glVertex2f(830,810);
glVertex2f(830,810);
glVertex2f(830,830);

glVertex2f(840,820);
glVertex2f(860,820);
glVertex2f(860,820);
glVertex2f(860,840);



    glEnd();

    glPopMatrix();
    birdX -= 0.35f; // Move bus to the left
    if (birdX < -900)
    {
        birdX = 1000.0f;
    }

    glutPostRedisplay();

}
void plane1()
{
    glPushMatrix();
    glTranslatef(planeX, 0, 0);

    if (planeFacingRight)
    {
        glTranslatef(110, 0, 0); // Translate to pivot point
        glScalef(-1, 1, 1); // Mirror the plane along the y-axis
        glTranslatef(-110, 0, 0); // Translate back
    }

    //plane
    glLineWidth(3.0);
glBegin(GL_LINES);
glColor3f(0.024, 0.298, 0.365); // Dark blue-green
glVertex2i(0,950);
glVertex2i(80,950);

glVertex2i(-30,940);
glVertex2i(30,940);

glVertex2i(-40,930);
glVertex2i(20,930);

glVertex2i(-30,920);
glVertex2i(30,920);

glVertex2i(-40,910);
glVertex2i(20,910);

glVertex2i(-30,900);
glVertex2i(30,900);

glVertex2i(10,890);
glVertex2i(80,890);

glVertex2i(-20,880);
glVertex2i(90,880);

glEnd();

glLineWidth(2.0);

glColor3f(0.635, 0.063, 0.122); // Dark red
circle360(40,18,140,915);
glColor3f(0,0,0);
drawCircleOutline1(40,18,140,915);

glBegin(GL_QUADS);
glColor3f(0.024, 0.290, 0.451); // Dark blue
glVertex2i(100,930);
glVertex2i(130,940);
glVertex2i(90,970);
glVertex2i(80,960);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(100,930);
glVertex2i(130,940);
glVertex2i(90,970);
glVertex2i(80,960);
glVertex2i(100,930);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.635, 0.063, 0.122); // Dark red
glVertex2i(50,900);
glVertex2i(170,900);
glVertex2i(130,950);
glVertex2i(50,930);
glEnd();

glLineWidth(2.0);
glBegin(GL_LINES);
glColor3f(0,0,0);
glVertex2i(170,900);
glVertex2i(50,900);
glVertex2i(50,930);
glVertex2i(130,950);
glEnd();


glBegin(GL_POLYGON);
glColor3f(0.635, 0.063, 0.122); // Dark red
glVertex2i(50,900);
glVertex2i(40,900);
glVertex2i(20,930);
glVertex2i(40,940);
glVertex2i(50,930);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(50,900);
glVertex2i(40,900);
glVertex2i(20,930);
glVertex2i(40,940);
glVertex2i(50,930);
glEnd();


glBegin(GL_QUADS);
glColor3f(0.024, 0.290, 0.451); // Dark blue
glVertex2i(100,900);
glVertex2i(150,900);
glVertex2i(110,860);
glVertex2i(90,860);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(100,900);
glVertex2i(150,900);
glVertex2i(110,860);
glVertex2i(90,860);
glVertex2i(100,900);
glEnd();



glColor3f(0.878, 0.863, 0.698); // Light yellow
circle0to160(15,20,130,930);
circle360(5,5,70,920);
circle360(5,5,90,920);
circle360(5,5,110,920);

    glPopMatrix();
// Update plane position
    planeX += planeSpeed;
    if (planeX > 1000)
    {
        planeSpeed = -planeSpeed;
        planeFacingRight = true; // Plane is now facing right
    }
    else if (planeX < -200)
    {
        planeSpeed = -planeSpeed;
        planeFacingRight = false; // Plane is now facing left
    }

    // Request to redraw the scene
    glutPostRedisplay();
}





void scenary2()
{
 glBegin(GL_QUADS);
    glColor3f(0.008, 0.161, 0.024); // Dark green
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 560);
    glVertex2i(0, 560);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0.1, 0.1, 0.1); // Dark gray
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 560);
    glVertex2i(0, 560);
    glEnd();

    // SKY
    glBegin(GL_QUADS);
    glColor3f(0.004, 0.078, 0.212); // Dark blue
    glVertex2i(0, 560);
    glVertex2i(1000, 560);
    glVertex2i(1000, 1000);
    glVertex2i(0, 1000);
    glEnd();

    //moon

    glColor3f(0.988, 0.882, 0.4);
    circle360(40,40,850,820);
    glColor3f(0.004, 0.078, 0.212);
    circle360(40,40,870,840);


    glColor3f(0.988, 0.882, 0.4);
    drawStar(50,900,5);
    drawStar(40,950,10);
    drawStar(70,980,5);

    drawStar(450,950,5);
    drawStar(350,880,7);
    drawStar(470,980,5);

    drawStar(240,900,5);
    drawStar(640,950,3);
    drawStar(880,850,5);

    drawStar(900,700,3);
    drawStar(700,750,3);

    plane1();

    bird1();





    //plane

//tree1
//green circle
glColor3f(0.043, 0.106, 0.011); // Darker green
circle360(32, 32, 30, 710);
circle360(32, 32, 10, 690);
circle360(40, 40, 10, 730);

glColor3f(0.035, 0.153, 0.008); // Even darker green
circle360(25, 25, 30, 710);
circle360(25, 25, 10, 690);
circle360(30, 30, 10, 730);

glBegin(GL_POLYGON);
glColor3f(0.306, 0.208, 0.123); // Dark brown
glVertex2i(20, 600);
glVertex2i(20, 700);
glVertex2i(30, 710);
glVertex2i(30, 720);
glVertex2i(10, 700);
glVertex2i(0, 710);
glVertex2i(0, 600);
glEnd();

//tree2
glColor3f(0.043, 0.106, 0.011); // Darker green
circle360(40, 40, 280, 720);
circle360(40, 40, 210, 720);
circle360(50, 70, 245, 730);
circle360(30, 30, 260, 690);
circle360(30, 30, 230, 690);
circle360(20, 20, 210, 750);
circle360(20, 20, 280, 750);

glColor3f(0.035, 0.153, 0.008); // Even darker green
circle360(35, 35, 280, 720);
circle360(35, 35, 210, 720);
circle360(45, 65, 245, 730);
circle360(25, 25, 260, 690);
circle360(25, 25, 230, 690);
circle360(15, 15, 210, 750);
circle360(15, 15, 280, 750);

glBegin(GL_POLYGON);
glColor3f(0.306, 0.208, 0.123); // Dark brown
glVertex2i(230, 600);
glVertex2i(260, 600);
glVertex2i(260, 700);
glVertex2i(270, 710);
glVertex2i(270, 720);
glVertex2i(245, 700);
glVertex2i(220, 720);
glVertex2i(220, 710);
glVertex2i(230, 700);
glEnd();

//tree3
glColor3f(0.043, 0.106, 0.011); // Darker green
circle360(40, 40, 560, 720);
circle360(40, 40, 490, 720);
circle360(50, 70, 525, 730);
circle360(30, 30, 510, 680);
circle360(30, 30, 540, 680);
circle360(20, 20, 490, 750);
circle360(20, 20, 560, 750);

glColor3f(0.035, 0.153, 0.008); // Even darker green
circle360(35, 35, 560, 720);
circle360(35, 35, 490, 720);
circle360(45, 65, 525, 730);
circle360(25, 25, 510, 680);
circle360(25, 25, 540, 680);
circle360(15, 15, 490, 750);
circle360(15, 15, 560, 750);

glBegin(GL_POLYGON);
glColor3f(0.306, 0.208, 0.123); // Dark brown
glVertex2i(510, 600);
glVertex2i(540, 600);
glVertex2i(540, 700);
glVertex2i(550, 710);
glVertex2i(550, 720);
glVertex2i(525, 700);
glVertex2i(500, 720);
glVertex2i(500, 710);
glVertex2i(510, 700);
glEnd();


//HOUSE1



    glBegin(GL_QUADS);
    glColor3f(0.122, 0.149, 0.157);
    glVertex2i(180,560);
    glVertex2i(290,560);
    glVertex2i(290,660);
    glVertex2i(180,660);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(270,600);
    glVertex2i(280,600);
    glVertex2i(280,610);
    glVertex2i(270,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(270,620);
    glVertex2i(280,620);
    glVertex2i(280,630);
    glVertex2i(270,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(270,640);
    glVertex2i(280,640);
    glVertex2i(280,650);
    glVertex2i(270,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(250,600);
    glVertex2i(260,600);
    glVertex2i(260,610);
    glVertex2i(250,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(250,620);
    glVertex2i(260,620);
    glVertex2i(260,630);
    glVertex2i(250,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(250,640);
    glVertex2i(260,640);
    glVertex2i(260,650);
    glVertex2i(250,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(210,580);
    glVertex2i(220,580);
    glVertex2i(220,590);
    glVertex2i(210,590);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(210,600);
    glVertex2i(220,600);
    glVertex2i(220,610);
    glVertex2i(210,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(210,620);
    glVertex2i(220,620);
    glVertex2i(220,630);
    glVertex2i(210,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(210,640);
    glVertex2i(220,640);
    glVertex2i(220,650);
    glVertex2i(210,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(210,560);
    glVertex2i(220,560);
    glVertex2i(220,570);
    glVertex2i(210,570);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(190,580);
    glVertex2i(200,580);
    glVertex2i(200,590);
    glVertex2i(190,590);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(190,600);
    glVertex2i(200,600);
    glVertex2i(200,610);
    glVertex2i(190,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(190,620);
    glVertex2i(200,620);
    glVertex2i(200,630);
    glVertex2i(190,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(190,640);
    glVertex2i(200,640);
    glVertex2i(200,650);
    glVertex2i(190,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(190,560);
    glVertex2i(200,560);
    glVertex2i(200,570);
    glVertex2i(190,570);
    glEnd();


    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(180,560);
    glVertex2f(180,660);

    glVertex2f(180,660);
    glVertex2f(290,660);

    glVertex2f(290,660);
    glVertex2f(290,560);

    glVertex2f(290,560);
    glVertex2f(180,560);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(230,580);
    glVertex2i(240,580);
    glVertex2i(240,610);
    glVertex2i(230,610);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(230,620);
    glVertex2i(240,620);
    glVertex2i(240,650);
    glVertex2i(230,650);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(230,580);
    glVertex2i(240,580);
    glVertex2i(240,610);
    glVertex2i(230,610);
    glVertex2i(230,580);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(230,620);
    glVertex2i(240,620);
    glVertex2i(240,650);
    glVertex2i(230,650);
    glVertex2i(230,620);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,600);
    glVertex2i(280,600);
    glVertex2i(280,610);
    glVertex2i(270,610);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,620);
    glVertex2i(280,620);
    glVertex2i(280,630);
    glVertex2i(270,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,640);
    glVertex2i(280,640);
    glVertex2i(280,650);
    glVertex2i(270,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,600);
    glVertex2i(260,600);
    glVertex2i(260,610);
    glVertex2i(250,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,620);
    glVertex2i(260,620);
    glVertex2i(260,630);
    glVertex2i(250,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,640);
    glVertex2i(260,640);
    glVertex2i(260,650);
    glVertex2i(250,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,580);
    glVertex2i(220,580);
    glVertex2i(220,590);
    glVertex2i(210,590);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,600);
    glVertex2i(220,600);
    glVertex2i(220,610);
    glVertex2i(210,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,620);
    glVertex2i(220,620);
    glVertex2i(220,630);
    glVertex2i(210,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,640);
    glVertex2i(220,640);
    glVertex2i(220,650);
    glVertex2i(210,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,560);
    glVertex2i(220,560);
    glVertex2i(220,570);
    glVertex2i(210,570);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,580);
    glVertex2i(200,580);
    glVertex2i(200,590);
    glVertex2i(190,590);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,600);
    glVertex2i(200,600);
    glVertex2i(200,610);
    glVertex2i(190,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,620);
    glVertex2i(200,620);
    glVertex2i(200,630);
    glVertex2i(190,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,640);
    glVertex2i(200,640);
    glVertex2i(200,650);
    glVertex2i(190,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,560);
    glVertex2i(200,560);
    glVertex2i(200,570);
    glVertex2i(190,570);
    glEnd();



    //house 2

//base
    glBegin(GL_QUADS);
    glColor3f(0.678, 0.663, 0.498);
    glVertex2i(80,560);
    glVertex2i(180,560);
    glVertex2i(180,620);
    glVertex2i(80,620);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.678, 0.663, 0.498);
    glVertex2i(80,640);
    glVertex2i(180,640);
    glVertex2i(180,680);
    glVertex2i(80,680);
    glEnd();

//roof

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(80,620);
    glVertex2i(200, 620);
    glVertex2i(180, 640);
    glVertex2i(80, 640);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(60,680);
    glVertex2i(200,680);
    glVertex2i(180,700);
    glVertex2i(80,700);
    glEnd();

//window
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(100,650);
    glVertex2i(120,650);
    glVertex2i(120,670);
    glVertex2i(100,670);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(140,650);
    glVertex2i(160,650);
    glVertex2i(160,670);
    glVertex2i(140,670);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(100,650);
    glVertex2d(120,650);

    glVertex2d(120,650);
    glVertex2d(120,670);

    glVertex2d(120,670);
    glVertex2d(100,670);

    glVertex2d(100,670);
    glVertex2d(100,650);

    glVertex2d(140,650);
    glVertex2d(160,650);

    glVertex2d(160,650);
    glVertex2d(160,670);


    glVertex2d(160,670);
    glVertex2d(140,670);

    glVertex2d(140,670);
    glVertex2d(140,650);
    glEnd();



//door

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(110,560);
    glVertex2i(150, 560);
    glVertex2i(150, 620);
    glVertex2i(110, 620);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(110, 560);
    glVertex2d(150, 560);

    glVertex2d(150,560);
    glVertex2d(150,620);

    glVertex2d(150,620);
    glVertex2d(110,620);

    glVertex2d(110,620);
    glVertex2d(110,560);

    // House outline

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(80, 560);
    glVertex2d(180, 560);

    glVertex2d(180,560);
    glVertex2d(180,620);

    glVertex2d(200, 620);
    glVertex2d(80, 620);

    glVertex2d(80, 640);
    glVertex2d(180, 640);

    glVertex2d(80, 640);
    glVertex2d(80, 680);

    glVertex2d(180, 640);
    glVertex2d(200,620);

    glVertex2d(180, 640);
    glVertex2d(180, 680);

    glVertex2d(200, 680);
    glVertex2d(60, 680);

    glVertex2d(60,680);
    glVertex2d(80,700);

    glVertex2d(80, 700);
    glVertex2d(180, 700);

    glVertex2d(180, 700);
    glVertex2d(200, 680);

    glVertex2d(130,562);
    glVertex2d(130,620);

    glVertex2d(110, 590);
    glVertex2d(150, 590);

    glVertex2d(100, 660);
    glVertex2d(120, 660);

    glVertex2d(110, 650);
    glVertex2d(110, 670);

    glVertex2d(140, 660);
    glVertex2d(160, 660);

    glVertex2d(150, 650);
    glVertex2d(150, 670);
    glEnd();


    //HOUSE3
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.442, 0.219);
    glVertex2i(0,560);
    glVertex2i(100,560);
    glVertex2i(100,630);
    glVertex2i(0,630);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(0,560);
    glVertex2f(0,630);

    glVertex2f(0, 630);
    glVertex2f(100,630);

    glVertex2f(100,630);
    glVertex2f(100, 560);

    glVertex2f(100,560);
    glVertex2f(0,560);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2f(0,630);
    glVertex2f(100,630);
    glVertex2f(50,680);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(0,630);
    glVertex2f(50,680);

    glVertex2f(50, 680);
    glVertex2f(100,630);

    glVertex2f(100,630);
    glVertex2f(0,630);
    glEnd();

    glColor3f(0.961, 0.933, 0.369);
    circle360(12,12, 50,650);

    glColor3f(0, 0, 0);
    drawCircleOutline(50,650,12,80);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(50,638);
    glVertex2f(50,662);

    glVertex2f(38, 650);
    glVertex2f(62,650);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(20,562);
    glVertex2i(40,562);
    glVertex2i(40,580);
    glVertex2i(20,580);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(20,600);
    glVertex2i(40,600);
    glVertex2i(40,620);
    glVertex2i(20,620);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(60,600);
    glVertex2i(80,600);
    glVertex2i(80,620);
    glVertex2i(60,620);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(20,562);
    glVertex2f(20,580);

    glVertex2f(30,562);
    glVertex2f(30,580);

    glVertex2f(20,570);
    glVertex2f(40,570);

    glVertex2f(20,580);
    glVertex2f(40,580);

    glVertex2f(40,580);
    glVertex2f(40,562);

    glVertex2f(40,562);
    glVertex2f(20,562);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(20,600);
    glVertex2f(20,620);

    glVertex2f(20,620);
    glVertex2f(40,620);

    glVertex2f(40,620);
    glVertex2f(40,600);

    glVertex2f(40,600);
    glVertex2f(20,600);

    glVertex2f(20,610);
    glVertex2f(40,610);

    glVertex2f(30,600);
    glVertex2f(30,620);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(60,600);
    glVertex2f(80,600);

    glVertex2f(80,600);
    glVertex2f(80,620);

    glVertex2f(80,620);
    glVertex2f(60,620);

    glVertex2f(60,620);
    glVertex2f(60,600);

    glVertex2f(60,610);
    glVertex2f(80,610);

    glVertex2f(70,600);
    glVertex2f(70,620);
    glEnd();

//HOUSE4
    //base
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.437, 0.215); // Darkened orange
    glVertex2i(290,560);
    glVertex2i(330, 560);
    glVertex2i(330, 680);
    glVertex2i(290, 680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(290,560);
    glVertex2i(330, 560);
    glVertex2i(330, 680);
    glVertex2i(290, 680);
    glVertex2i(290,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(300,570);
    glVertex2i(320, 570);
    glVertex2i(320, 590);
    glVertex2i(300, 590);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(300,610);
    glVertex2i(320,610);
    glVertex2i(320,630);
    glVertex2i(300,630);
    glEnd();



    //window1
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(300,570);
    glVertex2i(320, 570);
    glVertex2i(320, 590);
    glVertex2i(300, 590);
    glVertex2i(300,570);
    glEnd();
    //window2
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(300,610);
    glVertex2i(320,610);
    glVertex2i(320,630);
    glVertex2i(300,630);
    glVertex2i(300,610);
    glEnd();


    //roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(310,710);
    glVertex2i(330,680);
    glVertex2i(290,680);
    glEnd();



    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(310,710);
    glVertex2i(330,680);
    glVertex2i(290,680);
    glVertex2i(310,710);
    glEnd();



    //circle
    glColor3f(0.961, 0.933, 0.369);
    circle360(10,10,310,660);
    //halfcircle1
    circle0to160(10,10,310,590);
    //halfcircle2
    circle0to160(10,10,310,630);

    glColor3f(0,0,0);
    drawCircleOutline(310,660,10,80);
    drawHalfCircleOutline(310,590,10,50);
    drawHalfCircleOutline(310,630,10,50);

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(310,570);
    glVertex2i(310,590);
    glVertex2i(310,610);
    glVertex2i(310,630);
    glVertex2i(300,580);
    glVertex2i(320,580);
    glVertex2i(300,620);
    glVertex2i(320,620);
    glEnd();



//HOUSE5
    //base
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.437, 0.215); // Darkened orange
    glVertex2i(380,560);
    glVertex2i(480, 560);
    glVertex2i(480, 660);
    glVertex2i(380, 660);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(380,560);
    glVertex2i(480, 560);
    glVertex2i(480, 660);
    glVertex2i(380, 660);
    glVertex2i(380,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(440,590);
    glVertex2i(460,590);
    glVertex2i(460,610);
    glVertex2i(440,610);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(440,630);
    glVertex2i(460,630);
    glVertex2i(460,650);
    glVertex2i(440,650);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(400,630);
    glVertex2i(420,630);
    glVertex2i(420,650);
    glVertex2i(400,650);
    //window4
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(400,590);
    glVertex2i(420,590);
    glVertex2i(420,610);
    glVertex2i(400,610);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(440,590);
    glVertex2i(460,590);
    glVertex2i(460,610);
    glVertex2i(440,610);
    glVertex2i(440,590);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(440,630);
    glVertex2i(460,630);
    glVertex2i(460,650);
    glVertex2i(440,650);
    glVertex2i(440,630);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(400,630);
    glVertex2i(420,630);
    glVertex2i(420,650);
    glVertex2i(400,650);
    glVertex2i(400,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(400,590);
    glVertex2i(420,590);
    glVertex2i(420,610);
    glVertex2i(400,610);
    glVertex2i(400,590);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(450,590);
    glVertex2i(450,610);

    glVertex2i(450,630);
    glVertex2i(450,650);

    glVertex2i(410,630);
    glVertex2i(410,650);

    glVertex2i(440,600);
    glVertex2i(460,600);

    glVertex2i(400,600);
    glVertex2i(420,600);

    glVertex2i(440,640);
    glVertex2i(460,640);

    glVertex2i(400,640);
    glVertex2i(420,640);
    glEnd();


    //roof
    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(360,660);
    glVertex2i(500,660);
    glVertex2i(480,680);
    glVertex2i(380,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(360,660);
    glVertex2i(500,660);
    glVertex2i(480,680);
    glVertex2i(380,680);
    glVertex2i(360,660);
    glEnd();

//HOUSE6
    //base
    glBegin(GL_QUADS);
    glColor3f(0.239, 0.296, 0.314); // Darkened blueish color
    glVertex2i(330,560);
    glVertex2i(410, 560);
    glVertex2i(410, 640);
    glVertex2i(330, 640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,560);
    glVertex2i(410, 560);
    glVertex2i(410, 640);
    glVertex2i(330, 640);
    glVertex2i(330,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(370,560);
    glVertex2i(400, 560);
    glVertex2i(400, 570);
    glVertex2i(370, 570);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,560);
    glVertex2i(400, 560);
    glVertex2i(400, 570);
    glVertex2i(370, 570);
    glVertex2i(370,560);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(370,580);
    glVertex2i(400,580);
    glVertex2i(400,600);
    glVertex2i(370,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,580);
    glVertex2i(400,580);
    glVertex2i(400,600);
    glVertex2i(370,600);
    glVertex2i(370,580);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(370,610);
    glVertex2i(400,610);
    glVertex2i(400,630);
    glVertex2i(370,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,610);
    glVertex2i(400,610);
    glVertex2i(400,630);
    glVertex2i(370,630);
    glVertex2i(370,610);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(330,580);
    glVertex2i(360,580);
    glVertex2i(360,600);
    glVertex2i(330,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,580);
    glVertex2i(360,580);
    glVertex2i(360,600);
    glVertex2i(330,600);
    glVertex2i(330,580);
    glEnd();

    //window5
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(330,610);
    glVertex2i(360,610);
    glVertex2i(360,630);
    glVertex2i(330,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,610);
    glVertex2i(360,610);
    glVertex2i(360,630);
    glVertex2i(330,630);
    glVertex2i(330,610);
    glEnd();

//HOUSE7
    //base
    glBegin(GL_QUADS);
    glColor3f(0.478, 0.213, 0.099); // Darkened orange color
    glVertex2i(480,560);
    glVertex2i(570,560);
    glVertex2i(570,650);
    glVertex2i(480,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(480,560);
    glVertex2i(570,560);
    glVertex2i(570,650);
    glVertex2i(480,650);
    glVertex2i(480,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(490,580);
    glVertex2i(520,580);
    glVertex2i(520,600);
    glVertex2i(490,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,580);
    glVertex2i(520,580);
    glVertex2i(520,600);
    glVertex2i(490,600);
    glVertex2i(490,580);
    glEnd();

    //window2
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(490,620);
    glVertex2i(520,620);
    glVertex2i(520,640);
    glVertex2i(490,640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,620);
    glVertex2i(520,620);
    glVertex2i(520,640);
    glVertex2i(490,640);
    glVertex2i(490,620);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(530,620);
    glVertex2i(560,620);
    glVertex2i(560,640);
    glVertex2i(530,640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(530,620);
    glVertex2i(560,620);
    glVertex2i(560,640);
    glVertex2i(530,640);
    glVertex2i(530,620);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(530,580);
    glVertex2i(560,580);
    glVertex2i(560,600);
    glVertex2i(530,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(530,580);
    glVertex2i(560,580);
    glVertex2i(560,600);
    glVertex2i(530,600);
    glVertex2i(530,580);
    glEnd();



//HOUSE8
    //base
    glBegin(GL_QUADS);
    glColor3f(0.415, 0.29, 0.239); // Darkened brown color
    glVertex2i(570,560);
    glVertex2i(670,560);
    glVertex2i(670,690);
    glVertex2i(570,690);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(570,560);
    glVertex2i(670,560);
    glVertex2i(670,690);
    glVertex2i(570,690);
    glVertex2i(570,560);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.415, 0.29, 0.239); // Darkened brown color
    glVertex2i(580,690);
    glVertex2i(660,690);
    glVertex2i(660,720);
    glVertex2i(580,720);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,690);
    glVertex2i(660,690);
    glVertex2i(660,720);
    glVertex2i(580,720);
    glVertex2i(580,690);
    glEnd();

    //door
    glColor3f(0.961, 0.933, 0.369);
    circle360(20,10,620,610);
    glColor3f(0,0,0);
    drawCircleOutline1(20,10,620,610);

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(600,560);
    glVertex2i(640,560);
    glVertex2i(640,610);
    glVertex2i(600,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(600,560);
    glVertex2i(640,560);
    glVertex2i(640,610);
    glVertex2i(600,610);
    glVertex2i(600,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(580,630);
    glVertex2i(600,630);
    glVertex2i(600,650);
    glVertex2i(580,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,630);
    glVertex2i(600,630);
    glVertex2i(600,650);
    glVertex2i(580,650);
    glVertex2i(580,630);
    glEnd();

    //window2
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(610,630);
    glVertex2i(630,630);
    glVertex2i(630,650);
    glVertex2i(610,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(610,630);
    glVertex2i(630,630);
    glVertex2i(630,650);
    glVertex2i(610,650);
    glVertex2i(610,630);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(640,630);
    glVertex2i(660,630);
    glVertex2i(660,650);
    glVertex2i(640,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(640,630);
    glVertex2i(660,630);
    glVertex2i(660,650);
    glVertex2i(640,650);
    glVertex2i(640,630);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(640,660);
    glVertex2i(660,660);
    glVertex2i(660,680);
    glVertex2i(640,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(640,660);
    glVertex2i(660,660);
    glVertex2i(660,680);
    glVertex2i(640,680);
    glVertex2i(640,660);
    glEnd();

    //window5
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(610,660);
    glVertex2i(630,660);
    glVertex2i(630,680);
    glVertex2i(610,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(610,660);
    glVertex2i(630,660);
    glVertex2i(630,680);
    glVertex2i(610,680);
    glVertex2i(610,660);
    glEnd();

    //window6
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(580,660);
    glVertex2i(600,660);
    glVertex2i(600,680);
    glVertex2i(580,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,660);
    glVertex2i(600,660);
    glVertex2i(600,680);
    glVertex2i(580,680);
    glVertex2i(580,660);
    glEnd();

    //roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.49, 0.184, 0.102);
    glVertex2i(580,720);
    glVertex2i(660,720);
    glVertex2i(620,750);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,720);
    glVertex2i(660,720);
    glVertex2i(620,750);
    glVertex2i(580,720);
    glEnd();

    //flag board

    glBegin(GL_QUADS);
    glColor3f(0.878, 0.863, 0.698);
    glVertex2i(670,560);
    glVertex2i(680,560);
    glVertex2i(680,680);
    glVertex2i(670,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(670,560);
    glVertex2i(680,560);
    glVertex2i(680,680);
    glVertex2i(670,680);
    glVertex2i(670,560);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.961, 0.933, 0.369);
    glVertex2i(680,640);
    glVertex2i(730,640);
    glVertex2i(730,670);
    glVertex2i(680,670);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(680,640);
    glVertex2i(730,640);
    glVertex2i(730,670);
    glVertex2i(680,670);
    glVertex2i(680,640);
    glEnd();

    //hotel word
    glColor3f(0.0, 0.0, 0.0);
    circle360(3,5,697,655);

    glColor3f(1,1,1);
    circle360(1,3,697,655);


    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    //H
    glVertex2d(685, 650);
    glVertex2d(685, 660);

    glVertex2d(685, 655);
    glVertex2d(690,655);

    glVertex2d(690, 650);
    glVertex2d(690, 660);
    //T
    glVertex2d(705, 650);
    glVertex2d(705, 660);

    glVertex2d(702, 660);
    glVertex2d(708,660);
    //E
    glVertex2d(710, 650);
    glVertex2d(710, 660);

    glVertex2d(710, 650);
    glVertex2d(714,650);

    glVertex2d(710, 655);
    glVertex2d(714, 655);

    glVertex2d(710, 660);
    glVertex2d(714, 660);

    //L
    glVertex2d(718, 650);
    glVertex2d(718, 660);

    glVertex2d(718, 650);
    glVertex2d(722,650);

    glEnd();






//GREEN CIRCLE
    glColor3f(0.008, 0.161, 0.024);
    circle360(30,30,80,560);
    circle360(20,20,160,560);
    circle360(30,30,260,560);
    circle360(20,20,340,560);
    circle360(30,30,440,560);
    circle360(20,20,520,560);
    circle360(30,30,620,560);
    circle360(20,20,700,560);
    circle360(30,30,800,560);
    circle360(20,20,880,560);
    circle360(30,30,970,560);

    glColor3f(0, 0, 0);
    drawHalfCircleOutline(80,560,30,160);
    drawHalfCircleOutline(160,560,20,120);
    drawHalfCircleOutline(260,560,30,160);
    drawHalfCircleOutline(340,560,20,120);
    drawHalfCircleOutline(440,560,30,160);
    drawHalfCircleOutline(520,560,20,120);
    drawHalfCircleOutline(620,560,30,160);
    drawHalfCircleOutline(700,560,20,120);
    drawHalfCircleOutline(800,560,30,160);
    drawHalfCircleOutline(880,560,20,120);
    drawHalfCircleOutline(970,560,30,160);


    //ROAD

    glBegin(GL_QUADS);
    glColor3f(0.149, 0.149, 0.145); // Darkened road color
    glVertex2i(0,380);
    glVertex2i(1000,380);
    glVertex2i(1000,520);
    glVertex2i(0,520);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0,380);
    glVertex2i(1000,380);
    glVertex2i(1000,520);
    glVertex2i(0,520);
    glVertex2i(0,380);
    glEnd();

    glBegin(GL_QUADS);
glColor3f(0.961, 0.882, 0.541); // Warm light color
    glVertex2i(10,440);
    glVertex2i(130,440);
    glVertex2i(130,460);
    glVertex2i(10,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(10,440);
    glVertex2i(130,440);
    glVertex2i(130,460);
    glVertex2i(10,460);
    glVertex2i(10,440);
    glEnd();
    glBegin(GL_QUADS);
glColor3f(0.961, 0.882, 0.541); // Warm light color
    glVertex2i(170,440);
    glVertex2i(290,440);
    glVertex2i(290,460);
    glVertex2i(170,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(170,440);
    glVertex2i(290,440);
    glVertex2i(290,460);
    glVertex2i(170,460);
    glVertex2i(170,440);
    glEnd();
    glBegin(GL_QUADS);
glColor3f(0.961, 0.882, 0.541); // Warm light color
    glVertex2i(330,440);
    glVertex2i(450,440);
    glVertex2i(450,460);
    glVertex2i(330,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,440);
    glVertex2i(450,440);
    glVertex2i(450,460);
    glVertex2i(330,460);
    glVertex2i(330,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.882, 0.541);
    glVertex2i(490,440);
    glVertex2i(610,440);
    glVertex2i(610,460);
    glVertex2i(490,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,440);
    glVertex2i(610,440);
    glVertex2i(610,460);
    glVertex2i(490,460);
    glVertex2i(490,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.882, 0.541);
    glVertex2i(650,440);
    glVertex2i(770,440);
    glVertex2i(770,460);
    glVertex2i(650,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(650,440);
    glVertex2i(770,440);
    glVertex2i(770,460);
    glVertex2i(650,460);
    glVertex2i(650,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.961, 0.882, 0.541);
    glVertex2i(810,440);
    glVertex2i(930,440);
    glVertex2i(930,460);
    glVertex2i(810,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(810,440);
    glVertex2i(930,440);
    glVertex2i(930,460);
    glVertex2i(810,460);
    glVertex2i(810,440);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.961, 0.882, 0.541);
    glVertex2f(0,390);
    glVertex2f(1000,390);

    glVertex2f(1000,510);
    glVertex2f(0,510);
    glEnd();

    cars1();

    schoolbus1();
//road border
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.42, 0.392);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();

    //road relling
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(0,395);
    glVertex2i(680,395);
    glVertex2i(680,405);
    glVertex2i(0,405);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(0,395);
    glVertex2i(680,395);
    glVertex2i(680,405);
    glVertex2i(0,405);
    glVertex2i(0,395);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(10,360);
    glVertex2i(30,360);
    glVertex2i(30,420);
    glVertex2i(10,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(10,360);
    glVertex2i(30,360);
    glVertex2i(30,420);
    glVertex2i(10,420);
    glVertex2i(10,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(60,360);
    glVertex2i(80,360);
    glVertex2i(80,420);
    glVertex2i(60,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(60,360);
    glVertex2i(80,360);
    glVertex2i(80,420);
    glVertex2i(60,420);
    glVertex2i(60,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(110,360);
    glVertex2i(130,360);
    glVertex2i(130,420);
    glVertex2i(110,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(110,360);
    glVertex2i(130,360);
    glVertex2i(130,420);
    glVertex2i(110,420);
    glVertex2i(110,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(160,360);
    glVertex2i(180,360);
    glVertex2i(180,420);
    glVertex2i(160,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(160,360);
    glVertex2i(180,360);
    glVertex2i(180,420);
    glVertex2i(160,420);
    glVertex2i(160,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(210,360);
    glVertex2i(230,360);
    glVertex2i(230,420);
    glVertex2i(210,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,360);
    glVertex2i(230,360);
    glVertex2i(230,420);
    glVertex2i(210,420);
    glVertex2i(210,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(260,360);
    glVertex2i(280,360);
    glVertex2i(280,420);
    glVertex2i(260,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(260,360);
    glVertex2i(280,360);
    glVertex2i(280,420);
    glVertex2i(260,420);
    glVertex2i(260,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(310,360);
    glVertex2i(330,360);
    glVertex2i(330,420);
    glVertex2i(310,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(310,360);
    glVertex2i(330,360);
    glVertex2i(330,420);
    glVertex2i(310,420);
    glVertex2i(310,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(360,360);
    glVertex2i(380,360);
    glVertex2i(380,420);
    glVertex2i(360,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(360,360);
    glVertex2i(380,360);
    glVertex2i(380,420);
    glVertex2i(360,420);
    glVertex2i(360,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(410,360);
    glVertex2i(430,360);
    glVertex2i(430,420);
    glVertex2i(410,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(410,360);
    glVertex2i(430,360);
    glVertex2i(430,420);
    glVertex2i(410,420);
    glVertex2i(410,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(460,360);
    glVertex2i(480,360);
    glVertex2i(480,420);
    glVertex2i(460,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(460,360);
    glVertex2i(480,360);
    glVertex2i(480,420);
    glVertex2i(460,420);
    glVertex2i(460,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(510,360);
    glVertex2i(530,360);
    glVertex2i(530,420);
    glVertex2i(510,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(510,360);
    glVertex2i(530,360);
    glVertex2i(530,420);
    glVertex2i(510,420);
    glVertex2i(510,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(560,360);
    glVertex2i(580,360);
    glVertex2i(580,420);
    glVertex2i(560,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(560,360);
    glVertex2i(580,360);
    glVertex2i(580,420);
    glVertex2i(560,420);
    glVertex2i(560,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(610,360);
    glVertex2i(630,360);
    glVertex2i(630,420);
    glVertex2i(610,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(610,360);
    glVertex2i(630,360);
    glVertex2i(630,420);
    glVertex2i(610,420);
    glVertex2i(610,360);
    glEnd();



//OCEAN

glBegin(GL_QUADS);
glColor3f(0.149, 0.294, 0.447); // Darkened ocean color
glVertex2i(0, 0);
glVertex2i(1000, 0);
glVertex2i(1000, 380);
glVertex2i(0, 380);
glEnd();

glLineWidth(4.0);
glBegin(GL_LINES);
glColor3f(0.057, 0.1, 0.178); // Darkened wave lines color
glVertex2i(690, 330);
glVertex2i(730, 330);

glVertex2i(760, 330);
glVertex2i(800, 330);

glVertex2i(830, 330);
glVertex2i(870, 330);

glVertex2i(900, 330);
glVertex2i(940, 330);

glVertex2i(970, 330);
glVertex2i(1000, 330);

glVertex2i(700, 320);
glVertex2i(720, 320);

glVertex2i(770, 320);
glVertex2i(790, 320);

glVertex2i(840, 320);
glVertex2i(860, 320);

glVertex2i(910, 320);
glVertex2i(930, 320);

glVertex2i(980, 320);
glVertex2i(1000, 320);

glEnd();


    //ship
glBegin(GL_QUADS);
glColor3f(0.408, 0.229, 0.057); // Darkened ship base color
glVertex2i(830, 230);
glVertex2i(970, 230);
glVertex2i(980, 250);
glVertex2i(820, 250);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(830, 230);
glVertex2i(970, 230);
glVertex2i(980, 250);
glVertex2i(820, 250);
glVertex2i(830, 230);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.129, 0.359, 0.165); // Darkened ship upper part color
glVertex2i(830, 250);
glVertex2i(970, 250);
glVertex2i(970, 270);
glVertex2i(830, 270);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(830, 250);
glVertex2i(970, 250);
glVertex2i(970, 270);
glVertex2i(830, 270);
glVertex2i(830, 250);
glEnd();
glBegin(GL_QUADS);
glColor3f(0, 0, 0);
glVertex2i(850, 270);
glVertex2i(870, 270);
glVertex2i(870, 300);
glVertex2i(850, 300);
glEnd();
glBegin(GL_QUADS);
glColor3f(0, 0, 0);
glVertex2i(890, 270);
glVertex2i(910, 270);
glVertex2i(910, 300);
glVertex2i(890, 300);
glEnd();
glBegin(GL_QUADS);
glColor3f(0, 0, 0);
glVertex2i(930, 270);
glVertex2i(950, 270);
glVertex2i(950, 300);
glVertex2i(930, 300);
glEnd();

// Darkened smoke color
glColor3f(0.192, 0.225, 0.263);
circle360(5, 5, 860, 305);
circle360(5, 5, 860, 310);
circle360(5, 5, 865, 315);
circle360(5, 5, 870, 320);
circle360(5, 5, 875, 325);

circle360(5, 5, 900, 305);
circle360(5, 5, 900, 310);
circle360(5, 5, 905, 315);
circle360(5, 5, 910, 320);
circle360(5, 5, 915, 325);

circle360(5, 5, 940, 305);
circle360(5, 5, 940, 310);
circle360(5, 5, 945, 315);
circle360(5, 5, 950, 320);
circle360(5, 5, 955, 325);

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.057, 0.1, 0.178); // Darkened wave lines color
    glVertex2i(800,230);
    glVertex2i(1000,230);

    glVertex2i(800,220);
    glVertex2i(840,220);

    glVertex2i(860,220);
    glVertex2i(900,220);

    glVertex2i(920,220);
    glVertex2i(960,220);

    glVertex2i(820,210);
    glVertex2i(870,210);

    glVertex2i(890,210);
    glVertex2i(940,210);

    glVertex2i(950,210);
    glVertex2i(1000,210);

    glEnd();



    boat1();

    fish1();


    // ROAD BORDER
glBegin(GL_QUADS);
glColor3f(0.212, 0.208, 0.196); // Darkened road border color
glVertex2i(0, 520);
glVertex2i(1000, 520);
glVertex2i(1000, 535);
glVertex2i(0, 535);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glLineWidth(2.0);
glColor3f(0, 0, 0); // Darkened road border line color
glVertex2i(0, 520);
glVertex2i(1000, 520);
glVertex2i(1000, 535);
glVertex2i(0, 535);
glEnd();


//beach
glBegin(GL_POLYGON);
glColor3f(0.4, 0.314, 0.184); // Darkened color for beach
glVertex2d(0, 0);
glVertex2d(250, 0);
glVertex2d(430, 130);
glVertex2d(370, 130);
glVertex2d(530, 230);
glVertex2d(450, 230);
glVertex2d(630, 380);
glVertex2d(0, 380);
glEnd();

// Darkened color for water curves
glColor3f(0.149, 0.294, 0.447);
circle360(30, 15, 480, 235);
circle360(30, 15, 400, 135);
circle360(30, 15, 280, 5);

// Darkened color for water triangles
glBegin(GL_TRIANGLES);
glColor3f(0.149, 0.294, 0.447);
glVertex2i(460, 245);
glVertex2i(460, 235);
glVertex2d(575, 310);
glEnd();
glBegin(GL_TRIANGLES);
glColor3f(0.149, 0.294, 0.447);
glVertex2i(480, 220);
glVertex2i(530, 230);
glVertex2d(530, 240);
glEnd();

glBegin(GL_TRIANGLES);
glColor3f(0.149, 0.294, 0.447);
glVertex2i(390, 145);
glVertex2i(390, 135);
glVertex2d(510, 200);
glEnd();
glBegin(GL_TRIANGLES);
glColor3f(0.149, 0.294, 0.447);
glVertex2i(260, 15);
glVertex2i(280, 5);
glVertex2d(370, 80);
glEnd();

// Darkened color for star outline
glColor3f(0.286, 0.102, 0.082);
drawStar(250, 330, 25);




//big tree
    glColor3f(0.082, 0.133, 0.052); // Darkened color for tree trunk
circle360(100,100,50,400);
circle360(20,20,50,300);
circle360(30,30,80,310);
circle360(20,20,110,320);
circle360(20,20,130,330);
circle360(30,30,130,360);
circle360(20,20,150,370);
circle360(30,30,150,380);
circle360(20,20,150,400);
circle360(30,30,130,420);
circle360(20,20,120,440);
circle360(30,30,130,460);
circle360(20,20,100,480);
circle360(30,30,80,500);
circle360(20,20,50,500);
circle360(30,30,20,500);

glColor3f(0.072, 0.322, 0.013); // Darkened color for tree leaves
circle360(100,100,50,400);
circle360(15,15,50,300);
circle360(25,25,80,310);
circle360(15,15,110,320);
circle360(15,15,130,330);
circle360(25,25,130,360);
circle360(15,15,150,370);
circle360(25,25,150,380);
circle360(15,15,150,400);
circle360(25,25,130,420);
circle360(15,15,120,440);
circle360(25,25,130,460);
circle360(15,15,100,480);
circle360(25,25,80,500);
circle360(15,15,50,500);
circle360(25,25,20,500);

glBegin(GL_QUADS);
glColor3f(0.216, 0.126, 0.047); // Darkened color for ground
glVertex2d(0,0);
glVertex2d(40,0);
glVertex2d(40,330);
glVertex2d(0,330);
glEnd();

glBegin(GL_QUADS);
glColor3f(0.216, 0.126, 0.047); // Darkened color for ground
glVertex2d(40,310);
glVertex2d(100,380);
glVertex2d(80,380);
glVertex2d(30,330);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.216, 0.126, 0.047); // Darkened color for ground
glVertex2d(40,330);
glVertex2d(0,380);
glVertex2d(0,360);
glVertex2d(25,330);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.216, 0.126, 0.047); // Darkened color for ground
glVertex2d(40,330);
glVertex2d(0,350);
glVertex2d(0,330);
glVertex2d(30,330);
glEnd();
glBegin(GL_QUADS);
glColor3f(0.216, 0.126, 0.047); // Darkened color for ground
glVertex2d(30,330);
glVertex2d(40,330);
glVertex2d(52,380);
glVertex2d(40,380);
glEnd();


/*glBegin(GL_POLYGON);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(70,0);
        glVertex2d(60,10);
        glVertex2d(55,15);
        glVertex2d(45,30);
        glVertex2d(40,40);
        glVertex2d(35,50);
        glVertex2d(30,60);
        glVertex2d(25,70);
        glVertex2d(25,0);
        glEnd();


        /*glColor3f(0, 0, 0); // Black color for outline
        glLineWidth(2); // Line width for the outline
        glBegin(GL_LINE_LOOP);
        glVertex2d(70, 0);
        glVertex2d(60, 10);
        glVertex2d(55, 15);
        glVertex2d(45, 30);
        glVertex2d(40, 40);
        glVertex2d(35, 50);
        glVertex2d(30, 60);
        glVertex2d(25, 70);
        glVertex2d(25, 0);
        glEnd();
          glColor3f(0.173, 0.278, 0.11);
        circle360(20,20,90,380);
        circle360(10,10,90,360);
        circle360(10,10,110,370);
        circle360(10,10,110,390);
        circle360(10,10,90,400);
        circle360(10,10,70,390);
        circle360(10,10,70,370);*/

//UMBRELLA

    glBegin(GL_QUADS);
    glColor3f(0.188, 0.082, 0.017); // Darkened color for umbrella fabric
    glVertex2i(120,30);
    glVertex2i(140,30);
    glVertex2i(140,180);
    glVertex2i(120,180);
    glEnd();
    glLineWidth(2); // Line width for the outline
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(120,30);
    glVertex2i(140,30);
    glVertex2i(140,180);
    glVertex2i(120,180);
    glVertex2i(120,30);
    glEnd();
    // Darkened color for the first triangle
glBegin(GL_TRIANGLES);
glColor3f(0.6, 0.02, 0.02);
glVertex2i(130, 290);
glVertex2i(0, 180);
glVertex2i(30, 180);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 290);
glVertex2i(0, 180);
glVertex2i(30, 180);
glEnd();

// Darkened color for the second triangle
glBegin(GL_TRIANGLES);
glColor3f(0.6, 0.33, 0.06);
glVertex2i(130, 290);
glVertex2i(30, 180);
glVertex2i(70, 180);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 290);
glVertex2i(30, 180);
glVertex2i(70, 180);
glEnd();

   // Darkened color for the first triangle
glBegin(GL_TRIANGLES);
glColor3f(0.5, 0.5, 0.06); // Darkened yellow
glVertex2i(130, 290);
glVertex2i(70, 180);
glVertex2i(130, 180);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 290);
glVertex2i(70, 180);
glVertex2i(130, 180);
glEnd();

// Darkened color for the second triangle
glBegin(GL_TRIANGLES);
glColor3f(0.1, 0.4, 0.1); // Darkened green
glVertex2i(130, 290);
glVertex2i(130, 180);
glVertex2i(190, 180);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 290);
glVertex2i(130, 180);
glVertex2i(190, 180);
glEnd();

// Darkened color for the third triangle
glBegin(GL_TRIANGLES);
glColor3f(0, 0.2, 0.7); // Darkened blue
glVertex2i(130, 290);
glVertex2i(190, 180);
glVertex2i(230, 180);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0);
glVertex2i(130, 290);
glVertex2i(190, 180);
glVertex2i(230, 180);
glEnd();
// Darkened color for the triangle
glBegin(GL_TRIANGLES);
glColor3f(0.5, 0.015, 0.015); // Darkened red
glVertex2i(130, 290);
glVertex2i(230, 180);
glVertex2i(270, 180);
glEnd();

// Darkened color for the outline
glBegin(GL_LINE_STRIP);
glColor3f(0, 0, 0); // Darkened black
glVertex2i(130, 290);
glVertex2i(230, 180);
glVertex2i(270, 180);
glVertex2i(130, 290);
glEnd();


    glColor3f(0.8, 0.8, 0.8); // Darkened color for circles
circle180to360(15, 10, 15, 180);
circle180to360(15, 10, 45, 180);
circle180to360(15, 10, 75, 180);
circle180to360(15, 10, 105, 180);
circle180to360(15, 10, 135, 180);
circle180to360(15, 10, 165, 180);
circle180to360(15, 10, 195, 180);
circle180to360(15, 10, 225, 180);
circle180to360(15, 10, 255, 180);



    glColor3f(0,0,0);
    drawHalfCircleOutline2(15, 10, 15, 180);
    drawHalfCircleOutline2(15, 10, 45, 180);
    drawHalfCircleOutline2(15, 10, 75, 180);
    drawHalfCircleOutline2(15, 10, 105, 180);
    drawHalfCircleOutline2(15, 10, 135, 180);
    drawHalfCircleOutline2(15, 10, 165, 180);
    drawHalfCircleOutline2(15, 10, 195, 180);
    drawHalfCircleOutline2(15, 10, 225, 180);
    drawHalfCircleOutline2(15, 10, 255, 180);


//chair
    glBegin(GL_QUADS);
    glColor3f(0.2, 0.09, 0.02); // Darkened brown
    glVertex2i(180,0);
    glVertex2i(190,0);
    glVertex2i(190,40);
    glVertex2i(180,40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(180,0);
    glVertex2i(190,0);
    glVertex2i(190,40);
    glVertex2i(180,40);
    glVertex2i(180,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8, 0.78, 0.2); // Darkened yellow
    glVertex2i(40,110);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(90,160);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(40,110);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(90,160);
    glVertex2i(40,110);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.8, 0.78, 0.2); // Darkened yellow
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(200,42);
    glVertex2i(110,0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(200,42);
    glVertex2i(110,0);
    glVertex2i(90,30);
    glEnd();

    glBegin(GL_QUADS);
   glColor3f(0.2, 0.09, 0.02); // Darkened brown
    glVertex2i(20,110);
    glVertex2i(30,120);
    glVertex2i(120,0);
    glVertex2i(110,0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(20,110);
    glVertex2i(30,120);
    glVertex2i(120,0);
    glVertex2i(110,0);
    glVertex2i(20,110);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2, 0.09, 0.02); // Darkened brown
    glVertex2i(42,0);
    glVertex2i(58,0);
    glVertex2i(72,50);
    glVertex2i(62,60);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(42,0);
    glVertex2i(58,0);
    glVertex2i(72,50);
    glVertex2i(62,60);
    glVertex2i(42,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.2, 0.09, 0.02); // Darkened brown
    glVertex2i(80,150);
    glVertex2i(90,160);
    glVertex2i(80,170);
    glVertex2i(70,160);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(80,150);
    glVertex2i(90,160);
    glVertex2i(80,170);
    glVertex2i(70,160);
    glVertex2i(80,150);
    glEnd();

    glColor3f(0.8, 0.031, 0.027); // Darkened red
circle360(15, 15, 180, 100);

glColor3f(0.4, 0.4, 0.4); // Lightened outline to grayish tone
drawCircleOutline(180, 100, 15, 100);

glColor3f(1, 1, 1); // White color for the small circle
circle360(6, 2, 180, 108);

glLineWidth(3.0);
glBegin(GL_LINES);
glColor3f(0.6, 0.447, 0.2); // Slightly desaturated color for the lines
glVertex2i(160, 80);
glVertex2i(200, 80);

glVertex2i(170, 85);
glVertex2i(190, 85);
glEnd();






//bridge
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.35, 0.3);
    glVertex2i(650,380);
    glVertex2i(1000,380);
    glVertex2i(1000,410);
    glVertex2i(680,410);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(650,380);
    glVertex2i(1000,380);
    glVertex2i(1000,410);
    glVertex2i(680,410);
    glVertex2i(650,380);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.4, 0.35, 0.3);
    glVertex2i(650,520);
    glVertex2i(1000,520);
    glVertex2i(1000,550);
    glVertex2i(680,550);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(650,520);
    glVertex2i(1000,520);
    glVertex2i(1000,550);
    glVertex2i(680,550);
    glVertex2i(650,520);
    glEnd();

    //bridge piller1
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(680,550);
    glVertex2i(700,550);
    glVertex2i(700,630);
    glVertex2i(680,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(680,550);
    glVertex2i(700,550);
    glVertex2i(700,630);
    glVertex2i(680,630);
    glVertex2i(680,550);
    glEnd();

    //bridge piller2
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(770,550);
    glVertex2i(790,550);
    glVertex2i(790,630);
    glVertex2i(770,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(770,550);
    glVertex2i(790,550);
    glVertex2i(790,630);
    glVertex2i(770,630);
    glVertex2i(770,550);
    glEnd();

    //bridge piller3
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(870,550);
    glVertex2i(890,550);
    glVertex2i(890,630);
    glVertex2i(870,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(870,550);
    glVertex2i(890,550);
    glVertex2i(890,630);
    glVertex2i(870,630);
    glVertex2i(870,550);
    glEnd();
    //bridge piller4
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(970,550);
    glVertex2i(990,550);
    glVertex2i(990,630);
    glVertex2i(970,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(970,550);
    glVertex2i(990,550);
    glVertex2i(990,630);
    glVertex2i(970,630);
    glVertex2i(970,550);
    glEnd();

    //bridge piller5
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(680,410);
    glVertex2i(700,410);
    glVertex2i(700,490);
    glVertex2i(680,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(680,410);
    glVertex2i(700,410);
    glVertex2i(700,490);
    glVertex2i(680,490);
    glVertex2i(680,410);
    glEnd();

    //bridge piller6
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(770,410);
    glVertex2i(790,410);
    glVertex2i(790,490);
    glVertex2i(770,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(770,410);
    glVertex2i(790,410);
    glVertex2i(790,490);
    glVertex2i(770,490);
    glVertex2i(770,410);
    glEnd();

    //bridge piller7
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(870,410);
    glVertex2i(890,410);
    glVertex2i(890,490);
    glVertex2i(870,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(870,410);
    glVertex2i(890,410);
    glVertex2i(890,490);
    glVertex2i(870,490);
    glVertex2i(870,410);
    glEnd();
    //bridge piller8
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.15, 0.12);
    glVertex2i(970,410);
    glVertex2i(990,410);
    glVertex2i(990,490);
    glVertex2i(970,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(970,410);
    glVertex2i(990,410);
    glVertex2i(990,490);
    glVertex2i(970,490);
    glVertex2i(970,410);
    glEnd();

    glLineWidth(3.0);
    glColor3f(0,0,0);
    drawHalfCircleOutline2(35,30,735,620);
    drawHalfCircleOutline2(40,30,830,620);
    drawHalfCircleOutline2(40,30,930,620);

    drawHalfCircleOutline2(35,30,735,480);
    drawHalfCircleOutline2(40,30,830,480);
    drawHalfCircleOutline2(40,30,930,480);


// Bridge Lower Pillar 1
glBegin(GL_QUADS);
glColor3f(0.616, 0.549, 0.482); // Darkened color for nighttime
glVertex2i(700,330);
glVertex2i(720,330);
glVertex2i(720,380);
glVertex2i(700,380);
glEnd();
glLineWidth(2.0);
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(700,330);
glVertex2i(720,330);
glVertex2i(720,380);
glVertex2i(700,380);
glVertex2i(700,330);
glEnd();

// Bridge Lower Pillar 2
glBegin(GL_QUADS);
glColor3f(0.616, 0.549, 0.482); // Darkened color for nighttime
glVertex2i(770,330);
glVertex2i(790,330);
glVertex2i(790,380);
glVertex2i(770,380);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(770,330);
glVertex2i(790,330);
glVertex2i(790,380);
glVertex2i(770,380);
glVertex2i(770,330);
glEnd();

// Bridge Lower Pillar 3
glBegin(GL_QUADS);
glColor3f(0.616, 0.549, 0.482); // Darkened color for nighttime
glVertex2i(840,330);
glVertex2i(860,330);
glVertex2i(860,380);
glVertex2i(840,380);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(840,330);
glVertex2i(860,330);
glVertex2i(860,380);
glVertex2i(840,380);
glVertex2i(840,330);
glEnd();

// Bridge Lower Pillar 4
glBegin(GL_QUADS);
glColor3f(0.616, 0.549, 0.482); // Darkened color for nighttime
glVertex2i(910,330);
glVertex2i(930,330);
glVertex2i(930,380);
glVertex2i(910,380);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(910,330);
glVertex2i(930,330);
glVertex2i(930,380);
glVertex2i(910,380);
glVertex2i(910,330);
glEnd();

// Bridge Lower Pillar 5
glBegin(GL_QUADS);
glColor3f(0.616, 0.549, 0.482); // Darkened color for nighttime
glVertex2i(980,330);
glVertex2i(1000,330);
glVertex2i(1000,380);
glVertex2i(980,380);
glEnd();
glBegin(GL_LINE_STRIP);
glColor3f(0,0,0);
glVertex2i(980,330);
glVertex2i(1000,330);
glVertex2i(1000,380);
glVertex2i(980,380);
glVertex2i(980,330);
glEnd();

    glColor3f(0.149, 0.294, 0.447);
    circle0to160(25,20,745,375);
    circle0to160(25,20,815,375);
    circle0to160(25,20,885,375);
    circle0to160(25,20,955,375);
    glColor3f(0,0,0);
    drawHalfCircleOutline3(25,20,745,375);
    drawHalfCircleOutline3(25,20,815,375);
    drawHalfCircleOutline3(25,20,885,375);
    drawHalfCircleOutline3(25,20,955,375);


}




void scenary1()
{

    // Green box
    glBegin(GL_QUADS);
    glColor3f(0.047, 0.392, 0.063);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 560);
    glVertex2i(0, 560);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 560);
    glVertex2i(0, 560);
    glEnd();

    //road border
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.42, 0.392);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();

//SKY
    glBegin(GL_QUADS);
    glColor3f(0.545, 0.816, 0.925);
    glVertex2i(0,560);
    glVertex2i(1000,560);
    glVertex2i(1000,1000);
    glVertex2i(0,1000);
    glEnd();

    //sun
    glColor3f(1, 0.886, 0.286);
    circle360(60,60,850,800);
    glColor3f(0.945, 0.439, 0.161);
    circle360(50,50,850,800);
    glColor3f(0.757, 0.031, 0.031);
    circle360(40,40,850,800);




    plane();
    cloud1();
    cloud2();
    bird();





    //plane

//tree1
//green circle
    glColor3f(0.173, 0.42, 0.043);
    circle360(32,32,30,710);
    circle360(32,32,10,690);
    circle360(40,40,10,730);

    glColor3f(0.137, 0.604, 0.031);
    circle360(25,25,30,710);
    circle360(25,25,10,690);
    circle360(30,30,10,730);



    glBegin(GL_POLYGON);
    glColor3f(0.612, 0.416, 0.247);
    glVertex2i(20,600);
    glVertex2i(20,700);
    glVertex2i(30,710);
    glVertex2i(30,720);
    glVertex2i(10,700);
    glVertex2i(0,710);
    glVertex2i(0,600);
    glEnd();

    //tree2
    glColor3f(0.173, 0.42, 0.043);
    circle360(40,40,280,720);
    circle360(40,40,210,720);
    circle360(50,70,245,730);
    circle360(30,30,260,690);
    circle360(30,30,230,690);
    circle360(20,20,210,750);
    circle360(20,20,280,750);

    glColor3f(0.137, 0.604, 0.031);
    circle360(35,35,280,720);
    circle360(35,35,210,720);
    circle360(45,65,245,730);
    circle360(25,25,260,690);
    circle360(25,25,230,690);
    circle360(15,15,210,750);
    circle360(15,15,280,750);


    glBegin(GL_POLYGON);
    glColor3f(0.612, 0.416, 0.247);
    glVertex2i(230,600);
    glVertex2i(260,600);
    glVertex2i(260,700);
    glVertex2i(270,710);
    glVertex2i(270,720);
    glVertex2i(245,700);
    glVertex2i(220,720);
    glVertex2i(220,710);
    glVertex2i(230,700);
    glEnd();

    //tree3
    glColor3f(0.173, 0.42, 0.043);
    circle360(40,40,560,720);
    circle360(40,40,490,720);
    circle360(50,70,525,730);
    circle360(30,30,510,680);
    circle360(30,30,540,680);
    circle360(20,20,490,750);
    circle360(20,20,560,750);

    glColor3f(0.137, 0.604, 0.031);
    circle360(35,35,560,720);
    circle360(35,35,490,720);
    circle360(45,65,525,730);
    circle360(25,25,510,680);
    circle360(25,25,540,680);
    circle360(15,15,490,750);
    circle360(15,15,560,750);


    glBegin(GL_POLYGON);
    glColor3f(0.612, 0.416, 0.247);
    glVertex2i(510,600);
    glVertex2i(540,600);
    glVertex2i(540,700);
    glVertex2i(550,710);
    glVertex2i(550,720);
    glVertex2i(525,700);
    glVertex2i(500,720);
    glVertex2i(500,710);
    glVertex2i(510,700);
    glEnd();





//HOUSE1



    glBegin(GL_QUADS);
    glColor3f(0.655, 0.792, 0.831);
    glVertex2i(180,560);
    glVertex2i(290,560);
    glVertex2i(290,660);
    glVertex2i(180,660);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(270,600);
    glVertex2i(280,600);
    glVertex2i(280,610);
    glVertex2i(270,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(270,620);
    glVertex2i(280,620);
    glVertex2i(280,630);
    glVertex2i(270,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(270,640);
    glVertex2i(280,640);
    glVertex2i(280,650);
    glVertex2i(270,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(250,600);
    glVertex2i(260,600);
    glVertex2i(260,610);
    glVertex2i(250,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(250,620);
    glVertex2i(260,620);
    glVertex2i(260,630);
    glVertex2i(250,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(250,640);
    glVertex2i(260,640);
    glVertex2i(260,650);
    glVertex2i(250,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(210,580);
    glVertex2i(220,580);
    glVertex2i(220,590);
    glVertex2i(210,590);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(210,600);
    glVertex2i(220,600);
    glVertex2i(220,610);
    glVertex2i(210,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(210,620);
    glVertex2i(220,620);
    glVertex2i(220,630);
    glVertex2i(210,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(210,640);
    glVertex2i(220,640);
    glVertex2i(220,650);
    glVertex2i(210,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(210,560);
    glVertex2i(220,560);
    glVertex2i(220,570);
    glVertex2i(210,570);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(190,580);
    glVertex2i(200,580);
    glVertex2i(200,590);
    glVertex2i(190,590);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(190,600);
    glVertex2i(200,600);
    glVertex2i(200,610);
    glVertex2i(190,610);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(190,620);
    glVertex2i(200,620);
    glVertex2i(200,630);
    glVertex2i(190,630);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(190,640);
    glVertex2i(200,640);
    glVertex2i(200,650);
    glVertex2i(190,650);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(190,560);
    glVertex2i(200,560);
    glVertex2i(200,570);
    glVertex2i(190,570);
    glEnd();


    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(180,560);
    glVertex2f(180,660);

    glVertex2f(180,660);
    glVertex2f(290,660);

    glVertex2f(290,660);
    glVertex2f(290,560);

    glVertex2f(290,560);
    glVertex2f(180,560);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(230,580);
    glVertex2i(240,580);
    glVertex2i(240,610);
    glVertex2i(230,610);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(230,620);
    glVertex2i(240,620);
    glVertex2i(240,650);
    glVertex2i(230,650);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(230,580);
    glVertex2i(240,580);
    glVertex2i(240,610);
    glVertex2i(230,610);
    glVertex2i(230,580);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(230,620);
    glVertex2i(240,620);
    glVertex2i(240,650);
    glVertex2i(230,650);
    glVertex2i(230,620);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,600);
    glVertex2i(280,600);
    glVertex2i(280,610);
    glVertex2i(270,610);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,620);
    glVertex2i(280,620);
    glVertex2i(280,630);
    glVertex2i(270,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(270,640);
    glVertex2i(280,640);
    glVertex2i(280,650);
    glVertex2i(270,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,600);
    glVertex2i(260,600);
    glVertex2i(260,610);
    glVertex2i(250,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,620);
    glVertex2i(260,620);
    glVertex2i(260,630);
    glVertex2i(250,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(250,640);
    glVertex2i(260,640);
    glVertex2i(260,650);
    glVertex2i(250,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,580);
    glVertex2i(220,580);
    glVertex2i(220,590);
    glVertex2i(210,590);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,600);
    glVertex2i(220,600);
    glVertex2i(220,610);
    glVertex2i(210,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,620);
    glVertex2i(220,620);
    glVertex2i(220,630);
    glVertex2i(210,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,640);
    glVertex2i(220,640);
    glVertex2i(220,650);
    glVertex2i(210,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,560);
    glVertex2i(220,560);
    glVertex2i(220,570);
    glVertex2i(210,570);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,580);
    glVertex2i(200,580);
    glVertex2i(200,590);
    glVertex2i(190,590);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,600);
    glVertex2i(200,600);
    glVertex2i(200,610);
    glVertex2i(190,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,620);
    glVertex2i(200,620);
    glVertex2i(200,630);
    glVertex2i(190,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,640);
    glVertex2i(200,640);
    glVertex2i(200,650);
    glVertex2i(190,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(190,560);
    glVertex2i(200,560);
    glVertex2i(200,570);
    glVertex2i(190,570);
    glEnd();



    //house 2

//base
    glBegin(GL_QUADS);
    glColor3f(0.878, 0.863, 0.698);
    glVertex2i(80,560);
    glVertex2i(180,560);
    glVertex2i(180,620);
    glVertex2i(80,620);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.878, 0.863, 0.698);
    glVertex2i(80,640);
    glVertex2i(180,640);
    glVertex2i(180,680);
    glVertex2i(80,680);
    glEnd();

//roof

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(80,620);
    glVertex2i(200, 620);
    glVertex2i(180, 640);
    glVertex2i(80, 640);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(60,680);
    glVertex2i(200,680);
    glVertex2i(180,700);
    glVertex2i(80,700);
    glEnd();

//window
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(100,650);
    glVertex2i(120,650);
    glVertex2i(120,670);
    glVertex2i(100,670);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(140,650);
    glVertex2i(160,650);
    glVertex2i(160,670);
    glVertex2i(140,670);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(100,650);
    glVertex2d(120,650);

    glVertex2d(120,650);
    glVertex2d(120,670);

    glVertex2d(120,670);
    glVertex2d(100,670);

    glVertex2d(100,670);
    glVertex2d(100,650);

    glVertex2d(140,650);
    glVertex2d(160,650);

    glVertex2d(160,650);
    glVertex2d(160,670);


    glVertex2d(160,670);
    glVertex2d(140,670);

    glVertex2d(140,670);
    glVertex2d(140,650);
    glEnd();



//door

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(110,560);
    glVertex2i(150, 560);
    glVertex2i(150, 620);
    glVertex2i(110, 620);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(110, 560);
    glVertex2d(150, 560);

    glVertex2d(150,560);
    glVertex2d(150,620);

    glVertex2d(150,620);
    glVertex2d(110,620);

    glVertex2d(110,620);
    glVertex2d(110,560);

    // House outline

    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2d(80, 560);
    glVertex2d(180, 560);

    glVertex2d(180,560);
    glVertex2d(180,620);

    glVertex2d(200, 620);
    glVertex2d(80, 620);

    glVertex2d(80, 640);
    glVertex2d(180, 640);

    glVertex2d(80, 640);
    glVertex2d(80, 680);

    glVertex2d(180, 640);
    glVertex2d(200,620);

    glVertex2d(180, 640);
    glVertex2d(180, 680);

    glVertex2d(200, 680);
    glVertex2d(60, 680);

    glVertex2d(60,680);
    glVertex2d(80,700);

    glVertex2d(80, 700);
    glVertex2d(180, 700);

    glVertex2d(180, 700);
    glVertex2d(200, 680);

    glVertex2d(130,562);
    glVertex2d(130,620);

    glVertex2d(110, 590);
    glVertex2d(150, 590);

    glVertex2d(100, 660);
    glVertex2d(120, 660);

    glVertex2d(110, 650);
    glVertex2d(110, 670);

    glVertex2d(140, 660);
    glVertex2d(160, 660);

    glVertex2d(150, 650);
    glVertex2d(150, 670);
    glEnd();


    //HOUSE3
    glBegin(GL_QUADS);
    glColor3f(1, 0.737, 0.365);
    glVertex2i(0,560);
    glVertex2i(100,560);
    glVertex2i(100,630);
    glVertex2i(0,630);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(0,560);
    glVertex2f(0,630);

    glVertex2f(0, 630);
    glVertex2f(100,630);

    glVertex2f(100,630);
    glVertex2f(100, 560);

    glVertex2f(100,560);
    glVertex2f(0,560);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2f(0,630);
    glVertex2f(100,630);
    glVertex2f(50,680);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(0,630);
    glVertex2f(50,680);

    glVertex2f(50, 680);
    glVertex2f(100,630);

    glVertex2f(100,630);
    glVertex2f(0,630);
    glEnd();

    glColor3f(0.965, 0.976, 1);
    circle360(12,12, 50,650);

    glColor3f(0, 0, 0);
    drawCircleOutline(50,650,12,80);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);

    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(50,638);
    glVertex2f(50,662);

    glVertex2f(38, 650);
    glVertex2f(62,650);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.965, 0.976, 1);
    glVertex2i(20,562);
    glVertex2i(40,562);
    glVertex2i(40,580);
    glVertex2i(20,580);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.965, 0.976, 1);
    glVertex2i(20,600);
    glVertex2i(40,600);
    glVertex2i(40,620);
    glVertex2i(20,620);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.965, 0.976, 1);
    glVertex2i(60,600);
    glVertex2i(80,600);
    glVertex2i(80,620);
    glVertex2i(60,620);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(20,562);
    glVertex2f(20,580);

    glVertex2f(30,562);
    glVertex2f(30,580);

    glVertex2f(20,570);
    glVertex2f(40,570);

    glVertex2f(20,580);
    glVertex2f(40,580);

    glVertex2f(40,580);
    glVertex2f(40,562);

    glVertex2f(40,562);
    glVertex2f(20,562);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(20,600);
    glVertex2f(20,620);

    glVertex2f(20,620);
    glVertex2f(40,620);

    glVertex2f(40,620);
    glVertex2f(40,600);

    glVertex2f(40,600);
    glVertex2f(20,600);

    glVertex2f(20,610);
    glVertex2f(40,610);

    glVertex2f(30,600);
    glVertex2f(30,620);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(0.122, 0.122, 0.122);
    glVertex2f(60,600);
    glVertex2f(80,600);

    glVertex2f(80,600);
    glVertex2f(80,620);

    glVertex2f(80,620);
    glVertex2f(60,620);

    glVertex2f(60,620);
    glVertex2f(60,600);

    glVertex2f(60,610);
    glVertex2f(80,610);

    glVertex2f(70,600);
    glVertex2f(70,620);
    glEnd();

//HOUSE4
    //base
    glBegin(GL_QUADS);
    glColor3f(1, 0.737, 0.365);
    glVertex2i(290,560);
    glVertex2i(330, 560);
    glVertex2i(330, 680);
    glVertex2i(290, 680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(290,560);
    glVertex2i(330, 560);
    glVertex2i(330, 680);
    glVertex2i(290, 680);
    glVertex2i(290,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(300,570);
    glVertex2i(320, 570);
    glVertex2i(320, 590);
    glVertex2i(300, 590);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(300,610);
    glVertex2i(320,610);
    glVertex2i(320,630);
    glVertex2i(300,630);
    glEnd();



    //window1
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(300,570);
    glVertex2i(320, 570);
    glVertex2i(320, 590);
    glVertex2i(300, 590);
    glVertex2i(300,570);
    glEnd();
    //window2
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(300,610);
    glVertex2i(320,610);
    glVertex2i(320,630);
    glVertex2i(300,630);
    glVertex2i(300,610);
    glEnd();


    //roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(310,710);
    glVertex2i(330,680);
    glVertex2i(290,680);
    glEnd();



    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(310,710);
    glVertex2i(330,680);
    glVertex2i(290,680);
    glVertex2i(310,710);
    glEnd();



    //circle
    glColor3f(1, 1, 1);
    circle360(10,10,310,660);
    //halfcircle1
    circle0to160(10,10,310,590);
    //halfcircle2
    circle0to160(10,10,310,630);

    glColor3f(0,0,0);
    drawCircleOutline(310,660,10,80);
    drawHalfCircleOutline(310,590,10,50);
    drawHalfCircleOutline(310,630,10,50);

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(310,570);
    glVertex2i(310,590);
    glVertex2i(310,610);
    glVertex2i(310,630);
    glVertex2i(300,580);
    glVertex2i(320,580);
    glVertex2i(300,620);
    glVertex2i(320,620);
    glEnd();



//HOUSE5
    //base
    glBegin(GL_QUADS);
    glColor3f(1, 0.737, 0.365);
    glVertex2i(380,560);
    glVertex2i(480, 560);
    glVertex2i(480, 660);
    glVertex2i(380, 660);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(380,560);
    glVertex2i(480, 560);
    glVertex2i(480, 660);
    glVertex2i(380, 660);
    glVertex2i(380,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(440,590);
    glVertex2i(460,590);
    glVertex2i(460,610);
    glVertex2i(440,610);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(440,630);
    glVertex2i(460,630);
    glVertex2i(460,650);
    glVertex2i(440,650);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(400,630);
    glVertex2i(420,630);
    glVertex2i(420,650);
    glVertex2i(400,650);
    //window4
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(400,590);
    glVertex2i(420,590);
    glVertex2i(420,610);
    glVertex2i(400,610);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(440,590);
    glVertex2i(460,590);
    glVertex2i(460,610);
    glVertex2i(440,610);
    glVertex2i(440,590);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(440,630);
    glVertex2i(460,630);
    glVertex2i(460,650);
    glVertex2i(440,650);
    glVertex2i(440,630);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(400,630);
    glVertex2i(420,630);
    glVertex2i(420,650);
    glVertex2i(400,650);
    glVertex2i(400,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(400,590);
    glVertex2i(420,590);
    glVertex2i(420,610);
    glVertex2i(400,610);
    glVertex2i(400,590);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex2i(450,590);
    glVertex2i(450,610);

    glVertex2i(450,630);
    glVertex2i(450,650);

    glVertex2i(410,630);
    glVertex2i(410,650);

    glVertex2i(440,600);
    glVertex2i(460,600);

    glVertex2i(400,600);
    glVertex2i(420,600);

    glVertex2i(440,640);
    glVertex2i(460,640);

    glVertex2i(400,640);
    glVertex2i(420,640);
    glEnd();


    //roof
    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(360,660);
    glVertex2i(500,660);
    glVertex2i(480,680);
    glVertex2i(380,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(360,660);
    glVertex2i(500,660);
    glVertex2i(480,680);
    glVertex2i(380,680);
    glVertex2i(360,660);
    glEnd();

//HOUSE6
    //base
    glBegin(GL_QUADS);
    glColor3f(0.478, 0.592, 0.627);
    glVertex2i(330,560);
    glVertex2i(410, 560);
    glVertex2i(410, 640);
    glVertex2i(330, 640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,560);
    glVertex2i(410, 560);
    glVertex2i(410, 640);
    glVertex2i(330, 640);
    glVertex2i(330,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(370,560);
    glVertex2i(400, 560);
    glVertex2i(400, 570);
    glVertex2i(370, 570);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,560);
    glVertex2i(400, 560);
    glVertex2i(400, 570);
    glVertex2i(370, 570);
    glVertex2i(370,560);
    glEnd();
    //window2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(370,580);
    glVertex2i(400,580);
    glVertex2i(400,600);
    glVertex2i(370,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,580);
    glVertex2i(400,580);
    glVertex2i(400,600);
    glVertex2i(370,600);
    glVertex2i(370,580);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(370,610);
    glVertex2i(400,610);
    glVertex2i(400,630);
    glVertex2i(370,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(370,610);
    glVertex2i(400,610);
    glVertex2i(400,630);
    glVertex2i(370,630);
    glVertex2i(370,610);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(330,580);
    glVertex2i(360,580);
    glVertex2i(360,600);
    glVertex2i(330,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,580);
    glVertex2i(360,580);
    glVertex2i(360,600);
    glVertex2i(330,600);
    glVertex2i(330,580);
    glEnd();

    //window5
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(330,610);
    glVertex2i(360,610);
    glVertex2i(360,630);
    glVertex2i(330,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,610);
    glVertex2i(360,610);
    glVertex2i(360,630);
    glVertex2i(330,630);
    glVertex2i(330,610);
    glEnd();

//HOUSE7
    //base
    glBegin(GL_QUADS);
    glColor3f(0.949, 0.435, 0.165);
    glVertex2i(480,560);
    glVertex2i(570,560);
    glVertex2i(570,650);
    glVertex2i(480,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(480,560);
    glVertex2i(570,560);
    glVertex2i(570,650);
    glVertex2i(480,650);
    glVertex2i(480,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(490,580);
    glVertex2i(520,580);
    glVertex2i(520,600);
    glVertex2i(490,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,580);
    glVertex2i(520,580);
    glVertex2i(520,600);
    glVertex2i(490,600);
    glVertex2i(490,580);
    glEnd();

    //window2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(490,620);
    glVertex2i(520,620);
    glVertex2i(520,640);
    glVertex2i(490,640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,620);
    glVertex2i(520,620);
    glVertex2i(520,640);
    glVertex2i(490,640);
    glVertex2i(490,620);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(530,620);
    glVertex2i(560,620);
    glVertex2i(560,640);
    glVertex2i(530,640);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(530,620);
    glVertex2i(560,620);
    glVertex2i(560,640);
    glVertex2i(530,640);
    glVertex2i(530,620);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(530,580);
    glVertex2i(560,580);
    glVertex2i(560,600);
    glVertex2i(530,600);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(530,580);
    glVertex2i(560,580);
    glVertex2i(560,600);
    glVertex2i(530,600);
    glVertex2i(530,580);
    glEnd();



//HOUSE8
    //base
    glBegin(GL_QUADS);
    glColor3f(0.827, 0.58, 0.478);
    glVertex2i(570,560);
    glVertex2i(670,560);
    glVertex2i(670,690);
    glVertex2i(570,690);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(570,560);
    glVertex2i(670,560);
    glVertex2i(670,690);
    glVertex2i(570,690);
    glVertex2i(570,560);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.827, 0.58, 0.478);
    glVertex2i(580,690);
    glVertex2i(660,690);
    glVertex2i(660,720);
    glVertex2i(580,720);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,690);
    glVertex2i(660,690);
    glVertex2i(660,720);
    glVertex2i(580,720);
    glVertex2i(580,690);
    glEnd();

    //door
    glColor3f(1, 1, 1);
    circle360(20,10,620,610);
    glColor3f(0,0,0);
    drawCircleOutline1(20,10,620,610);

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(600,560);
    glVertex2i(640,560);
    glVertex2i(640,610);
    glVertex2i(600,610);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(600,560);
    glVertex2i(640,560);
    glVertex2i(640,610);
    glVertex2i(600,610);
    glVertex2i(600,560);
    glEnd();

    //window1
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(580,630);
    glVertex2i(600,630);
    glVertex2i(600,650);
    glVertex2i(580,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,630);
    glVertex2i(600,630);
    glVertex2i(600,650);
    glVertex2i(580,650);
    glVertex2i(580,630);
    glEnd();

    //window2
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(610,630);
    glVertex2i(630,630);
    glVertex2i(630,650);
    glVertex2i(610,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(610,630);
    glVertex2i(630,630);
    glVertex2i(630,650);
    glVertex2i(610,650);
    glVertex2i(610,630);
    glEnd();

    //window3
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(640,630);
    glVertex2i(660,630);
    glVertex2i(660,650);
    glVertex2i(640,650);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(640,630);
    glVertex2i(660,630);
    glVertex2i(660,650);
    glVertex2i(640,650);
    glVertex2i(640,630);
    glEnd();

    //window4
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(640,660);
    glVertex2i(660,660);
    glVertex2i(660,680);
    glVertex2i(640,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(640,660);
    glVertex2i(660,660);
    glVertex2i(660,680);
    glVertex2i(640,680);
    glVertex2i(640,660);
    glEnd();

    //window5
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(610,660);
    glVertex2i(630,660);
    glVertex2i(630,680);
    glVertex2i(610,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(610,660);
    glVertex2i(630,660);
    glVertex2i(630,680);
    glVertex2i(610,680);
    glVertex2i(610,660);
    glEnd();

    //window6
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(580,660);
    glVertex2i(600,660);
    glVertex2i(600,680);
    glVertex2i(580,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,660);
    glVertex2i(600,660);
    glVertex2i(600,680);
    glVertex2i(580,680);
    glVertex2i(580,660);
    glEnd();

    //roof
    glBegin(GL_TRIANGLES);
    glColor3f(0.49, 0.184, 0.102);
    glVertex2i(580,720);
    glVertex2i(660,720);
    glVertex2i(620,750);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(580,720);
    glVertex2i(660,720);
    glVertex2i(620,750);
    glVertex2i(580,720);
    glEnd();

    //flag board

    glBegin(GL_QUADS);
    glColor3f(0.878, 0.863, 0.698);
    glVertex2i(670,560);
    glVertex2i(680,560);
    glVertex2i(680,680);
    glVertex2i(670,680);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(670,560);
    glVertex2i(680,560);
    glVertex2i(680,680);
    glVertex2i(670,680);
    glVertex2i(670,560);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex2i(680,640);
    glVertex2i(730,640);
    glVertex2i(730,670);
    glVertex2i(680,670);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(680,640);
    glVertex2i(730,640);
    glVertex2i(730,670);
    glVertex2i(680,670);
    glVertex2i(680,640);
    glEnd();

    //hotel word
    glColor3f(0.0, 0.0, 0.0);
    circle360(3,5,697,655);

    glColor3f(1,1,1);
    circle360(1,3,697,655);


    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);
    //H
    glVertex2d(685, 650);
    glVertex2d(685, 660);

    glVertex2d(685, 655);
    glVertex2d(690,655);

    glVertex2d(690, 650);
    glVertex2d(690, 660);
    //T
    glVertex2d(705, 650);
    glVertex2d(705, 660);

    glVertex2d(702, 660);
    glVertex2d(708,660);
    //E
    glVertex2d(710, 650);
    glVertex2d(710, 660);

    glVertex2d(710, 650);
    glVertex2d(714,650);

    glVertex2d(710, 655);
    glVertex2d(714, 655);

    glVertex2d(710, 660);
    glVertex2d(714, 660);

    //L
    glVertex2d(718, 650);
    glVertex2d(718, 660);

    glVertex2d(718, 650);
    glVertex2d(722,650);

    glEnd();






//GREEN CIRCLE
    glColor3f(0.047, 0.392, 0.063);
    circle360(30,30,80,560);
    circle360(20,20,160,560);
    circle360(30,30,260,560);
    circle360(20,20,340,560);
    circle360(30,30,440,560);
    circle360(20,20,520,560);
    circle360(30,30,620,560);
    circle360(20,20,700,560);
    circle360(30,30,800,560);
    circle360(20,20,880,560);
    circle360(30,30,970,560);

    glColor3f(0, 0, 0);
    drawHalfCircleOutline(80,560,30,160);
    drawHalfCircleOutline(160,560,20,120);
    drawHalfCircleOutline(260,560,30,160);
    drawHalfCircleOutline(340,560,20,120);
    drawHalfCircleOutline(440,560,30,160);
    drawHalfCircleOutline(520,560,20,120);
    drawHalfCircleOutline(620,560,30,160);
    drawHalfCircleOutline(700,560,20,120);
    drawHalfCircleOutline(800,560,30,160);
    drawHalfCircleOutline(880,560,20,120);
    drawHalfCircleOutline(970,560,30,160);


    //ROAD

    glBegin(GL_QUADS);
    glColor3f(0.298, 0.298, 0.29);
    glVertex2i(0,380);
    glVertex2i(1000,380);
    glVertex2i(1000,520);
    glVertex2i(0,520);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0,380);
    glVertex2i(1000,380);
    glVertex2i(1000,520);
    glVertex2i(0,520);
    glVertex2i(0,380);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(10,440);
    glVertex2i(130,440);
    glVertex2i(130,460);
    glVertex2i(10,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(10,440);
    glVertex2i(130,440);
    glVertex2i(130,460);
    glVertex2i(10,460);
    glVertex2i(10,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(170,440);
    glVertex2i(290,440);
    glVertex2i(290,460);
    glVertex2i(170,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(170,440);
    glVertex2i(290,440);
    glVertex2i(290,460);
    glVertex2i(170,460);
    glVertex2i(170,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(330,440);
    glVertex2i(450,440);
    glVertex2i(450,460);
    glVertex2i(330,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(330,440);
    glVertex2i(450,440);
    glVertex2i(450,460);
    glVertex2i(330,460);
    glVertex2i(330,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(490,440);
    glVertex2i(610,440);
    glVertex2i(610,460);
    glVertex2i(490,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(490,440);
    glVertex2i(610,440);
    glVertex2i(610,460);
    glVertex2i(490,460);
    glVertex2i(490,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(650,440);
    glVertex2i(770,440);
    glVertex2i(770,460);
    glVertex2i(650,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(650,440);
    glVertex2i(770,440);
    glVertex2i(770,460);
    glVertex2i(650,460);
    glVertex2i(650,440);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1,1,1);
    glVertex2i(810,440);
    glVertex2i(930,440);
    glVertex2i(930,460);
    glVertex2i(810,460);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(810,440);
    glVertex2i(930,440);
    glVertex2i(930,460);
    glVertex2i(810,460);
    glVertex2i(810,440);
    glEnd();

    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1, 1, 1);
    glVertex2f(0,390);
    glVertex2f(1000,390);

    glVertex2f(1000,510);
    glVertex2f(0,510);
    glEnd();

    cars();

    schoolbus();
//road border
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.42, 0.392);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();

    //road relling
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(0,395);
    glVertex2i(680,395);
    glVertex2i(680,405);
    glVertex2i(0,405);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(0,395);
    glVertex2i(680,395);
    glVertex2i(680,405);
    glVertex2i(0,405);
    glVertex2i(0,395);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(10,360);
    glVertex2i(30,360);
    glVertex2i(30,420);
    glVertex2i(10,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(10,360);
    glVertex2i(30,360);
    glVertex2i(30,420);
    glVertex2i(10,420);
    glVertex2i(10,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(60,360);
    glVertex2i(80,360);
    glVertex2i(80,420);
    glVertex2i(60,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(60,360);
    glVertex2i(80,360);
    glVertex2i(80,420);
    glVertex2i(60,420);
    glVertex2i(60,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(110,360);
    glVertex2i(130,360);
    glVertex2i(130,420);
    glVertex2i(110,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(110,360);
    glVertex2i(130,360);
    glVertex2i(130,420);
    glVertex2i(110,420);
    glVertex2i(110,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(160,360);
    glVertex2i(180,360);
    glVertex2i(180,420);
    glVertex2i(160,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(160,360);
    glVertex2i(180,360);
    glVertex2i(180,420);
    glVertex2i(160,420);
    glVertex2i(160,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(210,360);
    glVertex2i(230,360);
    glVertex2i(230,420);
    glVertex2i(210,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(210,360);
    glVertex2i(230,360);
    glVertex2i(230,420);
    glVertex2i(210,420);
    glVertex2i(210,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(260,360);
    glVertex2i(280,360);
    glVertex2i(280,420);
    glVertex2i(260,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(260,360);
    glVertex2i(280,360);
    glVertex2i(280,420);
    glVertex2i(260,420);
    glVertex2i(260,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(310,360);
    glVertex2i(330,360);
    glVertex2i(330,420);
    glVertex2i(310,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(310,360);
    glVertex2i(330,360);
    glVertex2i(330,420);
    glVertex2i(310,420);
    glVertex2i(310,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(360,360);
    glVertex2i(380,360);
    glVertex2i(380,420);
    glVertex2i(360,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(360,360);
    glVertex2i(380,360);
    glVertex2i(380,420);
    glVertex2i(360,420);
    glVertex2i(360,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(410,360);
    glVertex2i(430,360);
    glVertex2i(430,420);
    glVertex2i(410,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(410,360);
    glVertex2i(430,360);
    glVertex2i(430,420);
    glVertex2i(410,420);
    glVertex2i(410,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(460,360);
    glVertex2i(480,360);
    glVertex2i(480,420);
    glVertex2i(460,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(460,360);
    glVertex2i(480,360);
    glVertex2i(480,420);
    glVertex2i(460,420);
    glVertex2i(460,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(510,360);
    glVertex2i(530,360);
    glVertex2i(530,420);
    glVertex2i(510,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(510,360);
    glVertex2i(530,360);
    glVertex2i(530,420);
    glVertex2i(510,420);
    glVertex2i(510,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(560,360);
    glVertex2i(580,360);
    glVertex2i(580,420);
    glVertex2i(560,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(560,360);
    glVertex2i(580,360);
    glVertex2i(580,420);
    glVertex2i(560,420);
    glVertex2i(560,360);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.424, 0.031, 0.031);
    glVertex2i(610,360);
    glVertex2i(630,360);
    glVertex2i(630,420);
    glVertex2i(610,420);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(610,360);
    glVertex2i(630,360);
    glVertex2i(630,420);
    glVertex2i(610,420);
    glVertex2i(610,360);
    glEnd();



//OCEAN

    glBegin(GL_QUADS);
    glColor3f(0.29, 0.569, 0.894);
    glVertex2i(0,0);
    glVertex2i(1000,0);
    glVertex2i(1000,380);
    glVertex2i(0,380);
    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.286, 0.502, 0.89);
    glVertex2i(690,330);
    glVertex2i(730,330);

    glVertex2i(760,330);
    glVertex2i(800,330);

    glVertex2i(830,330);
    glVertex2i(870,330);

    glVertex2i(900,330);
    glVertex2i(940,330);

    glVertex2i(970,330);
    glVertex2i(1000,330);

    glVertex2i(700,320);
    glVertex2i(720,320);

    glVertex2i(770,320);
    glVertex2i(790,320);

    glVertex2i(840,320);
    glVertex2i(860,320);

    glVertex2i(910,320);
    glVertex2i(930,320);

    glVertex2i(980,320);
    glVertex2i(1000,320);

    glEnd();

    //ship
    glBegin(GL_QUADS);
    glColor3f(0.816, 0.459, 0.114);
    glVertex2i(830,230);
    glVertex2i(970,230);
    glVertex2i(980,250);
    glVertex2i(820,250);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(830,230);
    glVertex2i(970,230);
    glVertex2i(980,250);
    glVertex2i(820,250);
    glVertex2i(830,230);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.259, 0.718, 0.329);
    glVertex2i(830,250);
    glVertex2i(970,250);
    glVertex2i(970,270);
    glVertex2i(830,270);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(830,250);
    glVertex2i(970,250);
    glVertex2i(970,270);
    glVertex2i(830,270);
    glVertex2i(830,250);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2i(850,270);
    glVertex2i(870,270);
    glVertex2i(870,300);
    glVertex2i(850,300);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2i(890,270);
    glVertex2i(910,270);
    glVertex2i(910,300);
    glVertex2i(890,300);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0,0,0);
    glVertex2i(930,270);
    glVertex2i(950,270);
    glVertex2i(950,300);
    glVertex2i(930,300);
    glEnd();
//0.384, 0.451, 0.525
    glColor3f(1,1,1);
    circle360(5,5,860,305);
    circle360(5,5,860,310);
    circle360(5,5,865,315);
    circle360(5,5,870,320);
    circle360(5,5,875,325);

    circle360(5,5,900,305);
    circle360(5,5,900,310);
    circle360(5,5,905,315);
    circle360(5,5,910,320);
    circle360(5,5,915,325);

    circle360(5,5,940,305);
    circle360(5,5,940,310);
    circle360(5,5,945,315);
    circle360(5,5,950,320);
    circle360(5,5,955,325);

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.286, 0.502, 0.89);
    glVertex2i(800,230);
    glVertex2i(1000,230);

    glVertex2i(800,220);
    glVertex2i(840,220);

    glVertex2i(860,220);
    glVertex2i(900,220);

    glVertex2i(920,220);
    glVertex2i(960,220);

    glVertex2i(820,210);
    glVertex2i(870,210);

    glVertex2i(890,210);
    glVertex2i(940,210);

    glVertex2i(950,210);
    glVertex2i(1000,210);

    glEnd();



    boat();

    fish();


    //road border
    glBegin(GL_QUADS);
    glColor3f(0.424, 0.42, 0.392);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glColor3f(0,0,0);
    glVertex2i(0, 520);
    glVertex2i(1000, 520);
    glVertex2i(1000, 535);
    glVertex2i(0, 535);
    glEnd();


//BEACH




    glBegin(GL_POLYGON);
    glColor3f(0.961, 0.757, 0.447);
    glVertex2d(0,0);
    glVertex2d(250,0);
    glVertex2d(430,130);
    glVertex2d(370,130);
    glVertex2d(530,230);
    glVertex2d(450,230);
    glVertex2d(630,380);
    glVertex2d(0,380);
    glEnd();

    //curve
    glColor3f(0.29, 0.569, 0.894);
    circle360(30,15,480,235);
    circle360(30,15,400,135);
    circle360(30,15,280,5);



    glBegin(GL_TRIANGLES);
    glColor3f(0.29, 0.569, 0.894);
    glVertex2i(460,245);
    glVertex2i(460,235);
    glVertex2d(575,310);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.29, 0.569, 0.894);
    glVertex2i(480,220);
    glVertex2i(530,230);
    glVertex2d(530,240);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.29, 0.569, 0.894);
    glVertex2i(390,145);
    glVertex2i(390,135);
    glVertex2d(510,200);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.29, 0.569, 0.894);
    glVertex2i(260,15);
    glVertex2i(280,5);
    glVertex2d(370,80);
    glEnd();
    glColor3f(0.788, 0.286, 0.227);
    drawStar(250,330,25);
    glColor3f(0,0,0);
    drawStar(250,330,15);

    glColor3f(0,0,0);
    circle360(52,22,260,80);

    glColor3f(1, 0.894, 0.098);
    circle360(50,20,260,80);

    glColor3f(0,0,0);
    circle360(32,12,260,85);


    glColor3f(0.961, 0.757, 0.447);
    circle360(30,10,260,85);







    //big tree


        glColor3f(0.173, 0.278, 0.11);
        circle360(100,100,50,400);
        circle360(20,20,50,300);
        circle360(30,30,80,310);
        circle360(20,20,110,320);
        circle360(20,20,130,330);
        circle360(30,30,130,360);
        circle360(20,20,150,370);
        circle360(30,30,150,380);
        circle360(20,20,150,400);
        circle360(30,30,130,420);
        circle360(20,20,120,440);
        circle360(30,30,130,460);
        circle360(20,20,100,480);
        circle360(30,30,80,500);
        circle360(20,20,50,500);
        circle360(30,30,20,500);

        glColor3f(0.137, 0.604, 0.031);
        circle360(100,100,50,400);
        circle360(15,15,50,300);
        circle360(25,25,80,310);
        circle360(15,15,110,320);
        circle360(15,15,130,330);
        circle360(25,25,130,360);
        circle360(15,15,150,370);
        circle360(25,25,150,380);
        circle360(15,15,150,400);
        circle360(25,25,130,420);
        circle360(15,15,120,440);
        circle360(25,25,130,460);
        circle360(15,15,100,480);
        circle360(25,25,80,500);
        circle360(15,15,50,500);
        circle360(25,25,20,500);

        glBegin(GL_QUADS);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(0,0);
        glVertex2d(40,0);
        glVertex2d(40,330);
        glVertex2d(0,330);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(40,310);
        glVertex2d(100,380);
        glVertex2d(80,380);
        glVertex2d(30,330);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(40,330);
        glVertex2d(0,380);
        glVertex2d(0,360);
        glVertex2d(25,330);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(40,330);
        glVertex2d(0,350);
        glVertex2d(0,330);
        glVertex2d(30,330);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(30,330);
        glVertex2d(40,330);
        glVertex2d(52,380);
        glVertex2d(40,380);
        glEnd();


/*glBegin(GL_POLYGON);
        glColor3f(0.388, 0.227, 0.086);
        glVertex2d(70,0);
        glVertex2d(60,10);
        glVertex2d(55,15);
        glVertex2d(45,30);
        glVertex2d(40,40);
        glVertex2d(35,50);
        glVertex2d(30,60);
        glVertex2d(25,70);
        glVertex2d(25,0);
        glEnd();


        /*glColor3f(0, 0, 0); // Black color for outline
        glLineWidth(2); // Line width for the outline
        glBegin(GL_LINE_LOOP);
        glVertex2d(70, 0);
        glVertex2d(60, 10);
        glVertex2d(55, 15);
        glVertex2d(45, 30);
        glVertex2d(40, 40);
        glVertex2d(35, 50);
        glVertex2d(30, 60);
        glVertex2d(25, 70);
        glVertex2d(25, 0);
        glEnd();
          glColor3f(0.173, 0.278, 0.11);
        circle360(20,20,90,380);
        circle360(10,10,90,360);
        circle360(10,10,110,370);
        circle360(10,10,110,390);
        circle360(10,10,90,400);
        circle360(10,10,70,390);
        circle360(10,10,70,370);*/

//uUMBRELLA

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(120,30);
    glVertex2i(140,30);
    glVertex2i(140,180);
    glVertex2i(120,180);
    glEnd();
    glLineWidth(2); // Line width for the outline
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(120,30);
    glVertex2i(140,30);
    glVertex2i(140,180);
    glVertex2i(120,180);
    glVertex2i(120,30);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.992, 0.031, 0.031);
    glVertex2i(130,290);
    glVertex2i(0,180);
    glVertex2i(30,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(0,180);
    glVertex2i(30,180);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.996, 0.561, 0.102);
    glVertex2i(130,290);
    glVertex2i(30,180);
    glVertex2i(70,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(30,180);
    glVertex2i(70,180);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0.125);
    glVertex2i(130,290);
    glVertex2i(70,180);
    glVertex2i(130,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(70,180);
    glVertex2i(130,180);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.18, 0.902, 0.286);
    glVertex2i(130,290);
    glVertex2i(130,180);
    glVertex2i(190,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(130,180);
    glVertex2i(190,180);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.031, 0.412, 0.973);
    glVertex2i(130,290);
    glVertex2i(190,180);
    glVertex2i(230,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(190,180);
    glVertex2i(230,180);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(0.992, 0.031, 0.031);
    glVertex2i(130,290);
    glVertex2i(230,180);
    glVertex2i(270,180);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(130,290);
    glVertex2i(230,180);
    glVertex2i(270,180);
    glVertex2i(130,290);
    glEnd();

    glColor3f(1,1,1);
    circle180to360(15,10,15,180);
    circle180to360(15,10,45,180);
    circle180to360(15,10,75,180);
    circle180to360(15,10,105,180);
    circle180to360(15,10,135,180);
    circle180to360(15,10,165,180);
    circle180to360(15,10,195,180);
    circle180to360(15,10,225,180);
    circle180to360(15,10,255,180);


    glColor3f(0,0,0);
    drawHalfCircleOutline2(15, 10, 15, 180);
    drawHalfCircleOutline2(15, 10, 45, 180);
    drawHalfCircleOutline2(15, 10, 75, 180);
    drawHalfCircleOutline2(15, 10, 105, 180);
    drawHalfCircleOutline2(15, 10, 135, 180);
    drawHalfCircleOutline2(15, 10, 165, 180);
    drawHalfCircleOutline2(15, 10, 195, 180);
    drawHalfCircleOutline2(15, 10, 225, 180);
    drawHalfCircleOutline2(15, 10, 255, 180);


//chair
    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(180,0);
    glVertex2i(190,0);
    glVertex2i(190,40);
    glVertex2i(180,40);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(180,0);
    glVertex2i(190,0);
    glVertex2i(190,40);
    glVertex2i(180,40);
    glVertex2i(180,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.937, 0.922, 0.247);
    glVertex2i(40,110);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(90,160);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(40,110);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(90,160);
    glVertex2i(40,110);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.937, 0.922, 0.247);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(200,42);
    glVertex2i(110,0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(90,30);
    glVertex2i(140,82);
    glVertex2i(200,42);
    glVertex2i(110,0);
    glVertex2i(90,30);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(20,110);
    glVertex2i(30,120);
    glVertex2i(120,0);
    glVertex2i(110,0);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(20,110);
    glVertex2i(30,120);
    glVertex2i(120,0);
    glVertex2i(110,0);
    glVertex2i(20,110);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(42,0);
    glVertex2i(58,0);
    glVertex2i(72,50);
    glVertex2i(62,60);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(42,0);
    glVertex2i(58,0);
    glVertex2i(72,50);
    glVertex2i(62,60);
    glVertex2i(42,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.376, 0.169, 0.035);
    glVertex2i(80,150);
    glVertex2i(90,160);
    glVertex2i(80,170);
    glVertex2i(70,160);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(80,150);
    glVertex2i(90,160);
    glVertex2i(80,170);
    glVertex2i(70,160);
    glVertex2i(80,150);
    glEnd();

    glColor3f(0.996, 0.039, 0.031);
    circle360(15,15,180,100);
    glColor3f(0,0,0);
    drawCircleOutline(180,100,15,100);
    glColor3f(1,1,1);
    circle360(6,2,180,108);

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glColor3f(0.749, 0.557, 0.267);
    glVertex2i(160,80);
    glVertex2i(200,80);

    glVertex2i(170,85);
    glVertex2i(190,85);

    glEnd();





//bridge
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(650,380);
    glVertex2i(1000,380);
    glVertex2i(1000,410);
    glVertex2i(680,410);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(650,380);
    glVertex2i(1000,380);
    glVertex2i(1000,410);
    glVertex2i(680,410);
    glVertex2i(650,380);
    glEnd();


    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(650,520);
    glVertex2i(1000,520);
    glVertex2i(1000,550);
    glVertex2i(680,550);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(650,520);
    glVertex2i(1000,520);
    glVertex2i(1000,550);
    glVertex2i(680,550);
    glVertex2i(650,520);
    glEnd();

    //bridge piller1
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(680,550);
    glVertex2i(700,550);
    glVertex2i(700,630);
    glVertex2i(680,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(680,550);
    glVertex2i(700,550);
    glVertex2i(700,630);
    glVertex2i(680,630);
    glVertex2i(680,550);
    glEnd();

    //bridge piller2
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(770,550);
    glVertex2i(790,550);
    glVertex2i(790,630);
    glVertex2i(770,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(770,550);
    glVertex2i(790,550);
    glVertex2i(790,630);
    glVertex2i(770,630);
    glVertex2i(770,550);
    glEnd();

    //bridge piller3
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(870,550);
    glVertex2i(890,550);
    glVertex2i(890,630);
    glVertex2i(870,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(870,550);
    glVertex2i(890,550);
    glVertex2i(890,630);
    glVertex2i(870,630);
    glVertex2i(870,550);
    glEnd();
    //bridge piller4
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(970,550);
    glVertex2i(990,550);
    glVertex2i(990,630);
    glVertex2i(970,630);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(970,550);
    glVertex2i(990,550);
    glVertex2i(990,630);
    glVertex2i(970,630);
    glVertex2i(970,550);
    glEnd();

    //bridge piller5
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(680,410);
    glVertex2i(700,410);
    glVertex2i(700,490);
    glVertex2i(680,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(680,410);
    glVertex2i(700,410);
    glVertex2i(700,490);
    glVertex2i(680,490);
    glVertex2i(680,410);
    glEnd();

    //bridge piller6
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(770,410);
    glVertex2i(790,410);
    glVertex2i(790,490);
    glVertex2i(770,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(770,410);
    glVertex2i(790,410);
    glVertex2i(790,490);
    glVertex2i(770,490);
    glVertex2i(770,410);
    glEnd();

    //bridge piller7
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(870,410);
    glVertex2i(890,410);
    glVertex2i(890,490);
    glVertex2i(870,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(870,410);
    glVertex2i(890,410);
    glVertex2i(890,490);
    glVertex2i(870,490);
    glVertex2i(870,410);
    glEnd();
    //bridge piller8
    glBegin(GL_QUADS);
    glColor3f(0.573, 0.282, 0.235);
    glVertex2i(970,410);
    glVertex2i(990,410);
    glVertex2i(990,490);
    glVertex2i(970,490);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(970,410);
    glVertex2i(990,410);
    glVertex2i(990,490);
    glVertex2i(970,490);
    glVertex2i(970,410);
    glEnd();

    glLineWidth(3.0);
    glColor3f(0,0,0);
    drawHalfCircleOutline2(35,30,735,620);
    drawHalfCircleOutline2(40,30,830,620);
    drawHalfCircleOutline2(40,30,930,620);

    drawHalfCircleOutline2(35,30,735,480);
    drawHalfCircleOutline2(40,30,830,480);
    drawHalfCircleOutline2(40,30,930,480);


//bridge lower piller
    //bridge piller1
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(700,330);
    glVertex2i(720,330);
    glVertex2i(720,380);
    glVertex2i(700,380);
    glEnd();
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(700,330);
    glVertex2i(720,330);
    glVertex2i(720,380);
    glVertex2i(700,380);
    glVertex2i(700,330);
    glEnd();

    //bridge piller2
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(770,330);
    glVertex2i(790,330);
    glVertex2i(790,380);
    glVertex2i(770,380);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(770,330);
    glVertex2i(790,330);
    glVertex2i(790,380);
    glVertex2i(770,380);
    glVertex2i(770,330);
    glEnd();

    //bridge piller3
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(840,330);
    glVertex2i(860,330);
    glVertex2i(860,380);
    glVertex2i(840,380);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(840,330);
    glVertex2i(860,330);
    glVertex2i(860,380);
    glVertex2i(840,380);
    glVertex2i(840,330);
    glEnd();

    //bridge piller4
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(910,330);
    glVertex2i(930,330);
    glVertex2i(930,380);
    glVertex2i(910,380);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(910,330);
    glVertex2i(930,330);
    glVertex2i(930,380);
    glVertex2i(910,380);
    glVertex2i(910,330);
    glEnd();

    //bridge piller5
    glBegin(GL_QUADS);
    glColor3f(0.831, 0.745, 0.655);
    glVertex2i(980,330);
    glVertex2i(1000,330);
    glVertex2i(1000,380);
    glVertex2i(980,380);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);
    glVertex2i(980,330);
    glVertex2i(1000,330);
    glVertex2i(1000,380);
    glVertex2i(980,380);
    glVertex2i(980,330);
    glEnd();

    glColor3f(0.29, 0.569, 0.894);
    circle0to160(25,20,745,375);
    circle0to160(25,20,815,375);
    circle0to160(25,20,885,375);
    circle0to160(25,20,955,375);
    glColor3f(0,0,0);
    drawHalfCircleOutline3(25,20,745,375);
    drawHalfCircleOutline3(25,20,815,375);
    drawHalfCircleOutline3(25,20,885,375);
    drawHalfCircleOutline3(25,20,955,375);


    /*  glColor3f(1, 1, 1); // White color for the steam circles
      for (int i = 0; i < 15; i++) {
          steamcircle(5, circleX[i], circleY[i]);
      }

    for (int i = 0; i < 15; i++) {
          circleY[i] += speed;
          circleX[i] += x_increment;
          if (circleY[i] > 1000) {
              circleY[i] = 305;
              circleX[i] -= (1000 - 305) * x_increment; // Reset X position appropriately
          }
      }
      glutPostRedisplay();*/



}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
        scenary = 1; // Set scene to 1
        break;
    case 'n':
        scenary = 2; // Set scene to 2
        break;
     case '1':
        scenary = 3; // Set scene to day rain
        break;
    case '2':
        scenary = 4; // Set scene to night rain
        break;
    case 'a': // Move left
            shiftX -= 30; // Adjust the step size as needed
            direction = 1; // Facing left
            break;
     case 's': // Move right
            shiftX += 30; // Adjust the step size as needed
            direction = -1; // Facing right
            break;


    }
    glutPostRedisplay();
}


void initRain() {
    srand(time(NULL));
    for (int i = 0; i < MAX_RAIN_DROPS; i++) {
        rainDrops[i].x = (float)(rand() % 2500);
        rainDrops[i].y = (float)(rand() % 2500);
        rainDrops[i].speed = (float)(rand() % 5 + 5);
    }
}

void drawRain() {
    glColor3f(1,1,1); // Light blue for day rain
    if (scenary == 2) {
        glColor3f(0.678, 0.847, 0.902); // Lighter blue for night rain
    }
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAIN_DROPS; i++) {
        glVertex2f(rainDrops[i].x, rainDrops[i].y);
        glVertex2f(rainDrops[i].x, rainDrops[i].y - 10);
    }
    glEnd();
}

void updateRain() {
    for (int i = 0; i < MAX_RAIN_DROPS; i++) {
        rainDrops[i].y -= rainDrops[i].speed;
        if (rainDrops[i].y < 0) {
            rainDrops[i].x = (float)(rand() % 2500);
            rainDrops[i].y = 1000;
        }
    }
    glutPostRedisplay();
}

void drawDayRain() {
    // Draw the day rain scene
    glClearColor(0.529, 0.808, 0.922, 1.0); // Light blue background
    glClear(GL_COLOR_BUFFER_BIT);

    scenary1();
    drawRain();

}

void drawNightRain() {
    // Draw the night rain scene
    glClearColor(0.098, 0.098, 0.439, 1.0); // Dark blue background
    glClear(GL_COLOR_BUFFER_BIT);

    scenary2();
    drawRain();

}

void timer(int value) {
    updateRain();
    glutTimerFunc(30, timer, 0);
}


void display()
{


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black
    // Draw green roadside
    // Draw the current scene based on the 'scene' variable
    if (scenary == 1) {
        scenary1();
    }
    else if (scenary == 2) {
        scenary2();
    }
    else if (scenary == 3) {
        drawDayRain();
    }
    else
        drawNightRain();

    glutDisplayFunc(display);

    glutKeyboardFunc(key);
    glutTimerFunc(30, timer, 0);

    glFlush();
    glutSwapBuffers();
}



void init()
{
    glClearColor(1.0, 1.0, 1.0, 0); // Set clear color to white
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1000, 0, 1000); // Set the window size
    initRain();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000); // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("OpenGL GLUT Project");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
