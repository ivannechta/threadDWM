#ifndef GENERATOR_MODULE
#define GENERATOR_MODULE
#include "Header.h"
using namespace std;

class Generator:public Gauss{
private:
    int arraySize;
    float Dispersion;
    float Mean;
    long Time;
    
public:
    float *values;
    float publicValue; //Наблюдаемая переменная. Один поток (генератор) заполняет её, а второй считывает значение.
    long DeltaTime;

    Generator(int _arraySize, float _Dispersion, float _Mean){
        arraySize=_arraySize;
        values=new float[_arraySize];
        Dispersion=_Dispersion;
        Mean=_Mean;    
        DeltaTime=0;
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
        deltaTime();
    }    

    void deltaTime(){
        auto t0 = std::chrono::high_resolution_clock::now();        
        auto nanosec = t0.time_since_epoch();
        long tmp=nanosec.count();
        DeltaTime=tmp-Time;
        Time=tmp;
    }

};


#endif