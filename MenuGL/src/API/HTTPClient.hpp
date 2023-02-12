//
//  HTTPClient.hpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#ifndef HTTPClient_hpp
#define HTTPClient_hpp

#include "../../libs/json.hpp"
#include "../Models/HTTPResponse.hpp"
#include <curl/curl.h>
#include <iostream>
#include <vector>

#define HTTP_STATUS_OK 200
#define HTTP_STATUS_NO_CONTENT 204

using JSON = nlohmann::json;
using String = std::string;
using ByteVector = std::vector<uint8_t>;

class HTTPClient {
    private:
        CURL *curl;
        CURLcode res;
    public:
        HTTPClient();
        HTTPResponse<JSON> getJSON(std::string url);
        HTTPResponse<ByteVector> getImage(std::string url);
};

#endif /* HTTPClient_hpp */
