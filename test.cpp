#include <pthread.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <cmath>

struct arguments
{
    char ch;
    int *asciiPTR;
};


void *chToascii(void *void_ptr)
{
    std::string ch1 = "C";
    std::string ch2 = "O";
    std::string ch3 = "S";
    std::string ch4 = "3";
    std::string ch5 = "6";
    std::string ch6 = "0";
    
	struct arguments *arg_ptr =  (struct arguments *)void_ptr;// cast the void pointer to a struct arguments pointer
	// store the ASCII value of the received character into the memory location provided in the arguments (asciiPTR). 
	if (arg_ptr->ch == ch1.at(0)){
	    *arg_ptr->asciiPTR = 67;
	    
	    std::cout<< arg_ptr->ch << "test";
	}
	if (arg_ptr->ch == ch2.at(0)){
	    *arg_ptr->asciiPTR = 79;
	}
	if (arg_ptr->ch == ch3.at(0)){
	    *arg_ptr->asciiPTR = 83;
	}
	if (arg_ptr->ch == ch4.at(0)){
	    *arg_ptr->asciiPTR = 51;
	}
	if (arg_ptr->ch == ch5.at(0)){
	    *arg_ptr->asciiPTR = 54;
	}
	if (arg_ptr->ch == ch6.at(0)){
	    *arg_ptr->asciiPTR = 48;
	}
	
	
	return nullptr;
}

int main()
{

    std::string word ="COSC3360";
  //  std::cin >> word;
    int size = word.length();
    pthread_t *tid = new pthread_t[size];
    struct arguments * arg= new arguments[size];
    int *asciiValues = new int[size];

	for (int i = 0; i < size; i++)
	{
        arg[i].ch = word.at(i);// assign a character from the input word.
        arg[i].asciiPTR = &asciiValues[i]; // assign the address from the asciiValues array where you want to store the ASCII value.   
        if (pthread_create(&tid[i], NULL, chToascii, &arg[i]) )
		{
			    fprintf(stderr, "Error creating thread\n");
			    return 1;
		}
	}
    // call pthread_join here
    
    for (int i = 0; i < size; i++){
        pthread_join(tid[i],NULL);
    }
    std::cout << "The word \"" << word << "\" is represented with the following ASCII values:" << std::endl;
    for (int i=0; i < size; i++)
    {
        std::cout << asciiValues[i];
        if (i < size -1)
            std::cout << " ";
        else
            std::cout << std::endl;
    }
	delete [] tid;
    delete [] arg;
    delete [] asciiValues;
    return 0;
}