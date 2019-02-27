#include <stdio.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void writeSphereFile(string forma, const char* radius, const char* slices, const char* stacks, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		file << "Forma: " + forma;
		file << "\nRadius: " + string(radius);
		file << "\nSlices: " + string(slices);
		file << "\nStacks: " + string(stacks);
	}
	else printf("File not opened\n");
	file.close();
}

void writePlaneFile(string forma, const char* x, const char* z, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		file << "Forma: " + forma;
		file << "\nX: " + string(z);
		file << "\nZ: " + string(x);
	}
	else printf("File not opened\n");
	file.close();
}

void writeBoxFile(string forma, const char* x, const char* y, const char* z, const char* divisions, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		file << "Forma: " + forma;
		file << "\nX: " + string(x);
		file << "\nY: " + string(y);
		file << "\nZ: " + string(z);
		file << "\nDivisions: " + string(divisions);
	}
	else printf("File not opened\n");
	file.close();
}

void writeConeFile(string forma, const char* radius, const char* height, const char* slices, const char* stacks, string name) {
	fstream file;
	file.open(name, ios::out);
	if (file.is_open()) {
		file << "Forma: " + forma;
		file << "\nBottom Radius: " + string(radius);
		file << "\nHeight: " + string(height);
		file << "\nSlices: " + string(slices);
		file << "\nStacks: " + string(stacks);
	}
	else printf("File not opened\n");
	file.close();
}

int main(int argc, const char* argv[]) {
	string forma = string(argv[1]);
	string fileName = string(argv[argc - 1]);
	if (!forma.compare("sphere") && argc == 6) { writeSphereFile(forma, argv[2], argv[3], argv[4], fileName); }
	else if (!forma.compare("plane") && argc == 5) { writePlaneFile(forma, argv[2], argv[3], fileName); }
	else if (!forma.compare("box") && argc == 7) { writeBoxFile(forma, argv[2], argv[3], argv[4], argv[5], fileName); }
	else if (!forma.compare("cone") && argc == 7) { writeConeFile(forma, argv[2], argv[3], argv[4], argv[5], fileName); }
	return 1;
}
