#include<GL/glut.h> 
#include "font.h"
#include <windows.h>

// ASCII�ַ��ܹ�ֻ��0��127��һ��128���ַ�
#define MAX_CHAR       128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall) { // ����ǵ�һ�ε��ã�ִ�г�ʼ��
					   // Ϊÿһ��ASCII�ַ�����һ����ʾ�б�
		isFirstCall = 0;

		// ����MAX_CHAR����������ʾ�б���
		lists = glGenLists(MAX_CHAR);

		// ��ÿ���ַ��Ļ������װ����Ӧ����ʾ�б���
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// ����ÿ���ַ���Ӧ����ʾ�б�����ÿ���ַ�
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void* bitmap_fonts[7] = {
	GLUT_BITMAP_9_BY_15,
	GLUT_BITMAP_8_BY_13,
	GLUT_BITMAP_TIMES_ROMAN_10,
	GLUT_BITMAP_TIMES_ROMAN_24,
	GLUT_BITMAP_HELVETICA_10,
	GLUT_BITMAP_HELVETICA_12,
	GLUT_BITMAP_HELVETICA_18
};
void print_bitmap_string(void* font, const char* s)
{
	if (s && strlen(s)) {
		while (*s) {
			glutBitmapCharacter(font, *s);
			s++;
		}
	}
}
int TextOut(float x, float y, const char* cstr)
{
	glRasterPos2f(x, y);
	print_bitmap_string(bitmap_fonts[4], cstr);
	return 1;
}
