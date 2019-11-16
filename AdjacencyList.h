#include <memory>

struct Node {
        long data;
        long count;
        std::unique_ptr<Node> next;
        Node(): data(-1), count(1), next(std::unique_ptr<Node>(nullptr)){};
        Node(long data): data(data), count(1), next(std::unique_ptr<Node>(nullptr)){
        }
};

struct Edges {
    Edges(){incident = 0L; total = 0ULL;};
    Edges(long e){
        data = std::unique_ptr<long[]>(new long[e]);
        incident = 0L;
        total = 0ULL;
    }
    void reserve(long e) {
        data = std::unique_ptr<long[]>(new long[e]);
        incident = 0L;
        total = 0ULL;
    }
    std::unique_ptr<long[]> data;
    unsigned long incident;
    unsigned long long total;
    bool operator < (const Edges& rhs) {
       return incident < rhs.incident;
    }
    bool operator >(const Edges& rhs) {
        return incident > rhs.incident;
    }
    bool operator==(const Edges& rhs) {
        return incident == rhs.incident;
    }
    bool operator !=(const Edges& rhs) {
        return incident != rhs.incident;
    }

    long& operator[](const size_t index) {
        return data[index];
    }
};

class AdjacencyList {
//    std::unique_ptr<Node[]> data;
    std::unique_ptr<Edges[]> data;

    long size;
    long& at(long, long);
    void add(long, long);
public:
    
    AdjacencyList();
    AdjacencyList(long);
    void insert(long, long);
    bool is_adjacent(long, long);
    void print();

};




