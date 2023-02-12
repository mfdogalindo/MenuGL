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

using JSON = nlohmann::json;
using ContainerVector = std::vector<uint>;

class ContentManager{
    
    private:
        Home home;
        AppConfiguration* apiConfig;
    
    public:
        ContentManager(AppConfiguration* apiConfig);
        void getHome();
    
};

#endif /* ContentManager_hpp */
