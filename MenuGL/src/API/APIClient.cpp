//
//  APIClient.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 8/02/23.
//

#include "APIClient.hpp"

APIClient::APIClient(std::string url){
    this->url = url;
}

nlohmann::json APIClient::getHome(){
    int status = client.get(url + "/home.json");
    if(status == HTTP_GET_OK){
        return client.getData();
    }
    return 0;
}

nlohmann::json APIClient::getSet(std::string refId){
    int status = client.get(url + "/sets/" + refId + ".json");
    if(status == HTTP_GET_OK){
        return client.getData();
    }
    return 0;
}
