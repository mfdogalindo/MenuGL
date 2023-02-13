//
//  HTTPClient.cpp
//  MenuGL
//
//  Created by Manuel Galindo on 7/02/23.
//

#include "HTTPClient.hpp"

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

HTTPClient::HTTPClient() {

}

HTTPResponse<JSON> HTTPClient::getJSON(std::string url){
    
    try{
        String readBuffer;
        JSON jsonOutput;
        this->curl = curl_easy_init();
        curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, 3);
        res = curl_easy_perform(this->curl);
        int http_code = 0;
        curl_easy_getinfo (this->curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(this->curl);
        
        ByteVector vec(readBuffer.begin(), readBuffer.end());
        if(http_code == HTTP_STATUS_OK){
            jsonOutput = JSON::parse(readBuffer);
        }
        curl_global_cleanup();
        return HTTPResponse<JSON>(http_code, jsonOutput);
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << '\n';
        return HTTPResponse<JSON>(-1, 0);
    }
    return HTTPResponse<JSON>(0, 0);
};


HTTPResponse<ByteVector> HTTPClient::getImage(String url){
    ByteVector temp;
    try{
        String readBuffer;
        this->curl = curl_easy_init();
        curl_easy_setopt(this->curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(this->curl, CURLOPT_TIMEOUT, 3);
        res = curl_easy_perform(this->curl);
        int http_code = 0;
        curl_easy_getinfo (this->curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(this->curl);
        
        ByteVector vec(readBuffer.begin(), readBuffer.end());
        curl_global_cleanup();
        return HTTPResponse<ByteVector>(http_code, vec);
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << '\n';
        return HTTPResponse<ByteVector>(-1, temp);
    }
    return HTTPResponse<ByteVector>(0, temp);
};
