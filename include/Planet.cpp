#include "Planet.hpp"

#define PI 3.14159265

using namespace arma;

Planet::Planet(Lector& objectoOBJ){
	this->objectoOBJ = &objectoOBJ;
	this->objectoOBJ->lector();
    this->angle = 0.0f;
}

Planet::~Planet(){}

void Planet::draw(){
	
    vector <Vertex> verticesObjeto = objectoOBJ->getSortVertices(); //getfacesverts //Regresa todos los vertices
    vector <Vertex>verticesDibujar;

    this->angle = (this->angle < 360.0) ? this->angle+this->velocity : 0.0f;
    this->transf = transform.R(0,1,0, this->angle);
    this->transf *= this->translation;
    this->transf *= this->scale;
    
    for (unsigned int i=0; i<verticesObjeto.size(); i++ ){
        fcolvec v = {verticesObjeto.at(i).homogenea()}; //.h()
        fcolvec vp = transf * v;
        Vertex rv = Vertex();
        frowvec vp2 = trans(vp);
        rv.setCoordenadas(vp2.at(0),vp2.at(1),vp2.at(2)); // setvalues
        verticesDibujar.push_back(rv);
    } 

    glColor3f(this->R, this->G, this->B);
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0; i<verticesDibujar.size(); i++ ) {
        frowvec vert = {verticesDibujar[i].getX(),verticesDibujar[i].getY(),verticesDibujar[i].getZ()}; //getvalues
        glVertex3f(vert[0], vert[1], vert[2]);
    }
    glEnd();
}

void Planet::setColor(const float &R, const float &G, const float &B){
	this->R = R;
	this->G = G;
	this->B = B;
}

void Planet::setScale(float x, float y, float z){
    this->scale = transform.S(x,y,z);
}

void Planet::setTranslation(float x,float y,float z){
    this->translation = transform.T(x,y,z);
}

void Planet::setVelocity(float velocity){
    this->velocity = velocity;
}