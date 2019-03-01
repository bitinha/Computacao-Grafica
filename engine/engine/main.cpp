#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;
#include "Shape.h"
#include "Sphere.h"
#include "Cone.h"
#include "Box.h"
#include "Plane.h"
#include "glut.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

Sphere criaEsfera(FILE *file) {
	float radius = 0;
	int stacks = 0;
	int slices = 0;
	fscanf_s(file, "Radius: %f\n", &radius);
	fscanf_s(file, "Slices: %i\n", &slices);
	fscanf_s(file, "Stacks: %i", &stacks);

	return Sphere(radius, slices, stacks);
}

Cone criaCone(FILE *file) {
	float radius = 0;
	float height = 0;
	int stacks = 0;
	int slices = 0;
	fscanf_s(file, "Radius: %f\n", &radius);
	fscanf_s(file, "Height: %f\n", &height);
	fscanf_s(file, "Slices: %i\n", &slices);
	fscanf_s(file, "Stacks: %i", &stacks);

	return Cone(radius, height, slices, stacks);
}

Box criaBox(FILE *file) {
	double x = 0;
	double y = 0;
	double z = 0;
	int divisions = 0;
	fscanf_s(file, "X: %d\n", &x);
	fscanf_s(file, "Y: %d\n", &y);
	fscanf_s(file, "Z: %d\n", &z);
	fscanf_s(file, "Divisions: %i", &divisions);

	return Box(x, y, z, divisions);
}

Plane criaPlano(FILE *file) {
	double x = 0;
	double z = 0;
	fscanf_s(file, "X: %d\n", &x);
	fscanf_s(file, "Z: %d\n", &z);

	return Plane(x, z);
}

Shape novaForma(char forma[], FILE* file) {
	string shape = string(forma);
	if (!shape.compare("sphere")) { return (criaEsfera(file)); }
	else if (!shape.compare("plane")) { return (criaPlano(file));}
	else if (!shape.compare("box")) { return (criaBox(file));}
	else if (!shape.compare("cone")) { return (criaCone(file));}
}

list<Shape> interpretador(list<string> files) {
	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it;
	std::list<Shape> sh;
	list<Shape> ::iterator iter = sh.begin();
	errno_t erro;
	for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
		FILE *pfile;
		erro = fopen_s(&pfile, (*it).c_str(), "r");
		std::cout << ' ' << erro;
		if ( erro == 0) {
			char forma[10];
			fscanf_s(pfile, "Forma: %s\n", forma, sizeof(forma));
			std::cout << ' ' << forma;
			Shape s = novaForma(forma, pfile);
			sh.insert(iter, s);
			fclose(pfile);
		}
	}
	return sh;
}

list<string> extraiFicheiros(const char* filename) {


	list<string> files;
	list<string> ::iterator it;
	/*Ler um ficheiro XML*/
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile((char*)filename);

	if (eResult) {
		printf("Não foi possível carregar o ficheiro xml");
		exit(1);
	}



	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) {
		printf("Erro ao ler o ficheiro xml");
		exit(XML_ERROR_FILE_READ_ERROR);
	}

	XMLElement * pElement = pRoot->FirstChildElement("model");
	if (pElement == nullptr) {
		printf("Erro ao ler o ficheiro xml");
		exit(XML_ERROR_PARSING_ELEMENT);
	}

	const char * szAttributeText = nullptr;
	XMLElement * pListElement = pRoot->FirstChildElement("model");
	it = files.begin();
	while (pListElement != nullptr) {
		const char* iOutListValue;
		iOutListValue = pListElement->Attribute("file");
		files.insert(it, iOutListValue);
		pListElement = pListElement->NextSiblingElement("model");
	}

	return files;
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
	gluLookAt(10, 10, 10,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);

	glutWireTeapot(10);
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {

	// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here
	switch (key) {
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Indique um ficheiro a partir do qual se deva gerar");
		return 1;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	const char * filename = argv[1];

	list<Shape> formas;
	list<string> files = extraiFicheiros(filename);

	list<string> ::iterator it;
	it = files.begin();

	for (std::list<string>::iterator it = files.begin(); it != files.end(); ++it)
		std::cout << ' ' << *it << '\n';

	formas = interpretador(files);

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

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}