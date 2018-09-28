#include "camera.h"

#include "..\\font.h"
#include <iostream>
#include <string>

using namespace std;

Camera::Camera()
{
    _world_BLx = 0;
    _world_BLy = 0;
    _world_W = 1;
    _world_H = 1;
    _window_W = 100;
    _window_H = 100;
    _fb_W = 100;
    _fb_H = 100;
    _window = NULL;
}

Camera::Camera(double world_BLx, double world_BLy,
                   double world_W, double world_H,
               int window_W, int window_H,
               GLFWwindow* window)
{
    _world_BLx = world_BLx;
    _world_BLy = world_BLy;
    _world_W = world_W;
    _world_H = world_H;
    _window_W = window_W;
    _window_H = window_H;
    _fb_W = window_W;
    _fb_H = window_H;
    _window = window;
}

void Camera::mouse_to_world(int mx, int my,  double &wx, double &wy)
{
    int vx = mx;
    int vy = (int)(_window_H - my);

    viewport_to_world(vx, vy, wx, wy);
}

void Camera::viewport_to_world(int vx, int vy,  double &wx, double &wy)
{
    double x_fraction = vx / _window_W;
    double y_fraction = vy / _window_H;

    wx = _world_BLx + x_fraction * _world_W;
    wy = _world_BLy + y_fraction * _world_H;
}

void Camera::world_to_viewport(double wx, double wy,
                               int& vx, int& vy) {
    vx = (int)((wx - _world_BLx) / _world_W * _window_W + 0.5);
    vy = (int)((wx - _world_BLy) / _world_H * _window_H + 0.5);
}

void Camera::begin_drawing()
{
    glViewport(0,0, (int)_fb_W, (int)_fb_H);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double half_W = _world_W / 2;
    double half_H = _world_H / 2;
    glOrtho(-half_W, +half_W,
            -half_H, +half_H,
            0, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(-(_world_BLx + half_W),
                 -(_world_BLy + half_H),
                 -1);
}

void Camera::check_resize()
{
    int width, height;

    glfwGetFramebufferSize(_window, &width, &height);
    _fb_W = width;
    _fb_H = height;
}

void Camera::draw_grid(double minor_spacing, double major_spacing)
{
    double x,y;
    double left   = (int)(_world_BLx);
    double right  = left + _world_W;
    double bottom = (int)(_world_BLy);
    double top    = bottom + _world_H;
	double minor_spacingx = _world_W / 20;
	double major_spacingx = _world_W / 4;
	double minor_spacingy = _world_H / 20;
	double major_spacingy = _world_H / 4;

    glDisable(GL_DEPTH_TEST);

    glLineWidth(1.0f);       // lines as thin as possible

    glBegin(GL_LINES);      // every two glVertex calls will draw a line segment

    // the minor vertical grid lines
    glColor3d(0.6, 0.4, 0.4);    // darkish red
    for (x = left; x <= right; x += minor_spacingx)
    {
        glVertex2d(x, bottom);
        glVertex2d(x, top);
    }
    // the minor horizontal grid lines
    for (y = bottom; y <= top; y += minor_spacingy)
    {
        glVertex2d(left,  y);
        glVertex2d(right, y);
    }
	glEnd();

	glLineWidth(2.0f);       // lines as thin as possible
	glBegin(GL_LINES);      // every two glVertex calls will draw a line segment
    glColor3d(0.4, 0.7, 0.4);// 主网线颜色: darkish green
    for (x = left; x <= right; x += major_spacingx)
    {
        glVertex2d(x, bottom);
        glVertex2d(x, top);
    }
    for (y = bottom; y <= top; y += major_spacingy)// 水平线
    {
        glVertex2d(left,  y);
        glVertex2d(right, y);
    }
    glEnd();
	//画x轴
	double aix_width = 4.0;
	glLineWidth(aix_width);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d( left,bottom);
	glVertex2d(right,bottom);
	//画y轴
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(left, bottom);
	glVertex2d(left,top);
	glEnd();
	//画x轴刻度值
	glColor3f(0.0, 0.0, 0.0);
	double vb = 0.02, vl=3;
	viewport_to_world(aix_width/2, aix_width/2, vl, vb);
	for (x = left+major_spacingx; x < right; x += major_spacingx)
	{
		glPushMatrix();
		glRasterPos3f(x, bottom+vb, 0.0);
		drawString(to_string((int)x).c_str());
		glPopMatrix();
	}
	glPushMatrix();
	glRasterPos3f(right-5, bottom+vb , 0.0);
	drawString("X");
	glPopMatrix();
	
	for (y = bottom+major_spacingy; y <= top; y += major_spacingy)
	{
		glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glRasterPos3f(left+vl, y, 0.0);
		drawString(to_string(y).substr(0,4).c_str());
		glPopMatrix();
	}
	glPushMatrix();
	glRasterPos3f(left +vl, top - vb*5, 0.0);
	drawString("Y");
	glPopMatrix();
	//圆心
	glPushMatrix();
	glRasterPos3f(left + vl, bottom +vb, 0.0);
	drawString("O");
	glPopMatrix();
	
}
