//
//  CommonViews.h
//  MenuGL
//
//  Created by Manuel Galindo on 13/02/23.
//

#ifndef CommonViews_h
#define CommonViews_h

#include "Common.h"
#include <ctime>

void drawAppStatus(String msg){
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(50, 20, GLUT_BITMAP_HELVETICA_18, msg);
}

void drawTitle(String* appTitle){
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(50,h-50,GLUT_BITMAP_HELVETICA_18, *appTitle);
}

void drawTime(int* window_height,int* window_width){
    glColor3f(1.0, 1.0, 1.0);
    time_t now = time(0);
    char date_string[100];
    strftime(date_string, 100, "%a %b %d %H:%M %Y", localtime(&now));
    String time_string(date_string);
    renderBitmapString(*window_width-250,*window_height-50,GLUT_BITMAP_HELVETICA_18, time_string);
}

void drawSquare(int* cursor_x, int* cursor_y)
{
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(*cursor_x, *cursor_y);
    glVertex2i(*cursor_x + CURSOR_SPACING, *cursor_y);
    glVertex2i(*cursor_x + CURSOR_SPACING, *cursor_y+15);
    glVertex2i(*cursor_x, *cursor_y + 15);
    glEnd();
}

#endif /* CommonViews_h */
