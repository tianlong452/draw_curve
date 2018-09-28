//========================================================================
// Untangle a graph.
// Author: Alejo Hausner
// Date: Sept. 3, 2017.
//
// Heavily modified from an example by Camilla Berglund <elmindreda@glfw.org>
//========================================================================

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
//#include "GeomLib.h"

using namespace std;

Camera cam;

vector<double> vertex_x;
vector<double> vertex_y;
vector< vector<bool> > is_edge;

int mouse_x, mouse_y;

double vertex_size = 0.5;

int active_vertex = -1;
int m_left = 0;
//////////////////////////////////////////////////////////////////////
//
// Draw the coordinate grid.
//
// *** NO NEED TO CHANGE THIS ***
//
//////////////////////////////////////////////////////////////////////

void drawCoordGrid()
{
    double x,y;

    glColor3d(.5,.5,.7);    // light blue
    glLineWidth(0.1);         // lines as thin as possible
    glBegin(GL_LINES);      // every two glVertex calls will draw a line segment

    // the minor vertical grid lines
    for (x=0; x<=360; x+=10)
    {
        glVertex2d(x,-3.0);
        glVertex2d(x, 3.0);
    }
    // the minor horizontal grid lines
    for (y=-1; y<=1; y+=0.1)
    {
        glVertex2d(0,y);
        glVertex2d( 360,y);
    }

    // the major vertical grid lines: lighter blue
	glColor3d(0, 0, .9);
	glLineWidth(1);
    for (x=0; x<=360; x+=90)
    {
        glVertex2d(x,-3.0);
        glVertex2d(x, 3.0);
    }

    // the major horizontal grid lines
    for (y=-1; y<=1; y+=0.5)
    {
        glVertex2d(0,y);
        glVertex2d( 360,y);
    }

	// the coordinate axes.
    glColor3d(.9,.7,.7);
    glVertex2d(0.0,-3.0);
    glVertex2d(0.0, 3.0);
    glVertex2d(-3.0,0.0);
    glVertex2d( 3.0,0.0);

    glEnd();
}

//////////////////////////////////////////////////////////////////////
//
// Convenience function to check if the mouse is on a vertex.
//
// Inputs:
//    x,y   - mouse coordinates (they are passed in to handleMouseAction
//            or handleMouseMotion
//    hx,hy - coordinates of the vertex.
//
// Returns:
//    true - the mouse x,is near a vertex.
//
// NOTE:
//    You will have to call this function repeatedly, to
//    identify which vertex the user clicked on.
//
// *** NO NEED TO CHANGE THIS ***
//
//////////////////////////////////////////////////////////////////////

bool on_vertex(int x, int y, double vx, double vy)
{

    double wx,wy;
    cam.mouse_to_world(x,y, wx,wy);
    double s = vertex_size;
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

//////////////////////////////////////////////////////////////////////
//
// ************************ YOU SHOULD CHANGE THIS *******************
// **** ADD OTHER FUNCTIONS IF NECCESSARY   **************************
//
// This function is called when the user presses or releases a
// mouse button.
// Parameters:
//
//    button: possible values: GLUT_LEFT, GLUT_MIDDLE or GLUT_RIGHT
//            Identifies the button.
//
//    state:  possible values: GLUT_UP or GLUT_DOWN
//            The state of the button.
//
//    x,y:    The position of the mouse.
//            x goes from 0 on the left to winWidth-1 on the right.
//            y goes from 0 on the top to winHeight-1 on the bottom.
//
//////////////////////////////////////////////////////////////////////


/*
Point4 cross_point(Point4 A, Point4 B, Point4 C, Point4 D) {
	Vector4 V = D - C;    
	Vector4 N(-V.Y(), V.X(), 0);    
	Point4 Q = C;
	Point4 P(0,0,0);
	double t = 0;
	// check if denominator is zero before the next line:
	double denominator = (N*(B - A));
	if(denominator > EPSILON)
		t = (N * (Q-A)) / denominator; 
	if (t > 0 && t < 1) {
		P = A + t * (B - A);
		P.Z() = 1;
	}
	//check P is on CD
	if (P.X() > C.X()+EPSILON && P.X() < D.X()-EPSILON || P.X() > D.X()+EPSILON && P.X() < C.X()-EPSILON) {
		return P;
	}
	else
		return Point4(0, 0, 0);
}*/

//////////////////////////////////////////////////////////////////////
//
// main() calls this function to re-draw the scene.
//
// YOU MUST CHANGE THIS!
//
//////////////////////////////////////////////////////////////////////

void display(void)
{
    //
    // Set the background colour to darkish blue-gray.
    //
	/*相交检测
	vector<Point4> cross_p;
	for (int i = 0; i < is_edge.size(); ++i)
		for (int j = 0; j < is_edge.size(); ++j) 
			if (is_edge[i][j] == true) // edge1
				for (int ii = 0; ii < is_edge.size(); ++ii)
					for (int jj = 0; jj < is_edge.size(); ++jj)
						if (is_edge[ii][jj] == true) // edge2
						{
							Point4 p = cross_point(Point4(vertex_x[i], vertex_y[i], 0),
								Point4(vertex_x[j], vertex_y[j], 0),
								Point4(vertex_x[ii], vertex_y[ii], 0),
								Point4(vertex_x[jj], vertex_y[jj], 0));
							if (p.Z() > EPSILON) //Z record have cross or not
								cross_p.push_back(p);
						}
	if (cross_p.size()) 
		glClearColor(.4f, .4f, 0.6f, 1.f);
	else
		glClearColor(1, 1, 1, 1.f);*/

    //
    // OK, now clear the screen with the background colour
    //
	glClearColor(1, 1, 1, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.begin_drawing();

    //
    // draw the coordinate grid
    //
    drawCoordGrid();
	double s;
    // Draw little boxs ( vertexs)

    s = vertex_size;
    glColor3d(0.0, 0.0, 1.0);
	//画顶点
    glBegin(GL_QUADS);
	for (int i = 0; i < vertex_x.size(); ++i) {
		int zoom = 1;
		if (i == active_vertex)
			glColor3d(1.0, 0.0, 0.0);
			glVertex2d(vertex_x[i] - s*zoom, vertex_y[i] - s * zoom/90);
			glVertex2d(vertex_x[i] + s * zoom, vertex_y[i] - s * zoom / 90);
			glVertex2d(vertex_x[i] + s * zoom, vertex_y[i] + s * zoom / 90);
			glVertex2d(vertex_x[i] - s * zoom, vertex_y[i] + s * zoom / 90);
			if (i == active_vertex)
				glColor3d(0.0, 0.0, 1.0);
	}
    glEnd();
	// Draw little boxs ( cross points) 
	/*s = vertex_size / 4;
	glColor3d(1.0, 0.0, 0.0);
	
	glBegin(GL_QUADS);
	for (int i = 0; i < cross_p.size(); ++i) {
		glVertex2d(cross_p[i].X() - s, cross_p[i].Y() - s);
		glVertex2d(cross_p[i].X() + s, cross_p[i].Y() - s);
		glVertex2d(cross_p[i].X() + s, cross_p[i].Y() + s);
		glVertex2d(cross_p[i].X() - s, cross_p[i].Y() + s);
	}
	glEnd();*/
    // Draw lines segment (edges)
    glColor3d(0.0, 0.0, 0.0);
    glLineWidth(2);  // lines are 3 pixels wide
    glBegin(GL_LINES);
	for (int i=0;i+1<vertex_x.size();++i)
	{
		glVertex2d(vertex_x[i], vertex_y[i]);
		glVertex2d(vertex_x[i+1], vertex_y[i+1]);
	}
    glEnd();
}

//////////////////////////////////////////////////////////////////////
//
// Read the graph from a file.
// The graph is stored as an adjacency matrix.
// First line : number of vertices:
// Each remaining line: a list of 0s and 1s.
// entry (a b) is 1 if there's an edge from vertex "a" to vertex "b",
// entry (a b) is 0 otherwise.
// (note the matrix is symmetric, since this is an undirected graph)
//
// YOU MUST CHANGE THIS!
//
//////////////////////////////////////////////////////////////////////

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
	// Here, if mouse is currently pressing on some vertex,
	// change the vertex's position.

	mouse_x = (int)x;
	mouse_y = (int)y;
	double wx, wy;
	/*if (active_vertex != -1) {
	//vertex_x[active_vertex] = wx;
	vertex_y[active_vertex] = wy;
	}*/
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
		//vertex_x[active_vertex] = wx;
		vertex_y[vertex] += y/10;
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
	cam = Camera(0, -1, 360, 2, w, h, window);
}
int main(int argc, char *argv[])
{
    GLFWwindow* window;
    int w = 1440;
    int h = 900;
    if (argc != 2)
    {
        cerr << "Usage:\n";
        cerr << "  untangle <graph-filename>\n";
        cerr << "PRESS <Control-C>\n";
        char line[100];
        cin >> line;
        exit (EXIT_FAILURE);
    }

    read_graph(argv[1]);

    glfwSetErrorCallback(error_callback);

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
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	cam = Camera(0, -1, 360, 2, w, h, window);
	// 选择投影矩阵，并重置坐标系统
   // cam = Camera(-1.5,-1.5, 3, 3, w, h, window);
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
