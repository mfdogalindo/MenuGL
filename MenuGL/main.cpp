//
//  main.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#include "main.hpp"
#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <chrono>
#include <thread>

AppConfiguration appConfig;
ContentManager* contentManager;


void displayMessage(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void renderBitmapString(float x, float y, void *font, std::string str)
{
    glRasterPos2f(x, y);
    for (std::string::iterator i = str.begin(); i != str.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}


void updateMessage(String msg){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glutPostRedisplay();
    float x = 0;
    float y = 0;
    float z = 0;
    float fontSize = 24.0f;

    // Ancho y alto de la ventana
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    x = (w - glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char *)msg.c_str())) / 2;
    y = (h / 2) + (fontSize * z);
    z -= 1.0f;

    // Muestra la palabra
    renderBitmapString(x, y, GLUT_BITMAP_TIMES_ROMAN_24, msg);
    glutSwapBuffers();
}

#define STAT_ON_STARTUP 0
#define STAT_MENU_DOWNLOADING 1
#define STAT_MENU_DOWNLOADED 2
#define STAT_MENU_NO_CONTENT 3

volatile int app_status = STAT_ON_STARTUP;

std::vector<std::thread> threads;

void thGetHome(){
    app_status = STAT_MENU_DOWNLOADING;
    contentManager->getHome();
    app_status = contentManager->getStatus() == CONTENT_OK ? STAT_MENU_DOWNLOADED : STAT_MENU_NO_CONTENT;
}

void HomeLoop(){
    switch(app_status){
        case STAT_ON_STARTUP:
            updateMessage("Welcome");
            threads.emplace_back(std::thread(thGetHome));
            break;
        case STAT_MENU_DOWNLOADING:
            updateMessage("Downloading");
            break;
        case STAT_MENU_DOWNLOADED:
            updateMessage("Downloaded :)");
            break;
        default:
            updateMessage("Menu err :(");
    }

}


int main(int argc,  char** argv) {
    
    if(argc < 2){
        std::cerr << "No URL parameter" << '\n';
        return -1;
    }

    appConfig.setApiUrl(std::string{argv[1]});
    contentManager = new ContentManager(&appConfig);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Texto con OpenGL y GLUT");
    glutDisplayFunc( HomeLoop);
    glutMainLoop();
}
