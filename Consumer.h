#ifndef CONSUMER_MODULE
#define CONSUMER_MODULE
#include "Header.h"

class Consumer{
private:
    int arraySize;

public:
    float *values;    

    Consumer(int _arraySize){
        arraySize=_arraySize;
        values=new float[_arraySize];        
    }
    ~Consumer(){
        delete values;
    }
    
    void addVal(float x){
        int tmp;
        if ((arraySize==0)||(arraySize%10!=0)||(arraySize%2!=0)) {cout<< "Wrong arraySize";throw 1;}
        x=x*arraySize/10.0f;
        x=x+0.5*arraySize;
        tmp=x;    
        if ((tmp<0)||(tmp>=arraySize)) throw 2;
        values[tmp]++;
    }       

};

#endif
