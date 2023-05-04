#ifndef STATISTIC_MODULE
#define STATISTIC_MODULE
#include "Header.h"
using namespace std;

class Statistic{
private: 
    int arraySize;

public: 
    Statistic (int _arraySize){
        arraySize=_arraySize;
    }

    float KL(float *_val1,float *_val2,int _arraySize){ //Дивергенция Кульбака-Лейблера
        float mesure=0;
        float p,q;
        float sum1=0,sum2=0;
        for (int i=0;i<_arraySize;i++){
            sum1+=_val1[i];
            sum2+=_val2[i];
        }
        for (int i=0;i<_arraySize;i++){
            p=1.0f*_val1[i]/sum1; 
            q=1.0f*_val2[i]/sum2;
            if ((q!=0)&&(p!=0)){
                mesure+=(p*log2(p/q));            
            }
        }
        return mesure;
    }

    void showStatistic(float * _v1,float * _v2){
        cout<< KL(_v1,_v2,arraySize);
    }
    void showStatisticTab(float * _v1,float * _v2){
        showStatistic(_v1,_v2);
        cout << "      ";
    }
    void showStatisticLn(float * _v1,float * _v2){
        showStatistic(_v1,_v2);
        cout << "\n";
    }
    void showTime(Generator *g){        
        cout << g->DeltaTime<<endl;
    }

};

#endif