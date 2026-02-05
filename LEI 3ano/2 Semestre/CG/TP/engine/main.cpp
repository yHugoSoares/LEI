#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

// Structure to hold a 3D vertex
struct Point {
    float x, y, z;
};

// Global list to store all vertices loaded from .3d files
std::vector<Point> scenePoints;

// 1. Function to read your custom .3d file format
void loadModel(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    int numVertices;
    file >> numVertices; // Read the header (number of vertices)

    for (int i = 0; i < numVertices; ++i) {
        Point p;
        file >> p.x >> p.y >> p.z;
        scenePoints.push_back(p);
    }
    file.close();
    std::cout << "Loaded " << numVertices << " vertices from " << filename << std::endl;
}

// 2. Window Reshape Callback
void changeSize(int w, int h) {
    if (h == 0) h = 1;
    float ratio = w * 1.0 / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
}

// 3. Rendering Callback
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera (Position, LookAt, Up)
    // In Phase 1, you will eventually get these values from the XML
    gluLookAt(10.0, 10.0, 10.0, 
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Draw the models
    glBegin(GL_TRIANGLES);
    for (const auto& p : scenePoints) {
        // For sphere, the normal at each vertex is the normalized position vector
        float length = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
        if (length > 0.001f) {
            glNormal3f(p.x / length, p.y / length, p.z / length);
        }
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    // Phase 1 Requirement: Engine receives an XML file as an argument
    if (argc < 2) {
        std::cout << "Usage: ./engine <config.xml>" << std::endl;
        // For now, we will manually load a test file to see if it works
        // loadModel("plane.3d"); 
    } else {
        // TODO: Insert TinyXML2 code here to parse argv[1] 
        // and call loadModel() for each <model> found.
        // Quick temporary fix: just hardcode the model path for testing
        std::cout << "Loading XML: " << argv[1] << std::endl;
        loadModel("models/sphere.3d");
    }

    // GLUT Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("CG Phase 1 - Engine");

    // Callback Registration
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene); // Keep rendering

    // OpenGL Settings
    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE); // Disabled for now to see both sides of triangles
    glClearColor(0.2, 0.2, 0.2, 0); // Slightly gray background to see white geometry
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Fill mode (solid)
    
    // // Enable lighting for 3D appearance
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    
    // // Set up a simple light
    // GLfloat lightPos[] = {10.0f, 10.0f, 10.0f, 1.0f};
    // GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    // GLfloat lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    
    // // Set material properties
    // GLfloat matAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    // GLfloat matDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    // glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matAmbient);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDiffuse);

    glutMainLoop();
    
    return 1;
}