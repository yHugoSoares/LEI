#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

struct Point {
    float x, y, z;
};

// Helper to write the vector of points to the .3d file
void saveFile(const std::string& filename, const std::vector<Point>& points) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << points.size() << "\n";
        for (const auto& p : points) {
            file << p.x << " " << p.y << " " << p.z << "\n";
        }
        file.close();
        std::cout << "File " << filename << " saved with " << points.size() << " vertices." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// Generates a plane centered at the origin on the XZ plane
void generatePlane(float size, int divisions, const std::string& filename) {
    std::vector<Point> points;
    float start = -size / 2.0f;
    float step = size / (float)divisions;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            float x1 = start + i * step;
            float z1 = start + j * step;
            float x2 = x1 + step;
            float z2 = z1 + step;

            // Every square is made of two triangles
            // Triangle 1
            points.push_back({x1, 0, z1});
            points.push_back({x1, 0, z2});
            points.push_back({x2, 0, z2});

            // Triangle 2
            points.push_back({x1, 0, z1});
            points.push_back({x2, 0, z2});
            points.push_back({x2, 0, z1});
        }
    }
    saveFile(filename, points);
}

// Generates a sphere centered at the origin
void generateSphere(float radius, int slices, int stacks, const std::string& filename) {
    std::vector<Point> points;
    float pi = 3.14159265359f;
    
    for (int i = 0; i < stacks; i++) {
        float lat1 = pi * (-0.5f + (float)i / stacks);
        float lat2 = pi * (-0.5f + (float)(i + 1) / stacks);
        float y1 = radius * sin(lat1);
        float y2 = radius * sin(lat2);
        float r1 = radius * cos(lat1);
        float r2 = radius * cos(lat2);
        
        for (int j = 0; j < slices; j++) {
            float lon1 = 2 * pi * (float)j / slices;
            float lon2 = 2 * pi * (float)(j + 1) / slices;
            
            float x1 = r1 * cos(lon1);
            float z1 = r1 * sin(lon1);
            float x2 = r1 * cos(lon2);
            float z2 = r1 * sin(lon2);
            float x3 = r2 * cos(lon2);
            float z3 = r2 * sin(lon2);
            float x4 = r2 * cos(lon1);
            float z4 = r2 * sin(lon1);
            
            // Triangle 1
            points.push_back({x1, y1, z1});
            points.push_back({x4, y2, z4});
            points.push_back({x3, y2, z3});
            
            // Triangle 2
            points.push_back({x1, y1, z1});
            points.push_back({x3, y2, z3});
            points.push_back({x2, y1, z2});
        }
    }
    saveFile(filename, points);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: ./generator <shape> <args> <output_file>" << std::endl;
        return 1;
    }

    std::string shape = argv[1];

    if (shape == "plane" && argc == 5) {
        float size = std::stof(argv[2]);
        int divisions = std::stoi(argv[3]);
        generatePlane(size, divisions, argv[4]);
    } 
    else if (shape == "sphere" && argc == 6) {
        float radius = std::stof(argv[2]);
        int slices = std::stoi(argv[3]);
        int stacks = std::stoi(argv[4]);
        generateSphere(radius, slices, stacks, argv[5]);
    }
    // Add logic for "box", "cone" here...
    else {
        std::cout << "Invalid arguments or shape." << std::endl;
    }

    return 0;
}