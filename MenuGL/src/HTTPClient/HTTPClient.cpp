//
//  HTTPClient.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#include "HTTPClient.hpp"

HTTPClient::HTTPClient() {
    HTTPClient::status = http::Status::NoContent;
}

int HTTPClient::get(std::string url){
    
    try{
        
        std::string arguments;
        auto protocol = http::InternetProtocol::v4;
        nlohmann::json jsonOutput;
        
        http::Request request{url, protocol};
        
        const auto response = request.send("GET", arguments,{
            {"Content-Type", "application/json"},
            {"User-Agent", "runscope/0,1"},
            {"Accept", "application/json"}
        }, std::chrono::seconds(2));
        
        std::cout << response.status.reason << '\n';
        
        if(response.status.code == http::Status::Ok){
            std::string responseStr = std::string{response.body.begin(), response.body.end()};

            jsonOutput = nlohmann::json::parse(responseStr);
            HTTPClient::data = jsonOutput;
        }
        else {
            HTTPClient::status = response.status.code;
        }
        return 1;
    }
    catch( const http::ResponseError& e){
        std::cerr << "Request Error: " << e.what() << '\n';
        return -2;
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << '\n';
        return -1;
    }
    return 0;
};

nlohmann::json HTTPClient::getData() {
    return this->data;
}
