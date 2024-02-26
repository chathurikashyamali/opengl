#include <glut.h>
#include <cmath>
#include <vector>

int width = 800, height = 600;
std::vector<std::pair<int, int>> vertices;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float incX = dx / static_cast<float>(steps);
    float incY = dy / static_cast<float>(steps);

    float x = x1, y = y1;

    drawPixel(static_cast<int>(x), static_cast<int>(y));

    for (int i = 0; i < steps; i++) {
        x += incX;
        y += incY;
        drawPixel(static_cast<int>(x), static_cast<int>(y));
    }
}

void drawPolygon() {
    glColor3f(1.0, 1.0, 1.0);

    // Draw the polygon using DDA Line Algorithm
    if (vertices.size() > 1) {
        for (size_t i = 0; i < vertices.size() - 1; i++) {
            drawLineDDA(vertices[i].first, vertices[i].second,
                        vertices[i + 1].first, vertices[i + 1].second);
        }
    }

    // Close the polygon if there are enough vertices
    if (vertices.size() > 2) {
        drawLineDDA(vertices[0].first, vertices[0].second,
                    vertices[vertices.size() - 1].first, vertices[vertices.size() - 1].second);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);

    // Draw the vertices
    for (size_t i = 0; i < vertices.size(); i++) {
        glColor3f(1.0, 1.0, 1.0);
        drawPixel(vertices[i].first, vertices[i].second);
    }

    drawPolygon();

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        vertices.push_back(std::make_pair(x, height - y));
		
        //glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Connect the first and last vertices
        if (vertices.size() > 2) {
            drawLineDDA(vertices[0].first, vertices[0].second,
                        vertices[vertices.size() - 1].first, vertices[vertices.size() - 1].second);
        }
        glutPostRedisplay();
    }
}


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glPointSize(2.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutCreateWindow("Polygon Drawing with DDA Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
