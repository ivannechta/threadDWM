#ifndef STATISTIC_MODULE
#define STATISTIC_MODULE
#include "Header.h"

class Statistic{
public: 
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

    }

    /*void showStatistic2(float * _v1, float * _v2, float * _v3, float * _v4){

    }*/





};

#endif