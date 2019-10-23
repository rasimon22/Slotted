//
// Created by rasimon on 9/30/19.

//



#ifndef SLOTTED_DATAGEN_H
#define SLOTTED_DATAGEN_H

#include <memory>
#include <cstdlib>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <vector>
enum class Distribution {
    Uniform = 0, Skewed = 1, Four_Tiered = 2, Custom = 3
};

template<typename T, Distribution U>
class DataGen {

    std::unique_ptr<T[]> data;
    T *front;
    T *back;
    size_t len;

    void swap(T *a, T *b) {
        T tmp = *a;
        *a = *b;
        *b = tmp;
    }

public:
    DataGen<T, U>(size_t, size_t);

    void regen();

    size_t get_len();

    T *getData();

    static int rand_linear(DataGen<T, U>&, DataGen<T, U>&);

    T yield();
};

template<typename T>
class DataGen <T, Distribution::Custom> {

};

template<typename T, Distribution U>
DataGen<T, U>::DataGen(size_t min, size_t max) {
    time_t t;
    size_t range = max - min;
    srand((unsigned) time(&t));
    data = std::unique_ptr<T[]>(new T[range]);
    front = data.get();
    back = &data[range-1];
    for(size_t i = 0; i < range; ++i) {
    data[i] = static_cast<T>(min + i) + 1;
    }
    len = range;
    regen();
}

template<typename T, Distribution U>
void DataGen<T, U>::regen() {

    for (size_t i = len; i > 0; i--) {
    size_t j = rand() % i;
    swap(&data[i - 1], &data[j]);
    }
    srand(data[0]);
    front = data.get();
}

template<typename T, Distribution U>
T *DataGen<T, U>::getData() {
    return data.get();
}

template<typename T, Distribution U>
size_t DataGen<T, U>::get_len() {
    return len;
}

template <typename T, Distribution U>
T DataGen<T, U>::yield() {
    if(front + 1 > back) {
    regen();
    }
    front++;
    return *(front - 1);
}

int rand_normal(double mean, double stddev)
{//Box muller method
    static double n2 = 0.0;
    static int n2_cached = 0;
    if (!n2_cached)
    {
    double x, y, r;
    do
    {
        x = 2.0*rand()/RAND_MAX - 1;
        y = 2.0*rand()/RAND_MAX - 1;

        r = x*x + y*y;
    }
    while (r == 0.0 || r > 1.0);
    {
        double d = sqrt(-2.0*log(r)/r);
        double n1 = x*d;
        n2 = y*d;
        double result = n1*stddev + mean;
        n2_cached = 1;
        return int(result);
    }
    }
    else
    {
    n2_cached = 0;
    return n2*stddev + mean;
    }
}

template <typename T, Distribution U>
int DataGen<T, U>::rand_linear(DataGen<T,U> &first, DataGen<T, U> &second){
    return std::max(first.yield(), second.yield());
}

template<typename T, Distribution U>
int rand_tiered(DataGen<T,U> &g1, DataGen<T,U> &g2, DataGen<T,U> &g3, DataGen<T,U> &g4, int probs[4]) {
    time_t t;
    int sum = 0; 
    for(int i = 0; i < 4; ++i) {
        sum += probs[i];
    }
    short index = 0;
    int pick = (rand() % sum);
    if (pick > probs[0]) index = 1;
    if (pick > probs[1]) index = 2;
    if (pick > probs[2]) index = 3;
    switch (index){

        case 0:
            return g1.yield();
            break;
        case 1:
            return g2.yield();
            break;
        case 2:
            return g3.yield();
            break;
        case 3:
            return g4.yield();
            break;
    }
} 


#endif //SLOTTED_DATAGEN_H
