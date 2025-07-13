#include <windows.h>
#include <GL/glut.h>
#include <cmath>
#include <cctype>
enum SceneMode { DAY, NIGHT, WINTER, MONSOON };
SceneMode currentScene = DAY;
float cloudPosition1 = -1.2f;
float cloudPosition2 = -1.2f;
float birdX = -1.0f;
float birdY = 0.5f;
float bird2X = -1.0f;
float bird2Y = 0.4f;
float bird3X = -1.0f;
float bird3Y = 0.6f;
float cartX = -0.8f;
float boatX = -0.9f;
float manY = 0.3f;
float womanY = 0.35f;
float boyY = 0.3f;
float sunflowerAngle = 0.0f;
bool swayRight = true;
float cropSwayAngle = 0.0f;
bool swayCropRight = true;
float bladeAngle = 0.0f;
float PI = 3.1416;
float cloud4Position14 = -1.2f;
float cloud4Position24 = -1.2f;
float birdX4 = -1.0f;
float birdY4 = 0.5f;
float bird2X4 = -1.0f;
float bird2Y4 = 0.4f;
float cartX4 = -0.8f;
float sunflower4Angle4 = 0.0f;
bool swayRight4 = true;
float crop4SwayAngle4 = 0.0f;
bool swaycrop4Right4 = true;
float bladeAngle4 = 0.0f;
float PI4 = 3.1416;
float snowY = 0.0f;
float smokeYOffset = 0.0f;
float fogDensity = 0.05f;
float cloud3Position13 = -1.2f;
float cloud3Position23 = -1.2f;
float rainX[200], rainY[200];
bool isLightning = false;
int lightningTimer = 0;
float rippleRadius = 0.0f;
bool expanding = true;
float jumpPhase = 0.0f;
float cartX3 = -0.8f;
float boat3X3 = -0.9f;
float man3Y3 = 0.3f;
float woman3Y3 = 0.35f;
float boy3Y4 = 0.3f;
float sunflowerAngle3 = 0.0f;
bool swayRight3 = true;
float crop3SwayAngle3 = 0.0f;
bool swaycrop3Right3 = true;
float bladeAngle3 = 0.0f;
float PI3 = 3.1416;
float cloud2Position12 = -1.2f;
float cloud2Position22 = -1.2f;
float birdX2 = -1.0f;
float birdY2 = 0.5f;
float bird2X2 = -1.0f;
float bird2Y2 = 0.4f;
float bird3X2 = -1.0f;
float bird3Y2 = 0.6f;
float cartX2 = -0.8f;
float boatX2 = -0.9f;
float manY2 = 0.3f;
float womanY2 = 0.35f;
float boyY2 = 0.3f;
float sunflower2Angle2 = 0.0f;
bool swayRight2 = true;
float crop2SwayAngle2 = 0.0f;
bool swaycrop2Right2 = true;
float bladeAngle2 = 0.0f;
float PI2 = 3.1416;
struct Ripple {
    float x, y;
    float radius;
    bool active;
};

Ripple ripples[20];
void initGL() {

    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
}
void ground()
{
    glColor3f(0.4f,0.7f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(1.0f,0.3f);
        glVertex2f(1.0f,-1.0f);
        glVertex2f(-1.0f,-1.0f);
    glEnd();
}

void hills()
{
    glPushMatrix();
    glTranslatef(-0.1f,0.03f,0.0f);
    glScalef(0.9f,0.9f,1.0f);

    glColor3f(0.0f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(-0.8f,0.5f);
        glVertex2f(-0.5f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f,0.3f);
        glVertex2f(-0.4f,0.5f);
        glVertex2f(-0.1f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f,0.3f);
        glVertex2f(0.0f,0.5f);
        glVertex2f(0.3f,0.3f);
    glEnd();
    glPopMatrix();
}

void drawCircle(float x, float y, float radius) {
    glPushMatrix();
    glScalef(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}

void cloud(float x, float y, float radius) {
    glPushMatrix();
    glScalef(0.7f,0.7f,0.7f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}
void windMill()
{
    glPushMatrix();
    glTranslatef(-0.15f,0.1f,0.5f);
    glScalef(0.7f,0.7f,0.6f);
    glColor3f(0.6f,0.4f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.17f,0.6f);
        glVertex2f(-0.13f,0.6f);
        glVertex2f(0.001f,0.2f);
        glVertex2f(-0.28f,0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.15f, 0.6f, 0.0f); // Move to hub center
    glRotatef(bladeAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

    glColor3f(1.0f, 0.7f, 0.2f);
    for (int i = 0; i < 3; i++) {
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate for each blade
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.05f, 0.15f);
            glVertex2f(-0.05f, 0.15f);
        glEnd();
    }

    glPopMatrix();

    glColor3f(0.2f,0.1f,0.0f);
    drawCircle(-0.15f,0.6f,0.04f);
    glPopMatrix();
}

void bushFlower(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(-0.01f, 0.0f, 0.01f);
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle(-0.0f, 0.01f, 0.01f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle(0.01f, 0.0f, 0.01f);
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle(0.0f, -0.01f, 0.01f);
    glColor3f(1.0f, 0.98f, 0.0f);
    drawCircle(-0.001f, 0.0f, 0.007f);
    glPopMatrix();

    glPopMatrix();

}

void bush(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.4f, 0.0f);
    drawCircle(-0.05f, 0.0f, 0.06f);
    drawCircle(0.0f, 0.02f, 0.07f);
    drawCircle(0.05f, 0.0f, 0.06f);

    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(-0.03f, 0.0f, 0.03f);
    drawCircle(0.0f, 0.02f, 0.04f);
    drawCircle(0.03f, 0.0f, 0.03f);

    bushFlower(0.0f, 0.06f, 1.0f);
    bushFlower(-0.04f, 0.28f, 1.2f);
    bushFlower(-0.16f, 0.28f, 1.2f);
    bushFlower(-0.96f, 0.28f, 1.2f);
    bushFlower(-0.85f, 0.28f, 1.2f);
    bushFlower(-0.76f, 0.28f, 1.2f);
    bushFlower(-0.65f, 0.28f, 1.2f);
    bushFlower(-0.56f, 0.28f, 1.2f);
    bushFlower(-0.45f, 0.28f, 1.2f);
    bushFlower(-0.36f, 0.28f, 1.2f);
    bushFlower(-0.25f, 0.28f, 1.2f);
    bushFlower(0.05f, 0.28f, 1.2f);
    bushFlower(0.15f, 0.28f, 1.2f);
    bushFlower(0.25f, 0.28f, 1.2f);
    bushFlower(0.35f, 0.28f, 1.2f);
    bushFlower(0.45f, 0.28f, 1.2f);
    bushFlower(0.55f, 0.28f, 1.2f);
    bushFlower(0.65f, 0.28f, 1.2f);
    bushFlower(0.75f, 0.28f, 1.2f);
    bushFlower(0.85f, 0.28f, 1.2f);
    bushFlower(0.95f, 0.28f, 1.2f);
    glPopMatrix();
}

void road1(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,-0.1f);
        glVertex2f(1.0f,-0.1f);
        glVertex2f(1.0f,-0.3f);
        glVertex2f(-1.0f,-0.3f);
    glEnd();
    glPopMatrix();
}

void road2(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f,0.3f);
        glVertex2f(0.1f,0.3f);
        glVertex2f(0.1f,-0.4f);
        glVertex2f(-0.1f,-0.4f);
    glEnd();
    glPopMatrix();
}
void cropArea(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.52f,0.35f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.17f);
        glVertex2f(-0.2f,0.17f);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(-1.0f,-0.2f);
    glEnd();
    glPopMatrix();
}

void drawTree(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw trunk

    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.04f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();


    // Draw canopy (leaves)
    glColor3f(0.3f, 0.9f, 0.2f); // Green
    drawCircle(0.0f, 0.44f, 0.05f);
    drawCircle(-0.05f, 0.32f, 0.07f);
    drawCircle(0.05f, 0.32f, 0.07f);
    drawCircle(-0.03f, 0.38f, 0.06f);
    drawCircle(0.03f, 0.38f, 0.06f);

    glPopMatrix();
}

void house(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.8f, 0.5f, 0.0f); // orange wall
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Roof (triangle)
    glColor3f(0.6f, 0.3f, 0.0f); // red roof
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f, 0.2f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    // Door
    glColor3f(0.6f, 0.3f, 0.0f); // brown door
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(0.1f, -0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    // Left window
    glColor3f(0.6f, 0.3f, 0.0f); // light blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.35f, 0.15f);
    glEnd();

    // Right window
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.15f);
        glVertex2f(0.2f, 0.15f);
    glEnd();
    glPopMatrix();
}

void wellTop(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center of circle

    for (int i = 0; i <= num_segments; i++) {
        float angle = 2 * PI * i / num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}
void waterWell(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.75f, 1.0f);
    wellTop(-0.008f, 0.12f, 0.11f, 100);
    // === Rectangular Side Wall (to make it look tall) ===
    glColor3f(0.5f, 0.5f, 0.5f); // Slightly darker gray
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);   // Top-left
        glVertex2f(0.15f, 0.1f);    // Top-right
        glVertex2f(0.15f, -0.15f);  // Bottom-right (slightly narrower for pseudo-3D)
        glVertex2f(-0.15f, -0.15f); // Bottom-left
    glEnd();

    // === Vertical Posts ===
    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.14f, 0.1f);
        glVertex2f(-0.11f, 0.1f);
        glVertex2f(-0.11f, 0.3f);
        glVertex2f(-0.14f, 0.3f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.13f, 0.1f);
        glVertex2f(0.13f, 0.3f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    // === Roof ===
    glColor3f(0.6f, 0.0f, 0.0f); // Dark red
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.3f);
        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(-0.25f, 0.33f);
    glEnd();

    // === Rope ===
    glColor3f(0.0f, 0.0f, 0.0f); // Black rope
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.2f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(0.02f, 0.15f);
        glVertex2f(-0.02f, 0.15f);
    glEnd();

    glPopMatrix();
}

void river() {
    glColor3f(0.0f, 0.75f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.65f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void grass(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.2f, 0.6f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();
    glPopMatrix();
}

/*void seeds(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.97f, 0.87f, 0.06f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01, 0.52f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01, 0.52f);
        glVertex2f(-0.01f, 0.52f);
        glVertex2f(0.0f, 0.54f);
        glVertex2f(0.01f, 0.52f);
    glEnd();
    glPopMatrix();
}
void paddy(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.8f, 0.7f, 0.12f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.2f, 0.5f);
    glEnd();

    glPopMatrix();

}*/
void crop(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);


    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void rail(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(0.1f, -0.2);
        glVertex2f(-0.1f, -0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.1f, 0.2f);
    glEnd();
    glPopMatrix();
}

void rope(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 0.39f, 0.13f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.01f);
        glVertex2f(0.2f, 0.01f);
        glVertex2f(0.2f, -0.01f);
        glVertex2f(-0.2f, -0.01f);
    glEnd();
    glPopMatrix();
}

void ybush(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.96f, 0.89f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();

    glPopMatrix();
}

void bar(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.2f);
        glVertex2f(0.01f, 0.2f);
        glVertex2f(0.01f, -0.2f);
        glVertex2f(-0.01f, -0.2f);
    glEnd();
    glPopMatrix();
}

void cartcrop(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void bullockcart(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.06f);
        glVertex2f(0.07f, 0.06f);
        glVertex2f(0.07f, -0.08f);
        glVertex2f(0.0f, -0.08f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.03f, 0.04f);
        glVertex2f(0.05f, 0.04f);
        glVertex2f(0.05f, 0.09f);
        glVertex2f(0.03f, 0.09f);
        glColor3f(0.43f, 0.12f, 0.03f);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.3f, -0.05f);
        glVertex2f(-0.3f, -0.07f);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(-0.37f, -0.087f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.22f, -0.2f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.08f, -0.2f);
        glVertex2f(-0.03f, -0.2f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.08f, -0.3f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.22f, -0.35f);
        glVertex2f(-0.27f, -0.35f);
        glVertex2f(-0.08f, -0.3f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.03f, -0.35f);
        glVertex2f(-0.08f, -0.35f);
    glEnd();

    glColor3f(0.51f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(-0.04f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(-0.4f, -0.1f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.4f, 0.04f);
        glVertex2f(-0.33f, 0.04f);
        glVertex2f(-0.33f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glColor3f(0.51f, 0.0f, 0.12f);
        glVertex2f(-0.8f, 0.08f);
        glVertex2f(-0.4f, 0.08f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.8f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.7f, -0.3f, 0.07f);
    drawCircle(-0.5f, -0.3f, 0.07f);

    glColor3f(0.87f, 0.62f, 0.43f);
    drawCircle(-0.5f, -0.3f, 0.03f);
    drawCircle(-0.7f, -0.3f, 0.03f);

    glColor3f(0.96f, 0.89f, 0.08f);
    ybush(-0.6f, 0.0f, 0.8f);

    cartcrop(-0.74f, -0.25f, 0.3f);
    cartcrop(-0.74f, -0.25f, 0.3f);
    cartcrop(-0.72f, -0.25f, 0.3f);
    cartcrop(-0.72f, -0.25f, 0.3f);
    cartcrop(-0.7f, -0.25f, 0.3f);
    cartcrop(-0.7f, -0.25f, 0.3f);
    cartcrop(-0.68f, -0.25f, 0.3f);
    cartcrop(-0.68f, -0.25f, 0.3f);
    cartcrop(-0.66f, -0.25f, 0.3f);
    cartcrop(-0.66f, -0.25f, 0.3f);
    cartcrop(-0.64f, -0.25f, 0.3f);
    cartcrop(-0.64f, -0.25f, 0.3f);
    cartcrop(-0.62f, -0.25f, 0.3f);
    cartcrop(-0.62f, -0.25f, 0.3f);
    cartcrop(-0.6f, -0.25f, 0.3f);
    cartcrop(-0.6f, -0.25f, 0.3f);
    cartcrop(-0.58f, -0.25f, 0.3f);
    cartcrop(-0.58f, -0.25f, 0.3f);
    cartcrop(-0.56f, -0.25f, 0.3f);
    cartcrop(-0.56f, -0.25f, 0.3f);
    cartcrop(-0.54f, -0.25f, 0.3f);
    cartcrop(-0.54f, -0.25f, 0.3f);
    cartcrop(-0.52f, -0.25f, 0.3f);
    cartcrop(-0.52f, -0.25f, 0.3f);
    cartcrop(-0.5f, -0.25f, 0.3f);
    cartcrop(-0.5f, -0.25f, 0.3f);
    cartcrop(-0.48f, -0.25f, 0.3f);
    cartcrop(-0.48f, -0.25f, 0.3f);
    cartcrop(-0.46f, -0.25f, 0.3f);
    cartcrop(-0.46f, -0.25f, 0.3f);
    cartcrop(-0.44f, -0.25f, 0.3f);
    cartcrop(-0.44f, -0.25f, 0.3f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.38f, 0.18f);
        glVertex2f(-0.32f, 0.18f);
        glVertex2f(-0.32f, 0.12f);
        glVertex2f(-0.38f, 0.12f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.12f);
        glVertex2f(-0.33f, 0.12f);
        glVertex2f(-0.33f, 0.06f);
        glVertex2f(-0.37f, 0.06f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.06f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.32f, 0.04f);
        glVertex2f(-0.37f, 0.04f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.3f, 0.06f);
        glVertex2f(-0.3f, 0.01f);
        glVertex2f(-0.32f, 0.01f);
        //Hand
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.3f, 0.09f);
        glVertex2f(-0.3f, 0.07f);
        glVertex2f(-0.35f, 0.1f);
    glEnd();

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.3f, 0.08f);
        glVertex2f(0.0f, -0.02f);
    glEnd();
    glPopMatrix();
}

void boatrider(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.38f, 0.16f);
        glVertex2f(-0.32f, 0.16f);
        glVertex2f(-0.32f, 0.12f);
        glVertex2f(-0.38f, 0.12f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.37f, 0.12f);
        glVertex2f(-0.33f, 0.12f);
        glVertex2f(-0.33f, 0.06f);
        glVertex2f(-0.37f, 0.06f);
    glEnd();
        //Hand
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.3f, 0.09f);
        glVertex2f(-0.3f, 0.07f);
        glVertex2f(-0.35f, 0.1f);
    glEnd();

    glPopMatrix();
}
void boat(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    glPopMatrix();
}

void man(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.8f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.8f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //leg
    glColor3f(0.3f, 0.18f, 0.56f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.05f, 0.0f, 0.03f);
    drawCircle(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.05f, 0.0f, 0.01f);
    drawCircle(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void woman(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.75f, 0.07f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.85f, 0.2f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(0.15f, -0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.15f, 0.1f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
        glVertex2f(0.15f, 0.1f);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.2f, 0.15f);
        glVertex2f(0.15f, 0.15f);
    glEnd();

    //leg
    glColor3f(0.3f, 0.18f, 0.56f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.05f, 0.0f, 0.03f);
    drawCircle(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.05f, 0.0f, 0.01f);
    drawCircle(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();

    //bucket
    glColor3f(0.4f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(0.15f, 0.1f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(-0.15f, 0.25f);
        glColor3f(0.2f, 0.0f, 0.0f);
        glVertex2f(-0.05f, 0.25f);
        glVertex2f(0.05f, 0.25f);
        glVertex2f(0.05f, 0.3f);
        glVertex2f(-0.05f, 0.3f);
    glEnd();
    glPopMatrix();
}

void boy(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.89f, 0.85f, 0.38f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.89f, 0.85f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //leg
    glColor3f(0.18f, 0.31f, 0.27f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.05f, 0.0f, 0.03f);
    drawCircle(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-0.05f, 0.0f, 0.01f);
    drawCircle(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void sunflower(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glColor3f(1.0f, 0.8f, 0.09f);
    drawCircle(0.0f, 0.44f, 0.02f);
    drawCircle(0.0f, 0.36f, 0.02f);
    drawCircle(-0.04f, 0.4f, 0.02f);
    drawCircle(0.04f, 0.4f, 0.02f);
    drawCircle(-0.02f, 0.435f, 0.02f);
    drawCircle(0.018f, 0.365f, 0.02f);
    drawCircle(-0.038f, 0.385f, 0.02f);
    drawCircle(0.038f, 0.385f, 0.02f);
    drawCircle(0.02f, 0.44f, 0.02f);
    drawCircle(-0.02f, 0.36f, 0.02f);

    glColor3f(0.37f, 0.28f, 0.18f);
    drawCircle(0.0f, 0.4f, 0.04f);
    glPopMatrix();

}

void drawBirdBody(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawBird()
{
    glPushMatrix();
    glTranslatef(birdX, birdY, 0.0f); // Move bird to current position
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBirdBody(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBirdBody(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}

void drawBird2()
{
    glPushMatrix();
    glTranslatef(bird2X, bird2Y, 0.0f); // Move bird to current position
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBirdBody(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBirdBody(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}

void drawBird3()
{
    glPushMatrix();
    glTranslatef(bird3X, bird3Y, 0.0f); // Move bird to current position
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBirdBody(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBirdBody(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}
void displayDay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    // Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(0.0f, 0.8f, 0.1f);

    // Cloud
    glColor3f(1.0f, 1.0f, 1.0f);
    cloud(cloudPosition1 - 0.1f, 1.1f, 0.1f);
    cloud(cloudPosition1, 1.1f, 0.15f);
    cloud(cloudPosition1 + 0.1f, 1.1f, 0.1f);

    glColor3f(1.0f, 1.0f, 1.0f);
    cloud(cloudPosition2 - 0.1f, 0.75f, 0.1f);
    cloud(cloudPosition2, 0.75f, 0.15f);
    cloud(cloudPosition2+ 0.1f, 0.75f, 0.1f);


    ground();
    road1(0.0f, -0.25f, 1.0f);
    road2(0.0f, 0.0f, 1.0f);
    road2(0.7f, -0.2f, 0.5f);
    grass(-0.9f, -0.649f, 0.45f, 0.0f);
    grass(-0.9f, -0.7f, 0.45f, -30.0f);
    grass(-0.95f, -0.73f, 0.45f, -70.0f);
    grass(-0.7f, -0.649f, 0.45f, 0.0f);
    grass(-0.73f, -0.7f, 0.45f, -60.0f);
    grass(-0.6f, -0.649f, 0.45f, 0.0f);
    grass(-0.6f, -0.7f, 0.45f, -30.0f);
    grass(-0.65f, -0.7f, 0.45f, -30.0f);
    grass(-0.6f, -0.73f, 0.45f, -70.0f);
    grass(-0.4f, -0.649f, 0.45f, 0.0f);
    grass(-0.4f, -0.7f, 0.45f, -30.0f);
    grass(-0.45f, -0.73f, 0.45f, -70.0f);
    grass(-0.3f, -0.649f, 0.45f, 0.0f);
    grass(-0.33f, -0.7f, 0.45f, -60.0f);
    grass(-0.2f, -0.649f, 0.45f, 0.0f);
    grass(-0.2f, -0.7f, 0.45f, -30.0f);
    grass(-0.15f, -0.7f, 0.45f, -30.0f);
    grass(-0.18f, -0.73f, 0.45f, -70.0f);
    grass(0.0f, -0.649f, 0.45f, 0.0f);
    grass(0.0f, -0.7f, 0.45f, -30.0f);
    grass(0.05f, -0.73f, 0.45f, -70.0f);
    grass(0.1f, -0.649f, 0.45f, 0.0f);
    grass(1.13f, -0.7f, 0.45f, -60.0f);
    grass(0.2f, -0.649f, 0.45f, 0.0f);
    grass(0.2f, -0.7f, 0.45f, -30.0f);
    grass(0.25f, -0.7f, 0.45f, -30.0f);
    grass(0.2f, -0.73f, 0.45f, -70.0f);
    grass(0.4f, -0.649f, 0.45f, 0.0f);
    grass(0.4f, -0.7f, 0.45f, -30.0f);
    grass(0.45f, -0.73f, 0.45f, -70.0f);
    grass(0.5f, -0.649f, 0.45f, 0.0f);
    grass(0.6f, -0.649f, 0.45f, 0.0f);
    grass(0.6f, -0.7f, 0.45f, -30.0f);
    grass(0.65f, -0.7f, 0.45f, -30.0f);
    grass(0.63f, -0.73f, 0.45f, -70.0f);
    grass(0.75f, -0.7f, 0.45f, -30.0f);
    grass(0.73f, -0.73f, 0.45f, -70.0f);
    grass(0.8f, -0.649f, 0.45f, 0.0f);
    grass(0.8f, -0.7f, 0.45f, -30.0f);
    grass(0.85f, -0.73f, 0.45f, -70.0f);
    grass(0.9f, -0.649f, 0.45f, 0.0f);
    grass(1.0f, -0.649f, 0.45f, 0.0f);
    grass(1.0f, -0.7f, 0.45f, -30.0f);
    grass(1.05f, -0.7f, 0.45f, -30.0f);
    hills();
    windMill();

    bush(-0.9f, 0.25f, 1.2f);
    bush(-0.7f, 0.25f, 1.2f);
    bush(-0.5f, 0.25f, 1.2f);
    bush(-0.3f, 0.25f, 1.2f);
    bush(-0.1f, 0.25f, 1.2f);
    bush(0.1f, 0.25f, 1.2f);
    bush(0.3f, 0.25f, 1.2f);
    bush(0.5f, 0.25f, 1.2f);
    bush(0.7f, 0.25f, 1.2f);
    bush(0.9f, 0.25f, 1.2f);

    bar(0.26f, 0.01f, 0.18f, 0.0f);
    bar(0.34f, 0.01f, 0.18f, 0.0f);
    bar(0.3f, 0.04f, 0.25f, -90.0f);

    ybush(0.49f, 0.1f, 0.5f);
    crop(0.58f, 0.15f, 0.3f, 180.0f);
    crop(0.58f, 0.05f, 0.3f, 0.0f);
    crop(0.56f, 0.15f, 0.3f, 180.0f);
    crop(0.56f, 0.05f, 0.3f, 0.0f);
    crop(0.54f, 0.15f, 0.3f, 180.0f);
    crop(0.54f, 0.05f, 0.3f, 0.0f);
    crop(0.52f, 0.15f, 0.3f, 180.0f);
    crop(0.52f, 0.05f, 0.3f, 0.0f);
    crop(0.59f, 0.15f, 0.3f, 180.0f);
    crop(0.59f, 0.05f, 0.3f, 0.0f);
    crop(0.57f, 0.15f, 0.3f, 180.0f);
    crop(0.57f, 0.05f, 0.3f, 0.0f);
    crop(0.55f, 0.15f, 0.3f, 180.0f);
    crop(0.55f, 0.05f, 0.3f, 0.0f);
    crop(0.53f, 0.15f, 0.3f, 180.0f);
    crop(0.53f, 0.05f, 0.3f, 0.0f);
    crop(0.5f, 0.15f, 0.3f, 180.0f);
    crop(0.5f, 0.05f, 0.3f, 0.0f);
    crop(0.48f, 0.15f, 0.3f, 180.0f);
    crop(0.48f, 0.05f, 0.3f, 0.0f);
    crop(0.46f, 0.15f, 0.3f, 180.0f);
    crop(0.46f, 0.05f, 0.3f, 0.0f);
    crop(0.44f, 0.15f, 0.3f, 180.0f);
    crop(0.44f, 0.05f, 0.3f, 0.0f);
    crop(0.42f, 0.15f, 0.3f, 180.0f);
    crop(0.42f, 0.05f, 0.3f, 0.0f);
    crop(0.4f, 0.15f, 0.3f, 180.0f);
    crop(0.4f, 0.05f, 0.3f, 0.0f);
    crop(0.51f, 0.15f, 0.3f, 180.0f);
    crop(0.51f, 0.05f, 0.3f, 0.0f);
    crop(0.49f, 0.15f, 0.3f, 180.0f);
    crop(0.49f, 0.05f, 0.3f, 0.0f);
    crop(0.47f, 0.15f, 0.3f, 180.0f);
    crop(0.47f, 0.05f, 0.3f, 0.0f);
    crop(0.45f, 0.15f, 0.3f, 180.0f);
    crop(0.45f, 0.05f, 0.3f, 0.0f);
    crop(0.43f, 0.15f, 0.3f, 180.0f);
    crop(0.43f, 0.05f, 0.3f, 0.0f);
    crop(0.41f, 0.15f, 0.3f, 180.0f);
    crop(0.41f, 0.05f, 0.3f, 0.0f);



    drawTree(-0.9f, 0.15f, 1.2f);
    drawTree(-0.6f, 0.15f, 1.0f);
    drawTree(0.85f, 0.0f, 1.2f);

    cropArea(0.0f, -0.03f, 1.0f);

    man(-0.25f, manY, 0.25f);
    //Row 1
    crop(-0.97f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.91f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.85f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.79f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.73f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.67f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.61f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.55f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.49f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.43f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.37f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.31f, 0.1f, 0.3f, cropSwayAngle);
    crop(-0.25f, 0.1f, 0.3f, cropSwayAngle);
    //Row 2
    crop(-0.99f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.93f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.87f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.81f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.75f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.69f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.63f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.57f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.51f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.45f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.39f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.33f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.27f, 0.0f, 0.3f, cropSwayAngle);
    crop(-0.22f, 0.0f, 0.3f, cropSwayAngle);
    //Row 3
    crop(-0.97f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.91f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.85f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.79f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.73f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.67f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.61f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.55f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.49f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.43f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.37f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.31f, -0.1f, 0.3f, cropSwayAngle);
    crop(-0.25f, -0.1f, 0.3f, cropSwayAngle);
    //Row 4
    crop(-0.99f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.93f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.87f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.81f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.75f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.69f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.63f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.57f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.51f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.45f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.39f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.33f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.27f, -0.2f, 0.3f, cropSwayAngle);
    crop(-0.22f, -0.2f, 0.3f, cropSwayAngle);

    //man(-0.25f, 0.3f, 0.25f);

    waterWell(0.3f, -0.2f, 0.6f);

    rope(0.5f, -0.07f, 0.5f, 0.0f);
    rope(0.41f, -0.17f, 0.5f, -90.0f);
    rope(0.5f, -0.3f, 0.5f, 0.0f);
    rope(0.61f, -0.17f, 0.5f, -90.0f);
    rope(0.793f, -0.17f, 0.5f, -90.0f);
    rope(0.9f, -0.3f, 0.5f, 0.0f);
    house(0.7f,0.0f,0.5f);
    drawTree(0.95f, -0.3f, 1.2f);
    rail(0.49f, -0.075f, 0.13f);
    rail(0.45f, -0.075f, 0.13f);
    rail(0.41f, -0.075f, 0.13f);
    rail(0.41f, -0.15f, 0.13f);
    rail(0.41f, -0.225f, 0.13f);
    rail(0.41f, -0.3f, 0.13f);
    rail(0.45f, -0.3f, 0.13f);
    rail(0.49f, -0.3f, 0.13f);
    rail(0.53f, -0.3f, 0.13f);
    rail(0.57f, -0.3f, 0.13f);
    rail(0.61f, -0.3f, 0.13f);
    rail(0.61f, -0.225f, 0.13f);
    rail(0.61f, -0.15f, 0.13f);
    rail(0.79f, -0.15f, 0.13f);
    rail(0.79f, -0.225f, 0.13f);
    rail(0.79f, -0.3f, 0.13f);
    rail(0.83f, -0.3f, 0.13f);
    rail(0.87f, -0.3f, 0.13f);
    rail(0.91f, -0.3f, 0.13f);
    rail(0.95f, -0.3f, 0.13f);
    rail(0.99f, -0.3f, 0.13f);

    boy(-0.05f, boyY, 0.2f);
    woman(0.05f, womanY, 0.3f);


    sunflower(0.45f, -0.17f, 0.4f, sunflowerAngle);
    sunflower(0.52f, -0.17f, 0.4f, sunflowerAngle);
    sunflower(0.58f, -0.17f, 0.4f, sunflowerAngle);
    sunflower(0.44f, -0.25f, 0.4f, sunflowerAngle);
    sunflower(0.51f, -0.25f, 0.4f, sunflowerAngle);
    sunflower(0.57f, -0.25f, 0.4f, sunflowerAngle);


    bullockcart(cartX, -0.3f, 0.5f);

    river();
    boatrider(boatX +0.28, -0.83f, 1.0f);
    boat(boatX, -0.9f, 0.7f);

    drawBird();
    drawBird2();
    drawBird3();



    glutSwapBuffers();
}
void ground2()
{
 glColor3f(0.1f, 0.3f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(1.0f,0.3f);
        glVertex2f(1.0f,-1.0f);
        glVertex2f(-1.0f,-1.0f);
    glEnd();
}

void hills2()
{
    glPushMatrix();
    glTranslatef(-0.1f,0.03f,0.0f);
    glScalef(0.9f,0.9f,1.0f);

   glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(-0.8f,0.5f);
        glVertex2f(-0.5f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f,0.3f);
        glVertex2f(-0.4f,0.5f);
        glVertex2f(-0.1f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f,0.3f);
        glVertex2f(0.0f,0.5f);
        glVertex2f(0.3f,0.3f);
    glEnd();
    glPopMatrix();
}

void drawCircle2(float x, float y, float radius) {
    glPushMatrix();
    glScalef(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}

void cloud2(float x, float y, float radius) {
    glPushMatrix();
    glScalef(0.7f,0.7f,0.7f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}
void windMill2()
{
    glPushMatrix();
    glTranslatef(-0.15f,0.1f,0.5f);
    glScalef(0.7f,0.7f,0.6f);
    glColor3f(0.1f, 0.1f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(-0.17f,0.6f);
        glVertex2f(-0.13f,0.6f);
        glVertex2f(0.001f,0.2f);
        glVertex2f(-0.28f,0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.15f, 0.6f, 0.0f); // Move to hub center
    glRotatef(bladeAngle2, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

    glColor3f(0.6f, 0.6f, 0.6f);
    for (int i = 0; i < 3; i++) {
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate for each blade
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.05f, 0.15f);
            glVertex2f(-0.05f, 0.15f);
        glEnd();
    }

    glPopMatrix();

    glColor3f(0.2f,0.1f,0.0f);
    drawCircle2(-0.15f,0.6f,0.04f);
    glPopMatrix();
}

void bush222(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.5f, 0.0f, 0.0f);
    drawCircle2(-0.01f, 0.0f, 0.01f);
    glColor3f(0.4f, 0.0f, 0.0f);
    drawCircle2(-0.0f, 0.01f, 0.01f);
    glColor3f(0.5f, 0.0f, 0.0f);
    drawCircle2(0.01f, 0.0f, 0.01f);
    glColor3f(0.4f, 0.0f, 0.0f);
    drawCircle2(0.0f, -0.01f, 0.01f);
    glColor3f(0.5f, 0.6f, 0.0f);
    drawCircle2(-0.001f, 0.0f, 0.007f);
    glPopMatrix();

    glPopMatrix();

}
void drawFirefly2(float x, float y, float scale) {
    // Head (larger black circle)
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(x, y + 0.005f * scale, 0.007f * scale);

    // Body (smaller glowing green circle just below)
    glColor3f(0.0f, 1.0f, 0.0f);
    drawCircle2(x, y, 0.004f * scale);
}
void bush2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.4f, 0.0f);
    drawCircle2(-0.05f, 0.0f, 0.06f);
    drawCircle2(0.0f, 0.02f, 0.07f);
    drawCircle2(0.05f, 0.0f, 0.06f);

    glColor3f(0.0f, 0.3f, 0.0f);
    drawCircle2(-0.03f, 0.0f, 0.03f);
    drawCircle2(0.0f, 0.02f, 0.04f);
    drawCircle2(0.03f, 0.0f, 0.03f);

    bush222(0.0f, 0.03f, 1.0f);
    bush222(-0.04f, 0.28f, 1.2f);
    bush222(-0.16f, 0.28f, 1.2f);
    bush222(-0.96f, 0.28f, 1.2f);
    bush222(-0.85f, 0.28f, 1.2f);
    bush222(-0.76f, 0.28f, 1.2f);
    bush222(-0.65f, 0.28f, 1.2f);
    bush222(-0.56f, 0.28f, 1.2f);
    bush222(-0.45f, 0.28f, 1.2f);
    bush222(-0.36f, 0.28f, 1.2f);
    bush222(-0.25f, 0.28f, 1.2f);
    bush222(0.05f, 0.28f, 1.2f);
    bush222(0.15f, 0.28f, 1.2f);
    bush222(0.25f, 0.28f, 1.2f);
    bush222(0.35f, 0.28f, 1.2f);
    bush222(0.45f, 0.28f, 1.2f);
    bush222(0.55f, 0.28f, 1.2f);
    bush222(0.65f, 0.28f, 1.2f);
    bush222(0.75f, 0.28f, 1.2f);
    bush222(0.85f, 0.28f, 1.2f);
    bush222(0.95f, 0.28f, 1.2f);

    drawFirefly2(-0.8f, 0.25f, 1.0f);
    drawFirefly2(-0.7f, 0.25f, 1.0f);
    drawFirefly2(-0.6f, 0.25f, 1.0f);
    drawFirefly2(-0.5f, 0.25f, 1.0f);
    drawFirefly2(-0.4f, 0.25f, 1.0f);
    drawFirefly2(-0.3f, 0.21f, 1.0f);
    drawFirefly2(-0.2f, 0.25f, 1.0f);
    drawFirefly2(-0.1f, 0.21f, 1.0f);
    drawFirefly2(0.2f, 0.23f, 1.0f);
    drawFirefly2(0.3f, 0.24f, 1.0f);
    drawFirefly2(0.4f, 0.25f, 1.0f);
    drawFirefly2(0.5f, 0.24f, 1.0f);
    drawFirefly2(0.6f, 0.25f, 1.0f);
    drawFirefly2(0.7f, 0.26f, 1.0f);
    glPopMatrix();
}

void road12(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(0.3f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,-0.1f);
        glVertex2f(1.0f,-0.1f);
        glVertex2f(1.0f,-0.3f);
        glVertex2f(-1.0f,-0.3f);
    glEnd();
    glPopMatrix();
}

void road22(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(0.3f, 0.3f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f,0.3f);
        glVertex2f(0.1f,0.3f);
        glVertex2f(0.1f,-0.4f);
        glVertex2f(-0.1f,-0.4f);
    glEnd();
    glPopMatrix();
}
void crop2Area2(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
   glColor3f(0.1f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.17f);
        glVertex2f(-0.2f,0.17f);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(-1.0f,-0.2f);
    glEnd();
    glPopMatrix();
}

void drawTree2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw trunk

   glColor3f(0.1f, 0.2f, 0.1f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.04f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();


    // Draw canopy (leaves)
    glColor3f(0.1f, 0.3f, 0.1f); // Green
    drawCircle2(0.0f, 0.44f, 0.05f);
    drawCircle2(-0.05f, 0.32f, 0.07f);
    drawCircle2(0.05f, 0.32f, 0.07f);
    drawCircle2(-0.03f, 0.38f, 0.06f);
    drawCircle2(0.03f, 0.38f, 0.06f);

    glPopMatrix();
}

void house2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    // Dark wall color for night
    glColor3f(0.2f, 0.1f, 0.0f); // very dark brown
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Roof
    glColor3f(0.1f, 0.05f, 0.0f); // almost black
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f, 0.2f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    // Door (dark wood)
    glColor3f(0.15f, 0.07f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(0.1f, -0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    // Left window (lit yellow)
    glColor3f(1.0f, 0.85f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.35f, 0.15f);
    glEnd();

    // Right window (lit yellow)
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.15f);
        glVertex2f(0.2f, 0.15f);
    glEnd();

    glPopMatrix();
}

void drawBoatAtCorner2() {
    glPushMatrix();
    glTranslatef(0.85, -0.8, 0.0f);
    glScalef(1.0f, 1.0f, 1.0f); // Restored original size

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

   glColor3f(0.0f, 0.0f, 0.0f); // Black rope2 color
glBegin(GL_LINES);
    glVertex2f(-0.2f, 0.2f);     // Front-left corner of the boat
    glVertex2f(-0.23f, 0.23f);   // Closer anchor point
glEnd();

// Stick (post) at end of rope2
glColor3f(0.3f, 0.15f, 0.0f); // Dark brown stick
glBegin(GL_QUADS);
    glVertex2f(-0.235f, 0.23f);   // Left side
    glVertex2f(-0.225f, 0.23f);   // Right side
    glVertex2f(-0.225f, 0.33f);   // Top-right
    glVertex2f(-0.235f, 0.33f);   // Top-left
glEnd();
    glPopMatrix();
}
void wellTop2(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center of circle

    for (int i = 0; i <= num_segments; i++) {
        float angle = 2 * PI2 * i / num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}
void waterWell2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

     glColor3f(0.05f, 0.2f, 0.3f);
    wellTop2(-0.008f, 0.12f, 0.11f, 100);
    // === Rectangular Side Wall (to make it look tall) ===
     glColor3f(0.3f, 0.2f, 0.1f); // Slightly darker gray
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);   // Top-left
        glVertex2f(0.15f, 0.1f);    // Top-right
        glVertex2f(0.15f, -0.15f);  // Bottom-right (slightly narrower for pseudo-3D)
        glVertex2f(-0.15f, -0.15f); // Bottom-left
    glEnd();

    // === Vertical Posts ===
    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.14f, 0.1f);
        glVertex2f(-0.11f, 0.1f);
        glVertex2f(-0.11f, 0.3f);
        glVertex2f(-0.14f, 0.3f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.13f, 0.1f);
        glVertex2f(0.13f, 0.3f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    // === Roof ===
    glColor3f(0.6f, 0.0f, 0.0f); // Dark red
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.3f);
        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(-0.25f, 0.33f);
    glEnd();

    // === rope2 ===
    glColor3f(0.0f, 0.0f, 0.0f); // Black rope2
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.2f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(0.02f, 0.15f);
        glVertex2f(-0.02f, 0.15f);
    glEnd();

    glPopMatrix();
}

void river2() {
   glColor3f(0.05f, 0.2f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.65f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void grass2(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.08f, 0.2f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();
    glPopMatrix();
}


void crop2(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.55f, 0.4f, 0.2f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void rail2(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(0.1f, -0.2);
        glVertex2f(-0.1f, -0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.1f, 0.2f);
    glEnd();
    glPopMatrix();
}

void rope2(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 0.39f, 0.13f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.01f);
        glVertex2f(0.2f, 0.01f);
        glVertex2f(0.2f, -0.01f);
        glVertex2f(-0.2f, -0.01f);
    glEnd();
    glPopMatrix();
}

void ybush2(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.05f, 0.15f, 0.05f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();

    glPopMatrix();
}

void bar2(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.2f);
        glVertex2f(0.01f, 0.2f);
        glVertex2f(0.01f, -0.2f);
        glVertex2f(-0.01f, -0.2f);
    glEnd();
    glPopMatrix();
}

void cartcrop2(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void sunflower2(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

     glColor3f(0.7f, 0.5f, 0.06f);
    drawCircle2(0.0f, 0.44f, 0.02f);
    drawCircle2(0.0f, 0.36f, 0.02f);
    drawCircle2(-0.04f, 0.4f, 0.02f);
    drawCircle2(0.04f, 0.4f, 0.02f);
    drawCircle2(-0.02f, 0.435f, 0.02f);
    drawCircle2(0.018f, 0.365f, 0.02f);
    drawCircle2(-0.038f, 0.385f, 0.02f);
    drawCircle2(0.038f, 0.385f, 0.02f);
    drawCircle2(0.02f, 0.44f, 0.02f);
    drawCircle2(-0.02f, 0.36f, 0.02f);

    glColor3f(0.37f, 0.28f, 0.18f);
    drawCircle2(0.0f, 0.4f, 0.04f);
    glPopMatrix();

}
void drawOwl(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.2f, 0.2f, 1.0f);

    // Body
    glColor3f(0.4f, 0.2f, 0.0f); // Dark brown
    drawCircle2(0.0f, 0.0f, 0.2f);

    // Eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle2(-0.07f, 0.05f, 0.04f);
    drawCircle2(0.07f, 0.05f, 0.04f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(-0.07f, 0.05f, 0.015f);
    drawCircle2(0.07f, 0.05f, 0.015f);

    // Beak
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.02f);
        glVertex2f(-0.02f, -0.03f);
        glVertex2f(0.02f, -0.03f);
    glEnd();

    glPopMatrix();
}
void drawMoon() {
    glPushMatrix();
    glTranslatef(0.8f, 0.8f, 0.0f);
    glColor3f(0.85f, 0.85f, 0.85f); // Dimmer moon
    drawCircle2(0.0f, 0.0f, 0.08f);

    // Craters (subtly darker)
    glColor3f(0.6f, 0.6f, 0.6f);
    drawCircle2(0.02f, 0.02f, 0.01f);
    drawCircle2(-0.03f, -0.01f, 0.012f);
    drawCircle2(0.01f, -0.03f, 0.008f);
    drawCircle2(-0.02f, 0.03f, 0.007f);
    glPopMatrix();
}
void drawStars() {
    glPushMatrix();
    glScalef(1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // White stars

    // Custom stars similar to existing drawCircle2 calls
    drawCircle2(-0.85f, 0.9f, 0.008f);
    drawCircle2(-0.2f, 0.92f, 0.008f);
    drawCircle2(0.3f, 0.88f, 0.008f);
    drawCircle2(0.65f, 0.93f, 0.008f);
    drawCircle2(-0.4f, 0.75f, 0.008f);
    drawCircle2(0.1f, 0.8f, 0.008f);
    drawCircle2(-0.7f, 0.95f, 0.006f);
    drawCircle2(-0.55f, 0.85f, 0.006f);
    drawCircle2(-0.35f, 0.93f, 0.007f);
    drawCircle2(-0.1f, 0.87f, 0.006f);
    drawCircle2(0.0f, 0.95f, 0.007f);
    drawCircle2(0.2f, 0.91f, 0.006f);
    drawCircle2(0.4f, 0.96f, 0.007f);
    drawCircle2(0.55f, 0.89f, 0.006f);
    drawCircle2(-0.9f, 0.6f, 0.006f);
    drawCircle2(-0.7f, 0.55f, 0.006f);
    drawCircle2(-0.5f, 0.62f, 0.007f);
    drawCircle2(-0.3f, 0.58f, 0.006f);
    drawCircle2(-0.1f, 0.6f, 0.007f);
    drawCircle2(0.1f, 0.55f, 0.006f);
    drawCircle2(0.3f, 0.62f, 0.006f);
    drawCircle2(0.5f, 0.6f, 0.007f);
    drawCircle2(0.7f, 0.58f, 0.006f);
    drawCircle2(0.85f, 0.6f, 0.007f);

    glPopMatrix();
}
void bullockcart2(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.06f);
        glVertex2f(0.07f, 0.06f);
        glVertex2f(0.07f, -0.08f);
        glVertex2f(0.0f, -0.08f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.03f, 0.04f);
        glVertex2f(0.05f, 0.04f);
        glVertex2f(0.05f, 0.09f);
        glVertex2f(0.03f, 0.09f);

        glColor3f(0.43f, 0.12f, 0.03f);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.3f, -0.2f);

        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.3f, -0.05f);
        glVertex2f(-0.3f, -0.07f);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(-0.37f, -0.087f);

        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.22f, -0.2f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.27f, -0.3f);

        glVertex2f(-0.08f, -0.2f);
        glVertex2f(-0.03f, -0.2f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.08f, -0.3f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.22f, -0.35f);
        glVertex2f(-0.27f, -0.35f);

        glVertex2f(-0.08f, -0.3f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.03f, -0.35f);
        glVertex2f(-0.08f, -0.35f);
    glEnd();

    glColor3f(0.51f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(-0.04f, -0.05f);

        glVertex2f(-0.4f, -0.05f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(-0.4f, -0.1f);

        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.4f, 0.04f);
        glVertex2f(-0.33f, 0.04f);
        glVertex2f(-0.33f, -0.05f);
        glVertex2f(-0.4f, -0.05f);

        glColor3f(0.51f, 0.0f, 0.12f);
        glVertex2f(-0.8f, 0.08f);
        glVertex2f(-0.4f, 0.08f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.8f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle2(-0.7f, -0.3f, 0.07f);
    drawCircle2(-0.5f, -0.3f, 0.07f);

    glColor3f(0.87f, 0.62f, 0.43f);
    drawCircle2(-0.5f, -0.3f, 0.03f);
    drawCircle2(-0.7f, -0.3f, 0.03f);

    glColor3f(0.96f, 0.89f, 0.08f);
    ybush2(-0.6f, 0.0f, 0.8f);

    cartcrop2(-0.74f, -0.25f, 0.3f);
    cartcrop2(-0.74f, -0.25f, 0.3f);
    cartcrop2(-0.72f, -0.25f, 0.3f);
    cartcrop2(-0.72f, -0.25f, 0.3f);
    cartcrop2(-0.7f, -0.25f, 0.3f);
    cartcrop2(-0.7f, -0.25f, 0.3f);
    cartcrop2(-0.68f, -0.25f, 0.3f);
    cartcrop2(-0.68f, -0.25f, 0.3f);
    cartcrop2(-0.66f, -0.25f, 0.3f);
    cartcrop2(-0.66f, -0.25f, 0.3f);
    cartcrop2(-0.64f, -0.25f, 0.3f);
    cartcrop2(-0.64f, -0.25f, 0.3f);
    cartcrop2(-0.62f, -0.25f, 0.3f);
    cartcrop2(-0.62f, -0.25f, 0.3f);
    cartcrop2(-0.6f, -0.25f, 0.3f);
    cartcrop2(-0.6f, -0.25f, 0.3f);
    cartcrop2(-0.58f, -0.25f, 0.3f);
    cartcrop2(-0.58f, -0.25f, 0.3f);
    cartcrop2(-0.56f, -0.25f, 0.3f);
    cartcrop2(-0.56f, -0.25f, 0.3f);
    cartcrop2(-0.54f, -0.25f, 0.3f);
    cartcrop2(-0.54f, -0.25f, 0.3f);
    cartcrop2(-0.52f, -0.25f, 0.3f);
    cartcrop2(-0.52f, -0.25f, 0.3f);
    cartcrop2(-0.5f, -0.25f, 0.3f);
    cartcrop2(-0.5f, -0.25f, 0.3f);
    cartcrop2(-0.48f, -0.25f, 0.3f);
    cartcrop2(-0.48f, -0.25f, 0.3f);
    cartcrop2(-0.46f, -0.25f, 0.3f);
    cartcrop2(-0.46f, -0.25f, 0.3f);
    cartcrop2(-0.44f, -0.25f, 0.3f);
    cartcrop2(-0.44f, -0.25f, 0.3f);

    glPopMatrix();
}

void displayNight() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    drawMoon();
   //star
   drawStars();


    // cloud2
     glColor3f(0.3f, 0.3f, 0.4f);
    cloud2(cloud2Position12 - 0.1f, 1.1f, 0.1f);
    cloud2(cloud2Position12, 1.1f, 0.15f);
    cloud2(cloud2Position12 + 0.1f, 1.1f, 0.1f);

     glColor3f(0.3f, 0.3f, 0.4f);
    cloud2(cloud2Position22 - 0.1f, 0.75f, 0.1f);
    cloud2(cloud2Position22, 0.75f, 0.15f);
    cloud2(cloud2Position22+ 0.1f, 0.75f, 0.1f);


    ground2();
    road12(0.0f, -0.25f, 1.0f);
    road22(0.0f, 0.0f, 1.0f);
    road22(0.7f, -0.2f, 0.5f);
    grass2(-0.9f, -0.649f, 0.45f, 0.0f);
    grass2(-0.9f, -0.7f, 0.45f, -30.0f);
    grass2(-0.95f, -0.73f, 0.45f, -70.0f);
    grass2(-0.7f, -0.649f, 0.45f, 0.0f);
    grass2(-0.73f, -0.7f, 0.45f, -60.0f);
    grass2(-0.6f, -0.649f, 0.45f, 0.0f);
    grass2(-0.6f, -0.7f, 0.45f, -30.0f);
    grass2(-0.65f, -0.7f, 0.45f, -30.0f);
    grass2(-0.6f, -0.73f, 0.45f, -70.0f);
    grass2(-0.4f, -0.649f, 0.45f, 0.0f);
    grass2(-0.4f, -0.7f, 0.45f, -30.0f);
    grass2(-0.45f, -0.73f, 0.45f, -70.0f);
    grass2(-0.3f, -0.649f, 0.45f, 0.0f);
    grass2(-0.33f, -0.7f, 0.45f, -60.0f);
    grass2(-0.2f, -0.649f, 0.45f, 0.0f);
    grass2(-0.2f, -0.7f, 0.45f, -30.0f);
    grass2(-0.15f, -0.7f, 0.45f, -30.0f);
    grass2(-0.18f, -0.73f, 0.45f, -70.0f);
    grass2(0.0f, -0.649f, 0.45f, 0.0f);
    grass2(0.0f, -0.7f, 0.45f, -30.0f);
    grass2(0.05f, -0.73f, 0.45f, -70.0f);
    grass2(0.1f, -0.649f, 0.45f, 0.0f);
    grass2(1.13f, -0.7f, 0.45f, -60.0f);
    grass2(0.2f, -0.649f, 0.45f, 0.0f);
    grass2(0.2f, -0.7f, 0.45f, -30.0f);
    grass2(0.25f, -0.7f, 0.45f, -30.0f);
    grass2(0.2f, -0.73f, 0.45f, -70.0f);
    grass2(0.4f, -0.649f, 0.45f, 0.0f);
    grass2(0.4f, -0.7f, 0.45f, -30.0f);
    grass2(0.45f, -0.73f, 0.45f, -70.0f);
    grass2(0.5f, -0.649f, 0.45f, 0.0f);
    grass2(0.6f, -0.649f, 0.45f, 0.0f);
    grass2(0.6f, -0.7f, 0.45f, -30.0f);
    grass2(0.65f, -0.7f, 0.45f, -30.0f);
    grass2(0.63f, -0.73f, 0.45f, -70.0f);
    grass2(0.75f, -0.7f, 0.45f, -30.0f);
    grass2(0.73f, -0.73f, 0.45f, -70.0f);
    grass2(0.8f, -0.649f, 0.45f, 0.0f);
    grass2(0.8f, -0.7f, 0.45f, -30.0f);
    grass2(0.85f, -0.73f, 0.45f, -70.0f);
    grass2(0.9f, -0.649f, 0.45f, 0.0f);
    grass2(1.0f, -0.649f, 0.45f, 0.0f);
    grass2(1.0f, -0.7f, 0.45f, -30.0f);
    grass2(1.05f, -0.7f, 0.45f, -30.0f);
    hills2();
    windMill2();

    bush2(-0.9f, 0.25f, 1.2f);
    bush2(-0.7f, 0.25f, 1.2f);
    bush2(-0.5f, 0.25f, 1.2f);
    bush2(-0.3f, 0.25f, 1.2f);
    bush2(-0.1f, 0.25f, 1.2f);
    bush2(0.1f, 0.25f, 1.2f);
    bush2(0.3f, 0.25f, 1.2f);
    bush2(0.5f, 0.25f, 1.2f);
    bush2(0.7f, 0.25f, 1.2f);
    bush2(0.9f, 0.25f, 1.2f);

    bar2(0.26f, 0.01f, 0.18f, 0.0f);
    bar2(0.34f, 0.01f, 0.18f, 0.0f);
    bar2(0.3f, 0.04f, 0.25f, -90.0f);

    ybush2(0.49f, 0.1f, 0.5f);
    crop2(0.58f, 0.15f, 0.3f, 180.0f);
    crop2(0.58f, 0.05f, 0.3f, 0.0f);
    crop2(0.56f, 0.15f, 0.3f, 180.0f);
    crop2(0.56f, 0.05f, 0.3f, 0.0f);
    crop2(0.54f, 0.15f, 0.3f, 180.0f);
    crop2(0.54f, 0.05f, 0.3f, 0.0f);
    crop2(0.52f, 0.15f, 0.3f, 180.0f);
    crop2(0.52f, 0.05f, 0.3f, 0.0f);
    crop2(0.59f, 0.15f, 0.3f, 180.0f);
    crop2(0.59f, 0.05f, 0.3f, 0.0f);
    crop2(0.57f, 0.15f, 0.3f, 180.0f);
    crop2(0.57f, 0.05f, 0.3f, 0.0f);
    crop2(0.55f, 0.15f, 0.3f, 180.0f);
    crop2(0.55f, 0.05f, 0.3f, 0.0f);
    crop2(0.53f, 0.15f, 0.3f, 180.0f);
    crop2(0.53f, 0.05f, 0.3f, 0.0f);
    crop2(0.5f, 0.15f, 0.3f, 180.0f);
    crop2(0.5f, 0.05f, 0.3f, 0.0f);
    crop2(0.48f, 0.15f, 0.3f, 180.0f);
    crop2(0.48f, 0.05f, 0.3f, 0.0f);
    crop2(0.46f, 0.15f, 0.3f, 180.0f);
    crop2(0.46f, 0.05f, 0.3f, 0.0f);
    crop2(0.44f, 0.15f, 0.3f, 180.0f);
    crop2(0.44f, 0.05f, 0.3f, 0.0f);
    crop2(0.42f, 0.15f, 0.3f, 180.0f);
    crop2(0.42f, 0.05f, 0.3f, 0.0f);
    crop2(0.4f, 0.15f, 0.3f, 180.0f);
    crop2(0.4f, 0.05f, 0.3f, 0.0f);
    crop2(0.51f, 0.15f, 0.3f, 180.0f);
    crop2(0.51f, 0.05f, 0.3f, 0.0f);
    crop2(0.49f, 0.15f, 0.3f, 180.0f);
    crop2(0.49f, 0.05f, 0.3f, 0.0f);
    crop2(0.47f, 0.15f, 0.3f, 180.0f);
    crop2(0.47f, 0.05f, 0.3f, 0.0f);
    crop2(0.45f, 0.15f, 0.3f, 180.0f);
    crop2(0.45f, 0.05f, 0.3f, 0.0f);
    crop2(0.43f, 0.15f, 0.3f, 180.0f);
    crop2(0.43f, 0.05f, 0.3f, 0.0f);
    crop2(0.41f, 0.15f, 0.3f, 180.0f);
    crop2(0.41f, 0.05f, 0.3f, 0.0f);



    drawTree2(-0.9f, 0.15f, 1.2f);
    drawTree2(-0.6f, 0.15f, 1.0f);
    drawTree2(0.85f, 0.0f, 1.2f);

    crop2Area2(0.0f, -0.03f, 1.0f);

   //man(-0.25f, manY2, 0.25f);
    //Row 1
    crop2(-0.97f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.91f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.85f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.79f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.73f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.67f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.61f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.55f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.49f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.43f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.37f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.31f, 0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.25f, 0.1f, 0.3f, crop2SwayAngle2);
    //Row 2
    crop2(-0.99f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.93f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.87f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.81f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.75f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.69f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.63f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.57f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.51f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.45f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.39f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.33f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.27f, 0.0f, 0.3f, crop2SwayAngle2);
    crop2(-0.22f, 0.0f, 0.3f, crop2SwayAngle2);
    //Row 3
    crop2(-0.97f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.91f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.85f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.79f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.73f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.67f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.61f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.55f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.49f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.43f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.37f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.31f, -0.1f, 0.3f, crop2SwayAngle2);
    crop2(-0.25f, -0.1f, 0.3f, crop2SwayAngle2);
    //Row 4
    crop2(-0.99f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.93f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.87f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.81f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.75f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.69f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.63f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.57f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.51f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.45f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.39f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.33f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.27f, -0.2f, 0.3f, crop2SwayAngle2);
    crop2(-0.22f, -0.2f, 0.3f, crop2SwayAngle2);

    waterWell2(0.3f, -0.2f, 0.6f);

    rope2(0.5f, -0.07f, 0.5f, 0.0f);
    rope2(0.41f, -0.17f, 0.5f, -90.0f);
    rope2(0.5f, -0.3f, 0.5f, 0.0f);
    rope2(0.61f, -0.17f, 0.5f, -90.0f);
    rope2(0.793f, -0.17f, 0.5f, -90.0f);
    rope2(0.9f, -0.3f, 0.5f, 0.0f);
    house2(0.7f,0.0f,0.5f);
    drawTree2(0.95f, -0.3f, 1.2f);
    rail2(0.49f, -0.075f, 0.13f);
    rail2(0.45f, -0.075f, 0.13f);
    rail2(0.41f, -0.075f, 0.13f);
    rail2(0.41f, -0.15f, 0.13f);
    rail2(0.41f, -0.225f, 0.13f);
    rail2(0.41f, -0.3f, 0.13f);
    rail2(0.45f, -0.3f, 0.13f);
    rail2(0.49f, -0.3f, 0.13f);
    rail2(0.53f, -0.3f, 0.13f);
    rail2(0.57f, -0.3f, 0.13f);
    rail2(0.61f, -0.3f, 0.13f);
    rail2(0.61f, -0.225f, 0.13f);
    rail2(0.61f, -0.15f, 0.13f);
    rail2(0.79f, -0.15f, 0.13f);
    rail2(0.79f, -0.225f, 0.13f);
    rail2(0.79f, -0.3f, 0.13f);
    rail2(0.83f, -0.3f, 0.13f);
    rail2(0.87f, -0.3f, 0.13f);
    rail2(0.91f, -0.3f, 0.13f);
    rail2(0.95f, -0.3f, 0.13f);
    rail2(0.99f, -0.3f, 0.13f);

    sunflower2(0.45f, -0.17f, 0.4f, sunflower2Angle2);
    sunflower2(0.52f, -0.17f, 0.4f, sunflower2Angle2);
    sunflower2(0.58f, -0.17f, 0.4f, sunflower2Angle2);
    sunflower2(0.44f, -0.25f, 0.4f, sunflower2Angle2);
    sunflower2(0.51f, -0.25f, 0.4f, sunflower2Angle2);
    sunflower2(0.57f, -0.25f, 0.4f, sunflower2Angle2);


    bullockcart2(0.36f, 0.17f,0.27f);

    river2();
    drawOwl(-0.6f, 0.7f);
    drawOwl(-0.9f, 0.78f);
    drawBoatAtCorner2();


    glutSwapBuffers();
}
void ground3()
{
    glColor3f(0.4f,0.7f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(1.0f,0.3f);
        glVertex2f(1.0f,-1.0f);
        glVertex2f(-1.0f,-1.0f);
    glEnd();
}

void hills3()
{
    glPushMatrix();
    glTranslatef(-0.1f,0.03f,0.0f);
    glScalef(0.9f,0.9f,1.0f);

    glColor3f(0.0f, 0.5f, 0.4f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(-0.8f,0.5f);
        glVertex2f(-0.5f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f,0.3f);
        glVertex2f(-0.4f,0.5f);
        glVertex2f(-0.1f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f,0.3f);
        glVertex2f(0.0f,0.5f);
        glVertex2f(0.3f,0.3f);
    glEnd();
    glPopMatrix();
}

void drawCircle3(float x, float y, float radius) {
    glPushMatrix();
    glScalef(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}

void cloud3(float x, float y, float radius) {
    glPushMatrix();
    glScalef(0.7f,0.7f,0.7f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}
void windMill3()
{
    glPushMatrix();
    glTranslatef(-0.15f,0.1f,0.5f);
    glScalef(0.7f,0.7f,0.6f);
    glColor3f(0.6f,0.4f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.17f,0.6f);
        glVertex2f(-0.13f,0.6f);
        glVertex2f(0.001f,0.2f);
        glVertex2f(-0.28f,0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.15f, 0.6f, 0.0f); // Move to hub center
    glRotatef(bladeAngle3, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

    glColor3f(1.0f, 0.7f, 0.2f);
    for (int i = 0; i < 3; i++) {
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate for each blade
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.05f, 0.15f);
            glVertex2f(-0.05f, 0.15f);
        glEnd();
    }

    glPopMatrix();

    glColor3f(0.2f,0.1f,0.0f);
    drawCircle3(-0.15f,0.6f,0.04f);
    glPopMatrix();
}

void bush3Flower3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle3(-0.01f, 0.0f, 0.01f);
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle3(-0.0f, 0.01f, 0.01f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawCircle3(0.01f, 0.0f, 0.01f);
    glColor3f(0.8f, 0.0f, 0.0f);
    drawCircle3(0.0f, -0.01f, 0.01f);
    glColor3f(1.0f, 0.98f, 0.0f);
    drawCircle3(-0.001f, 0.0f, 0.007f);
    glPopMatrix();

    glPopMatrix();

}

void bush3(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.4f, 0.0f);
    drawCircle3(-0.05f, 0.0f, 0.06f);
    drawCircle3(0.0f, 0.02f, 0.07f);
    drawCircle3(0.05f, 0.0f, 0.06f);

    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle3(-0.03f, 0.0f, 0.03f);
    drawCircle3(0.0f, 0.02f, 0.04f);
    drawCircle3(0.03f, 0.0f, 0.03f);

    bush3Flower3(0.0f, 0.06f, 1.0f);
    bush3Flower3(-0.04f, 0.28f, 1.2f);
    bush3Flower3(-0.16f, 0.28f, 1.2f);
    bush3Flower3(-0.96f, 0.28f, 1.2f);
    bush3Flower3(-0.85f, 0.28f, 1.2f);
    bush3Flower3(-0.76f, 0.28f, 1.2f);
    bush3Flower3(-0.65f, 0.28f, 1.2f);
    bush3Flower3(-0.56f, 0.28f, 1.2f);
    bush3Flower3(-0.45f, 0.28f, 1.2f);
    bush3Flower3(-0.36f, 0.28f, 1.2f);
    bush3Flower3(-0.25f, 0.28f, 1.2f);
    bush3Flower3(0.05f, 0.28f, 1.2f);
    bush3Flower3(0.15f, 0.28f, 1.2f);
    bush3Flower3(0.25f, 0.28f, 1.2f);
    bush3Flower3(0.35f, 0.28f, 1.2f);
    bush3Flower3(0.45f, 0.28f, 1.2f);
    bush3Flower3(0.55f, 0.28f, 1.2f);
    bush3Flower3(0.65f, 0.28f, 1.2f);
    bush3Flower3(0.75f, 0.28f, 1.2f);
    bush3Flower3(0.85f, 0.28f, 1.2f);
    bush3Flower3(0.95f, 0.28f, 1.2f);
    glPopMatrix();
}

void road13(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,-0.1f);
        glVertex2f(1.0f,-0.1f);
        glVertex2f(1.0f,-0.3f);
        glVertex2f(-1.0f,-0.3f);
    glEnd();
    glPopMatrix();
}

void road23(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f,0.3f);
        glVertex2f(0.1f,0.3f);
        glVertex2f(0.1f,-0.4f);
        glVertex2f(-0.1f,-0.4f);
    glEnd();
    glPopMatrix();
}
void crop3Area3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.52f,0.35f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.17f);
        glVertex2f(-0.2f,0.17f);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(-1.0f,-0.2f);
    glEnd();
    glPopMatrix();
}

void drawTree3(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw trunk

    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.04f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();


    // Draw canopy (leaves)
    glColor3f(0.3f, 0.9f, 0.2f); // Green
    drawCircle3(0.0f, 0.44f, 0.05f);
    drawCircle3(-0.05f, 0.32f, 0.07f);
    drawCircle3(0.05f, 0.32f, 0.07f);
    drawCircle3(-0.03f, 0.38f, 0.06f);
    drawCircle3(0.03f, 0.38f, 0.06f);

    glPopMatrix();
}

void house3(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.8f, 0.5f, 0.0f); // orange wall
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Roof (triangle)
    glColor3f(0.6f, 0.3f, 0.0f); // red roof
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f, 0.2f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    // Door
    glColor3f(0.6f, 0.3f, 0.0f); // brown door
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(0.1f, -0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    // Left window
    glColor3f(0.6f, 0.3f, 0.0f); // light blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.35f, 0.15f);
    glEnd();

    // Right window
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.15f);
        glVertex2f(0.2f, 0.15f);
    glEnd();
    glPopMatrix();
}

void wellTop3(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center of circle

    for (int i = 0; i <= num_segments; i++) {
        float angle = 2 * PI3 * i / num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}
void waterWell3(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.75f, 1.0f);
    wellTop3(-0.008f, 0.12f, 0.11f, 100);
    // === Rectangular Side Wall (to make it look tall) ===
    glColor3f(0.5f, 0.5f, 0.5f); // Slightly darker gray
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);   // Top-left
        glVertex2f(0.15f, 0.1f);    // Top-right
        glVertex2f(0.15f, -0.15f);  // Bottom-right (slightly narrower for pseudo-3D)
        glVertex2f(-0.15f, -0.15f); // Bottom-left
    glEnd();

    // === Vertical Posts ===
    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.14f, 0.1f);
        glVertex2f(-0.11f, 0.1f);
        glVertex2f(-0.11f, 0.3f);
        glVertex2f(-0.14f, 0.3f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.13f, 0.1f);
        glVertex2f(0.13f, 0.3f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    // === Roof ===
    glColor3f(0.6f, 0.0f, 0.0f); // Dark red
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.3f);
        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(-0.25f, 0.33f);
    glEnd();

    // === rope3 ===
    glColor3f(0.0f, 0.0f, 0.0f); // Black rope3
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.2f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(0.02f, 0.15f);
        glVertex2f(-0.02f, 0.15f);
    glEnd();

    glPopMatrix();
}

void river3() {
    glColor3f(0.0f, 0.75f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.65f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void grass3(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.2f, 0.6f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();
    glPopMatrix();
}

void crop3(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);


    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void rail3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(0.1f, -0.2);
        glVertex2f(-0.1f, -0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.1f, 0.2f);
    glEnd();
    glPopMatrix();
}

void rope3(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 0.39f, 0.13f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.01f);
        glVertex2f(0.2f, 0.01f);
        glVertex2f(0.2f, -0.01f);
        glVertex2f(-0.2f, -0.01f);
    glEnd();
    glPopMatrix();
}

void ybush3(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.96f, 0.89f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();

    glPopMatrix();
}

void bar3(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.2f);
        glVertex2f(0.01f, 0.2f);
        glVertex2f(0.01f, -0.2f);
        glVertex2f(-0.01f, -0.2f);
    glEnd();
    glPopMatrix();
}

void cartcrop3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void bullockcart3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.06f);
        glVertex2f(0.07f, 0.06f);
        glVertex2f(0.07f, -0.08f);
        glVertex2f(0.0f, -0.08f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.03f, 0.04f);
        glVertex2f(0.05f, 0.04f);
        glVertex2f(0.05f, 0.09f);
        glVertex2f(0.03f, 0.09f);
        glColor3f(0.43f, 0.12f, 0.03f);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.3f, -0.05f);
        glVertex2f(-0.3f, -0.07f);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(-0.37f, -0.087f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.22f, -0.2f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.08f, -0.2f);
        glVertex2f(-0.03f, -0.2f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.08f, -0.3f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.22f, -0.35f);
        glVertex2f(-0.27f, -0.35f);
        glVertex2f(-0.08f, -0.3f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.03f, -0.35f);
        glVertex2f(-0.08f, -0.35f);
    glEnd();

    glColor3f(0.51f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(-0.04f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(-0.4f, -0.1f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.4f, 0.04f);
        glVertex2f(-0.33f, 0.04f);
        glVertex2f(-0.33f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glColor3f(0.51f, 0.0f, 0.12f);
        glVertex2f(-0.8f, 0.08f);
        glVertex2f(-0.4f, 0.08f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.8f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle3(-0.7f, -0.3f, 0.07f);
    drawCircle3(-0.5f, -0.3f, 0.07f);

    glColor3f(0.87f, 0.62f, 0.43f);
    drawCircle3(-0.5f, -0.3f, 0.03f);
    drawCircle3(-0.7f, -0.3f, 0.03f);

    glColor3f(0.96f, 0.89f, 0.08f);
    ybush3(-0.6f, 0.0f, 0.8f);

    cartcrop3(-0.74f, -0.25f, 0.3f);
    cartcrop3(-0.74f, -0.25f, 0.3f);
    cartcrop3(-0.72f, -0.25f, 0.3f);
    cartcrop3(-0.72f, -0.25f, 0.3f);
    cartcrop3(-0.7f, -0.25f, 0.3f);
    cartcrop3(-0.7f, -0.25f, 0.3f);
    cartcrop3(-0.68f, -0.25f, 0.3f);
    cartcrop3(-0.68f, -0.25f, 0.3f);
    cartcrop3(-0.66f, -0.25f, 0.3f);
    cartcrop3(-0.66f, -0.25f, 0.3f);
    cartcrop3(-0.64f, -0.25f, 0.3f);
    cartcrop3(-0.64f, -0.25f, 0.3f);
    cartcrop3(-0.62f, -0.25f, 0.3f);
    cartcrop3(-0.62f, -0.25f, 0.3f);
    cartcrop3(-0.6f, -0.25f, 0.3f);
    cartcrop3(-0.6f, -0.25f, 0.3f);
    cartcrop3(-0.58f, -0.25f, 0.3f);
    cartcrop3(-0.58f, -0.25f, 0.3f);
    cartcrop3(-0.56f, -0.25f, 0.3f);
    cartcrop3(-0.56f, -0.25f, 0.3f);
    cartcrop3(-0.54f, -0.25f, 0.3f);
    cartcrop3(-0.54f, -0.25f, 0.3f);
    cartcrop3(-0.52f, -0.25f, 0.3f);
    cartcrop3(-0.52f, -0.25f, 0.3f);
    cartcrop3(-0.5f, -0.25f, 0.3f);
    cartcrop3(-0.5f, -0.25f, 0.3f);
    cartcrop3(-0.48f, -0.25f, 0.3f);
    cartcrop3(-0.48f, -0.25f, 0.3f);
    cartcrop3(-0.46f, -0.25f, 0.3f);
    cartcrop3(-0.46f, -0.25f, 0.3f);
    cartcrop3(-0.44f, -0.25f, 0.3f);
    cartcrop3(-0.44f, -0.25f, 0.3f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.38f, 0.18f);
        glVertex2f(-0.32f, 0.18f);
        glVertex2f(-0.32f, 0.12f);
        glVertex2f(-0.38f, 0.12f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.12f);
        glVertex2f(-0.33f, 0.12f);
        glVertex2f(-0.33f, 0.06f);
        glVertex2f(-0.37f, 0.06f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.06f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.32f, 0.04f);
        glVertex2f(-0.37f, 0.04f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.3f, 0.06f);
        glVertex2f(-0.3f, 0.01f);
        glVertex2f(-0.32f, 0.01f);
        //Hand
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.3f, 0.09f);
        glVertex2f(-0.3f, 0.07f);
        glVertex2f(-0.35f, 0.1f);
    glEnd();

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.3f, 0.08f);
        glVertex2f(0.0f, -0.02f);
    glEnd();
    glPopMatrix();
}

void boat3rider3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.38f, 0.16f);
        glVertex2f(-0.32f, 0.16f);
        glVertex2f(-0.32f, 0.12f);
        glVertex2f(-0.38f, 0.12f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.37f, 0.12f);
        glVertex2f(-0.33f, 0.12f);
        glVertex2f(-0.33f, 0.06f);
        glVertex2f(-0.37f, 0.06f);
    glEnd();
        //Hand
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.3f, 0.09f);
        glVertex2f(-0.3f, 0.07f);
        glVertex2f(-0.35f, 0.1f);
    glEnd();

    glPopMatrix();
}
void boat3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    glPopMatrix();
}

void man3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.8f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.8f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //leg
    glColor3f(0.3f, 0.18f, 0.56f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle3(-0.05f, 0.0f, 0.03f);
    drawCircle3(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle3(-0.05f, 0.0f, 0.01f);
    drawCircle3(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void woman3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.75f, 0.07f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.85f, 0.2f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.15f, 0.15f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //leg
    glColor3f(0.3f, 0.18f, 0.56f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle3(-0.05f, 0.0f, 0.03f);
    drawCircle3(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle3(-0.05f, 0.0f, 0.01f);
    drawCircle3(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();

    glPopMatrix();
}

void boy3(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.89f, 0.85f, 0.38f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.89f, 0.85f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //leg
    glColor3f(0.18f, 0.31f, 0.27f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.5f);
        glVertex2f(-0.05f, -0.5f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(0.13f, -0.5f);
        glVertex2f(0.05f, -0.5f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.13f, -0.7f);
    glEnd();

    //foot
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.13f, -0.7f);
        glVertex2f(-0.05f, -0.7f);
        glVertex2f(-0.05f, -0.85f);
        glVertex2f(-0.13f, -0.85f);
        glVertex2f(0.13f, -0.7f);
        glVertex2f(0.05f, -0.7f);
        glVertex2f(0.05f, -0.85f);
        glVertex2f(0.13f, -0.85f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle3(-0.05f, 0.0f, 0.03f);
    drawCircle3(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle3(-0.05f, 0.0f, 0.01f);
    drawCircle3(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void marigoldFlower3(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // === Stem ===
    glColor3f(0.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.005f, 0.0f);
        glVertex2f(0.005f, 0.0f);
        glVertex2f(0.005f, 0.25f);
        glVertex2f(-0.005f, 0.25f);
    glEnd();

    // === Marigold petals ===
    glColor3f(1.0f, 0.6f, 0.0f); // Orange-yellow
    for (float angle = 0; angle < 360; angle += 30.0f) {
        float rad = angle * PI3 / 180.0f;
        float px = 0.0f + cos(rad) * 0.04f;
        float py = 0.25f + sin(rad) * 0.04f;
        drawCircle3(px, py, 0.015f);
    }

    // === Center ===
    glColor3f(0.8f, 0.3f, 0.0f);
    drawCircle3(0.0f, 0.25f, 0.02f);

    glPopMatrix();
}

void drawBird3(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawBird3(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBird3(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBird3(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}

void drawBird32(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(-1.0f, -1.0f, 1.0f);
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBird3(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBird3(0.07, -0.08, 0.05, 50);

    glPopMatrix();
}


void initRain3() {
    for (int i = 0; i < 200; i++) {
        rainX[i] = ((rand() % 200) / 100.0f) - 1.0f; // Range: -1.0 to 1.0 (full width)
        rainY[i] = ((rand() % 200) / 100.0f);        // Range: 0.0 to 2.0 (above screen)
    }
}

void drawRain3() {
    glColor3f(0.95f, 0.95f, 0.95f); // Near white raindrops
    for (int i = 0; i < 200; i++) {
        glPushMatrix();
        glTranslatef(rainX[i], rainY[i], 0.0f);
        glBegin(GL_LINES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.0f, -0.1f); // vertical drop
        glEnd();
        glPopMatrix();
    }
}

void drawRipple3(float x, float y, float radius)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(0.0f, 0.65f, 0.95f); // Match river3 color
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 100; i++) {
        float theta = 2.0f * PI3 * float(i) / float(100);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(dx, dy);
    }
    glEnd();
    glPopMatrix();
}

void lightningEffect3() {
    if (isLightning) {
        glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
        glBegin(GL_QUADS);
            glVertex2f(-1.0f, 1.0f);
            glVertex2f(1.0f, 1.0f);
            glVertex2f(1.0f, -1.0f);
            glVertex2f(-1.0f, -1.0f);
        glEnd();
    }
}

void umbrella(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.6f, 0.2f, 0.7f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.05f);
        for (int i = 0; i <= 180; i += 20) {
            float rad = i * 3.1416f / 180.0f;
            glVertex2f(0.1f * cos(rad), 0.05f + 0.05f * sin(rad));
        }
    glEnd();
    glPopMatrix();
}
void umbrella1(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.2f, 0.2f, 0.7f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.05f);
        for (int i = 0; i <= 180; i += 20) {
            float rad = i * 3.1416f / 180.0f;
            glVertex2f(0.1f * cos(rad), 0.05f + 0.05f * sin(rad));
        }
    glEnd();
    glColor3f(0.1f, 0.1f, 0.1f); // handle
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.05f);
        glVertex2f(0.0f, -0.05f);
    glEnd();
    glPopMatrix();
}


void displayMonsoon() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    // Sun
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle3(0.0f, 0.8f, 0.1f);

    // cloud3
    // cloud3
    glColor3f(0.3f, 0.3f, 0.3f);
    cloud3(cloud3Position13 - 0.1f, 1.1f, 0.1f);
    cloud3(cloud3Position13, 1.1f, 0.15f);
    cloud3(cloud3Position13 + 0.1f, 1.1f, 0.1f);

    glColor3f(0.3f, 0.3f, 0.3f);
    cloud3(cloud3Position23 - 0.1f, 0.75f, 0.1f);
    cloud3(cloud3Position23, 0.75f, 0.15f);
    cloud3(cloud3Position23+ 0.1f, 0.75f, 0.1f);

    cloud3(-0.15f, 1.1f, 0.1f);
    cloud3(-0.05f, 1.1f, 0.15f);
    cloud3(0.05f, 1.1f, 0.1f);


    ground3();
    road13(0.0f, -0.25f, 1.0f);
    road23(0.0f, 0.0f, 1.0f);
    road23(0.7f, -0.2f, 0.5f);
    grass3(-0.9f, -0.649f, 0.45f, 0.0f);
    grass3(-0.9f, -0.7f, 0.45f, -30.0f);
    grass3(-0.95f, -0.73f, 0.45f, -70.0f);
    grass3(-0.7f, -0.649f, 0.45f, 0.0f);
    grass3(-0.73f, -0.7f, 0.45f, -60.0f);
    grass3(-0.6f, -0.649f, 0.45f, 0.0f);
    grass3(-0.6f, -0.7f, 0.45f, -30.0f);
    grass3(-0.65f, -0.7f, 0.45f, -30.0f);
    grass3(-0.6f, -0.73f, 0.45f, -70.0f);
    grass3(-0.4f, -0.649f, 0.45f, 0.0f);
    grass3(-0.4f, -0.7f, 0.45f, -30.0f);
    grass3(-0.45f, -0.73f, 0.45f, -70.0f);
    grass3(-0.3f, -0.649f, 0.45f, 0.0f);
    grass3(-0.33f, -0.7f, 0.45f, -60.0f);
    grass3(-0.2f, -0.649f, 0.45f, 0.0f);
    grass3(-0.2f, -0.7f, 0.45f, -30.0f);
    grass3(-0.15f, -0.7f, 0.45f, -30.0f);
    grass3(-0.18f, -0.73f, 0.45f, -70.0f);
    grass3(0.0f, -0.649f, 0.45f, 0.0f);
    grass3(0.0f, -0.7f, 0.45f, -30.0f);
    grass3(0.05f, -0.73f, 0.45f, -70.0f);
    grass3(0.1f, -0.649f, 0.45f, 0.0f);
    grass3(1.13f, -0.7f, 0.45f, -60.0f);
    grass3(0.2f, -0.649f, 0.45f, 0.0f);
    grass3(0.2f, -0.7f, 0.45f, -30.0f);
    grass3(0.25f, -0.7f, 0.45f, -30.0f);
    grass3(0.2f, -0.73f, 0.45f, -70.0f);
    grass3(0.4f, -0.649f, 0.45f, 0.0f);
    grass3(0.4f, -0.7f, 0.45f, -30.0f);
    grass3(0.45f, -0.73f, 0.45f, -70.0f);
    grass3(0.5f, -0.649f, 0.45f, 0.0f);
    grass3(0.6f, -0.649f, 0.45f, 0.0f);
    grass3(0.6f, -0.7f, 0.45f, -30.0f);
    grass3(0.65f, -0.7f, 0.45f, -30.0f);
    grass3(0.63f, -0.73f, 0.45f, -70.0f);
    grass3(0.75f, -0.7f, 0.45f, -30.0f);
    grass3(0.73f, -0.73f, 0.45f, -70.0f);
    grass3(0.8f, -0.649f, 0.45f, 0.0f);
    grass3(0.8f, -0.7f, 0.45f, -30.0f);
    grass3(0.85f, -0.73f, 0.45f, -70.0f);
    grass3(0.9f, -0.649f, 0.45f, 0.0f);
    grass3(1.0f, -0.649f, 0.45f, 0.0f);
    grass3(1.0f, -0.7f, 0.45f, -30.0f);
    grass3(1.05f, -0.7f, 0.45f, -30.0f);
    hills3();
    windMill3();

    bush3(-0.9f, 0.25f, 1.2f);
    bush3(-0.7f, 0.25f, 1.2f);
    bush3(-0.5f, 0.25f, 1.2f);
    bush3(-0.3f, 0.25f, 1.2f);
    bush3(-0.1f, 0.25f, 1.2f);
    bush3(0.1f, 0.25f, 1.2f);
    bush3(0.3f, 0.25f, 1.2f);
    bush3(0.5f, 0.25f, 1.2f);
    bush3(0.7f, 0.25f, 1.2f);
    bush3(0.9f, 0.25f, 1.2f);

    bar3(0.26f, 0.01f, 0.18f, 0.0f);
    bar3(0.34f, 0.01f, 0.18f, 0.0f);
    bar3(0.3f, 0.04f, 0.25f, -90.0f);

    ybush3(0.49f, 0.1f, 0.5f);
    crop3(0.58f, 0.15f, 0.3f, 180.0f);
    crop3(0.58f, 0.05f, 0.3f, 0.0f);
    crop3(0.56f, 0.15f, 0.3f, 180.0f);
    crop3(0.56f, 0.05f, 0.3f, 0.0f);
    crop3(0.54f, 0.15f, 0.3f, 180.0f);
    crop3(0.54f, 0.05f, 0.3f, 0.0f);
    crop3(0.52f, 0.15f, 0.3f, 180.0f);
    crop3(0.52f, 0.05f, 0.3f, 0.0f);
    crop3(0.59f, 0.15f, 0.3f, 180.0f);
    crop3(0.59f, 0.05f, 0.3f, 0.0f);
    crop3(0.57f, 0.15f, 0.3f, 180.0f);
    crop3(0.57f, 0.05f, 0.3f, 0.0f);
    crop3(0.55f, 0.15f, 0.3f, 180.0f);
    crop3(0.55f, 0.05f, 0.3f, 0.0f);
    crop3(0.53f, 0.15f, 0.3f, 180.0f);
    crop3(0.53f, 0.05f, 0.3f, 0.0f);
    crop3(0.5f, 0.15f, 0.3f, 180.0f);
    crop3(0.5f, 0.05f, 0.3f, 0.0f);
    crop3(0.48f, 0.15f, 0.3f, 180.0f);
    crop3(0.48f, 0.05f, 0.3f, 0.0f);
    crop3(0.46f, 0.15f, 0.3f, 180.0f);
    crop3(0.46f, 0.05f, 0.3f, 0.0f);
    crop3(0.44f, 0.15f, 0.3f, 180.0f);
    crop3(0.44f, 0.05f, 0.3f, 0.0f);
    crop3(0.42f, 0.15f, 0.3f, 180.0f);
    crop3(0.42f, 0.05f, 0.3f, 0.0f);
    crop3(0.4f, 0.15f, 0.3f, 180.0f);
    crop3(0.4f, 0.05f, 0.3f, 0.0f);
    crop3(0.51f, 0.15f, 0.3f, 180.0f);
    crop3(0.51f, 0.05f, 0.3f, 0.0f);
    crop3(0.49f, 0.15f, 0.3f, 180.0f);
    crop3(0.49f, 0.05f, 0.3f, 0.0f);
    crop3(0.47f, 0.15f, 0.3f, 180.0f);
    crop3(0.47f, 0.05f, 0.3f, 0.0f);
    crop3(0.45f, 0.15f, 0.3f, 180.0f);
    crop3(0.45f, 0.05f, 0.3f, 0.0f);
    crop3(0.43f, 0.15f, 0.3f, 180.0f);
    crop3(0.43f, 0.05f, 0.3f, 0.0f);
    crop3(0.41f, 0.15f, 0.3f, 180.0f);
    crop3(0.41f, 0.05f, 0.3f, 0.0f);



    drawTree3(-0.9f, 0.15f, 1.2f);
    drawTree3(-0.6f, 0.15f, 1.0f);
    drawTree3(0.85f, 0.0f, 1.2f);

    crop3Area3(0.0f, -0.03f, 1.0f);

    umbrella(-0.25f, man3Y3, 0.7f);
    man3(-0.25f, man3Y3+0.01f, 0.25f);
    //Row 1
    crop3(-0.97f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.91f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.85f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.79f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.73f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.67f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.61f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.55f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.49f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.43f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.37f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.31f, 0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.25f, 0.1f, 0.3f, crop3SwayAngle3);
    //Row 2
    crop3(-0.99f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.93f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.87f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.81f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.75f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.69f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.63f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.57f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.51f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.45f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.39f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.33f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.27f, 0.0f, 0.3f, crop3SwayAngle3);
    crop3(-0.22f, 0.0f, 0.3f, crop3SwayAngle3);
    //Row 3
    crop3(-0.97f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.91f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.85f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.79f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.73f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.67f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.61f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.55f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.49f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.43f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.37f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.31f, -0.1f, 0.3f, crop3SwayAngle3);
    crop3(-0.25f, -0.1f, 0.3f, crop3SwayAngle3);
    //Row 4
    crop3(-0.99f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.93f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.87f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.81f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.75f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.69f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.63f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.57f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.51f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.45f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.39f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.33f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.27f, -0.2f, 0.3f, crop3SwayAngle3);
    crop3(-0.22f, -0.2f, 0.3f, crop3SwayAngle3);

    //man3(-0.25f, 0.3f, 0.25f);

    waterWell3(0.3f, -0.2f, 0.6f);

    rope3(0.5f, -0.07f, 0.5f, 0.0f);
    rope3(0.41f, -0.17f, 0.5f, -90.0f);
    rope3(0.5f, -0.3f, 0.5f, 0.0f);
    rope3(0.61f, -0.17f, 0.5f, -90.0f);
    rope3(0.793f, -0.17f, 0.5f, -90.0f);
    rope3(0.9f, -0.3f, 0.5f, 0.0f);
    house3(0.7f,0.0f,0.5f);
    drawTree3(0.95f, -0.3f, 1.2f);
    rail3(0.49f, -0.075f, 0.13f);
    rail3(0.45f, -0.075f, 0.13f);
    rail3(0.41f, -0.075f, 0.13f);
    rail3(0.41f, -0.15f, 0.13f);
    rail3(0.41f, -0.225f, 0.13f);
    rail3(0.41f, -0.3f, 0.13f);
    rail3(0.45f, -0.3f, 0.13f);
    rail3(0.49f, -0.3f, 0.13f);
    rail3(0.53f, -0.3f, 0.13f);
    rail3(0.57f, -0.3f, 0.13f);
    rail3(0.61f, -0.3f, 0.13f);
    rail3(0.61f, -0.225f, 0.13f);
    rail3(0.61f, -0.15f, 0.13f);
    rail3(0.79f, -0.15f, 0.13f);
    rail3(0.79f, -0.225f, 0.13f);
    rail3(0.79f, -0.3f, 0.13f);
    rail3(0.83f, -0.3f, 0.13f);
    rail3(0.87f, -0.3f, 0.13f);
    rail3(0.91f, -0.3f, 0.13f);
    rail3(0.95f, -0.3f, 0.13f);
    rail3(0.99f, -0.3f, 0.13f);

    boy3(0.2f, boy3Y4-0.1f, 0.2f);
    umbrella1(0.0f, woman3Y3+0.03f, 1.0f);
    woman3(0.05f, woman3Y3, 0.3f);


    marigoldFlower3(0.45f, -0.17f, 0.4f, sunflowerAngle3);
    marigoldFlower3(0.52f, -0.17f, 0.4f, sunflowerAngle3);
    marigoldFlower3(0.58f, -0.17f, 0.4f, sunflowerAngle3);
    marigoldFlower3(0.44f, -0.25f, 0.4f, sunflowerAngle3);
    marigoldFlower3(0.51f, -0.25f, 0.4f, sunflowerAngle3);
    marigoldFlower3(0.57f, -0.25f, 0.4f, sunflowerAngle3);


    bullockcart3(cartX3, -0.3f, 0.5f);

    river3();
    boat3rider3(boat3X3 +0.28, -0.83f, 1.0f);
    boat3(boat3X3, -0.9f, 0.7f);

    drawBird3(-0.9f, 0.77f);
    drawBird32(0.86f, 0.62f);


    // === Rain ===
    drawRain3();


    // === Lightning flash ===
    lightningEffect3();

    // Draw ripples on river3
    for (int i = 0; i < 20; i++) {
        if (ripples[i].active) {
        drawRipple3(ripples[i].x, ripples[i].y, ripples[i].radius);
        }
    }


    glutSwapBuffers();
}
void ground4()
{
    glColor3f(0.4f,0.7f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(1.0f,0.3f);
        glVertex2f(1.0f,-1.0f);
        glVertex2f(-1.0f,-1.0f);
    glEnd();
}

void hills4()
{
    glPushMatrix();
    glTranslatef(-0.1f,0.03f,0.0f);
    glScalef(0.9f,0.9f,1.0f);

    glColor3f(1.0f, 1.0f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f,0.3f);
        glVertex2f(-0.8f,0.5f);
        glVertex2f(-0.5f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.6f,0.3f);
        glVertex2f(-0.4f,0.5f);
        glVertex2f(-0.1f,0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.2f,0.3f);
        glVertex2f(0.0f,0.5f);
        glVertex2f(0.3f,0.3f);
    glEnd();
    glPopMatrix();
}

void drawCircle4(float x, float y, float radius) {
    glPushMatrix();
    glScalef(1.0f,1.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}

void cloud4(float x, float y, float radius) {
    glPushMatrix();
    glScalef(0.7f,0.7f,0.7f);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1415926f * i / 100;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
    glPopMatrix();
}
void windMill4()
{
    glPushMatrix();
    glTranslatef(-0.15f,0.1f,0.5f);
    glScalef(0.7f,0.7f,0.6f);
    glColor3f(0.6f,0.4f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.17f,0.6f);
        glVertex2f(-0.13f,0.6f);
        glVertex2f(0.001f,0.2f);
        glVertex2f(-0.28f,0.2f);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.15f, 0.6f, 0.0f); // Move to hub center
    glRotatef(bladeAngle4, 0.0f, 0.0f, 1.0f); // Rotate around Z axis

    glColor3f(1.0f, 0.7f, 0.2f);
    for (int i = 0; i < 3; i++) {
        glRotatef(120.0f, 0.0f, 0.0f, 1.0f); // Rotate for each blade
        glBegin(GL_TRIANGLES);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(0.05f, 0.15f);
            glVertex2f(-0.05f, 0.15f);
        glEnd();
    }

    glPopMatrix();

    glColor3f(0.2f,0.1f,0.0f);
    drawCircle4(-0.15f,0.6f,0.04f);
    glPopMatrix();
}

void bush4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.0f, 0.4f, 0.0f);
    drawCircle4(-0.05f, 0.0f, 0.06f);
    drawCircle4(0.0f, 0.02f, 0.07f);
    drawCircle4(0.05f, 0.0f, 0.06f);

    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle4(-0.03f, 0.0f, 0.03f);
    drawCircle4(0.0f, 0.02f, 0.04f);
    drawCircle4(0.03f, 0.0f, 0.03f);
    glPopMatrix();
}

void road14(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,-0.1f);
        glVertex2f(1.0f,-0.1f);
        glVertex2f(1.0f,-0.3f);
        glVertex2f(-1.0f,-0.3f);
    glEnd();
    glPopMatrix();
}

void road24(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x,y,1.0f);
    glScalef(scale,scale,1.0f);

    glColor3f(1.0f,0.95f,0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f,0.3f);
        glVertex2f(0.1f,0.3f);
        glVertex2f(0.1f,-0.4f);
        glVertex2f(-0.1f,-0.4f);
    glEnd();
    glPopMatrix();
}
void crop4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.52f,0.35f,0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f,0.17f);
        glVertex2f(-0.2f,0.17f);
        glVertex2f(-0.2f,-0.2f);
        glVertex2f(-1.0f,-0.2f);
    glEnd();
    glPopMatrix();
}

void drawTree4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw trunk

    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.04f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();

    glPopMatrix();
}

void dateTree4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Draw trunk

    glColor3f(0.4f, 0.2f, 0.0f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.04f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();


    // leaves
    glColor3f(0.3f, 0.7f, 0.2f); // Green
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.03f, 0.3f);
        glVertex2f(-0.03f, 0.3f);
        glVertex2f(-0.06f, 0.47f);
        glVertex2f(0.03f, 0.3f);
        glVertex2f(-0.03f, 0.3f);
        glVertex2f(0.06f, 0.47f);
        glVertex2f(0.03f, 0.3f);
        glVertex2f(-0.03f, 0.3f);//1
        glVertex2f(-0.12f, 0.44f);
        glVertex2f(0.03f, 0.3f);
        glVertex2f(-0.03f, 0.3f);
        glVertex2f(0.12f, 0.44f);
        glVertex2f(0.03f, 0.3f);
        glVertex2f(-0.03f, 0.3f);//2
        glVertex2f(-0.18f, 0.41f);
        glVertex2f(0.05f, 0.3f);
        glVertex2f(-0.05f, 0.3f);
        glVertex2f(0.18f, 0.41f);
        glVertex2f(0.05f, 0.3f);
        glVertex2f(-0.05f, 0.3f);//3
        glVertex2f(-0.24f, 0.38f);
        glVertex2f(0.08f, 0.3f);
        glVertex2f(-0.08f, 0.3f);
        glVertex2f(0.24f, 0.38f);
        glVertex2f(0.08f, 0.3f);
        glVertex2f(-0.08f, 0.3f);//4
    glEnd();

    glColor3f(0.2f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.28f);
        glVertex2f(0.01f, 0.28f);
        glVertex2f(0.01f, 0.3f);
        glVertex2f(-0.01f, 0.3f);
    glEnd();

    glColor3f(0.7f, 0.3f, 0.0f);
    drawCircle4(0.0f, 0.26f, 0.03f);
    glPopMatrix();
}

void house4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glColor3f(0.8f, 0.5f, 0.0f); // orange wall
    glBegin(GL_POLYGON);
        glVertex2f(-0.4f, -0.2f);
        glVertex2f(0.4f, -0.2f);
        glVertex2f(0.4f, 0.2f);
        glVertex2f(-0.4f, 0.2f);
    glEnd();

    // Roof (triangle)
    glColor3f(0.6f, 0.3f, 0.0f); // red roof
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f, 0.2f);
        glVertex2f(0.45f, 0.2f);
        glVertex2f(0.0f, 0.45f);
    glEnd();

    // Door
    glColor3f(0.6f, 0.3f, 0.0f); // brown door
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, -0.2f);
        glVertex2f(0.1f, -0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    // Left window
    glColor3f(0.6f, 0.3f, 0.0f); // light blue
    glBegin(GL_POLYGON);
        glVertex2f(-0.35f, 0.0f);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.2f, 0.15f);
        glVertex2f(-0.35f, 0.15f);
    glEnd();

    // Right window
    glBegin(GL_POLYGON);
        glVertex2f(0.2f, 0.0f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.35f, 0.15f);
        glVertex2f(0.2f, 0.15f);
    glEnd();
    glPopMatrix();
}

void wellTop4(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // center of circle

    for (int i = 0; i <= num_segments; i++) {
        float angle = 2 * PI4 * i / num_segments;
        float x = cx + r * cos(angle);
        float y = cy + r * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}
void waterWell4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.7f, 0.9f, 1.0f);
    wellTop4(-0.008f, 0.12f, 0.11f, 100);
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, 0.1f);
        glVertex2f(0.15f, 0.1f);
        glVertex2f(0.15f, -0.15f);
        glVertex2f(-0.15f, -0.15f);
    glEnd();

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.14f, 0.1f);
        glVertex2f(-0.11f, 0.1f);
        glVertex2f(-0.11f, 0.3f);
        glVertex2f(-0.14f, 0.3f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.13f, 0.1f);
        glVertex2f(0.13f, 0.3f);
        glVertex2f(0.1f, 0.3f);
    glEnd();

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.25f, 0.3f);
        glVertex2f(0.25f, 0.3f);
        glVertex2f(0.25f, 0.33f);
        glVertex2f(-0.25f, 0.33f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.0f, 0.15f);
    glEnd();

    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glVertex2f(-0.02f, 0.2f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(0.02f, 0.15f);
        glVertex2f(-0.02f, 0.15f);
    glEnd();

    glPopMatrix();
}

void river4() {
    glColor3f(0.7f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.65f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();
}

void grass4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.2f, 0.6f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.2f, 0.0f);
        glVertex2f(-0.4f, 0.3f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();
    glPopMatrix();
}

void crop4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);


    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void mustard4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glColor3f(1.0f, 0.8f, 0.09f);
    drawCircle4(0.0f, 0.44f, 0.02f);
    drawCircle4(0.0f, 0.36f, 0.02f);
    drawCircle4(-0.04f, 0.4f, 0.02f);
    drawCircle4(0.04f, 0.4f, 0.02f);
    drawCircle4(-0.02f, 0.435f, 0.02f);
    drawCircle4(0.018f, 0.365f, 0.02f);
    drawCircle4(-0.038f, 0.385f, 0.02f);
    drawCircle4(0.038f, 0.385f, 0.02f);
    drawCircle4(0.02f, 0.44f, 0.02f);
    drawCircle4(-0.02f, 0.36f, 0.02f);

    glColor3f(1.0f, 0.8f, 0.09f);
    drawCircle4(0.0f, 0.4f, 0.02f);
    glPopMatrix();

}
void rail4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.1f, 0.2f);
        glVertex2f(0.1f, -0.2);
        glVertex2f(-0.1f, -0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.1f, 0.2f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.1f, 0.2f);
    glEnd();
    glPopMatrix();
}

void rope4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0f, 0.39f, 0.13f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.01f);
        glVertex2f(0.2f, 0.01f);
        glVertex2f(0.2f, -0.01f);
        glVertex2f(-0.2f, -0.01f);
    glEnd();
    glPopMatrix();
}

void ybush4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.96f, 0.89f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.2f, -0.2f);
        glVertex2f(-0.2f, -0.2f);
    glEnd();

    glPopMatrix();
}

void bar4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, 0.2f);
        glVertex2f(0.01f, 0.2f);
        glVertex2f(0.01f, -0.2f);
        glVertex2f(-0.01f, -0.2f);
    glEnd();
    glPopMatrix();
}

void cartcrop4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.85f, 0.8f, 0.3f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(-0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.4f);
        glVertex2f(0.06, 0.45f);
        glVertex2f(0.0f, 0.38f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glPopMatrix();
}
void bullockcart4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.06f);
        glVertex2f(0.07f, 0.06f);
        glVertex2f(0.07f, -0.08f);
        glVertex2f(0.0f, -0.08f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.03f, 0.04f);
        glVertex2f(0.05f, 0.04f);
        glVertex2f(0.05f, 0.09f);
        glVertex2f(0.03f, 0.09f);
        glColor3f(0.43f, 0.12f, 0.03f);
        glVertex2f(-0.3f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.2f);
        glVertex2f(-0.3f, -0.2f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.3f, -0.05f);
        glVertex2f(-0.3f, -0.07f);
        glVertex2f(-0.45f, -0.1f);
        glVertex2f(-0.37f, -0.087f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.22f, -0.2f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.08f, -0.2f);
        glVertex2f(-0.03f, -0.2f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.08f, -0.3f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.27f, -0.3f);
        glVertex2f(-0.22f, -0.3f);
        glVertex2f(-0.22f, -0.35f);
        glVertex2f(-0.27f, -0.35f);
        glVertex2f(-0.08f, -0.3f);
        glVertex2f(-0.03f, -0.3f);
        glVertex2f(-0.03f, -0.35f);
        glVertex2f(-0.08f, -0.35f);
    glEnd();

    glColor3f(0.51f, 0.0f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(-0.04f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glVertex2f(0.0f, -0.05f);
        glVertex2f(0.0f, -0.1f);
        glVertex2f(-0.4f, -0.1f);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.4f, 0.04f);
        glVertex2f(-0.33f, 0.04f);
        glVertex2f(-0.33f, -0.05f);
        glVertex2f(-0.4f, -0.05f);
        glColor3f(0.51f, 0.0f, 0.12f);
        glVertex2f(-0.8f, 0.08f);
        glVertex2f(-0.4f, 0.08f);
        glVertex2f(-0.4f, -0.3f);
        glVertex2f(-0.8f, -0.3f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle4(-0.7f, -0.3f, 0.07f);
    drawCircle4(-0.5f, -0.3f, 0.07f);

    glColor3f(0.87f, 0.62f, 0.43f);
    drawCircle4(-0.5f, -0.3f, 0.03f);
    drawCircle4(-0.7f, -0.3f, 0.03f);

    glColor3f(0.96f, 0.89f, 0.08f);
    ybush4(-0.6f, 0.0f, 0.8f);

    cartcrop4(-0.74f, -0.25f, 0.3f);
    cartcrop4(-0.74f, -0.25f, 0.3f);
    cartcrop4(-0.72f, -0.25f, 0.3f);
    cartcrop4(-0.72f, -0.25f, 0.3f);
    cartcrop4(-0.7f, -0.25f, 0.3f);
    cartcrop4(-0.7f, -0.25f, 0.3f);
    cartcrop4(-0.68f, -0.25f, 0.3f);
    cartcrop4(-0.68f, -0.25f, 0.3f);
    cartcrop4(-0.66f, -0.25f, 0.3f);
    cartcrop4(-0.66f, -0.25f, 0.3f);
    cartcrop4(-0.64f, -0.25f, 0.3f);
    cartcrop4(-0.64f, -0.25f, 0.3f);
    cartcrop4(-0.62f, -0.25f, 0.3f);
    cartcrop4(-0.62f, -0.25f, 0.3f);
    cartcrop4(-0.6f, -0.25f, 0.3f);
    cartcrop4(-0.6f, -0.25f, 0.3f);
    cartcrop4(-0.58f, -0.25f, 0.3f);
    cartcrop4(-0.58f, -0.25f, 0.3f);
    cartcrop4(-0.56f, -0.25f, 0.3f);
    cartcrop4(-0.56f, -0.25f, 0.3f);
    cartcrop4(-0.54f, -0.25f, 0.3f);
    cartcrop4(-0.54f, -0.25f, 0.3f);
    cartcrop4(-0.52f, -0.25f, 0.3f);
    cartcrop4(-0.52f, -0.25f, 0.3f);
    cartcrop4(-0.5f, -0.25f, 0.3f);
    cartcrop4(-0.5f, -0.25f, 0.3f);
    cartcrop4(-0.48f, -0.25f, 0.3f);
    cartcrop4(-0.48f, -0.25f, 0.3f);
    cartcrop4(-0.46f, -0.25f, 0.3f);
    cartcrop4(-0.46f, -0.25f, 0.3f);
    cartcrop4(-0.44f, -0.25f, 0.3f);
    cartcrop4(-0.44f, -0.25f, 0.3f);

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.38f, 0.18f);
        glVertex2f(-0.32f, 0.18f);
        glVertex2f(-0.32f, 0.12f);
        glVertex2f(-0.38f, 0.12f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.12f);
        glVertex2f(-0.33f, 0.12f);
        glVertex2f(-0.33f, 0.06f);
        glVertex2f(-0.37f, 0.06f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.37f, 0.06f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.32f, 0.04f);
        glVertex2f(-0.37f, 0.04f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.32f, 0.06f);
        glVertex2f(-0.3f, 0.06f);
        glVertex2f(-0.3f, 0.01f);
        glVertex2f(-0.32f, 0.01f);
        //Hand
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-0.35f, 0.12f);
        glVertex2f(-0.3f, 0.09f);
        glVertex2f(-0.3f, 0.07f);
        glVertex2f(-0.35f, 0.1f);
    glEnd();

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.3f, 0.08f);
        glVertex2f(0.0f, -0.02f);
    glEnd();
    glPopMatrix();
}
void boat4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.2f, 0.2f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    glPopMatrix();
}

void man4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.8f, 0.5f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.8f, 0.7f, 0.9f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle4(-0.05f, 0.0f, 0.03f);
    drawCircle4(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle4(-0.05f, 0.0f, 0.01f);
    drawCircle4(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void woman4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.75f, 0.07f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.85f, 0.2f, 0.09f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();

    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle4(-0.05f, 0.0f, 0.03f);
    drawCircle4(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle4(-0.05f, 0.0f, 0.01f);
    drawCircle4(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();

    glPopMatrix();
}

void boy4(float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);

    //head
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(0.1f, 0.1f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(-0.1f, 0.05f);
    glEnd();

    //face
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.1f, 0.05f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.1f, -0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    //Body
    glColor3f(0.89f, 0.85f, 0.38f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.15f, -0.5f);
        glVertex2f(-0.15f, -0.5f);
    glEnd();

    //hand
    glColor3f(0.89f, 0.85f, 0.5f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.1f);
        glVertex2f(-0.2f, -0.1f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(0.15f, -0.1f);
        glVertex2f(0.2f, -0.1f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.15f, -0.4f);
    glEnd();

    //palm
    glColor3f(0.99f, 0.88f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(-0.15f, -0.4f);
        glVertex2f(-0.2f, -0.4f);
        glVertex2f(-0.2f, -0.45f);
        glVertex2f(-0.15f, -0.45f);
        glVertex2f(0.15f, -0.4f);
        glVertex2f(0.2f, -0.4f);
        glVertex2f(0.2f, -0.45f);
        glVertex2f(0.15f, -0.45f);
    glEnd();


    //eyes
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle4(-0.05f, 0.0f, 0.03f);
    drawCircle4(0.05f, 0.0f, 0.03f);

    //eyeballs
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle4(-0.05f, 0.0f, 0.01f);
    drawCircle4(0.05f, 0.0f, 0.01f);

    //nose
    glColor3f(1.0f, 0.88f, 0.85f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.03f, -0.08f);
        glVertex2f(0.0f, -0.03f);
        glVertex2f(0.03f, -0.08f);
    glEnd();
    glPopMatrix();
}

void sunflower4(float x, float y, float scale, float angle)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.01f, 0.0f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.01f, 0.0f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(-0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.35f);
        glVertex2f(0.06, 0.4f);
        glVertex2f(0.0f, 0.33f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(-0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.3f);
        glVertex2f(0.06, 0.35f);
        glVertex2f(0.0f, 0.28f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(-0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.25f);
        glVertex2f(0.06, 0.3f);
        glVertex2f(0.0f, 0.23f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(-0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.2f);
        glVertex2f(0.06, 0.25f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(-0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.06, 0.2f);
        glVertex2f(0.0f, 0.13f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(-0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
        glVertex2f(0.0f, 0.1f);
        glVertex2f(0.06, 0.15f);
        glVertex2f(0.0f, 0.08f);
    glEnd();

    glColor3f(1.0f, 0.8f, 0.09f);
    drawCircle4(0.0f, 0.44f, 0.02f);
    drawCircle4(0.0f, 0.36f, 0.02f);
    drawCircle4(-0.04f, 0.4f, 0.02f);
    drawCircle4(0.04f, 0.4f, 0.02f);
    drawCircle4(-0.02f, 0.435f, 0.02f);
    drawCircle4(0.018f, 0.365f, 0.02f);
    drawCircle4(-0.038f, 0.385f, 0.02f);
    drawCircle4(0.038f, 0.385f, 0.02f);
    drawCircle4(0.02f, 0.44f, 0.02f);
    drawCircle4(-0.02f, 0.36f, 0.02f);

    glColor3f(0.37f, 0.28f, 0.18f);
    drawCircle4(0.0f, 0.4f, 0.04f);
    glPopMatrix();

}

void drawBird4Body4(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawBird4()
{
    glPushMatrix();
    glTranslatef(birdX4, birdY4, 0.0f); // Move bird to current position
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBird4Body4(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBird4Body4(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}

void drawBird42()
{
    glPushMatrix();
    glTranslatef(bird2X4, bird2Y4, 0.0f); // Move bird to current position
    glScalef(0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBird4Body4(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBird4Body4(0.07, 0.08, 0.05, 50);

    glPopMatrix(); // Restore transformation state
}

void drawBird43(float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 1.0f);
    glScalef(-0.2f, 0.2f, 1.0f);       // Scale down the bird

    // Body
    glColor3f(1.0, 0.8, 0.0); // Yellow
    drawBird4Body4(0.0, 0.0, 0.2, 100);

    // Wing (triangle)
    glColor3f(0.9, 0.6, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.1f, 0.1f);
        glVertex2f(-0.1f, -0.1f);
    glEnd();

    // Tail (polygon)
    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.17f, 0.05f);
        glVertex2f(-0.27f, 0.2f);
        glVertex2f(-0.27f, -0.2f);
        glVertex2f(-0.17f, -0.05f);
    glEnd();

    // Beak (triangle)
    glColor3f(1.0, 0.3, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.2f, 0.05f);
        glVertex2f(0.35f, 0.0f);
        glVertex2f(0.2f, -0.05f);
    glEnd();

    // Eye (small circle)
    glColor3f(0.0, 0.0, 0.0);
    drawBird4Body4(0.07, 0.08, 0.05, 50);

    // Legs (lines)
    glColor3f(0.5, 0.3, 0.1);
    glBegin(GL_LINES);
        glVertex2f(-0.1f, -0.18f);
        glVertex2f(-0.1f, -0.3f);
        glVertex2f(0.1f, -0.18f);
        glVertex2f(0.1f, -0.3f);
    glEnd();

    glPopMatrix(); // Restore transformation state
}
void drawSnowflake4(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle4(0.0f, 0.0f, 0.005f);
    glPopMatrix();
}
void drawAllSnowflakes4() {
    for (float x = -1.0f; x <= 1.0f; x += 0.1f) {
        for (float y = 0.0f; y <= 1.0f; y += 0.1f) {
            float fallY = fmod(y - snowY + 1.0f, 1.0f);
            drawSnowflake4(x, fallY);
        }
    }
}
void drawSmoke4(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y + smokeYOffset, 0.0f);
    glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
    drawCircle4(0.0f, 0.0f, 0.03f);
    drawCircle4(0.02f, 0.03f, 0.025f);
    drawCircle4(-0.02f, 0.06f, 0.02f);
    glPopMatrix();
}
void vbonfireWithVillagers4(float x, float y, float scale) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Villagers around fire
    man4(-0.11f, 0.12f, 0.25f);
    woman4(0.1f, 0.12f, 0.25f);
    boy4(0.0f, 0.15f, 0.2f);

    // Fire
    glColor3f(1.0f, 0.4f, 0.0f);
    drawCircle4(0.0f, 0.0f, 0.04f);
    drawSmoke4(0.0f, 0.1f);

    glPopMatrix();
}


void displayWinter() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();


    // Sun
    glColor3f(1.0f, 1.0f, 0.5f);
    drawCircle4(0.0f, 0.8f, 0.1f);

    // cloud4
    glColor3f(1.0f, 1.0f, 1.0f);
    cloud4(cloud4Position14 - 0.1f, 1.1f, 0.1f);
    cloud4(cloud4Position14, 1.1f, 0.15f);
    cloud4(cloud4Position14 + 0.1f, 1.1f, 0.1f);

    glColor3f(1.0f, 1.0f, 1.0f);
    cloud4(cloud4Position24 - 0.1f, 0.75f, 0.1f);
    cloud4(cloud4Position24, 0.75f, 0.15f);
    cloud4(cloud4Position24+ 0.1f, 0.75f, 0.1f);


    ground4();
    road14(0.0f, -0.25f, 1.0f);
    road24(0.0f, 0.0f, 1.0f);
    road24(0.7f, -0.2f, 0.5f);
    grass4(-0.9f, -0.649f, 0.45f, 0.0f);
    grass4(-0.9f, -0.7f, 0.45f, -30.0f);
    grass4(-0.95f, -0.73f, 0.45f, -70.0f);
    grass4(-0.7f, -0.649f, 0.45f, 0.0f);
    grass4(-0.73f, -0.7f, 0.45f, -60.0f);
    grass4(-0.6f, -0.649f, 0.45f, 0.0f);
    grass4(-0.6f, -0.7f, 0.45f, -30.0f);
    grass4(-0.65f, -0.7f, 0.45f, -30.0f);
    grass4(-0.6f, -0.73f, 0.45f, -70.0f);
    grass4(-0.4f, -0.649f, 0.45f, 0.0f);
    grass4(-0.4f, -0.7f, 0.45f, -30.0f);
    grass4(-0.45f, -0.73f, 0.45f, -70.0f);
    grass4(-0.3f, -0.649f, 0.45f, 0.0f);
    grass4(-0.33f, -0.7f, 0.45f, -60.0f);
    grass4(-0.2f, -0.649f, 0.45f, 0.0f);
    grass4(-0.2f, -0.7f, 0.45f, -30.0f);
    grass4(-0.15f, -0.7f, 0.45f, -30.0f);
    grass4(-0.18f, -0.73f, 0.45f, -70.0f);
    grass4(0.0f, -0.649f, 0.45f, 0.0f);
    grass4(0.0f, -0.7f, 0.45f, -30.0f);
    grass4(0.05f, -0.73f, 0.45f, -70.0f);
    grass4(0.1f, -0.649f, 0.45f, 0.0f);
    grass4(1.13f, -0.7f, 0.45f, -60.0f);
    grass4(0.2f, -0.649f, 0.45f, 0.0f);
    grass4(0.2f, -0.7f, 0.45f, -30.0f);
    grass4(0.25f, -0.7f, 0.45f, -30.0f);
    grass4(0.2f, -0.73f, 0.45f, -70.0f);
    grass4(0.4f, -0.649f, 0.45f, 0.0f);
    grass4(0.4f, -0.7f, 0.45f, -30.0f);
    grass4(0.45f, -0.73f, 0.45f, -70.0f);
    grass4(0.5f, -0.649f, 0.45f, 0.0f);
    grass4(0.6f, -0.649f, 0.45f, 0.0f);
    grass4(0.6f, -0.7f, 0.45f, -30.0f);
    grass4(0.65f, -0.7f, 0.45f, -30.0f);
    grass4(0.63f, -0.73f, 0.45f, -70.0f);
    grass4(0.75f, -0.7f, 0.45f, -30.0f);
    grass4(0.73f, -0.73f, 0.45f, -70.0f);
    grass4(0.8f, -0.649f, 0.45f, 0.0f);
    grass4(0.8f, -0.7f, 0.45f, -30.0f);
    grass4(0.85f, -0.73f, 0.45f, -70.0f);
    grass4(0.9f, -0.649f, 0.45f, 0.0f);
    grass4(1.0f, -0.649f, 0.45f, 0.0f);
    grass4(1.0f, -0.7f, 0.45f, -30.0f);
    grass4(1.05f, -0.7f, 0.45f, -30.0f);
    hills4();
    windMill4();

    bush4(-0.9f, 0.25f, 1.2f);
    bush4(-0.7f, 0.25f, 1.2f);
    bush4(-0.5f, 0.25f, 1.2f);
    bush4(-0.3f, 0.25f, 1.2f);
    bush4(-0.1f, 0.25f, 1.2f);
    bush4(0.1f, 0.25f, 1.2f);
    bush4(0.3f, 0.25f, 1.2f);
    bush4(0.5f, 0.25f, 1.2f);
    bush4(0.7f, 0.25f, 1.2f);
    bush4(0.9f, 0.25f, 1.2f);

    bar4(0.26f, 0.01f, 0.18f, 0.0f);
    bar4(0.34f, 0.01f, 0.18f, 0.0f);
    bar4(0.3f, 0.04f, 0.25f, -90.0f);

    ybush4(0.49f, 0.1f, 0.5f);
    crop4(0.58f, 0.15f, 0.3f, 180.0f);
    crop4(0.58f, 0.05f, 0.3f, 0.0f);
    crop4(0.56f, 0.15f, 0.3f, 180.0f);
    crop4(0.56f, 0.05f, 0.3f, 0.0f);
    crop4(0.54f, 0.15f, 0.3f, 180.0f);
    crop4(0.54f, 0.05f, 0.3f, 0.0f);
    crop4(0.52f, 0.15f, 0.3f, 180.0f);
    crop4(0.52f, 0.05f, 0.3f, 0.0f);
    crop4(0.59f, 0.15f, 0.3f, 180.0f);
    crop4(0.59f, 0.05f, 0.3f, 0.0f);
    crop4(0.57f, 0.15f, 0.3f, 180.0f);
    crop4(0.57f, 0.05f, 0.3f, 0.0f);
    crop4(0.55f, 0.15f, 0.3f, 180.0f);
    crop4(0.55f, 0.05f, 0.3f, 0.0f);
    crop4(0.53f, 0.15f, 0.3f, 180.0f);
    crop4(0.53f, 0.05f, 0.3f, 0.0f);
    crop4(0.5f, 0.15f, 0.3f, 180.0f);
    crop4(0.5f, 0.05f, 0.3f, 0.0f);
    crop4(0.48f, 0.15f, 0.3f, 180.0f);
    crop4(0.48f, 0.05f, 0.3f, 0.0f);
    crop4(0.46f, 0.15f, 0.3f, 180.0f);
    crop4(0.46f, 0.05f, 0.3f, 0.0f);
    crop4(0.44f, 0.15f, 0.3f, 180.0f);
    crop4(0.44f, 0.05f, 0.3f, 0.0f);
    crop4(0.42f, 0.15f, 0.3f, 180.0f);
    crop4(0.42f, 0.05f, 0.3f, 0.0f);
    crop4(0.4f, 0.15f, 0.3f, 180.0f);
    crop4(0.4f, 0.05f, 0.3f, 0.0f);
    crop4(0.51f, 0.15f, 0.3f, 180.0f);
    crop4(0.51f, 0.05f, 0.3f, 0.0f);
    crop4(0.49f, 0.15f, 0.3f, 180.0f);
    crop4(0.49f, 0.05f, 0.3f, 0.0f);
    crop4(0.47f, 0.15f, 0.3f, 180.0f);
    crop4(0.47f, 0.05f, 0.3f, 0.0f);
    crop4(0.45f, 0.15f, 0.3f, 180.0f);
    crop4(0.45f, 0.05f, 0.3f, 0.0f);
    crop4(0.43f, 0.15f, 0.3f, 180.0f);
    crop4(0.43f, 0.05f, 0.3f, 0.0f);
    crop4(0.41f, 0.15f, 0.3f, 180.0f);
    crop4(0.41f, 0.05f, 0.3f, 0.0f);



    dateTree4(-0.9f, 0.15f, 1.2f);
    drawTree4(-0.6f, 0.15f, 1.0f);
    drawTree4(0.85f, 0.0f, 1.2f);

    crop4(0.0f, -0.03f, 1.0f);

    //Row 1
    mustard4(-0.97f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.91f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.85f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.79f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.73f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.67f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.61f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.55f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.49f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.43f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.37f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.31f, 0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.25f, 0.1f, 0.3f, crop4SwayAngle4);
    //Row 2
    mustard4(-0.99f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.93f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.87f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.81f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.75f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.69f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.63f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.57f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.51f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.45f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.39f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.33f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.27f, 0.0f, 0.3f, crop4SwayAngle4);
    mustard4(-0.22f, 0.0f, 0.3f, crop4SwayAngle4);
    //Row 3
    mustard4(-0.97f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.91f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.85f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.79f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.73f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.67f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.61f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.55f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.49f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.43f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.37f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.31f, -0.1f, 0.3f, crop4SwayAngle4);
    mustard4(-0.25f, -0.1f, 0.3f, crop4SwayAngle4);
    //Row 4
    mustard4(-0.99f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.93f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.87f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.81f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.75f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.69f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.63f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.57f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.51f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.45f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.39f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.33f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.27f, -0.2f, 0.3f, crop4SwayAngle4);
    mustard4(-0.22f, -0.2f, 0.3f, crop4SwayAngle4);

    waterWell4(0.3f, -0.2f, 0.6f);

    rope4(0.5f, -0.07f, 0.5f, 0.0f);
    rope4(0.41f, -0.17f, 0.5f, -90.0f);
    rope4(0.5f, -0.3f, 0.5f, 0.0f);
    rope4(0.61f, -0.17f, 0.5f, -90.0f);
    rope4(0.793f, -0.17f, 0.5f, -90.0f);
    rope4(0.9f, -0.3f, 0.5f, 0.0f);
    house4(0.7f,0.0f,0.5f);
    drawTree4(0.95f, -0.3f, 1.2f);
    rail4(0.49f, -0.075f, 0.13f);
    rail4(0.45f, -0.075f, 0.13f);
    rail4(0.41f, -0.075f, 0.13f);
    rail4(0.41f, -0.15f, 0.13f);
    rail4(0.41f, -0.225f, 0.13f);
    rail4(0.41f, -0.3f, 0.13f);
    rail4(0.45f, -0.3f, 0.13f);
    rail4(0.49f, -0.3f, 0.13f);
    rail4(0.53f, -0.3f, 0.13f);
    rail4(0.57f, -0.3f, 0.13f);
    rail4(0.61f, -0.3f, 0.13f);
    rail4(0.61f, -0.225f, 0.13f);
    rail4(0.61f, -0.15f, 0.13f);
    rail4(0.79f, -0.15f, 0.13f);
    rail4(0.79f, -0.225f, 0.13f);
    rail4(0.79f, -0.3f, 0.13f);
    rail4(0.83f, -0.3f, 0.13f);
    rail4(0.87f, -0.3f, 0.13f);
    rail4(0.91f, -0.3f, 0.13f);
    rail4(0.95f, -0.3f, 0.13f);
    rail4(0.99f, -0.3f, 0.13f);


    sunflower4(0.45f, -0.17f, 0.4f, sunflower4Angle4);
    sunflower4(0.52f, -0.17f, 0.4f, sunflower4Angle4);
    sunflower4(0.58f, -0.17f, 0.4f, sunflower4Angle4);
    sunflower4(0.44f, -0.25f, 0.4f, sunflower4Angle4);
    sunflower4(0.51f, -0.25f, 0.4f, sunflower4Angle4);
    sunflower4(0.57f, -0.25f, 0.4f, sunflower4Angle4);


    bullockcart4(cartX4, -0.3f, 0.5f);

    river4();
    boat4(-0.87f, -0.78f, 0.7f);

    drawBird4();
    drawBird42();
    drawBird43(0.95f, 0.115f);

    drawAllSnowflakes4();
    vbonfireWithVillagers4(0.245f, 0.08f, 0.88f);

    crop4(-1.0f, 0.0f, 1.0f);



    glutSwapBuffers();
}
void setSceneBackground() {
    switch (currentScene) {
        case DAY:     glClearColor(0.5f, 0.8f, 1.0f, 1.0f); break;
        case NIGHT:   glClearColor(0.05f, 0.05f, 0.2f, 1.0f); break;
        case WINTER:  glClearColor(0.85f, 0.85f, 0.9f, 1.0f); break;
        case MONSOON: glClearColor(0.4f, 0.4f, 0.5f, 1.0f); break;
    }
}
void mainDisplay() {
    setSceneBackground();
    switch (currentScene) {
        case DAY: displayDay(); break;
        case NIGHT: displayNight(); break;
        case WINTER: displayWinter(); break;
        case MONSOON: displayMonsoon(); break;
    }
}
void handleKeypress(unsigned char key, int x, int y) {
    switch (toupper(key)) {
        case 'D': currentScene = DAY; break;
        case 'N': currentScene = NIGHT; break;
        case 'W': currentScene = WINTER; break;
        case 'M': currentScene = MONSOON; break;
        case 'R': currentScene = DAY; break;
    }
    glutPostRedisplay();
}
void update(int value) {
    cloudPosition1 += 0.005f;
    if (cloudPosition1 > 1.2f) cloudPosition1 = -1.2f;

    cloudPosition2 += 0.003f;
    if (cloudPosition2 > 1.2f) cloudPosition2 = -1.2f;

    birdX += 0.005f;
    if (birdX > 1.2f || birdY > 1.2f) {
        birdX = -1.0f;
        birdY = 0.5f;
    }

    bird2X += 0.003f;
    if (bird2X > 1.2f || bird2Y > 1.2f) {
        bird2X = -1.0f;
        bird2Y = 0.4f;
    }

    bird3X += 0.007f;
    if (bird3X > 1.2f || bird3Y > 1.2f) {
        bird3X = -1.0f;
        bird3Y = 0.6f;
    }

    cartX += 0.003f;
    if (cartX > 1.0f) cartX = -0.8f;  // Loop around

    if (swayRight)
        sunflowerAngle += 0.2f;
    else
        sunflowerAngle -= 0.2f;

    if (sunflowerAngle > 5.0f) swayRight = false;
    if (sunflowerAngle < -5.0f) swayRight = true;

    bladeAngle += 2.0f;
    if (bladeAngle > 360.0f) bladeAngle -= 360.0f;

    if (swayCropRight)
        cropSwayAngle += 0.1f;
    else
        cropSwayAngle -= 0.1f;

    if (cropSwayAngle > 2.0f) swayCropRight = false;
    if (cropSwayAngle < -2.0f) swayCropRight = true;

    boatX += 0.002f;
    if (boatX > 1.0f) boatX = -0.9f;

    manY -= 0.0005f;
    if (manY < 0.0f) manY = 0.3f;
    womanY -= 0.0004f;
    if (womanY < -0.1f) womanY = 0.35f;
    boyY -= 0.0006f;
    if (boyY < -0.1f) boyY = 0.3f;

    //--------------Monsoon--------------//
    cloud3Position13 += 0.005f;
    if (cloud3Position13 > 1.2f) cloud3Position13 = -1.2f;

    cloud3Position23 += 0.003f;
    if (cloud3Position23 > 1.2f) cloud3Position23 = -1.2f;

    cartX3 += 0.003f;
    if (cartX3 > 1.0f) cartX3 = -0.8f;  // Loop around

    if (swayRight3)
        sunflowerAngle3 += 0.2f;
    else
        sunflowerAngle3 -= 0.2f;

    if (sunflowerAngle3 > 5.0f) swayRight3 = false;
    if (sunflowerAngle3 < -5.0f) swayRight3 = true;

    bladeAngle3 += 2.0f;
    if (bladeAngle3 > 360.0f) bladeAngle3 -= 360.0f;

    if (swaycrop3Right3)
        crop3SwayAngle3 += 0.1f;
    else
        crop3SwayAngle3 -= 0.1f;

    if (crop3SwayAngle3 > 2.0f) swaycrop3Right3 = false;
    if (crop3SwayAngle3 < -2.0f) swaycrop3Right3 = true;

    boat3X3 += 0.002f;
    if (boat3X3 > 1.0f) boat3X3 = -0.9f;

    man3Y3 -= 0.0005f;
    if (man3Y3 < 0.0f) man3Y3 = 0.3f;
    woman3Y3 -= 0.0004f;
    if (woman3Y3 < -0.1f) woman3Y3 = 0.35f;

    // === Move rain ===
    for (int i = 0; i < 200; i++) {
        rainY[i] -= 0.02f;
        rainX[i] += 0.002f;
        if (rainY[i] < -1.0f) {
            rainY[i] = 1.0f;
            rainX[i] = ((rand() % 200) - 100) / 100.0f;
        }
    }

    // === Ripple radius toggle ===
    if (expanding) {
        rippleRadius += 0.002f;
        if (rippleRadius >= 0.05f) expanding = false;
    } else {
        rippleRadius -= 0.002f;
        if (rippleRadius <= 0.01f) expanding = true;
    }

    // === Lightning timer ===
    lightningTimer++;
    if (lightningTimer > 200) {
        lightningTimer = 0;
        isLightning = rand() % 5 == 0; // random flash
    } else {
        isLightning = false;
    }

    // === boy3 jump animation ===
    jumpPhase += 0.1f;
    if (jumpPhase >= 2 * PI3) jumpPhase = 0.0f;
    boy3Y4 = 0.3f + 0.05f * fabs(sinf(jumpPhase)); // vertical bounce

    // Create ripple when rain hits river3 (approx. y = -0.65 to -1.0)
for (int i = 0; i < 200; i++) {
    if (rainY[i] < -0.65f && rainY[i] > -1.0f) {
        // Find inactive ripple slot
        for (int j = 0; j < 20; j++) {
            if (!ripples[j].active) {
                ripples[j].x = rainX[i];
                ripples[j].y = rainY[i];
                ripples[j].radius = 0.01f;
                ripples[j].active = true;
                break;
            }
        }
        // reset that raindrop upward
        rainY[i] = 1.0f;
        rainX[i] = ((rand() % 200) - 100) / 100.0f;
    }
}

// Expand ripples
for (int i = 0; i < 20; i++) {
    if (ripples[i].active) {
        ripples[i].radius += 0.001f;
        if (ripples[i].radius > 0.04f) {
            ripples[i].active = false;
        }
    }
}

//-------------------Winter---------------//
cloud4Position14 += 0.005f;
    if (cloud4Position14 > 1.2f) cloud4Position14 = -1.2f;

    cloud4Position24 += 0.003f;
    if (cloud4Position24 > 1.2f) cloud4Position24 = -1.2f;

    birdX4 += 0.005f;
    if (birdX4 > 1.2f || birdY4 > 1.2f) {
        birdX4 = -1.0f;
        birdY4 = 0.5f;
    }

    bird2X4 += 0.003f;
    if (bird2X4 > 1.2f || bird2Y4 > 1.2f) {
        bird2X4 = -1.0f;
        bird2Y4 = 0.4f;
    }


    cartX4 += 0.003f;
    if (cartX4 > 1.0f) cartX4 = -0.8f;  // Loop around

    if (swayRight4)
        sunflower4Angle4 += 0.2f;
    else
        sunflower4Angle4 -= 0.2f;

    if (sunflower4Angle4 > 5.0f) swayRight4 = false;
    if (sunflower4Angle4 < -5.0f) swayRight4 = true;

    bladeAngle4 += 2.0f;
    if (bladeAngle4 > 360.0f) bladeAngle4 -= 360.0f;

    if (swaycrop4Right4)
        crop4SwayAngle4 += 0.1f;
    else
        crop4SwayAngle4 -= 0.1f;

    if (crop4SwayAngle4 > 2.0f) swaycrop4Right4 = false;
    if (crop4SwayAngle4 < -2.0f) swaycrop4Right4 = true;


    snowY += 0.003f;
    if (snowY > 1.0f) snowY = 0.0f;

    smokeYOffset += 0.002f;
    if (smokeYOffset > 0.2f) smokeYOffset = 0.0f;

    cloud2Position12 += 0.005f;
    if (cloud2Position12 > 1.2f) cloud2Position12 = -1.2f;

    cloud2Position22 += 0.003f;
    if (cloud2Position22 > 1.2f) cloud2Position22 = -1.2f;

    birdX2 += 0.005f;
    if (birdX2 > 1.2f || birdY2 > 1.2f) {
        birdX2 = -1.0f;
        birdY2 = 0.5f;
    }

    bird2X2 += 0.003f;
    if (bird2X2 > 1.2f || bird2Y2 > 1.2f) {
        bird2X2 = -1.0f;
        bird2Y2 = 0.4f;
    }

    bird3X2 += 0.007f;
    if (bird3X2 > 1.2f || bird3Y2 > 1.2f) {
        bird3X2 = -1.0f;
        bird3Y2 = 0.6f;
    }

    cartX2 += 0.003f;
    if (cartX2 > 1.0f) cartX2 = -0.8f;  // Loop around

    if (swayRight2)
        sunflower2Angle2 += 0.2f;
    else
        sunflower2Angle2 -= 0.2f;

    if (sunflower2Angle2 > 5.0f) swayRight2 = false;
    if (sunflower2Angle2 < -5.0f) swayRight2 = true;

    bladeAngle2 += 2.0f;
    if (bladeAngle2 > 360.0f) bladeAngle2 -= 360.0f;

    if (swaycrop2Right2)
        crop2SwayAngle2 += 0.1f;
    else
        crop2SwayAngle2 -= 0.1f;

    if (crop2SwayAngle2 > 2.0f) swaycrop2Right2 = false;
    if (crop2SwayAngle2 < -2.0f) swaycrop2Right2 = true;

    boatX2 += 0.001f;
    if (boatX2 > 1.0f) boatX2 = -0.9f;

    manY2 -= 0.0005f;
    if (manY2 < 0.0f) manY2 = 0.3f;
    womanY2 -= 0.0004f;
    if (womanY2 < -0.1f) womanY2 = 0.35f;
    boyY2 -= 0.0006f;
    if (boyY2 < -0.1f) boyY2 = 0.3f;
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

void reshape(GLsizei width, GLsizei height) {
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(300, 150);
    glutCreateWindow("Rural Village Life");
    glutDisplayFunc(mainDisplay);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    initGL();
    initRain3();
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}
