// Write your program here

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <pthread.h>
#include <stdio.h>




//structs
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




//N THREADS 
void * decode(void *x_void_ptr)
{
	struct info *x_ptr = (struct info *)x_void_ptr;
   //get binary
    std::string r;
    while(x_ptr->getValue() !=0) {r=(x_ptr->getValue()%2==0 ?"0":"1")+r; x_ptr->setValue(x_ptr->getValue()/2);}


    for (int i = r.size(); i < x_ptr->getNumBits(); i++){
        r.insert(0,"0");
        
    }
        
        x_ptr->setBV(r);
    
 // get frequency
    for (int i=0; i < x_ptr->compMsgVector.size();i++){
        
        
            if (x_ptr->getBV() == x_ptr->compMsgVector.at(i)) {
                x_ptr->setFreq(x_ptr->getFreq()+1);
                
            
        }
    
    }
    
	
	return NULL;
}


//Mthreads
void * decode1(void *x_void_ptr)
{
    
	struct info1 *x_ptr = (struct info1 *)x_void_ptr;
   
   //decode message
   
    for ( int i = 0; i < x_ptr->binaryValues.size(); i++){
        if (x_ptr->compMsgVector == x_ptr->binaryValues[i]){
            x_ptr->decodedMsg = x_ptr->character[i];
           
        }
         
    }
   
	
	return NULL;
}


 

int main()
{

    

    //////INPUT
  
    std::string temp;
    std::string temp1;
    std::string temp3;
    
    int temp2 = 0;
    int symbols;
   //get # of symbols

    getline(std::cin, temp1);
    
    
    
    symbols = stoi(temp1);


    std::vector<info> first(symbols);
    std::vector<std::string> character;
    std::vector<int> value;

    //get chars and values  
    for(int i = 0; i< symbols; i++){
        getline(std::cin, temp);
        
      
        temp3 = temp.substr(2);
        temp1 = temp[0];
        temp2 = stoi(temp3);
        character.push_back(temp1);
        value.push_back(temp2);
        
       
        
        
    }
    //assign values to first struct for first thread func
    for (int i = 0; i < symbols; i++){
        first[i].setChar(character.at(i));
        first[i].setValue(value.at(i));
    }
    

    

    std::string compMsg;
    std::cin >> compMsg;




    

    

///////////////////////////////////////////// DECODING ////////////////////////////////


    // get max value and calculate num bits
    int maxValue = 0;

    for(int i = 0; i< symbols; i++){
        if (maxValue<first[i].getValue()){
            maxValue=first[i].getValue();
        }
    }
    
    
    for (int i = 0; i < symbols; i++){
    first[i].setNumBits(ceil(log2(maxValue)));
    }
    
   



    //split comp message into a vector and add to struct//////////////////////////////////////


    

    for (int i = 0; i< compMsg.size(); i+=first[0].getNumBits()){
        std::string tempString = "";
        for(int j = 0; j<first[0].getNumBits(); j++){

            tempString.push_back(compMsg.at(i+j));

        }
        for (int k = 0; k< first.size();k++){
            first[k].compMsgVector.push_back(tempString);
        }
    }
    

    // /  call first thread function to get binary and frequency

    pthread_t tid;

    for(int i = 0; i<symbols;i++){
        if(pthread_create(&tid, NULL, decode, &first[i]))
        {
			fprintf(stderr, "Error creating thread\n");
			return 1;

		}	
    }
    for (int i = 0; i < symbols; i++)
        	pthread_join(tid, NULL);

   
    //create second stuct and load values into it

    std::vector<info1> second(first[0].compMsgVector.size());

    


    for (int i = 0; i< compMsg.size(); i+=first[0].getNumBits()){
        std::string tempString = "";
        for(int j = 0; j<first[0].getNumBits(); j++){

            second[i/first[0].getNumBits()].compMsgVector.push_back(compMsg.at(i+j));

        }
        
    }

    for (int i = 0; i < second.size(); i++){

        
        for (int j = 0; j< first.size(); j++){
        second[i].character.push_back(first[j].getChar());
        second[i].binaryValues.push_back(first[j].getBV());
        
        
        


    
     
       

    }
   
    }

        
    // call second thread function to decode msg
    
    std::vector<pthread_t> tid1(first[0].compMsgVector.size());

    for(int i = 0; i<first[0].compMsgVector.size();i++){
        if(pthread_create(&tid1[i], NULL, decode1, &second[i]))
        {
			fprintf(stderr, "Error creating thread\n");
			return 1;

		}	
    }
    for (int i = 0; i < first[0].compMsgVector.size(); i++)
        	pthread_join(tid1[i], NULL);

    // put decoded message from second struct into a string for easy output
    
    std::string decodedMsg = "";

    for (int i = 0; i < second.size(); i++){
        decodedMsg.append(second[i].decodedMsg);
    }
    

    

    //OUTPUT

    std::cout << "Alphabet:"<< std::endl;

    
    for (int i = 0; i < symbols; i ++){
        std::cout << "Character: " << first[i].getChar() << ", Code: " << first[i].getBV() << ", Frequency: " << first[i].getFreq()<< std::endl;
    }


    std::cout << "\nDecompressed message: "  << decodedMsg;
    

    return 0;
};
