#include "Header.h"
#define N 100
#define AMOUNT_DATA 50

int THREAD_DELAY = 1;
float Dispersion=1;

char Mode='s';
int TOTAL_GENERATORS=0;

volatile bool Flag=true; //Флаг окончания работ потоков

Generator *gen1, *gen3, *gen4;
Consumer cons2(N);
Statistic stat(N);
Generator **Generators;

void SomeThread(){ //Множество генераторов (для оценки нагрузки на процессор)
    Generator tmp(N,1,0);
    while(Flag==true){               
        tmp.generate();

        usleep(THREAD_DELAY*1000);// 1 мсек
    }    
}
void A(){   // Генерация распределения

    while(Flag==true){               
        gen1->generate();
        gen3->generate();
        gen4->generate();

        usleep(THREAD_DELAY*1000);// 1 мсек
    }    
}
void B(){   //Считыватель распределения
    float tmp;
    while(Flag){  
        cons2.addVal(gen1->publicValue);

        usleep(THREAD_DELAY*1000); // 1 мсек
    }    
}
void C(){   //Вывод статистики
    for (int i=0;i<AMOUNT_DATA;i++){
        sleep(1);
        if (Mode=='s'){
        stat.showStatisticTab(gen1->values,cons2.values);
        stat.showStatisticTab(gen1->values,gen3->values);
        stat.showStatisticTab(gen3->values,cons2.values);
        stat.showStatisticTab(gen4->values,cons2.values);
        stat.showStatisticLn(gen3->values,gen4->values);        
        }
        if (Mode=='t'){
            stat.showTime(gen1);
        }
    }
}
void Init(){
    Generators=new Generator*[TOTAL_GENERATORS];
    for (int i=0;i<TOTAL_GENERATORS;i++){
        Generators[i]=new Generator(N,1,0);
    }
}
void Usage(char *argv0){
        cout<<"Usage:\n";
        cout<<argv0<<"[mode, 's'] [Dispersion,float] [thread2 delay, (int msec)] \n";
        cout<<argv0<<"[mode, 't'] [TOTAL_GENERATORS] [Dispersion,float] [thread2 delay, (int msec)] \n";

        cout<<"Output KL distance (1- in programm N(1,0), 2 - hooked, 3,4 - some other distrib N(param,0) ):\n";
        cout<<"1-2, 1-3, 3-2, 4-2, 3-4\n";
        cout<<"mode: t - timer overhead, s - distribution statistic\n";
}
int main(int argc,char *argv[]){     
    if ((argc!=4)&&(argc!=5)){
        Usage(argv[0]);
        return 0;
    }

    Mode=argv[1][0];

    switch(Mode){
        case 't':
            if (argc!=5) {Usage(argv[0]); return 0;}
            TOTAL_GENERATORS=stof(argv[2]);
            Dispersion=stof(argv[3]);
            THREAD_DELAY=atoi(argv[4]);            
            break;
        case 's':  
            if (argc!=4) {Usage(argv[0]); return 0;}
            Dispersion=stof(argv[2]);
            THREAD_DELAY=atoi(argv[3]);                
            break;
        default:
            Usage(argv[0]);
            return 0;
    }

    gen1=new Generator(N,1,0);
    gen3=new Generator(N,1,0);
    gen4=new Generator(N,Dispersion,0);

    std::thread thread1(A);  
    std::thread thread2(B);  
    std::thread thread3(C);  

    std::thread **Threader;
    Threader=new std::thread*[TOTAL_GENERATORS];
    for (int i=0;i<TOTAL_GENERATORS;i++){
        Threader[i]=new std::thread(SomeThread); 
    }

    thread3.join();    
    
    thread1.detach();
    thread2.detach();    
    return 0;
}