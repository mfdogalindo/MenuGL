//
//  HTTPResponse.hpp
//  MenuGL
//
//  Created by Manuel on 11/02/23.
//

#ifndef HTTPResponse_hpp
#define HTTPResponse_hpp

template <typename T>

class HTTPResponse {
private:
    int status;
    T data;
    
public:
    
    HTTPResponse(int status, T data){
        this->status = status;
        this->data = data;
    }
    
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

#endif /* HTTPResponse_hpp */
