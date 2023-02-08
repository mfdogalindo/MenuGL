//
//  main.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#include "main.hpp"

int main(int argc, const char * argv[]) {
    
    if(argc < 2){
        std::cerr << "No URL parameter" << '\n';
        return -1;
    }
    
    AppConfiguration appConfig;
    appConfig.setApiUrl(std::string{argv[1]});
    
    ContentManager* contentManager = new ContentManager(&appConfig);

    contentManager->getHome();
    
    return 0;
}
