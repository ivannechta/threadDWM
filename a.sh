#!/bin/bash

for I in 1 3 5 # Задержка между потоками
do 
for J in 2.0 1.7 1.5 1.2 1.1 1.05 1.0 # Дисперсия для второго распределения
do 
./ThreadDWM $J $I >$J\_$I.txt
done
done



 
