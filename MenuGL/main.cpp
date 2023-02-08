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
    
    std::string url = std::string{argv[1]};
    HTTPClient client;
    
    int status = client.get(url);
    if(status == HTTP_GET_OK){
        nlohmann::json data = client.getData();
        std::cout << data;
    }
    
    return 0;
}
