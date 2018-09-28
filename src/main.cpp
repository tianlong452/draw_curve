#include<GL/glut.h>  
#include <glad4.5/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"

using namespace std;

Camera cam;

vector<double> vertex_x;
vector<double> vertex_y;
vector< vector<bool> > is_edge;

int mouse_x, mouse_y;

double vertex_size = 0.5;

int active_vertex = -1;
int m_left = 0;

bool on_vertex(int x, int y, double vx, double vy)
{
    double wx,wy;
    cam.mouse_to_world(x,y, wx,wy);
    double s = vertex_size*2;
    return vx-s <= wx && wx <= vx+s;
}

int vertex_at(int x, int y) {

    for (int i = 0; i < vertex_x.size(); i++) {
        if (on_vertex(x, y, vertex_x[i], vertex_y[i])) {
            return i;
        }
    }
    return -1;
}

void display(void)
{
    
	glClearColor(1, 1, 1, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.begin_drawing();
	//画坐标系
	cam.draw_grid(1, 1);
	double s;
    // 画顶点
    s = vertex_size;
    glColor3d(0.0, 0.0, 1.0);
	//画顶点
    glBegin(GL_QUADS);
	for (int i = 0; i < vertex_x.size(); ++i) {
		int zoom = 1;
		glColor3d(1.0, 0.0, 0.0);
		glVertex2d(vertex_x[i] - s/**zoom*/, vertex_y[i] - s /**zoom*/ /90);
		glVertex2d(vertex_x[i] + s /**zoom*/, vertex_y[i] - s /**zoom*/ / 90);
		glVertex2d(vertex_x[i] + s /**zoom*/, vertex_y[i] + s /**zoom*/ / 90);
		glVertex2d(vertex_x[i] - s /**zoom*/, vertex_y[i] + s /**zoom*/ / 90);

		glfwPollEvents();
	}
    glEnd();
    glColor3d(1.0, 0.0, 0.0);
    glLineWidth(2);  // lines are 3 pixels wide
    glBegin(GL_LINES);
	for (int i=0;i+1<vertex_x.size();++i)
	{
		glVertex2d(vertex_x[i], vertex_y[i]);
		glVertex2d(vertex_x[i+1], vertex_y[i+1]);
	}
    glEnd();
}

void read_graph(char *filename)
{
	ifstream ifs(filename);
	if (!ifs)
		cerr << "can't open file\n";
	int n_vertices;
	n_vertices = 360;
	for (int i=0;i<n_vertices;++i)
	{
		//is_edge.push_back(vector<bool>());
		vertex_x.push_back(0 + 360 * double(i)/n_vertices);
		vertex_y.push_back(0);
		/*for (int j=0;j<n_vertices;++j)
		{
			int flag;
			ifs >> flag;
			is_edge[i].push_back(flag == 1);
		}*/
	}
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void mouse_button_callback(GLFWwindow* window, int button,
	int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT)
		return;

	if (action == GLFW_PRESS)
	{
		double wx, wy;
		cam.mouse_to_world(mouse_x, mouse_y, wx, wy);
		// Here, find out if mouse was pressed on some vertex,
		// and record the fact that this happened
		active_vertex = vertex_at(mouse_x, mouse_y);
		m_left = 1;
	}
	else {
		// Here, record the fact that NOTHING is being pressed
		// on anymore.
		active_vertex = -1;
		m_left = 0;
	}
}

void mouse_position_callback(GLFWwindow* window, double x, double y)
{
	mouse_x = (int)x;
	mouse_y = (int)y;
	double wx, wy;
	if (m_left) {
		active_vertex = vertex_at(mouse_x, mouse_y);
		cam.mouse_to_world(mouse_x, mouse_y, wx, wy);
		if(active_vertex !=-1)
			vertex_y[active_vertex] = wy;
	}
}

void scroll_callback(GLFWwindow* window, double x, double y) {
	double wx, wy;
	cam.mouse_to_world(mouse_x, mouse_y, wx, wy);
	int vertex = vertex_at(mouse_x, mouse_y);
	if (vertex != -1) {
		vertex_y[vertex] += 0.01*y;
	}
}
static void key_callback(GLFWwindow* window, int key,
                         int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_Q ) &&
        action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,1 /*GLFW_TRUE*/);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam = Camera(0, 0, 360, 10, w, h, window);
}
int main(int argc, char *argv[])
{
    GLFWwindow* window;
    int w = 720;
    int h = 450;
    read_graph(argv[1]);

    if (!glfwInit()) {
        cerr << "glfwInit failed!\n";
        cerr << "PRESS <ENTER>\n";
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(w, h, "Untangle a graph", NULL, NULL);
    if (!window)
    {
        cerr << "glfwCreateWindow failed!\n";
        cerr << "PRESS <ENTER>\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	// 选择投影矩阵，并重置坐标系统
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam = Camera(0, 0, 360, 10, w, h, window);
	//回调函数
	glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window,   mouse_position_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window))
    {
        cam.check_resize();
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
