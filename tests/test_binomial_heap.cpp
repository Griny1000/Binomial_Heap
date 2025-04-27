#include "../src/binomial_heap.h"
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>

using namespace bh;

TEST(BinomialHeapTest, InsertAndGetMin) {
    BinomialHeap heap;
    heap.insert(5);
    ASSERT_EQ(heap.getMin(), 5);
    
    heap.insert(3);
    ASSERT_EQ(heap.getMin(), 3);
    
    heap.insert(7);
    ASSERT_EQ(heap.getMin(), 3);
}

TEST(BinomialHeapTest, ExtractMinBasic) {
    BinomialHeap heap;
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    
    ASSERT_EQ(heap.getMin(), 3);
    heap.extractMin();
    ASSERT_EQ(heap.getMin(), 5);
    heap.extractMin();
    ASSERT_EQ(heap.getMin(), 7);
    heap.extractMin();
    ASSERT_TRUE(heap.isEmpty());
}

TEST(BinomialHeapTest, MergeTwoHeaps) {
    BinomialHeap heap1;
    heap1.insert(5);
    heap1.insert(2);
    
    BinomialHeap heap2;
    heap2.insert(7);
    heap2.insert(1);
    
    heap1.merge(heap2);
    
    ASSERT_EQ(heap1.getMin(), 1);
    ASSERT_TRUE(heap2.isEmpty());
}

TEST(BinomialHeapTest, MergeWithEmptyHeap) {
    BinomialHeap heap1;
    heap1.insert(3);
    
    BinomialHeap heap2; // empty
    
    heap1.merge(heap2);
    ASSERT_EQ(heap1.getMin(), 3);
    
    heap2.merge(heap1);
    ASSERT_EQ(heap2.getMin(), 3);
}

TEST(BinomialHeapTest, InsertDuplicateValues) {
    BinomialHeap heap;
    heap.insert(5);
    heap.insert(5);
    heap.insert(5);
    
    ASSERT_EQ(heap.getMin(), 5);
    heap.extractMin();
    ASSERT_EQ(heap.getMin(), 5);
    heap.extractMin();
    ASSERT_EQ(heap.getMin(), 5);
    heap.extractMin();
    ASSERT_TRUE(heap.isEmpty());
}

TEST(BinomialHeapTest, LargeInputTest) {
    BinomialHeap heap;
    std::vector<int> numbers;
    
    // Generate 1000 random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 10000);
    
    for (int i = 0; i < 1000; ++i) {
        int num = dist(gen);
        numbers.push_back(num);
        heap.insert(num);
    }
    
    // Verify extraction order
    std::sort(numbers.begin(), numbers.end());
    for (int expected : numbers) {
        ASSERT_EQ(heap.getMin(), expected);
        heap.extractMin();
    }
    ASSERT_TRUE(heap.isEmpty());
}

TEST(BinomialHeapTest, EmptyHeapOperations) {
    BinomialHeap heap;
    
    ASSERT_TRUE(heap.isEmpty());
    ASSERT_THROW(heap.getMin(), std::runtime_error);
    
    // ExtractMin on empty heap should do nothing
    heap.extractMin();
    ASSERT_TRUE(heap.isEmpty());
}

TEST(BinomialHeapTest, SingleElementHeap) {
    BinomialHeap heap;
    heap.insert(42);
    
    ASSERT_EQ(heap.getMin(), 42);
    ASSERT_FALSE(heap.isEmpty());
    
    heap.extractMin();
    ASSERT_TRUE(heap.isEmpty());
    ASSERT_THROW(heap.getMin(), std::runtime_error);
}

TEST(BinomialHeapTest, ComplexMergeOperations) {
    BinomialHeap heap1;
    heap1.insert(10);
    heap1.insert(2);
    heap1.insert(15);
    
    BinomialHeap heap2;
    heap2.insert(5);
    heap2.insert(1);
    heap2.insert(20);
    
    heap1.merge(heap2);
    
    ASSERT_EQ(heap1.getMin(), 1);
    heap1.extractMin();
    
    ASSERT_EQ(heap1.getMin(), 2);
    heap1.extractMin();
    
    ASSERT_EQ(heap1.getMin(), 5);
    heap1.extractMin();
    
    ASSERT_EQ(heap1.getMin(), 10);
    heap1.extractMin();
    
    ASSERT_EQ(heap1.getMin(), 15);
    heap1.extractMin();
    
    ASSERT_EQ(heap1.getMin(), 20);
    heap1.extractMin();
    
    ASSERT_TRUE(heap1.isEmpty());
}

TEST(BinomialHeapTest, MergeSelfTest) {
    BinomialHeap heap;
    heap.insert(5);
    heap.insert(3);
    
    heap.merge(heap); // merging with itself
    
    ASSERT_EQ(heap.getMin(), 3);
    ASSERT_FALSE(heap.isEmpty());
    
    heap.extractMin();
    ASSERT_EQ(heap.getMin(), 5);
}

TEST(BinomialHeapTest, ReverseOrderInsert) {
    BinomialHeap heap;
    for (int i = 100; i > 0; --i) {
        heap.insert(i);
    }
    
    for (int i = 1; i <= 100; ++i) {
        ASSERT_EQ(heap.getMin(), i);
        heap.extractMin();
    }
    ASSERT_TRUE(heap.isEmpty());
}

TEST(BinomialHeapTest, InsertAfterExtract) {
    BinomialHeap heap;
    heap.insert(5);
    heap.extractMin();
    
    heap.insert(3);
    ASSERT_EQ(heap.getMin(), 3);
    
    heap.insert(2);
    ASSERT_EQ(heap.getMin(), 2);
    
    heap.insert(7);
    ASSERT_EQ(heap.getMin(), 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}