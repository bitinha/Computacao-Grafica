#include "glew.h"
#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;
#include "Shape.h"
#include "glut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "xmlParser.h"
#include "Grupo.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

//Shape formas;
float alfa = 0;
float beta = 0;
float zoom = 20;

float pi = M_PI;

vector<Grupo> grupos;
GLuint buffers[1024];


int generateBuffers(Grupo group, int j) {

	vector<float> points = group.getPontos();
	glBindBuffer(GL_ARRAY_BUFFER, buffers[j]);
	glBufferData(GL_ARRAY_BUFFER, points.size() * 4, &points.front(), GL_STATIC_DRAW);
	//group.setBuffer(&buffers[j]);
	j++;
	vector<Grupo> grupos = group.getGrupos();

	for (vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		j = generateBuffers((*it), j);
	}
	return j;
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(zoom * cos(beta) * sin(alfa), zoom * sin(beta), zoom * cos(beta) * cos(alfa),
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);
	
	int j = 0;
	for (vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		j = (*it).draw(buffers, j);
	}
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

	if (c == '+' && zoom > 1) {
		zoom -= 1;
	}if (c == '-') {
		zoom += 1;
	}

	glutPostRedisplay();
}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here
	switch (key) {
	case GLUT_KEY_UP:
		if (!(beta + 0.01 > (pi / 2)))
			beta += 0.05;
		break;
	case GLUT_KEY_DOWN:
		if (!(beta - 0.01 < -(pi / 2)))
			beta -= 0.05;
		break;
	case GLUT_KEY_LEFT:
		alfa -= 0.05;
		break;
	case GLUT_KEY_RIGHT:
		alfa += 0.05;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Indique um ficheiro a partir do qual se deva gerar");
		return 1;
	}
	
	const char * filename = argv[1];
	grupos = xmlParser(filename);

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

#ifndef __APPLE__
	glewInit();
#endif

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnableClientState(GL_VERTEX_ARRAY);
	
	int tam = 0;
	for (vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		tam += (*it).tamanhoGrupo();
	}

	glGenBuffers(tam, buffers);
	
	int j = 0;
	for(vector<Grupo>::iterator it = grupos.begin(); it != grupos.end(); it++){
		j = generateBuffers((*it), j);
	}
	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}