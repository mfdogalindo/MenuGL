//
//  HTTPJSONResponse.hpp
//  MenuGL
//
//  Created by Manuel on 11/02/23.
//

#ifndef HTTPJSONResponse_hpp
#define HTTPJSONResponse_hpp

#include <stdio.h>
#include "../../libs/json.hpp"

using JSON = nlohmann::json;

template <typename T>

class HTTPResponse {
private:
    int status;
    T data;
    
public:
    
    void setStatus(int status){
        this->status = status;
    }
    
    int getStatus(){
        return this->status;
    }
    
    void setData(T input){
        this->data = input;
    }
    
    T getData(){
        return this->data;
    }
    
};

#endif /* HTTPJSONResponse_hpp */
