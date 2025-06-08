#pragma once
#include <string>

class imageYUEE {
private:
    int rows;
    int cols;
    unsigned char* pixelValues;       
    unsigned char* pixelProcessed;    

public:
    imageYUEE(std::string fname);     
    int imageProc(int Mode);          
    int imageWrite(std::string fname);
    ~imageYUEE();                     
};
 