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
#include <sstream>

// Structure to hold a 3D vertex
struct Point {
    float x, y, z;
};

// Configuration structures
struct Camera {
    float posX, posY, posZ;
    float lookX, lookY, lookZ;
    float upX, upY, upZ;
    float fov, nearPlane, farPlane;
} camera = {5, 5, 5, 0, 0, 0, 0, 1, 0, 60, 1, 1000};

struct Window {
    int width, height;
} windowConfig = {800, 600};

// Global list to store all vertices loaded from .3d files
std::vector<Point> scenePoints;
std::vector<std::string> modelFiles;

// Helper function to extract attribute value from XML line
std::string getAttribute(const std::string& line, const std::string& attr) {
    size_t pos = line.find(attr + "=\"");
    if (pos == std::string::npos) return "";
    pos += attr.length() + 2;
    size_t end = line.find("\"", pos);
    return line.substr(pos, end - pos);
}

// Simple XML parser for phase 1
void parseXML(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open XML file " << filename << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Parse window
        if (line.find("<window") != std::string::npos) {
            std::string w = getAttribute(line, "width");
            std::string h = getAttribute(line, "height");
            if (!w.empty()) windowConfig.width = std::stoi(w);
            if (!h.empty()) windowConfig.height = std::stoi(h);
        }
        // Parse camera position
        else if (line.find("<position") != std::string::npos) {
            std::string x = getAttribute(line, "x");
            std::string y = getAttribute(line, "y");
            std::string z = getAttribute(line, "z");
            if (!x.empty()) camera.posX = std::stof(x);
            if (!y.empty()) camera.posY = std::stof(y);
            if (!z.empty()) camera.posZ = std::stof(z);
        }
        // Parse camera lookAt
        else if (line.find("<lookAt") != std::string::npos) {
            std::string x = getAttribute(line, "x");
            std::string y = getAttribute(line, "y");
            std::string z = getAttribute(line, "z");
            if (!x.empty()) camera.lookX = std::stof(x);
            if (!y.empty()) camera.lookY = std::stof(y);
            if (!z.empty()) camera.lookZ = std::stof(z);
        }
        // Parse camera up
        else if (line.find("<up") != std::string::npos) {
            std::string x = getAttribute(line, "x");
            std::string y = getAttribute(line, "y");
            std::string z = getAttribute(line, "z");
            if (!x.empty()) camera.upX = std::stof(x);
            if (!y.empty()) camera.upY = std::stof(y);
            if (!z.empty()) camera.upZ = std::stof(z);
        }
        // Parse projection
        else if (line.find("<projection") != std::string::npos) {
            std::string fov = getAttribute(line, "fov");
            std::string near = getAttribute(line, "near");
            std::string far = getAttribute(line, "far");
            if (!fov.empty()) camera.fov = std::stof(fov);
            if (!near.empty()) camera.nearPlane = std::stof(near);
            if (!far.empty()) camera.farPlane = std::stof(far);
        }
        // Parse model files
        else if (line.find("<model") != std::string::npos) {
            std::string file = getAttribute(line, "file");
            if (!file.empty()) {
                modelFiles.push_back(file);
            }
        }
    }
    file.close();
    
    std::cout << "XML parsed successfully" << std::endl;
    std::cout << "Window: " << windowConfig.width << "x" << windowConfig.height << std::endl;
    std::cout << "Camera position: (" << camera.posX << ", " << camera.posY << ", " << camera.posZ << ")" << std::endl;
    std::cout << "Models to load: " << modelFiles.size() << std::endl;
}

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
    gluPerspective(camera.fov, ratio, camera.nearPlane, camera.farPlane);
    glMatrixMode(GL_MODELVIEW);
}

// 3. Rendering Callback
void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set the camera from XML configuration
    gluLookAt(camera.posX, camera.posY, camera.posZ, 
              camera.lookX, camera.lookY, camera.lookZ,
              camera.upX, camera.upY, camera.upZ);

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
        return 1;
    }
    
    // Parse XML configuration file
    std::cout << "Loading XML: " << argv[1] << std::endl;
    parseXML(argv[1]);
    
    // Load all models specified in the XML
    for (const auto& modelFile : modelFiles) {
        loadModel(modelFile);
    }

    // GLUT Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(windowConfig.width, windowConfig.height);
    glutCreateWindow("CG Phase 1 - Engine");

    // Callback Registration
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene); // Keep rendering

    // OpenGL Settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // Enable face culling to hide back faces
    glClearColor(0.2, 0.2, 0.2, 0); // Slightly gray background to see white geometry
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode
    
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