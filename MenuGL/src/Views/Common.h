//
//  Common.h
//  MenuGL
//
//  Created by Manuel Galindo on 13/02/23.
//

#ifndef Common_h
#define Common_h

#define CURSOR_START 150
#define CURSOR_SPACING 30

#define STAT_ON_STARTUP 0
#define STAT_MENU_DOWNLOADING 1
#define STAT_MENU_DOWNLOADED 2
#define STAT_MENU_NO_CONTENT 3
#define STAT_COLLECTION_SELECTED 4
#define STAT_ITEM_SELECTED 5

int app_status = STAT_ON_STARTUP;
AppConfiguration appConfig;
ContentManager* contentManager;
std::vector<std::thread> appThreads;

std::map<uint, String> collectionsMap;
std::map<uint, String> itemsMap;

ContentElement itemSelectedDetails;

int cursor_x = 100;
int cursor_y = 100;
int cursor_min_y = cursor_y;
int cursor_max_y = cursor_y + CURSOR_SPACING;
int window_width = 1280;
int window_height = 720;
String appTitle = "MenuFlixMax+";

uint selected_collection = 0;
uint selected_item = 0;

void initGUI(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    window_width = glutGet(GLUT_WINDOW_WIDTH);
    window_height = glutGet(GLUT_WINDOW_HEIGHT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window_width, 0, window_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    
    glBegin(GL_QUADS);
    glColor3f(0.05, 0.0, 0.3);
    glVertex2f(0, 0);
    glVertex2f(window_width, 0);
    glColor3f(0.01, 0.0, 0.1);
    glVertex2f(window_width, window_height);
    glVertex2f(0, window_height);
    glEnd();
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


#endif /* Common_h */
