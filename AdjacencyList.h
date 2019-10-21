#include <memory>

struct Node {
        size_t data;
        size_t count;
        std::unique_ptr<Node> next;
        Node(): data(0), count(1), next(std::unique_ptr<Node>(nullptr)){};
        Node(size_t data): data(data), count(1), next(std::unique_ptr<Node>(nullptr)){
        }
};

class AdjacencyList {
    std::unique_ptr<Node[]> data;
    size_t size;
    void add(size_t, size_t);
public:
    
    AdjacencyList();
    AdjacencyList(size_t);
    void insert(size_t, size_t);
    bool is_adjacent(size_t, size_t);
    void print();

};




