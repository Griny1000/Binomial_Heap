#include "binomial_heap.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace bh{
void BinomialHeap::deleteSubtree(BinomialHeap::Node* node) {
    if (!node) return;
    deleteSubtree(node->child);
    deleteSubtree(node->sibling);
    delete node;
}

BinomialHeap::BinomialHeap() : head(nullptr), minNode(nullptr) {}

BinomialHeap::~BinomialHeap() {
    deleteSubtree(head);
}

void BinomialHeap::insert(int key) {
    BinomialHeap tempHeap;
    tempHeap.head = new Node(key);
    tempHeap.minNode = tempHeap.head;
    merge(tempHeap);
}

int BinomialHeap::getMin() {
    if (!minNode) 
        throw std::runtime_error("Heap is empty");
    return minNode->key;
}

void BinomialHeap::extractMin() {
    if (!minNode) return;

    Node* prev = nullptr;
    Node* curr = head;
    while (curr && curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }

    if (prev) {
        prev->sibling = minNode->sibling;
    } else {
        head = minNode->sibling;
    }

    Node* child = minNode->child;
    delete minNode;
    minNode = nullptr;

    if (child) {
        BinomialHeap tempHeap;
        tempHeap.head = reverseList(child);
        merge(tempHeap);
    }

    updateMin();
}

void BinomialHeap::merge(BinomialHeap& other) {
    if (this == &other) return;

    // Слияние корневых списков
    Node* mergedList = mergeRootLists(head, other.head);
    head = mergedList;
    other.head = nullptr;

    adjustHeap();
    updateMin();
}


BinomialHeap::Node* BinomialHeap::mergeRootLists(Node* list1, Node* list2) {
    Node dummy(0);
    Node* tail = &dummy;
    
    while (list1 || list2) {
        if (!list2 || (list1 && list1->degree <= list2->degree)) {
            tail->sibling = list1;
            list1 = list1->sibling;
        } else {
            tail->sibling = list2;
            list2 = list2->sibling;
        }
        tail = tail->sibling;
    }
    return dummy.sibling;
}
void BinomialHeap::adjustHeap() {
    if (!head) return;

    Node* prev = nullptr;
    Node* curr = head;
    Node* next = curr->sibling;

    while (next) {
        bool shouldLink = (curr->degree == next->degree) &&
                        (!next->sibling || next->sibling->degree != curr->degree);

        if (!shouldLink) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            curr->sibling = next->sibling;
            linkTrees(next, curr);
        } else {
            if (!prev) head = next;
            else prev->sibling = next;
            linkTrees(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }
}

void BinomialHeap::linkTrees(Node* child, Node* parent) {
    child->parent = parent;
    child->sibling = parent->child;
    parent->child = child;
    parent->degree++;
}

BinomialHeap::Node* BinomialHeap::reverseList(Node* node) {
    Node* prev = nullptr;
    while (node) {
        Node* next = node->sibling;
        node->sibling = prev;
        prev = node;
        node = next;
    }
    return prev;
}

void BinomialHeap::updateMin() {
    minNode = nullptr;
    for (Node* curr = head; curr; curr = curr->sibling) {
        if (!minNode || curr->key < minNode->key) {
            minNode = curr;
        }
    }
}

bool BinomialHeap::isEmpty() const {
    return head == nullptr;
}
}