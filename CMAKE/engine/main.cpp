#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "xmlParser.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

using namespace tinyxml2;
using namespace std;

float pi = M_PI;
//Shape formas;
float alfa = pi/2;
//float alfa = 0;//
float beta = 0;
float zoom = 200;
float look = 0;
int xAnt, yAnt;
float camX = -100, camY = 0, camZ = 0;
bool mouseMoving = false;

Cena cena;
GLuint *buffers;
GLuint *buffersNormal;
GLuint *buffersTextura;

void generateTextura(Grupo* g) {
	vector<Figura*> figuras = (*g).getFiguras();
	
	for (vector<Figura*>::iterator itF = figuras.begin(); itF != figuras.end(); itF++) {
		if ((*itF)->getNome() != nullptr) {
			(*itF)->generateTexturaFigura();
		}
	}

	vector<Grupo*> grupos = g->getGrupos();
	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		generateTextura((*it));
	}
}

int generateBuffers(Grupo *group, int j) {

	vector<Figura*> figuras = group->getFiguras();
	for (vector<Figura*>::iterator it = figuras.begin(); it != figuras.end(); it++) {
		vector<float> pontos = (*it)->getPontos();
		glBindBuffer(GL_ARRAY_BUFFER, buffers[j]);
		glBufferData(GL_ARRAY_BUFFER, pontos.size() * 4, &pontos.front(), GL_STATIC_DRAW);
		
		vector<float> normais = (*it)->getNormais();
		glBindBuffer(GL_ARRAY_BUFFER, buffersNormal[j]);
		glBufferData(GL_ARRAY_BUFFER, normais.size() * 4, &normais.front(), GL_STATIC_DRAW);
		
		vector<float> textura = (*it)->getTextura();
		glBindBuffer(GL_ARRAY_BUFFER, buffersTextura[j]);
		glBufferData(GL_ARRAY_BUFFER, textura.size() * 4, &textura.front(), GL_STATIC_DRAW);
		
		(*it)->setBuffer(buffers[j]);
		(*it)->setBufferNormal(buffersNormal[j]);
		(*it)->setBufferTextura(buffersTextura[j]);
		j++;
	}
	vector<Grupo*> grupos = group->getGrupos();

	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
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

void iniciaLuz() {
	if (cena.getLuz().size() > 0)
		glEnable(GL_LIGHTING);
	for (int i = 0; i < cena.getLuz().size(); i++)
		glEnable(GL_LIGHT0 + i);
}

void geraIluminacao() {
	int i = 0;
	vector<Luz*> luz = cena.getLuz();
	for (vector<Luz*>::iterator it = luz.begin(); it != luz.end(); it++) {
		(*it)->ilumina(i);
		i++;
	}
}

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	/*gluLookAt(zoom * cos(beta) * sin(alfa), zoom * sin(beta), zoom * cos(beta) * cos(alfa),//
		0, 0, 0,//
		0.0f, 1.0f, 0.0f);//*/
	
	gluLookAt(camX, camY , camZ,
		camX + sin(alfa)*cos(beta), camY + sin(beta), camZ + cos(alfa)*cos(beta),
		0.0f, 1.0f, 0.0f);
	
	geraIluminacao();

	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	vector<Grupo*> grupos = cena.getGrupos();

	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		(*it)->draw(time);
	}
	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	/*if (c == '+' && zoom > 1) {
		zoom -= 1;
	}if (c == '-') {
		zoom += 1;
	}

	if (c == 'a') {
		look -= 1;
	}if (c == 'd') {
		look += 1;
	}*/

	
	if (c == 'w') {
		camX += sin(alfa)*cos(beta);
		camY += sin(beta);
		camZ += cos(alfa)*cos(beta);
	}

	else if (c == 'd') {
		camX += sin(alfa - M_PI_2);
		camZ += cos(alfa - M_PI_2);
	}

	else if (c == 's') {
		camX -= sin(alfa )*cos(beta );
		camY -= sin(beta );
		camZ -= cos(alfa )*cos(beta );
	}

	else if (c == 'a') {
		camX += sin(alfa + M_PI_2);
		camZ += cos(alfa + M_PI_2);
	}

	else if (c == 'z') {
		alfa += M_PI / 64.0f;
	}

	else if (c == 'x') {
		alfa -= M_PI / 64.0f;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {

	// put code to process special keys in here
	/*switch (key) {
	case GLUT_KEY_UP:
		if (!(beta + 0.05 > (pi / 2)))
			beta += 0.05;
		break;
	case GLUT_KEY_DOWN:
		if (!(beta - 0.05 < -(pi / 2)))
			beta -= 0.05;
		break;
	case GLUT_KEY_LEFT:
		alfa -= 0.05;
		break;
	case GLUT_KEY_RIGHT:
		alfa += 0.05;
		break;
	}*/
	switch (key) {
	case GLUT_KEY_UP:
		if (!(beta + M_PI / 64.0f > (pi / 2)))
			beta += M_PI / 64.0f;
		break;
	case GLUT_KEY_DOWN:
		if (!(beta - M_PI / 64.0f < -(pi / 2)))
			beta -= M_PI / 64.0f;
		break;
	case GLUT_KEY_LEFT:
		alfa += M_PI / 64.0f;
		break;
	case GLUT_KEY_RIGHT:
		alfa -= M_PI / 64.0f;
		break;
	}
	glutPostRedisplay();
}

void processMouse(int button, int state, int x, int y) {

	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouseMoving = true;
		xAnt = x;
		yAnt = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		mouseMoving = false;
	}

	glutPostRedisplay();
}
void mouseMotion(int x, int y) {

	if (mouseMoving) {

		if (!(beta + (y - yAnt)*M_PI / 2048.0f > (pi / 2)) && !(beta + (y - yAnt)*M_PI / 2048.0f < -(pi / 2)))
			beta += (y-yAnt)*M_PI / 2048.0f;
		alfa += (x - xAnt)*M_PI / 2048.0f;
		xAnt = x;
		yAnt = y;
	}
}

int main(int argc, char** argv) {

	if (argc < 2) {
		printf("Indique um ficheiro a partir do qual se deva gerar");
		return 1;
	}
	
	const char * filename = argv[1];
	cena = xmlParser(filename);

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouse);
	glutMotionFunc(mouseMotion);

#ifndef __APPLE__
	glewInit();
#endif
	ilInit();

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	
	// init
	iniciaLuz();
	
	vector<Grupo*> grupos = cena.getGrupos();
	int tam = 0;
	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		tam += (*it)->tamanhoGrupo();
	}

	buffers = (GLuint*) malloc(tam * sizeof(GLuint));
	buffersNormal = (GLuint*) malloc(tam * sizeof(GLuint));
	buffersTextura = (GLuint*)malloc(tam * sizeof(GLuint));
	
	glGenBuffers(tam, buffers);
	glGenBuffers(tam, buffersNormal);
	glGenBuffers(tam, buffersTextura);

	int j = 0;
	for(vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++){
		j = generateBuffers((*it), j);
	}

	for (vector<Grupo*>::iterator it = grupos.begin(); it != grupos.end(); it++) {
		generateTextura(*it);
	}

	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}