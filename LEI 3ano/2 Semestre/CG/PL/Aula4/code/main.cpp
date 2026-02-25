#define _USE_MATH_DEFINES   // Fix #2: must be before ALL includes
#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <vector>

float alfa = 0.0f, beta = 0.0f, radius = 5.0f;
float camX, camY, camZ;

GLuint vertices;
int verticeCount;

float lightPos[4] = { 4.0f, 6.0f, 4.0f, 1.0f }; // point light (w=1)

// plane: ax+by+cz+d=0  |  light: (x,y,z,w)
void shadowMatrix(float m[16], float plane[4], float light[4]) {
    float dot = plane[0]*light[0] + plane[1]*light[1]
              + plane[2]*light[2] + plane[3]*light[3];
    // Column-major (OpenGL order)
    m[0]  = dot-plane[0]*light[0]; m[4]  =    -plane[1]*light[0];
    m[8]  =    -plane[2]*light[0]; m[12] =    -plane[3]*light[0];
    m[1]  =    -plane[0]*light[1]; m[5]  = dot-plane[1]*light[1];
    m[9]  =    -plane[2]*light[1]; m[13] =    -plane[3]*light[1];
    m[2]  =    -plane[0]*light[2]; m[6]  =    -plane[1]*light[2];
    m[10] = dot-plane[2]*light[2]; m[14] =    -plane[3]*light[2];
    m[3]  =    -plane[0]*light[3]; m[7]  =    -plane[1]*light[3];
    m[11] =    -plane[2]*light[3]; m[15] = dot-plane[3]*light[3];
}


void prepareData() {
    std::vector<float> p;
    int sides = 100000;
    float r = 1.0f, height = 2.0f;
    float step = 2 * M_PI / sides;

    for (int i = 0; i < sides; i++) {
        float a0 = i * step;
        float a1 = (i + 1) * step;

        // ── Top (triangles) ─────────────────────
		p.push_back(0); p.push_back( height*0.5f); p.push_back(0);
		p.push_back(cos(a0)*r); p.push_back( height*0.5f); p.push_back(-sin(a0)*r);
		p.push_back(cos(a1)*r); p.push_back( height*0.5f); p.push_back(-sin(a1)*r);
    }

	for (int i = 0; i < sides; i++) {
        float a0 = i * step;
        float a1 = (i + 1) * step;

        // ── Bottom (triangles) ─────────────────────
		p.push_back(0); p.push_back(-height*0.5f); p.push_back(0);
		p.push_back(cos(a1)*r); p.push_back(-height*0.5f); p.push_back(-sin(a1)*r);
		p.push_back(cos(a0)*r); p.push_back(-height*0.5f); p.push_back(-sin(a0)*r); // WRONG
    }

	for (int i = 0; i < sides; i++) {
        float a0 = i * step;
        float a1 = (i + 1) * step;
        // ── Body (two triangles per quad) ─────────────────────
        p.push_back(cos(a0)*r); p.push_back( height*0.5f); p.push_back(-sin(a0)*r);
        p.push_back(cos(a0)*r); p.push_back(-height*0.5f); p.push_back(-sin(a0)*r);
        p.push_back(cos(a1)*r); p.push_back( height*0.5f); p.push_back(-sin(a1)*r);

        p.push_back(cos(a0)*r); p.push_back(-height*0.5f); p.push_back(-sin(a0)*r);
        p.push_back(cos(a1)*r); p.push_back(-height*0.5f); p.push_back(-sin(a1)*r);
        p.push_back(cos(a1)*r); p.push_back( height*0.5f); p.push_back(-sin(a1)*r);
    }

    verticeCount = p.size() / 3;

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * p.size(), p.data(), GL_STATIC_DRAW);
}

void spherical2Cartesian() {
    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

void changeSize(int w, int h) {
    if(h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

void cylinder0(float radius, float height, int sides) {
    int i;
    float step = 360.0 / sides;

    glColor3f(1,0,0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, height*0.5, 0);
        for (i = 0; i <= sides; i++)
            glVertex3f(cos(i*step*M_PI/180.0)*radius, height*0.5, -sin(i*step*M_PI/180.0)*radius);
    glEnd();

    glColor3f(0,1,0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(0, -height*0.5, 0);
        for (i = 0; i <= sides; i++)
            glVertex3f(cos(i*step*M_PI/180.0)*radius, -height*0.5, sin(i*step*M_PI/180.0)*radius);
    glEnd();

    glColor3f(0,0,1);
    glBegin(GL_TRIANGLE_STRIP);
        for (i = 0; i <= sides; i++) {
            glVertex3f(cos(i*step*M_PI/180.0)*radius,  height*0.5, -sin(i*step*M_PI/180.0)*radius);
            glVertex3f(cos(i*step*M_PI/180.0)*radius, -height*0.5, -sin(i*step*M_PI/180.0)*radius);
        }
    glEnd();
}

void cylinder(float radius, float height, int sides) {
    int i;
    float step = 360.0 / sides;

    glBegin(GL_TRIANGLES);

    // top
    for (i = 0; i < sides; i++) {
        glVertex3f(0, height*0.5, 0);
        glVertex3f(cos(i*step*M_PI/180.0)*radius,     height*0.5, -sin(i*step*M_PI/180.0)*radius);
        glVertex3f(cos((i+1)*step*M_PI/180.0)*radius, height*0.5, -sin((i+1)*step*M_PI/180.0)*radius);
    }

    // bottom
    for (i = 0; i < sides; i++) {
        glVertex3f(0, -height*0.5, 0);
        glVertex3f(cos((i+1)*step*M_PI/180.0)*radius, -height*0.5, -sin((i+1)*step*M_PI/180.0)*radius);
        glVertex3f(cos(i*step*M_PI/180.0)*radius,     -height*0.5, -sin(i*step*M_PI/180.0)*radius);
    }

    // body 
    for (i = 0; i < sides; i++) {
        glVertex3f(cos(i*step*M_PI/180.0)*radius,      height*0.5, -sin(i*step*M_PI/180.0)*radius);
        glVertex3f(cos(i*step*M_PI/180.0)*radius,     -height*0.5, -sin(i*step*M_PI/180.0)*radius);
        glVertex3f(cos((i+1)*step*M_PI/180.0)*radius,  height*0.5, -sin((i+1)*step*M_PI/180.0)*radius);

        glVertex3f(cos(i*step*M_PI/180.0)*radius,     -height*0.5, -sin(i*step*M_PI/180.0)*radius);
        glVertex3f(cos((i+1)*step*M_PI/180.0)*radius, -height*0.5, -sin((i+1)*step*M_PI/180.0)*radius);
        glVertex3f(cos((i+1)*step*M_PI/180.0)*radius,  height*0.5, -sin((i+1)*step*M_PI/180.0)*radius);
    }
    glEnd();
}

// FPS counter variables
int frameCount = 0;
float fps = 0.0f;
int previousTime = 0;

void renderBitmapString(float x, float y, void *font, const char *string) {
    glRasterPos2f(x, y);
    for (const char *c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, 0.0, 0.0, 0.0, 0.0f, 1.0f, 0.0f);

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, verticeCount);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Draw FPS
    char fpsString[32];
    snprintf(fpsString, sizeof(fpsString), "FPS: %.2f", fps);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1, 1, 1);
    renderBitmapString(10, 780, GLUT_BITMAP_HELVETICA_18, fpsString);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
}
void timerFunc(int value) {
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeInterval = currentTime - previousTime;
    if (timeInterval > 0) {
        fps = frameCount * 1000.0f / timeInterval;
    }
    previousTime = currentTime;
    frameCount = 0;
    glutTimerFunc(1000, timerFunc, 0);
}


void processKeys(unsigned char c, int xx, int yy) {
    switch (c) {
    case 27:
        exit(0);
        break;
    }
}

void processSpecialKeys(int key, int xx, int yy) {
    switch (key) {
    case GLUT_KEY_RIGHT:    alfa -= 0.1; break;
    case GLUT_KEY_LEFT:     alfa += 0.1; break;
    case GLUT_KEY_UP:
        beta += 0.1f;
        if (beta > 1.5f) beta = 1.5f;
        break;
    case GLUT_KEY_DOWN:
        beta -= 0.1f;
        if (beta < -1.5f) beta = -1.5f;
        break;
    case GLUT_KEY_PAGE_DOWN:
        radius -= 0.1f;
        if (radius < 0.1f) radius = 0.1f;
        break;
    case GLUT_KEY_PAGE_UP: radius += 0.1f; break;
    }
    spherical2Cartesian();
    glutPostRedisplay();
}

void printInfo() {
    printf("Vendor: %s\n",   glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n",  glGetString(GL_VERSION));
    printf("\nUse Arrows to move the camera up/down and left/right\n");
    printf("Page Up and Page Down control the distance from the camera to the origin");
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    // FPS counter init
    previousTime = glutGet(GLUT_ELAPSED_TIME);
    glutTimerFunc(1000, timerFunc, 0);

    // Idle function to count frames
    glutIdleFunc([](){
        frameCount++;
        glutPostRedisplay();
    });

#ifndef __APPLE__
    glewInit();
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_LINE);

    spherical2Cartesian();
    printInfo();
    prepareData();

    glutMainLoop();
    return 1;
}
