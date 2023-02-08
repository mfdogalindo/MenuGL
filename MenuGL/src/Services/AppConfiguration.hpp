//
//  AppConfiguration.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#ifndef AppConfiguration_hpp
#define AppConfiguration_hpp

#include <iostream>

class AppConfiguration {
private:
    std::string apiUrl;

public:
    void setApiUrl(std::string url);
    std::string getApiUrl();
};

#endif /* AppConfiguration_hpp */
