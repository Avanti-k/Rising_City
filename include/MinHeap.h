#ifndef MINHEAP_H
#define MINHEAP_H
#include "Building.h"
#include <vector>
#include "RBTree.h"

#define MAX_SIZE_MIN_HEAP 2000
#define FIRST_INDEX 0

using namespace std;
enum error{
    ERROR,
    SUCCESS
};

class MinHeap
{
    public:

        MinHeap();
        virtual ~MinHeap();
        int insert_new(RBNode *);
        RBNode * remove_min();
        vector <RBNode *> min_heap;

    private:

        void heapify_up(int index);
        void heapify_down(int index);
        void copy_last_to_top(int first, int last);
        void print_min_heap();

};

#endif // MINHEAP_H
