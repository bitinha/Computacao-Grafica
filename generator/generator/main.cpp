#define _USE_MATH_DEFINES
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <math.h>

float pi = M_PI;

using namespace std;

void writeSphereFile(string forma, const char* r, const char* sl, const char* st, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		float a = 0;
		float radius = atof(r);
		float slices = atof(sl);
		float stacks = atof(st);
		for (int i = 0; i < slices; i++) {
			a = i * 2 * pi / slices;
			float gama = (i + 1)* 2 * pi / slices;
			float b = pi / 2 - (pi / (stacks));
			
			file << " " << 0 << " " << radius << " " << 0 << "\n";
			file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";
			file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";

			b = -b;

			file << " " << 0 << " " << -radius << " " << 0 << "\n";
			file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
			file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";

			for (int j = 1; j < stacks - 1; j++) {
				b = pi / 2 - (j * pi / (stacks));
				float teta = pi / 2 - ((j + 1) * pi / (stacks));

				file << " " << radius * cos(b) * sin(a) << " " << radius * sin(b) << " " << radius * cos(b) * cos(a) << "\n";
				file << " " << radius * cos(teta) * sin(a) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(a) << "\n";
				file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";

				file << " " << radius * cos(b) * sin(gama) << " " << radius * sin(b) << " " << radius * cos(b) * cos(gama) << "\n";
				file << " " << radius * cos(teta) * sin(a) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(a) << "\n";
				file << " " << radius * cos(teta) * sin(gama) << " " << radius * sin(teta) << " " << radius * cos(teta) * cos(gama) << "\n";

			}
		}
	}
	else printf("File not opened\n");
	file.close();
}

void writePlaneFile(string forma, const char* x, string name) {
	fstream file; //Nome do ficheiro no qual vão ser escritos os vértices
	file.open(name, ios::out);
	if (file.is_open()) {
		float size = atof(x) / 2; //Módulo das coordenadas x, z dos vertices dos triangulos
		file << " " << -size << " " << 0 << " " << - size << "\n"; //Ponto A
		file << " " <<  size  << " " << 0 << " " <<  size << "\n"; //Ponto B
		file << " " <<  size  << " " << 0 << " " << -size << "\n"; //Ponto C
		
		file << " " <<  size  << " " << 0 << " " <<  size << "\n"; //Ponto B
		file << " " << -size << " " << 0 << " " <<  -size << "\n"; //Ponto A
		file << " " << -size << " " << 0 << " " <<   size << "\n"; //Ponto D
	}
	else printf("File not opened\n");
	file.close();
}

void writeBoxFile(string forma, const char* sizeX, const char* sizeY, const char* sizeZ, const char* divisions, string name) {
	fstream file;
	file.open(name, ios::out);
	float x = atof(sizeX) / 2;
	float y = atof(sizeY) / 2;
	float z = atof(sizeZ) / 2;
	float d = atof(divisions);
	if (file.is_open()) {

		for (float i = 0; i < d; i++) {
			for (float j = 0; j < d; j++) {

				//Tras
				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";
				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";

				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << -z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << -z << "\n";
				//Frente
				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";

				file << " " << -x + (j / d) * (x * 2) << " " << -y + (i / d) * (y * 2) << " " << z << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";
				file << " " << -x + (j / d) * (x * 2) << " " << -y + ((i + 1) / d) * (y * 2) << " " << z << "\n";

				//Baixo
				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";

				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -x + (j / d) * (x * 2) << " " << -y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				//Cima
				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";

				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x + (j / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -x + ((j + 1) / d) * (x * 2) << " " << y << " " << -z + ((i + 1) / d) * (z * 2) << "\n";

				//Esquerda
				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";

				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << -x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << -x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				//Direita
				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";

				file << " " << x << " " << -y + (j / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + (i / d) * (z * 2) << "\n";
				file << " " << x << " " << -y + ((j + 1) / d) * (y * 2) << " " << -z + ((i + 1) / d) * (z * 2) << "\n";
			}
		}

	}
	else printf("File not opened\n");
	file.close();
}

void writeConeFile(string forma, const char* r, const char* h, const char* sl, const char* st, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		float radius = atof(r);
		float height = atof(h);
		float slices = atoi(sl);
		float stacks = atoi(st);
		float slice = 2 * M_PI / slices; // Angulo de uma fatia
		float stackH = height / stacks; // Altura de uma camada
		float stackR = radius / stacks; // "Largura" de uma camada

		for (int i = 0; i < slices; i++) { // Itera pelas fatias
			float angle1 = i * slice;
			float angle2 = (i + 1) * slice;

			//Cria a base
			file << " " << 0 << " " << 0 << " " << 0 << "\n";
			file << " " << radius * cos(angle1) << " " << 0 << " " << radius * sin(angle1) << "\n";
			file << " " << radius * cos(angle2) << " " << 0 << " " << radius * sin(angle2) << "\n";

			for (int j = 0; j < stacks - 1; j++) { //Itera pelas camadas ; Na ultima camada vai desenhar um por cima do outro
				float lowerH = j * stackH; // Altura na camada inferior
				float upperH = (j + 1) * stackH; // Altura na camada superior
				float lowerR = radius - stackR * j;// Raio para a camada inferior
				float upperR = radius - stackR * (j + 1);// Raio para a camada superior

				file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
				file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";
				file << " " << lowerR * cos(angle1) << " " << lowerH << " " << lowerR * sin(angle1) << "\n";


				file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
				file << " " << upperR * cos(angle2) << " " << upperH << " " << upperR * sin(angle2) << "\n";
				file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";

			}
			// Acabar com os triangulos do bico
			float lowerH = (stacks-1) * stackH; // Altura na camada inferior
			float upperH = stacks * stackH; // Altura na camada superior
			float lowerR = radius - stackR * (stacks - 1);// Raio para a camada inferior
			float upperR = radius - stackR * stacks;// Raio para a camada superior

			file << " " << upperR * cos(angle1) << " " << upperH << " " << upperR * sin(angle1) << "\n";
			file << " " << lowerR * cos(angle2) << " " << lowerH << " " << lowerR * sin(angle2) << "\n";
			file << " " << lowerR * cos(angle1) << " " << lowerH << " " << lowerR * sin(angle1) << "\n";
		}
	}
	else printf("File not opened\n");
	file.close();
}

int main(int argc, const char* argv[]) {
	string forma = string(argv[1]);
	string fileName = string(argv[argc - 1]);
	if (!forma.compare("sphere") && argc == 6) { writeSphereFile(forma, argv[2], argv[3], argv[4], fileName); }
	else if (!forma.compare("plane") && argc == 4) { writePlaneFile(forma, argv[2], fileName); }
	else if (!forma.compare("box") && argc == 7) { writeBoxFile(forma, argv[2], argv[3], argv[4], argv[5], fileName); }
	else if (!forma.compare("cone") && argc == 7) { writeConeFile(forma, argv[2], argv[3], argv[4], argv[5], fileName); }
	return 1;
}
