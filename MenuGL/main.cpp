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


void renderBitmapString(float x, float y, void *font, std::string str)
{
    glRasterPos2f(x, y);
    for (std::string::iterator i = str.begin(); i != str.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}


void drawAppStatus(String msg){
    //int w = glutGet(GLUT_WINDOW_WIDTH);
    //int h = glutGet(GLUT_WINDOW_HEIGHT);
        
    glColor3f(1.0, 1.0, 1.0);
    //glRasterPos2i(400, 300);
    //gluOrtho2D(0, w, 0, h);
    glutPostRedisplay();
    //float x = 0;
    //float y = 100;
    //float z = 0;
    //float fontSize = 24.0f;

    // Ancho y alto de la ventana

    //x = (w - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, (unsigned char *)msg.c_str())) / 2;
    //y = (h / 2) + (fontSize * z);
    //z -= 1.0f;

    // Muestra la palabra
    renderBitmapString(50, 20, GLUT_BITMAP_HELVETICA_18, msg);

}

#define STAT_ON_STARTUP 0
#define STAT_MENU_DOWNLOADING 1
#define STAT_MENU_DOWNLOADED 2
#define STAT_MENU_NO_CONTENT 3

volatile int app_status = STAT_ON_STARTUP;

std::vector<std::thread> threads;

String appTitle = "MenuFlixMax+";

void thGetHome(){
    app_status = STAT_MENU_DOWNLOADING;
    contentManager->getHome();
    app_status = contentManager->getStatus() == CONTENT_OK ? STAT_MENU_DOWNLOADED : STAT_MENU_NO_CONTENT;
    appTitle = contentManager->getHome().getTitle();
}

void drawMenu(){
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1.0, 1.0, 1.0);
    
    // contentManager->getHome().getContainers()
    int offset=h-150;
    for(auto&container : contentManager->getHome().getContainers()){
        renderBitmapString(150,offset,GLUT_BITMAP_HELVETICA_18, container.second.name);
        offset-=30;
    }
}


void drawTitle()
{
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(50,h-50,GLUT_BITMAP_HELVETICA_18, appTitle);
}

void HomeLoop(){
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glBegin(GL_QUADS);
    glColor3f(0.05, 0.0, 0.3);
    glVertex2f(0, 0);
    glVertex2f(w, 0);
    glColor3f(0.01, 0.0, 0.1);
    glVertex2f(w, h);
    glVertex2f(0, h);
    glEnd();
    
    
    switch(app_status){
        case STAT_ON_STARTUP:
            drawAppStatus("Welcome");
            threads.emplace_back(std::thread(thGetHome));
            break;
        case STAT_MENU_DOWNLOADING:
            drawAppStatus("Downloading Menu Content");
            break;
        case STAT_MENU_DOWNLOADED:
            drawTitle();
            drawMenu();
            drawAppStatus("Menu Downloaded");
            break;
        default:
            drawAppStatus("Unhandled Error");
    }

    glutSwapBuffers();
}


int main(int argc,  char** argv) {
    
    if(argc < 2){
        std::cerr << "No URL parameter" << '\n';
        return -1;
    }

    appConfig.setApiUrl(std::string{argv[1]});
    contentManager = new ContentManager(&appConfig);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow(appTitle.c_str());
    glutDisplayFunc( HomeLoop);
    glutMainLoop();
}
