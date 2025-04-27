#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <stdexcept>

namespace bh{

class BinomialHeap {
private:
    struct Node {
        int key;
        int degree;
        Node* parent;
        Node* child;
        Node* sibling;
        
        Node(int k) 
            : key(k), degree(0), 
              parent(nullptr), 
              child(nullptr), 
              sibling(nullptr) {}
    };

    Node* head;
    Node* minNode;


    Node* mergeRootLists(Node* list1, Node* list2);
    void linkTrees(Node* child, Node* parent);
    Node* reverseList(Node* node);
    void adjustHeap();
    void updateMin();
    void deleteSubtree(BinomialHeap::Node* node);

public:
    BinomialHeap();
    ~BinomialHeap();
    

    void insert(int key);
    int getMin();
    void extractMin();
    void merge(BinomialHeap& other);
    bool isEmpty() const;
};

}
#endif 