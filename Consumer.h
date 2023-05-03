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
        x=x*10.0f;
        x=x+50;
        tmp=x;    
        if ((tmp<0)||(tmp>=arraySize)) throw 1;
        values[tmp]++;      
    }       

};

#endif
