#ifndef GAUSS_MODULE
#define GAUSS_MODULE
#include "Header.h"

class Gauss{
    
private:        
    float function(float d,float m,float x){        
        return 1.0f/(d*sqrt(2*3.14))*exp(-(x-m)*(x-m)/(2*d*d));
    }

public:
    Gauss(){        
        srand(time(NULL));
    }
    float GenNext(float _d,float _m){ //генерирует число в диапазоне [-5;5] по распределению Гаусса        
        float r;
        float x;        
        int errorcnt=0;
        do{
            errorcnt++;
            if (errorcnt>100) return 0; // Не удалось сгенерировать число - заменяем на ноль.
            x=0.01f*(rand()%1000-500);
            r=0.001f*(rand()%1000);            
        }while(r>function(_d,_m,x));        
    return x;
    }
};

#endif