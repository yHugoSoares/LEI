#include <stdio.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

// scene parameters
const int NUM_TREES = 1000;
const int NUM_TEAPOTS1 = 8;
const int NUM_TEAPOTS2 = 16;
std::vector<std::pair<float,float>> treePos; // x,z positions

// animation
float teapotAngle = 0.0f;



void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();
	
	// put code to draw scene in here
	// draw central torus (innerRadius, outerRadius)
	glPushMatrix();
	glColor3f(0.7f, 0.0f, 0.8f);
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(0, 1, 0, 0);
	glutSolidTorus(1.0f, 3.0f, 30, 30);
	glPopMatrix();

	// draw trees
	glColor3f(0.0f, 0.4f, 0.0f);
	for (auto &p : treePos) {
		float x = p.first, z = p.second;
		glPushMatrix();
		glTranslatef(x, 0.0f, z);
		// trunk: small cone (brown)
		glColor3f(0.45f, 0.2f, 0.05f);
		glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.0f);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(0.4f, 2.0f, 8, 8);
		glPopMatrix();
		// foliage: two cones
		glColor3f(0.0f, 0.5f, 0.0f);
		glPushMatrix();
		glTranslatef(0.0f, 2.0f, 0.0f);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(1.5f, 3.0f, 12, 12);
		glTranslatef(0.0f, -0.8f, 0.0f);
		glutSolidCone(1.0f, 2.0f, 12, 12);
		glPopMatrix();
		glPopMatrix();
	}


	// Outer ring: tangent to movement (spout faces CCW travel direction)
	for (int i = 0; i < NUM_TEAPOTS1; ++i) {
		float ang    = teapotAngle + (2.0f * M_PI * i) / NUM_TEAPOTS1;
		float r      = 10.0f;
		float x      = r * cos(ang);
		float z      = r * sin(ang);
		float angDeg = ang * 180.0f / (float)M_PI;

		glPushMatrix();
		glTranslatef(x, 1.5f, z);                  // 1. place on orbit
		glRotatef(-angDeg, 0.0f, 1.0f, 0.0f);     // 2. spout along tangent direction
		glColor3f(0.0f, 0.0f, 1.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	// Inner ring: back faces center (spout radially outward)
	for (int i = 0; i < NUM_TEAPOTS2; ++i) {
		float ang    = (teapotAngle + 90) + (2.0f * M_PI * i) / NUM_TEAPOTS2;
		float r      = 30.0f;
		float x      = r * cos(ang);
		float z      = r * sin(ang);
		float angDeg = ang * 180.0f / (float)M_PI;

		glPushMatrix();
		glTranslatef(x, 1.5f, z);                      // 1. place on orbit
		glRotatef((-90.0f) - angDeg, 0.0f, 1.0f, 0.0f);  // 2. spout outward → back to center
		glColor3f(1.0f, 0.0f, 0.0f);
		glutSolidTeapot(1.5f);
		glPopMatrix();
	}

	

	
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here
	switch (c) {
		case 27: // ESC
			exit(0);
			break;
		default:
			break;
	}
	glutPostRedisplay();

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}

void idle() {
	teapotAngle += 0.01f;
	glutPostRedisplay();
}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("Use Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin\n");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// seed random and generate tree positions using rejection sampling
	srand(time(NULL));
	treePos.reserve(NUM_TREES);
	while ((int)treePos.size() < NUM_TREES) {
		float x = -100.0f + 200.0f * (rand() / (float)RAND_MAX);
		float z = -100.0f + 200.0f * (rand() / (float)RAND_MAX);
		// accept if outside central circle of radius 50
		if (sqrtf(x*x + z*z) > 50.0f) {
			treePos.emplace_back(x, z);
		}
	}

	spherical2Cartesian();

	printInfo();

	glutIdleFunc(idle);

	// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
