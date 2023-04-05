#include <iostream>
#include <unistd.h>
#include <math.h>
#include <thread>
#define N 100
#define THREAD1_DELAY 1
#define THREAD2_DELAY 2

using namespace std;
float val1[N];
float val2[N];
float variable;
volatile bool Flag;

class Gauss{
    
private:    
    float d=1.0f; float m=0;
    float function(float x){        
        return 1.0f/(d*sqrt(2*3.14))*exp(-(x-m)*(x-m)/(2*d*d));
    }

public:
    Gauss(float _d=1, float _m=0){
        d=_d;
        m=_m;
        srand(time(NULL));
    }
    float GenNext(){ //генерирует число в диапазоне [-5;5] по распределению гаусса
        float r;
        float x;
        int errorcnt=0;
        do{
            errorcnt++;
            if (errorcnt>100) return 0;
            x=1.0f*(rand()%1000-500)/N;
            r=0.001f*(rand()%1000);            
        }while(r>function(x));
    return x;
    }
};
Gauss G;
void addVal(float *_val,float x){
    x=x*10.0f;
    x=x+50;
    if ((x<0)||(x>=N)) throw 1;
    _val[int(x)]++;    
}
float KL(float *_val1,float *_val2){
    float mesure=0;
    float p,q;
    float sum1=0,sum2=0;
    for (int i=0;i<N;i++){
        sum1+=_val1[i];
        sum2+=_val2[i];
    }
    for (int i=0;i<N;i++){
        p=1.0f*_val1[i]/sum1; 
        q=1.0f*_val2[i]/sum2;
        if (q!=0){
            mesure+=(p*log2(p/q));
        }
    }
    return mesure;
}
void A(){
    float tmp;
    while(Flag==true){
        tmp=G.GenNext();
        addVal(val1,tmp);         
        variable=tmp;
        usleep(THREAD1_DELAY*1000);
    }
    cout <<"A()\n";
}
void B(){
    float tmp;
    while(Flag){
        tmp=variable;
        addVal(val2,tmp);         
        usleep(THREAD2_DELAY*1000);
    }
    cout <<"B()\n";
}
void C(){
    for (int i=0;i<20;i++){
        sleep(1);
        cout<<KL(val1,val2)<<endl;
    }
}
void Init(){    
    Flag=true;
    for (int i=0;i<N;i++){
        val1[i]=val2[i]=0;
    }
}

int main(){
    Init();
    std::thread thread1(A);  
    std::thread thread2(B);  
    std::thread thread3(C);  

    cout<<"Wait ..."<<endl;
    thread3.join();    
    cout<<"Completed."<<endl;    
    thread1.detach();
    thread2.detach();    
    return 0;
}