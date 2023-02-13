//
//  Views.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 13/02/23.
//

#ifndef Views_h
#define Views_h

# define M_PIl          3.141592653589793238462643383279502884L

#include "Common.h"
#include "CommonViews.h"
#include "Home.hpp"

#include <stdio.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <CoreFoundation/CoreFoundation.h>
#import <CoreGraphics/CoreGraphics.h>



void renderImage(ByteVector imgData){
    try{
        CFDataRef cfImgData = CFDataCreateWithBytesNoCopy(kCFAllocatorDefault, imgData.data(), imgData.size(), kCFAllocatorNull);
        CGDataProviderRef provider = CGDataProviderCreateWithCFData(cfImgData);
        CGImageRef image = CGImageCreateWithJPEGDataProvider(provider, NULL, false, kCGRenderingIntentDefault);
        
        int width = (int)CGImageGetWidth(image);
        int height = (int)CGImageGetHeight(image);
        
        CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
        unsigned char *rawData = (unsigned char*)calloc(height * width * 4, sizeof(unsigned char));
        CGContextRef context = CGBitmapContextCreate(rawData, width, height, 8, 4 * width, colorSpace, kCGImageAlphaPremultipliedLast);
        CGContextTranslateCTM( context, 0, height ) ;
        CGContextScaleCTM(context, 1.0, -1.0);
        CGColorSpaceRelease(colorSpace);
        CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);
        
        glRasterPos2i(window_width/2 - width/2, 0);
        glDrawPixels(width, height,  GL_RGBA , GL_UNSIGNED_BYTE, rawData);
        free(rawData);
        CGContextRelease(context);
    }
    catch (const char* msg){
        renderBitmapString(window_width*2/3,window_height/2,GLUT_BITMAP_HELVETICA_18, "No image");
    }
    
}


void drawCollectionsMenu(){
    glColor3f(1.0, 1.0, 1.0);
    cursor_max_y = window_height-CURSOR_START;
    if(collectionsMap.size() == 0){
        for(auto&container : contentManager->getHome().getContainers()){
            collectionsMap.insert({container.first, container.second.name});
            renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, container.second.name);
            cursor_max_y-= CURSOR_SPACING;
        }
    }
    else{
        for(auto&collection : collectionsMap){
            renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, collection.second);
            cursor_max_y-= CURSOR_SPACING;
        }
    }
    
}

void drawItemsCollectionMenu(){
    glColor3f(1.0, 1.0, 1.0);
    cursor_max_y = window_height-CURSOR_START;
    renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, "< RETURN");
    cursor_max_y-= CURSOR_SPACING;
    
    if(itemsMap.size() == 0){
        ContainerElement container = contentManager->getHome().getContainer(selected_collection);
        for(auto&elementId : container.elementsIndex) {
            ContentElement element = contentManager->getHome().getElement(elementId);
            itemsMap.insert({elementId, element.name});
            renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, element.name);
            cursor_max_y-= CURSOR_SPACING;
        }
    }else{
        for(auto&element : itemsMap) {
            renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, element.second);
            cursor_max_y-= CURSOR_SPACING;
        }
    }
    
}

void drawItemDetails(){
    if(selected_item > 0){
        String type = "Series";
        if(itemSelectedDetails.isMovie){type = "Movie";}
        else if(itemSelectedDetails.isCollection){type = "Collection";}
        cursor_max_y = window_height-CURSOR_START;
        renderBitmapString(150,cursor_max_y,GLUT_BITMAP_HELVETICA_18, "< RETURN");
        cursor_max_y-= CURSOR_SPACING;
        
        renderBitmapString(150,window_height/2,GLUT_BITMAP_HELVETICA_18, "Type of content: ");
        renderBitmapString(200,(window_height/2) - CURSOR_SPACING,GLUT_BITMAP_HELVETICA_18,type);
        
        if(!itemSelectedDetails.hasImage){
            renderBitmapString(window_width*2/3,window_height/2,GLUT_BITMAP_HELVETICA_18, "No image");
        }else{
            renderImage(itemSelectedDetails.imageBytes);
        }
    }
}


#endif /* Views_h */
