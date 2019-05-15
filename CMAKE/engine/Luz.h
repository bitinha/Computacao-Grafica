#pragma once
class Luz
{
public: 
	float position[4];
	float diffuse[4];
	float ambient[4];
	float specular[4];
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
