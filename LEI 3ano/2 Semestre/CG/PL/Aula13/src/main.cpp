#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<stdio.h>
#include<stdlib.h>
// distance to target
float dist = 700;
// distance between the eyes
float disp = 30;


float angle=0;
float cBlack[] = {0,0,0,0};
float cWhite[] = {1,1,1,1};
float cRed[] = {0.4,0,0};
float cGreen[] = {0,0.4,0.4};
float cRedish[] = {0.2,0,0};
float cGreenish[] = {0,0.2,0.2};

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,400,10000);
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float lpos[] = {1,1,0,0};
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	// teapot size
	float ts = 150;

	// Red eye (left)
	glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_TRUE);
	glPushMatrix();
	gluLookAt(-disp/2, 0, dist, -disp/2, 0, 0, 0, 1, 0);
	glRotatef(angle, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cWhite);
	glutSolidTeapot(ts);
	glPopMatrix();

	// Clear depth buffer for the second pass
	glClear(GL_DEPTH_BUFFER_BIT);

	// Blue/Green eye (right)
	glColorMask(GL_FALSE, GL_TRUE, GL_TRUE, GL_TRUE);
	glPushMatrix();
	gluLookAt(disp/2, 0, dist, disp/2, 0, 0, 0, 1, 0);
	glRotatef(angle, 0, 1, 0);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cWhite);
	glutSolidTeapot(ts);
	glPopMatrix();

	// Restore color mask
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glutSwapBuffers();

	angle+=0.25;
}

void processNormalKeys(unsigned char key, int x, int y) {

	char s[20];
	if (key == 27) 
		exit(0);
	switch(key) {
		case 'a' : dist *=.9;break;
		case 's' : dist *= 1.1; break;
	}
	sprintf(s,"%f", dist);
	glutSetWindowTitle(s);

}


int main(int argc, char **argv) {

	// GLUT and window init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("CG @ DI");

	// GLUT callbacks
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	
	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);


	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	glClearColor(0.0f,0.0f,0.0f,0.0f);


	glutMainLoop();

	return 0;
}

