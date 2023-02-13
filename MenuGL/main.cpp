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

#include "ViewEvents.h"

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10000, timer, 0);
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
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow(appTitle.c_str());
    glutDisplayFunc( HomeLoop );
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboardEvent);
    glutMainLoop();
}
