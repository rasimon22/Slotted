#include "AdjacencyList.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <deque>

AdjacencyList::AdjacencyList() {};

AdjacencyList::AdjacencyList(long init_size) {
//    data = std::unique_ptr<Node[]>(new Node[init_size + 1]);
    data = std::unique_ptr<Edges[]>(new Edges[init_size]);
    //reserve for each edges
    for(int i = 0; i < init_size; ++i){
      data[i].reserve(init_size);
      data[i].classNum = i;
    }
    size = init_size;
}

long& AdjacencyList::at(long course, long index) {
    return data[course][index];
}

void AdjacencyList::add(long n1, long n2) {

    if(at(n1, n2) == 0) {
      data[n1].incident++;
    }
    data[n1].total++;
    ++at(n1, n2);
}

void  AdjacencyList::print() {
    for(long i = 0; i < size; ++i) {
        std::cout << i << ")";
        for (long j = 0; j < size; ++j) {
            std::cout << "->" << "(" << j << ":" << at(i, j) << ")";
        }
        std::cout << "::" << '[' << data[i].incident << ']';
        std::cout << "::" << '{' << data[i].total << '}';
        std::cout << std::endl;
    }
}

void AdjacencyList::insert(long n1, long n2) {
    add(n1, n2);
    add(n2, n1);
}

std::deque<Edges*> AdjacencyList::getSortedEdges() {
  std::deque<Edges*> e;
  for(size_t i = 0; i < size; ++i){
    e.push_back(&data[i]);
  }

  std::sort(e.begin(), e.end(), [](Edges *a, Edges*b){return *a < *b;});
  return e;
}

bool AdjacencyList::is_adjacent(long a, long b) {
  return data[a][b] != 0;
}

std::vector<Edges*> AdjacencyList::smallest_least_ordering() {
  std::vector<Edges*> ret;
  std::deque<Edges*> deq = getSortedEdges();
  std::stack<Edges*> removed;
  while(deq.size() > 0) {
    Edges *e = deq.front();
    deq.pop_front();
    for (size_t i = 0; i < e->len; ++i) {
      if ((*e)[i] != 0) {
        data[(*e)[i]].incident--;
      }
    }
    removed.push(e);
    std::sort(deq.begin(), deq.end(), [](Edges *a, Edges *b) { return *a < *b; });
  }
  std::cout << "LEN = " << removed.size() << std::endl;
  while(!removed.empty()) {
    int c = 1;
    Edges *e = removed.top();
    for(size_t i = 0; i < e->len; ++i) {
      if ((*e)[i] != 0) {
        if(c == data[i].color) {
          c = data[i].color + 1;
          i = 0;
        }
      }
    }
    e->color = c;
    std::cout << e->classNum << "==" << e->color << std::endl;
    ret.push_back(e);
    removed.pop();
  }
  return ret;
}


