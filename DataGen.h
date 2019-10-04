//
// Created by rasimon on 9/30/19.
//

#ifndef SLOTTED_DATAGEN_H
#define SLOTTED_DATAGEN_H

#include <memory>
#include <cstdlib>
#include <unistd.h>

enum class Distribution {
    Uniform = 0, Skewed = 1, Four_Tiered = 2, Custom = 3
};

template<typename T, Distribution U>
class DataGen {

    std::unique_ptr<T[]> data;
    size_t len;

    void swap(T *a, T *b) {
      T tmp = *a;
      *a = *b;
      *b = tmp;
    }

public:
    DataGen<T, U>(size_t);

    void regen();

    size_t get_len();

    T *getData();
};

template<typename T, Distribution U>
DataGen<T, U>::DataGen(size_t sz) {
  time_t t;
  srand((unsigned) time(&t));
  data = std::unique_ptr<T[]>(new T[sz]);
  for(size_t i = 0; i < sz; ++i) {
    data[i] = static_cast<T>(i) + 1;
  }
  len = sz;
  regen();

  usleep(900);
}

template<typename T, Distribution U>
void DataGen<T, U>::regen() {

  for (size_t i = len; i > 0; i--) {
    size_t j = rand() % i;
    swap(&data[i - 1], &data[j]);
  }
  srand(data[0]);
}

template<typename T, Distribution U>
T *DataGen<T, U>::getData() {
  return data.get();
}

template<typename T, Distribution U>
size_t DataGen<T, U>::get_len() {
  return len;
}

double rand_normal(double mean, double stddev)
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
      return result;
    }
  }
  else
  {
    n2_cached = 0;
    return n2*stddev + mean;
  }
}

#endif //SLOTTED_DATAGEN_H
