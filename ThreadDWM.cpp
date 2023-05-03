#include "Header.h"
#define N 100
#define AMOUNT_DATA 50
#define THREAD1_DELAY 1
int THREAD2_DELAY = 1;
float Dispersion=1;

volatile bool Flag=true; //Флаг окончания работ потоков

Generator gen1(N,1,0), gen3(N,1,0), gen4(N,Dispersion,0);
Consumer cons2(N);
Statistic stat(N);

void A(){   // Генератор распределения
    while(Flag==true){        
        gen1.generate();
        gen3.generate();
        gen4.generate();

        usleep(THREAD1_DELAY*1000);// 1 мсек
    }    
}
void B(){   //Считыватель распределения
    float tmp;
    while(Flag){  
        cons2.addVal(gen1.publicValue);

        usleep(THREAD2_DELAY*1000); // 1 мсек
    }    
}
void C(){   //Вывод статистики
    for (int i=0;i<AMOUNT_DATA;i++){
        sleep(1);
        stat.showStatisticTab(gen1.values,cons2.values);
        stat.showStatisticTab(gen1.values,gen3.values);
        stat.showStatisticTab(gen3.values,cons2.values);
        stat.showStatisticTab(gen4.values,cons2.values);
        stat.showStatisticLn(gen3.values,gen4.values);        
    }
}

int main(int argc,char *argv[]){ 
    if (argc!=3){
        cout<<"Usage:\n";
        cout<<argv[0]<<" [Dispersion,float] [thread2 delay, (int msec)]\n";

        cout<<"Output KL distance (1- in programm N(1,0), 2 - hooked, 3,4 - some other distrib N(param,0) ):\n";
        cout<<"1-2, 1-3, 3-2, 4-2, 3-4\n";

        return 0;
    }
    Dispersion=stof(argv[1]);
    THREAD2_DELAY=atoi(argv[2]);       
   
   
    std::thread thread1(A);  
    std::thread thread2(B);  
    std::thread thread3(C);  
    
    thread3.join();    
    
    thread1.detach();
    thread2.detach();    
    return 0;
}