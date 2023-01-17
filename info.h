#include <iostream>
#include <vector>

class info {

public:
    
    int getValue(void);
    void setValue(int i);
    int getNumBits();
    void setNumBits(int b);
    int getFreq();
    void setFreq(int f);
    std::string getChar();  
    void setChar(std::string c);
    std::string getBV();  
    void setBV(std::string b);
    std::vector<std::string>  charVector;    
    std::vector<std::string>  bvVector;
    std::string getCompMsg(){
        return compMsg;
    };  
    void setCompMsg(char c){
        compMsg.push_back(c);
    };
    std::string getDecodedMsg(){
        return decodedMsg;
    };  
    void setdecodedMsg(std::string b){
        decodedMsg=b;
    };
       
    std::vector<std::string> compMsgVector;

private:
    std::string compMsg;
    std::string decodedMsg;
    int value;
    int numBits;
    int frequency;
    std::string character; 
    std::string binaryValues; 
    
    
    
    
};

int info::getValue(void){
    return value;
}
void info::setValue(int i){
    value = i;
}
int info::getNumBits(void){
    return numBits;
}
void info::setNumBits(int b){
    numBits = b;
}
int info::getFreq(void){
    return frequency;
}
void info::setFreq(int f){
    frequency = f;
}
std::string info::getChar(void){
    return character;
}
void info::setChar(std::string c){
    character = c;
}
std::string info::getBV(void){
    return binaryValues;
}
void info::setBV(std::string b){
    binaryValues = b;
}
