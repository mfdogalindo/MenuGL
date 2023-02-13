//
//  ContentManager.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#ifndef ContentManager_hpp
#define ContentManager_hpp

#include <stdio.h>
#include "../Models/Home.hpp"
#include "../API/APIClient.hpp"
#include "./AppConfiguration.hpp"
#include "../../libs/json.hpp"
#include <vector>

#define NO_CONTENT 0
#define CONTENT_OK 1

using JSON = nlohmann::json;
using ContainerVector = std::vector<uint>;

class ContentManager{
    
    private:
        int status;
        Home home;
        AppConfiguration* apiConfig;
        void getHomeContentFromServer();
    
    public:
        ContentManager(AppConfiguration* apiConfig);
        Home getHome();
        int getStatus();
    
};

#endif /* ContentManager_hpp */
