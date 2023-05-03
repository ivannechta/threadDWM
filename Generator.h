#ifndef GENERATOR_MODULE
#define GENERATOR_MODULE
#include "Header.h"
using namespace std;

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
        if ((arraySize==0)||(arraySize%10!=0)||(arraySize%2!=0)) {cout<< "Wrong arraySize";throw 1;}
        x=x*arraySize/10.0f;
        x=x+0.5*arraySize;
        tmp=x;    
        if ((tmp<0)||(tmp>=arraySize)) throw 2;
        values[tmp]++;      
    }       

    void generate(){
        addVal(publicValue=GenNext(Dispersion,Mean));
    }

};


#endif