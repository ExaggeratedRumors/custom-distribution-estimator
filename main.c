#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define _ESTIMATE 1000
#define _MIN_LENGTH 8
#define _MAX_LENGTH 25
#define _MAX_STACK 3
#define _MAX_DURATION 5
#define _NEXT_DURATION 2
#define _BASIC_VALUE 1
#define _SUCCESS_PROBABILITY 0.25
#define _FAILURE_PROBABILITY_1 0.38
#define _FAILURE_PROBABILITY_2 0.1


#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

void currentValue(double *array){
    if((double)rand()/RAND_MAX < _SUCCESS_PROBABILITY && (double)rand()/RAND_MAX > _FAILURE_PROBABILITY_1 && (double)rand()/RAND_MAX > _FAILURE_PROBABILITY_2){
        if(array[1] == 0){
            array[2] = 1;
            array[1] = _MAX_DURATION;
            array[0] = _BASIC_VALUE;
        } else {
            array[1] = MIN(_MAX_DURATION, array[1] + _NEXT_DURATION);
            if(array[2] < _MAX_STACK){
                array[0] += 0.5 * _BASIC_VALUE;
                array[2]++;
            }
        }
    } else if(array[1] == 0) {
        array[2] = 0;
        array[0] = 0;
    }
    array[1] = MAX( array[1]-1 , 0);
}

double expectedValue(int currentLength){
    int iterator;
    double sum = 0;
    double tempArray[3] = {0};

    for(iterator = 0 ; iterator < currentLength ; iterator++){
        currentValue(tempArray);
        sum += tempArray[0];
    }
    return sum/currentLength;
}

double estimatedValue(int currentLength){
    int iterator;
    double sum = 0;
    for(iterator = 0 ; iterator < _ESTIMATE ; iterator++){
        sum += expectedValue(currentLength);
    }
    return sum/_ESTIMATE;
}

void collectEstimatedValue(double * container){
    int iterator;
    for(iterator = _MIN_LENGTH ; iterator <= _MAX_LENGTH ; iterator++){
        container[iterator - _MIN_LENGTH] = estimatedValue(iterator);
        printf("dlugosc walki: %d  estymowana wartosc: %f\n",iterator, container[iterator - _MIN_LENGTH]);
    }
}

void expectedValueOverall(double * container){
    int iterator;
    double sum = 0;
    for(iterator = 0 ; iterator < _MAX_LENGTH - _MIN_LENGTH + 1 ; iterator++){
        sum += container[iterator];
    }
    sum /= _MAX_LENGTH -_MIN_LENGTH + 1;
    printf("Ostateczna wartosc oczekiwana: %f\n", sum);

}


int main(){
    srand(time(NULL));
    double container[_MAX_LENGTH - _MIN_LENGTH + 1];
    collectEstimatedValue(container);
    expectedValueOverall(container);

    return 0;
}
