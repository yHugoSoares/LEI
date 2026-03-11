

#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif


float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;

// Grid data: one vertex per image pixel (x, y, z) with height = 0.0
static std::vector<float> g_vertices;
static int g_imgW = 0, g_imgH = 0;
static std::vector<unsigned char> g_imgData; // luminance per pixel
static std::vector<float> g_stripVertices; // vertices arranged per-strip: for each row, [top0,bottom0,top1,bottom1,...]
static GLuint g_vbo = 0;
static int g_stripVertexCount = 0; // total number of vertices in g_stripVertices
static int g_stripVerticesPerRow = 0; // number of vertices in one triangle strip (2 * g_imgW)

// Return height for pixel at column i, row j (i in [0..g_imgW), j in [0..g_imgH))
float h(int i, int j) {
	if (g_imgW <= 0 || g_imgH <= 0) return 0.0f;
	if (i < 0) i = 0; if (i >= g_imgW) i = g_imgW - 1;
	if (j < 0) j = 0; if (j >= g_imgH) j = g_imgH - 1;
	if (g_imgData.empty()) return 0.0f;
	unsigned char v = g_imgData[(size_t)j * (size_t)g_imgW + (size_t)i];
	return (v / 255.0f) * 10.0f; // scale 0-255 -> 0-60 meters
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void drawTerrain() {
	if (g_vbo == 0 || g_stripVertexCount == 0)
		return;

	glPushMatrix();
	// center terrain around origin
	glTranslatef(-g_imgW / 2.0f, 0.0f, -g_imgH / 2.0f);

	glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	// filled triangles
	glColor3f(1.0f, 1.0f, 1.0f);
	for (int row = 0; row < g_imgH - 1; ++row) {
		int first = row * g_stripVerticesPerRow;
		glDrawArrays(GL_TRIANGLE_STRIP, first, g_stripVerticesPerRow);
	}

	// wireframe overlay
	glColor3f(0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int row = 0; row < g_imgH - 1; ++row) {
		int first = row * g_stripVerticesPerRow;
		glDrawArrays(GL_TRIANGLE_STRIP, first, g_stripVerticesPerRow);
	}
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glPopMatrix();
}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

	drawTerrain();

	glutWireTeapot(2.5);

// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

// put code to process regular keys in here
}



void processMouseButtons(int button, int state, int xx, int yy) {
	
	if (state == GLUT_DOWN)  {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {
			
			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}


void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * 							     sin(betaAux * 3.14 / 180.0);
}


void init() {

	// Load image dimensions using DevIL and build a regular grid
	ilInit();
	const char *fname = "portugal.png";
	ILuint imgID;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);
	if (ilLoadImage(fname)) {
		// convert to single-channel luminance for easy intensity access
		ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
		g_imgW = ilGetInteger(IL_IMAGE_WIDTH);
		g_imgH = ilGetInteger(IL_IMAGE_HEIGHT);
		ILubyte *data = ilGetData();
		g_imgData.assign(data, data + (size_t)g_imgW * (size_t)g_imgH);
	} else {
		// fallback to a modest default if image not found
		g_imgW = 256;
		g_imgH = 256;
		g_imgData.assign((size_t)g_imgW * (size_t)g_imgH, 0);
	}
	ilDeleteImages(1, &imgID);

	// Build vertex array: one vertex per pixel, height = 0.0
	// Build vertex array (row-major) - keep for compatibility
	g_vertices.clear();
	g_vertices.reserve((size_t)g_imgW * (size_t)g_imgH * 3);
	for (int y = 0; y < g_imgH; ++y) {
		for (int x = 0; x < g_imgW; ++x) {
			g_vertices.push_back((float)x);
			g_vertices.push_back(h(x, y)); // height from pixel intensity
			g_vertices.push_back((float)y);
		}
	}

	// Build strip-ordered vertex array for VBOs: for each row, emit [top0,bottom0,top1,bottom1,...]
	g_stripVertices.clear();
	g_stripVertices.reserve((size_t)(g_imgH - 1) * (size_t)g_imgW * 2 * 3);
	for (int y = 0; y < g_imgH - 1; ++y) {
		for (int x = 0; x < g_imgW; ++x) {
			// top vertex (x, y)
			g_stripVertices.push_back((float)x);
			g_stripVertices.push_back(h(x, y));
			g_stripVertices.push_back((float)y);
			// bottom vertex (x, y+1)
			g_stripVertices.push_back((float)x);
			g_stripVertices.push_back(h(x, y + 1));
			g_stripVertices.push_back((float)(y + 1));
		}
	}

	g_stripVertexCount = (int)(g_stripVertices.size() / 3);
	g_stripVerticesPerRow = g_imgW * 2; // two vertices per column in each strip

	// Create/upload VBO
	if (g_vbo == 0) glGenBuffers(1, &g_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_vbo);
	glBufferData(GL_ARRAY_BUFFER, g_stripVertices.size() * sizeof(float), g_stripVertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(1600,900);
	glutCreateWindow("CG@DI-UM");

#ifndef __APPLE__
	// initialize GLEW for non-Apple platforms to get VBO entrypoints
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
	}
#endif
		

// Required callback registry
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);

	init();	

// enter GLUT's main cycle
	glutMainLoop();
	
	return 0;
}

