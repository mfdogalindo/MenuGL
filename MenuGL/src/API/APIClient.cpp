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

JSON APIClient::getHome(){
    HTTPResponse<JSON> response = client.getJSON(url + "/home.json");
    std::cout << ".";
    if(response.getStatus() == HTTP_STATUS_OK){
        return response.getData();
    }
    return 0;
}

JSON APIClient::getSet(String refId){
    HTTPResponse<JSON> response = client.getJSON(url + "/sets/" + refId + ".json");
    std::cout << ".";
    if(response.getStatus() == HTTP_STATUS_OK){
        return response.getData();
    }
    return 0;
}

ByteVector APIClient::getImage(String url){
    HTTPResponse<ByteVector> response = client.getImage(url);
    std::cout << ".";
    if(response.getStatus() == HTTP_STATUS_OK){
        return response.getData();
    }
    ByteVector temp;
    return temp;
}
