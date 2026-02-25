#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#define _USE_MATH_DEFINES
#include <math.h>


// First-person camera
float camX = 0.0f, camY = 0.0f, camZ = 10.0f; // camera position
float camYaw = M_PI;   // left/right (horizontal), 0 = +Z, pi/2 = +X
float camPitch = 0.0f; // up/down (vertical)
float moveSpeed = 0.2f;
float lookSpeed = 0.04f;




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


void drawCylinder(float radius, float height, int slices) {

	float h2 = height / 2.0f;
	float step = 2.0f * M_PI / slices;

	// --- Sides: build as triangles ---
	// --- Sides: triangle wireframes ---
	glColor3f(0.5f, 0.5f, 1.0f); // light blue
	for (int i = 0; i < slices; i++) {
		float angle1 = i * step;
		float angle2 = (i + 1) * step;
		float x1 = radius * cos(angle1);
		float z1 = radius * sin(angle1);
		float x2 = radius * cos(angle2);
		float z2 = radius * sin(angle2);

		// Triangle 1
		glBegin(GL_LINE_LOOP);
		glVertex3f(x1, h2, z1);
		glVertex3f(x1, -h2, z1);
		glVertex3f(x2, -h2, z2);
		glEnd();

		// Triangle 2
		glBegin(GL_LINE_LOOP);
		glVertex3f(x1, h2, z1);
		glVertex3f(x2, -h2, z2);
		glVertex3f(x2, h2, z2);
		glEnd();
	}

	// --- Top cap: triangle wireframes ---
	glColor3f(0.5f, 0.5f, 0.0f); // Yellow
	for (int i = 0; i < slices; i++) {
		float angle1 = i * step;
		float angle2 = (i + 1) * step;
		float x1 = radius * cos(angle1);
		float z1 = radius * sin(angle1);
		float x2 = radius * cos(angle2);
		float z2 = radius * sin(angle2);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, h2, 0);
		glVertex3f(x1, h2, z1);
		glVertex3f(x2, h2, z2);
		glEnd();
	}

	// --- Bottom cap: triangle wireframes ---
	glColor3f(0.5f, 0.0f, 0.5f); // purple
	for (int i = 0; i < slices; i++) {
		float angle1 = i * step;
		float angle2 = (i + 1) * step;
		float x1 = radius * cos(angle1);
		float z1 = radius * sin(angle1);
		float x2 = radius * cos(angle2);
		float z2 = radius * sin(angle2);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, -h2, 0);
		glVertex3f(x2, -h2, z2);
		glVertex3f(x1, -h2, z1);
		glEnd();
	}
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	// Calculate look direction from yaw/pitch
	float lx = cos(camPitch) * sin(camYaw);
	float ly = sin(camPitch);
	float lz = cos(camPitch) * cos(camYaw);
	gluLookAt(camX, camY, camZ, 
          camX + lx, camY + ly, camZ + lz,
          0.0f,1.0f,0.0f);

	drawCylinder(1,2,10);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

	// First-person controls: WASD to move, QE to look up/down, Z/X to turn left/right
	float lx = cos(camPitch) * sin(camYaw);
	float lz = cos(camPitch) * cos(camYaw);
	float ly = sin(camPitch);
	switch (c) {
		case 'w': // move forward
			camX += lx * moveSpeed;
			camY += ly * moveSpeed;
			camZ += lz * moveSpeed;
			break;
		case 's': // move backward
			camX -= lx * moveSpeed;
			camY -= ly * moveSpeed;
			camZ -= lz * moveSpeed;
			break;
		case 'a': // look left
			camYaw += lookSpeed;
			break;
		case 'd': // look right
			camYaw -= lookSpeed;
			break;
		case 'q': // look up
			camPitch += lookSpeed;
			if (camPitch > M_PI_2 - 0.01) camPitch = M_PI_2 - 0.01;
			break;
		case 'e': // look down
			camPitch -= lookSpeed;
			if (camPitch < -M_PI_2 + 0.01) camPitch = -M_PI_2 + 0.01;
			break;
		case 'z': // turn left (alias)
			camYaw -= lookSpeed;
			break;
		case 'x': // turn right (alias)
			camYaw += lookSpeed;
			break;
	}
	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here

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
	
// enter GLUT's main cycle
	glutMainLoop();
	
 return 0;
}
