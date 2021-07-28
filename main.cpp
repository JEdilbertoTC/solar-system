#include <armadillo>
#include <cmath>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "include/Lector.hpp"
#include "include/Planet.hpp"

using namespace arma;

int solarSystem();

int main(){
    solarSystem();
}

int solarSystem(){

    GLFWwindow* window;
    if(!glfwInit()){
        fprintf( stderr, "Fallo al inicializar GLFW\n" );
        getchar();
        return -1;
    }
    window = glfwCreateWindow(1024, 600, "Caida en Espiral", NULL, NULL);

    if(!window){
        fprintf( stderr, "Fallo al abrir la ventana de GLFW.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }

    const string archivoPelota = "models/roca.obj";
    Lector *planetReader = new Lector(archivoPelota);

    Planet sun(*planetReader);
    Planet mercury(*planetReader);
    Planet venus(*planetReader);
    Planet earth(*planetReader);
    Planet mars(*planetReader);
    Planet jupiter(*planetReader);
    Planet saturn(*planetReader);
    Planet uranus(*planetReader);
    Planet neptune(*planetReader);

    sun.setTranslation(0,0,0);    
    mercury.setTranslation(-0.25,0,0);
    venus.setTranslation(-0.5,0,0);
    earth.setTranslation(-0.75,0,0);
    mars.setTranslation(-1.1,0,0);
    jupiter.setTranslation(-6.5,0,0);
    saturn.setTranslation(-13,0,0);
    uranus.setTranslation(-26,0,0);
    neptune.setTranslation(-40,0,0);

    sun.setVelocity(0.0f);  
    mercury.setVelocity(0.05f);  
    venus.setVelocity(0.15f);  
    earth.setVelocity(0.12f);  
    mars.setVelocity(0.25f);  
    jupiter.setVelocity(0.7f);  
    saturn.setVelocity(0.6f);
    uranus.setVelocity(1.0f);
    neptune.setVelocity(1.7f); //164

    sun.setScale(0.182f, 0.182f, 0.182f);
    mercury.setScale(0.017f, 0.017f, 0.017f);
    venus.setScale(0.033f, 0.033f, 0.033f);
    earth.setScale(0.182f, 0.182f, 0.182f);
    mars.setScale(0.08f, 0.08f, 0.08f);
    jupiter.setScale(0.4f, 0.4f, 0.4f);
    saturn.setScale(0.024f, 0.024f, 0.024f);
    uranus.setScale(0.2f, 0.2f, 0.2f);
    neptune.setScale(0.1f, 0.1f, 0.1f);

    sun.setColor(1.0f, 0.54f, 0.15f);//
    mercury.setColor(0.39f, 0.39f, 0.39f);//
    venus.setColor(0.87f, 0.87f, 0.08f);//
    earth.setColor(0.25f, 0.67f, 0.68f);//
    mars.setColor(0.63f, 0.098f, 0.098f);//
    jupiter.setColor(0.84f, 0.79f, 0.61f);//
    saturn.setColor(0.552f,0.623f,0.666f);//
    uranus.setColor(0.19f, 0.59f, 0.26f);//
    neptune.setColor(0.24f, 0.37f, 0.54f);//

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

//  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ar = width / height;

//  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -100.0, 100.0);

//  Proyección en perspectiva
    //glFrustum(-1.0, 1.0, -1.0, -1.0, 3.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    frowvec eye = {0.0f, 0.0f, 10.0f}; // 0 0 10
    frowvec camera = {0.0f, 0.0f, 5.0f};
    frowvec viewUp = {0.0f, 1.0f, 0.0f}; //0 1 0

    do {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt(eye[0], eye[1], eye[2], camera[0], camera[1], camera[2], viewUp[0], viewUp[1], viewUp[2]);

        sun.draw();
        mercury.draw(); 
        venus.draw(); 
        earth.draw(); 
        mars.draw(); 
        jupiter.draw(); 
        saturn.draw(); 
        uranus.draw(); 
        neptune.draw(); 

        glRenderMode(GL_RENDER);
        glfwSwapBuffers(window);
        glfwPollEvents();

    } while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
    glfwTerminate();
    return 0;
}