#!/bin/bash

for I in 10 100 1000 10000  # Дисперсия для второго распределения
do 
./ThreadDWM t $I 1 1 >$I.time
done
done



 
