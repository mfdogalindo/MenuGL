//
//  ViewEvents.h
//  MenuGL
//
//  Created by Manuel Galindo on 13/02/23.
//

#ifndef ViewEvents_h
#define ViewEvents_h

#include "Views.hpp"
#include "Common.h"

void pickEvent(int* app_status, int* cursor_y){
    switch(*app_status){
        case STAT_MENU_DOWNLOADED:{
            int cursor_scan = window_height-CURSOR_START;
            for(auto&collection : collectionsMap){
                if(cursor_scan == *cursor_y){
                    selected_collection = collection.first;
                    *cursor_y = window_height-CURSOR_START;
                    std::cout << "Selected collection: " << collection.second << "\n";
                    appTitle = collection.second;
                    *app_status = STAT_COLLECTION_SELECTED;
                    break;
                }
                cursor_scan-= CURSOR_SPACING;
            }
            break;
        }
        case STAT_COLLECTION_SELECTED:{
            int cursor_scan = window_height-CURSOR_START;
            if(cursor_scan == *cursor_y){
                appTitle = contentManager->getHome().getTitle();
                selected_collection = -1;
                *app_status = STAT_MENU_DOWNLOADED;
                itemsMap.clear();
                *cursor_y = window_height-CURSOR_START;
                break;
            }
            cursor_scan-= CURSOR_SPACING;
            for(auto&item : itemsMap){
                if(cursor_scan == *cursor_y){
                    itemSelectedDetails = contentManager->getHome().getElement(item.first);
                    std::cout << "Selected item: " << item.second << "\n";
                    selected_item = item.first;
                    appTitle = item.second;
                    *app_status= STAT_ITEM_SELECTED;
                    *cursor_y = window_height-CURSOR_START;
                    break;
                }
                cursor_scan-= CURSOR_SPACING;
            }
            break;
        }
        case STAT_ITEM_SELECTED:{
            int cursor_scan = window_height-CURSOR_START;
            if(cursor_scan == *cursor_y){
                selected_item = -1;
                appTitle = collectionsMap[selected_collection];
                *app_status = STAT_COLLECTION_SELECTED;
                *cursor_y = window_height-CURSOR_START;
                break;
            }
        }
    }
}

void keyboardEvent(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            cursor_y += (window_height-CURSOR_START > cursor_y) ? 30:0;
            break;
        case GLUT_KEY_DOWN:
            cursor_y -= (cursor_y > cursor_max_y+CURSOR_SPACING) ? 30:0;
            break;
//        case GLUT_KEY_LEFT:
//            cursor_x -= 10;
//            break;
//        case GLUT_KEY_RIGHT:
//            cursor_x += 10;
//            break;
        case 13:
            pickEvent(&app_status, &cursor_y);
            break;
    }
    glutPostRedisplay();
}

void thGetHome(){
    app_status = STAT_MENU_DOWNLOADING;
    contentManager->getHome();
    app_status = contentManager->getStatus() == CONTENT_OK ? STAT_MENU_DOWNLOADED : STAT_MENU_NO_CONTENT;
    appTitle = contentManager->getHome().getTitle();
    glutPostRedisplay();
}



void HomeLoop(){
    initGUI();
    switch(app_status){
        case STAT_ON_STARTUP:
            drawAppStatus("Welcome");
            appThreads.emplace_back(std::thread(thGetHome));
            break;
        case STAT_MENU_DOWNLOADING:{
            drawAppStatus("Downloading Menu Content");
            cursor_y = window_height-CURSOR_START;
            break;
        }
        case STAT_MENU_DOWNLOADED:
            drawSquare(&cursor_x, &cursor_y);
            drawTime(&window_height, &window_width);
            drawTitle(&appTitle);
            drawCollectionsMenu();
            drawAppStatus("Menu Downloaded");
            break;
        case STAT_COLLECTION_SELECTED:
            drawSquare(&cursor_x, &cursor_y);
            drawTitle(&appTitle);
            drawTime(&window_height, &window_width);
            drawItemsCollectionMenu();
            drawAppStatus("Collection selected");
            break;
        case STAT_ITEM_SELECTED:
            drawSquare(&cursor_x, &cursor_y);
            drawTitle(&appTitle);
            drawTime(&window_height, &window_width);
            drawItemDetails();
            drawAppStatus("Item selected");
            break;
        default:
            drawAppStatus("Unhandled Error");
    }
    
    glutSwapBuffers();
}

#endif /* ViewEvents_h */
