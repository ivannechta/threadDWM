#ifndef GENERATOR_MODULE
#define GENERATOR_MODULE
#include "Header.h"

class Generator:public Gauss{
private:
    int arraySize;
    float Dispersion;
    float Mean;

public:
    float *values;
    float publicValue; //Наблюдаемая переменная. Один поток (генератор) заполняет её, а второй считывает значение.

    Generator(int _arraySize, float _Dispersion, float _Mean){
        arraySize=_arraySize;
        values=new float[_arraySize];
        Dispersion=_Dispersion;
        Mean=_Mean;
    }
    ~Generator(){
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

    void generate(){
        addVal(publicValue=GenNext(Dispersion,Mean));
    }

};


#endif