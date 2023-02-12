//
//  APIClient.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#ifndef APIClient_hpp
#define APIClient_hpp

#include "./HTTPClient.hpp"
#include "../../libs/json.hpp"

class APIClient{
private:
    std::string url;
    HTTPClient client;
public:
    APIClient(std::string url);
    nlohmann::json getHome();
    nlohmann::json getSet(String refId);
    ByteVector getImage(String url);
};

#endif /* APIClient_hpp */
