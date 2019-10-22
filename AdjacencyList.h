#include <memory>

struct Node {
        long data;
        long count;
        std::unique_ptr<Node> next;
        Node(): data(-1), count(1), next(std::unique_ptr<Node>(nullptr)){};
        Node(long data): data(data), count(1), next(std::unique_ptr<Node>(nullptr)){
        }
};

class AdjacencyList {
    std::unique_ptr<Node[]> data;
    long size;
    void add(long, long);
public:
    
    AdjacencyList();
    AdjacencyList(long);
    void insert(long, long);
    bool is_adjacent(long, long);
    void print();

};




