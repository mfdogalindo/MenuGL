//
//  HTTPClient.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#ifndef HTTPClient_hpp
#define HTTPClient_hpp

#include "../../libs/HTTPRequest.hpp"
#include "../../libs/json.hpp"
#include <iostream>
#include <fstream>

#define HTTP_GET_OK 1

class HTTPClient {
    private:
        nlohmann::json data;
        int status;
    public:
        HTTPClient();
        int get(std::string url);
        nlohmann::json getData();
        int currentStatus();
};

#endif /* HTTPClient_hpp */
