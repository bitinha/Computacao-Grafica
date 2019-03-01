#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "glut.h"
float x = M_PI;

void drawSphere(float radius, int slices, int stacks) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0, 0, 1);
	float a = 0;
	for (int i = 0; i < slices; i++) {
		a = i * 2 * x / slices;
		float b = x / 2 - (x / (stacks));
		glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLES);
		glVertex3f(0, radius, 0);
		glVertex3f(radius * cos(b) * sin(a), radius * sin(b), radius * cos(b) * cos(a));
		glVertex3f(radius * cos(b) * sin((i + 1) * 2 * x / slices), radius * sin(b), radius * cos(b) * cos((i + 1) * 2 * x / slices));
		glEnd();
		b = -b;
		glBegin(GL_TRIANGLES);
		glVertex3f(0, -radius, 0);
		glVertex3f(radius * cos(b) * sin((i + 1) * 2 * x / slices), radius * sin(b), radius * cos(b) * cos((i + 1) * 2 * x / slices));
		glVertex3f(radius * cos(b) * sin(a), radius * sin(b), radius * cos(b) * cos(a));
		glEnd();
		for (int j = 1; j < stacks - 1; j++) {
			b = x / 2 - (j * x / (stacks));
			glBegin(GL_TRIANGLES);
			glVertex3f(radius * cos(b) * sin(i * 2 * x / slices), radius * sin(b), radius * cos(b) * cos(i * 2 * x / slices));
			glVertex3f(radius * cos(x / 2 - ((j + 1) * x / (stacks))) * sin(i * 2 * x / slices), radius * sin(x / 2 - ((j + 1) * x / (stacks))), radius * cos(x / 2 - ((j + 1) * x / (stacks))) * cos(i * 2 * x / slices));
			glVertex3f(radius * cos(b) * sin((i + 1) * 2 * x / slices), radius * sin(b), radius * cos(b) * cos((i + 1) * 2 * x / slices));
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3f(radius * cos(b) * sin((i + 1) * 2 * x / slices), radius * sin(b), radius * cos(b) * cos((i + 1) * 2 * x / slices));
			glVertex3f(radius * cos(x / 2 - ((j + 1) * x / (stacks))) * sin(i * 2 * x / slices), radius * sin(x / 2 - ((j + 1) * x / (stacks))), radius * cos(x / 2 - ((j + 1) * x / (stacks))) * cos(i * 2 * x / slices));
			glVertex3f(radius * cos(x / 2 - ((j + 1) * x / (stacks))) * sin((i + 1) * 2 * x / slices), radius * sin(x / 2 - ((j + 1) * x / (stacks))), radius * cos(x / 2 - ((j + 1) * x / (stacks))) * cos((i + 1) * 2 * x / slices));
			glEnd();
		}
	}
}