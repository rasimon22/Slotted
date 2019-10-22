#include "AdjacencyList.h"
#include <iostream>

AdjacencyList::AdjacencyList() {};

AdjacencyList::AdjacencyList(size_t init_size) {
    data = std::unique_ptr<Node[]>(new Node[init_size + 1]);
    size = init_size;
}

void AdjacencyList::add(size_t n1, size_t n2) {
    if (n1 <= size && n2 <= size) {
        if (data[n1].data == 0) {
            data[n1].data = n2;
            return;
        } else {
            Node *it(&data[n1]);
            for(;;){
                if(it->data == n2) {
                    it->count++; 
                    return;
                }
                if(it->next.get()) {
                    it = it->next.get();
                } else {
                    break;
                }
            }
            it->next = std::unique_ptr<Node>(new Node(n2));
        }
    }
}

void  AdjacencyList::print() {
    for(size_t i = 0; i < size; ++i) {
        std::cout << i << ")";
        Node *it(&data[i]);
        std::cout << "->" << "(" << it->data << ":" << it->count << ")";
        while(it->next.get()) {
            it = it->next.get();
            std::cout << "->" << "(" << it->data << ":" << it->count << ")";
        }
        std::cout << std::endl;
    }
}

void AdjacencyList::insert(size_t n1, size_t n2) {
    add(n1, n2);
    add(n2, n1);
}
