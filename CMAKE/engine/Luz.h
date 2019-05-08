#pragma once
class Luz
{
public: 
	float position[3];
	float diffuse[3];
	float ambient[3];
	float specular[3];
	Luz();
	Luz(float p[3], float diff[3], float s[3], float a[3]);
	~Luz();
	virtual float* getPosition();
	void setPosition(float p[3]);
	float* getDiffuse();
	void setDiffuse(float d[3]);
	float* getSpecular();
	void setSpecular(float s[3]);
	float* getAmbient();
	void setAmbient(float a[3]);
	virtual void ilumina(int i);
};