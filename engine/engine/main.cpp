#include <iostream>
#include <vector>
#include "tinyxml2.h";
#include <string>;
#include <list>;
#include "Shape.h"
#include "glut.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

vector<Vertice> interpretador(list<string> files) {
	
	vector<Vertice> vr;
	Vertice v;
	errno_t erro;
	float px = 0, py = 0, pz = 0;
	int ch, ok;
	
	for (list<string>::iterator it = files.begin(); it != files.end(); it++) {
		FILE *pfile;
		erro = fopen_s(&pfile, (*it).c_str(), "r");
		if ( erro == 0) {
			while (EOF != (ch = getc(pfile))) {
				ok = fscanf_s(pfile, "%f ",  &px, sizeof(px));
				fscanf_s(pfile, "%f ",  &py, sizeof(py));
				fscanf_s(pfile, "%f" , &pz, sizeof(pz));
				if (ok >= 0) {
					v = Vertice(px, py, pz);
					vr.push_back(v);
				}
			}
			fclose(pfile);
		}
	}


	return vr;
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
	
	const char * filename = argv[1];

	vector<Vertice> vertices;
	list<string> files = extraiFicheiros(filename);

	list<string> ::iterator it;
	it = files.begin();

	vertices = interpretador(files);

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