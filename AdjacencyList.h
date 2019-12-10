#include <memory>
#include <vector>
#include <deque>

struct Node {
        long data;
        long count;
        std::unique_ptr<Node> next;
        Node(): data(-1), count(1), next(std::unique_ptr<Node>(nullptr)){};
        Node(long data): data(data), count(1), next(std::unique_ptr<Node>(nullptr)){
        }
};

struct Edges {
    Edges(){incident = 0L; total = 0ULL; len = 0; classNum = -1;};
    Edges(size_t e){
        data = std::unique_ptr<long[]>(new long[e]);
        incident = 0L;
        total = 0ULL;
        len = e;
        color = -1;
        classNum = -1;

    }
    Edges(const Edges& rhs) {
      reserve(rhs.len);
      for (int i = 0; i < len; ++i) {
        data[i] = rhs.data[i];
      }
      incident = rhs.incident;
      total = rhs.total;
      len = rhs.len;
      color= rhs.color;
      classNum = rhs.classNum;

    }

    Edges& operator=(const Edges &rhs) {
      Edges r(rhs);
      return r;
    }

    void reserve(size_t e) {
        data = std::unique_ptr<long[]>(new long[e]);
        incident = 0L;
        total = 0ULL;
        len = e;
    }
    size_t classNum;
    size_t len;
    size_t color;
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
    std::deque<Edges*> getSortedEdges();
public:
    
    AdjacencyList();
    AdjacencyList(long);
    void insert(long, long);
    bool is_adjacent(long, long);
    std::vector<Edges*> smallest_least_ordering();
    void print();

};




