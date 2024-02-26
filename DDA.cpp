#include <glut.h>
#include <vector>

std::vector<std::pair<int, int>> vertices;

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = static_cast<float>(dx) / steps;
    float yIncrement = static_cast<float>(dy) / steps;

    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; ++i) {
        glVertex2i(static_cast<int>(x), static_cast<int>(y));
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw vertices
    glColor3f(1.0, 0.0, 0.0); // Red color
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (const auto& vertex : vertices) {
        glVertex2i(vertex.first, vertex.second);
    }
    glEnd();

    // Draw lines using DDA algorithm
    glColor3f(0.0, 0.0, 1.0); // Blue color
    if (vertices.size() >= 2) {
        for (size_t i = 0; i < vertices.size() - 1; ++i) {
            drawLineDDA(vertices[i].first, vertices[i].second, vertices[i + 1].first, vertices[i + 1].second);
        }
    }

    glutSwapBuffers();
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Left button - add a vertex
        vertices.push_back(std::make_pair(x, glutGet(GLUT_WINDOW_HEIGHT) - y));
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Right button - connect the first and last vertices
        if (vertices.size() >= 3) {
            vertices.push_back(vertices.front()); // Connect to the first vertex
        }
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("DDA Polygon Drawing");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background

    glutDisplayFunc(display);
    glutMouseFunc(mouseCallback);

    glutMainLoop();

    return 0;
}