//========================================================================
// Untangle a graph.
// Author: Alejo Hausner
// Date: Sept. 3, 2017.
//
// Heavily modified from an example by Camilla Berglund <elmindreda@glfw.org>
//========================================================================

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>

#include "Camera.h"
#include "GeomLib.h"

using namespace std;

Camera cam;

vector<double> vertex_x;
vector<double> vertex_y;
vector< vector<bool> > is_edge;

int mouse_x, mouse_y;

double vertex_size = 0.1;

int active_vertex = -1;
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
    for (x=-3.0; x<=3.0; x+=0.1)
    {
        glVertex2d(x,-3.0);
        glVertex2d(x, 3.0);
    }
    // the minor horizontal grid lines
    for (y=-3.0; y<=3.0; y+=0.1)
    {
        glVertex2d(-3.0,y);
        glVertex2d( 3.0,y);
    }

    // the major vertical grid lines: lighter blue
    glColor3d(.7,.7,.9);
    for (x=-3.0; x<=3.0; x+=1)
    {
        glVertex2d(x,-3.0);
        glVertex2d(x, 3.0);
    }

    // the major horizontal grid lines
    for (y=-3.0; y<=3.0; y+=1)
    {
        glVertex2d(-3.0,y);
        glVertex2d( 3.0,y);
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
    cout << "on_vertex (x y)=(" << x << " " << y << ")\n";

    double wx,wy;
    cam.mouse_to_world(x,y, wx,wy);

    cout << "world coords: (x y)=(" << wx << " " << wy << ")\n";
    cout << "vertex coords:(x y)=(" << vx << " " << vy << ")\n";

    double s = vertex_size;

    return vx-s <= wx && wx <= vx+s && vy-s <= wy && wy <= vy+s;
}

int vertex_at(int x, int y) {
    cout << "\nvertex at (" << x << " " << y << ")\n";

    for (int i = 0; i < vertex_x.size(); i++) {
        if (on_vertex(x, y, vertex_x[i], vertex_y[i])) {

            cout << "mouse is on vertex " << i << "!\n";

            return i;
        }
    }

    cout << "mouse isn't on any vertex\n";

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

void mouse_button_callback( GLFWwindow* window, int button,
                            int action, int mods )
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
    }
    else {
        // Here, record the fact that NOTHING is being pressed
        // on anymore.
		active_vertex = -1;
    }
}

void mouse_position_callback( GLFWwindow* window, double x, double y )
{
    // Here, if mouse is currently pressing on some vertex,
    // change the vertex's position.

    mouse_x = (int)x;
    mouse_y = (int)y;
    double wx, wy;
	cam.mouse_to_world(mouse_x, mouse_y, wx, wy);
	if (active_vertex != -1) {
		vertex_x[active_vertex] = wx;
		vertex_y[active_vertex] = wy;
	}
}

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
}

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
		glClearColor(0, .8, 0, 1.f);

    //
    // OK, now clear the screen with the background colour
    //
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.begin_drawing();

    //
    // draw the coordinate grid
    //
    drawCoordGrid();
	double s;
    // Draw little boxs ( vertexs)

    s = vertex_size / 2;
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
	for (int i = 0; i < vertex_x.size(); ++i) {
		glVertex2d(vertex_x[i] - s, vertex_y[i] - s);
		glVertex2d(vertex_x[i] + s, vertex_y[i] - s);
		glVertex2d(vertex_x[i] + s, vertex_y[i] + s);
		glVertex2d(vertex_x[i] - s, vertex_y[i] + s);
	}
    glEnd();
	// Draw little boxs ( cross points) 
	s = vertex_size / 4;
	glColor3d(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	for (int i = 0; i < cross_p.size(); ++i) {
		glVertex2d(cross_p[i].X() - s, cross_p[i].Y() - s);
		glVertex2d(cross_p[i].X() + s, cross_p[i].Y() - s);
		glVertex2d(cross_p[i].X() + s, cross_p[i].Y() + s);
		glVertex2d(cross_p[i].X() - s, cross_p[i].Y() + s);
	}
	glEnd();
    // Draw lines segment (edges)
    glColor3d(1.0, 1.0, 0.0);
    glLineWidth(3);  // lines are 3 pixels wide
    glBegin(GL_LINES);
	for (int i=0;i<is_edge.size();++i)
		for (int j = 0; j < is_edge.size(); ++j)
			if (is_edge[i][j] == true)
			{
				glVertex2d(vertex_x[i], vertex_y[i]);
				glVertex2d(vertex_x[j], vertex_y[j]);
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
	ifs >> n_vertices;
	for (int i=0;i<n_vertices;++i)
	{
		is_edge.push_back(vector<bool>());
		vertex_x.push_back(0);
		vertex_y.push_back(0);
		for (int j=0;j<n_vertices;++j)
		{
			int flag;
			ifs >> flag;
			is_edge[i].push_back(flag == 1);
		}
	}
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
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

int main(int argc, char *argv[])
{
    GLFWwindow* window;
    int w = 600;
    int h = 600;

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
        char line[100];
        cin >> line;
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(w, h, "Untangle a graph", NULL, NULL);
    if (!window)
    {
        cerr << "glfwCreateWindow failed!\n";
        cerr << "PRESS <ENTER>\n";
        char line[100];
        cin >> line;

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    cam = Camera(-1.5,-1.5, 3, 3, w, h, window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window,   mouse_position_callback);

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
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
