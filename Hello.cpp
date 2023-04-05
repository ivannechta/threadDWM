#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <thread>
#define N 100
#define AMOUNT_DATA 20
#define THREAD1_DELAY 1
#define THREAD2_DELAY 1


using namespace std;
float val1[N];
float val2[N];
float val3[N];

float variable;
volatile bool Flag;
static pthread_mutex_t cs_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

class Gauss{
    
private:        
    float function(float d,float m,float x){        
        return 1.0f/(d*sqrt(2*3.14))*exp(-(x-m)*(x-m)/(2*d*d));
    }

public:
    Gauss(){        
        srand(time(NULL));
    }
    float GenNext(float _d,float _m){ //генерирует число в диапазоне [-5;5] по распределению гаусса        
        float r;
        float x;        
        int errorcnt=0;
        do{
            errorcnt++;
            if (errorcnt>100) return 0;
            x=1.0f*(rand()%1000-500)/N;
            r=0.001f*(rand()%1000);            
        }while(r>function(_d,_m,x));        
    return x;
    }
};
Gauss G;
void addVal(float *_val,float x){
    pthread_mutex_lock( &cs_mutex );
    x=x*10.0f;
    x=x+50;
    if ((x<0)||(x>=N)) throw 1;
    _val[int(x)]++;  
    pthread_mutex_unlock( &cs_mutex );  
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
        if ((q!=0)&&(p!=0)){
            mesure+=(p*log2(p/q));            
        }
    }
    return mesure;
}
void A(){    
    while(Flag==true){        
        addVal(val1,variable=G.GenNext(1,0));                 
        addVal(val3,G.GenNext(2.0,0));                 

        usleep(THREAD1_DELAY*1000);
    }    
}
void B(){
    float tmp;
    while(Flag){        
        addVal(val2,variable);         
        usleep(THREAD2_DELAY*1000);
    }    
}
void C(){
    for (int i=0;i<AMOUNT_DATA;i++){
        sleep(1);
        cout<<KL(val1,val2)<<"      "<<KL(val3,val2)<< "     "<<KL(val1,val3)<<endl;        
    }
}
void Init(){    
    Flag=true;
    for (int i=0;i<N;i++){
        val1[i]=val2[i]=val3[i]=0;
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