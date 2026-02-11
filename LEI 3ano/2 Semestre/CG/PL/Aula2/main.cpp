#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

// Global state variables
float translateX = 0.0f;
float translateY = 0.0f;
float translateZ = 0.0f;
float rotateAngle = 0.0f;
float scaleY = 1.0f;

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
	gluLookAt(5.0,3.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	// draw axis
	glBegin(GL_LINES);
		// X axis in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f( 50.0f, 0.0f, 0.0f);
		// Y Axis in Green
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 50.0f, 0.0f);
		// Z Axis in Blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 50.0f);
	glEnd();

	// geometric transformations
	glTranslatef(translateX, translateY, translateZ);
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	glScalef(1.0f, scaleY, 1.0f);

	// draw pyramid
	glBegin(GL_TRIANGLES);
		// front face
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		
		// right face
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		
		// back face
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		
		// left face
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);

		// bottom face
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);

		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events
void processKeys(unsigned char key, int xx, int yy) {
	
	switch (key) {
		case 'w':
			// increase height when 'w' is pressed
			scaleY *= 1.25f;
			break;
		case 's':
			// decrease height when 's' is pressed
			scaleY *= 0.75f;
			break;
		case 'a':
			// rotate left when 'q' is pressed
			rotateAngle -= 5.0f;
			break;
		case 'd':
			// rotate right when 'r' is pressed
			rotateAngle += 5.0f;
			break;
		case 'p':
			// change mode to GL_POINT when 'p' is pressed
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			break;
		case 'l':
			// change mode to GL_LINE when 'l' is pressed
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			break;
		case 'f':
			// change mode to GL_FILL when 'f' is pressed
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
	
	switch (key) {
		case GLUT_KEY_UP:
			// move on x axis when up arrow is pressed
			translateX -= 0.5f;
			break;
		case GLUT_KEY_DOWN:
			// move on x axis when down arrow is pressed
			translateX += 0.5f;
			break;
		case GLUT_KEY_LEFT:
			// move on z axis when left arrow is pressed
			translateZ += 0.5f;
			break;
		case GLUT_KEY_RIGHT:
			// move on z axis when right arrow is pressed
			translateZ -= 0.5f;
			break;
	}
	glutPostRedisplay();
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

	
// Registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
