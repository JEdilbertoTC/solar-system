#include <vector>
#include <cmath>
#include <armadillo>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "Lector.hpp"
#include "Transform.hpp"

class Planet{
public:	
	Planet(Lector& objetoOBJ);
	~Planet();
	void draw();
	void setColor(const float &R, const float &G, const float &B);
	void setScale(float x, float y, float z);
	void setTranslation(float,float,float);
	void setVelocity(float);
private:
	Lector* objectoOBJ;
	Transform transform = Transform();
	fmat scale;
	fmat transf;
	fmat translation;
	float R, G, B;
	float velocity;
	float angle;
};