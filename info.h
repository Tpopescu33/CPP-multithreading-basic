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
       
    std::vector<std::string> compMsgVector;

private:
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
struct info1 {
    
    std::vector<std::string>  character;    
    std::vector<std::string>  binaryValues;
    std::string compMsgVector;
    std::string decodedMsg;
    
};