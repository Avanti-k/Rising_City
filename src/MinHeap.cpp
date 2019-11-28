#include "MinHeap.h"
#include <iostream>

using namespace std;
MinHeap::MinHeap()
{
    //constructor
}

MinHeap::~MinHeap()
{
    //destructtor
}


/* Heapify up
 * when you insert new element and last then check if it has to go up*/

void MinHeap::heapify_up(int index)
{
    if(index == FIRST_INDEX)
        return;

    int parent_index = (index-1)/2;
    int ret = RBTree::compare_executed_time(min_heap[index], min_heap[parent_index]);
    if(ret == SMALLER)
    {
        RBNode* temp = min_heap[parent_index];
        min_heap[parent_index] = min_heap[index];
        min_heap[index] = temp;
        heapify_up(parent_index);
    }
}



/* Heapify down
 * when you do remove min, replace it with last element and delete last
 * the new top i.e first might be larger so heapify downwards */

void MinHeap::heapify_down(int index)
{
    int length = min_heap.size();
    int left_child = 2*index + 1;
    int right_child = 2*index + 2;

    if(left_child >= length)
        return; //index is a leaf

    int smallest = index; // maintains index of smallest value node
    int ret = RBTree::compare_executed_time(min_heap[left_child], min_heap[smallest]);

    if(ret == SMALLER)
    {
        smallest = left_child;
    }
    ret = RBTree::compare_executed_time(min_heap[right_child], min_heap[smallest]);

    if((right_child < length) && (ret == SMALLER))
    {
        smallest = right_child;
    }

    if(smallest != index)
    {
        //need to swap
        RBNode* temp = min_heap[index];
        min_heap[index] = min_heap[smallest];
        min_heap[smallest] = temp;
        heapify_down(smallest); // further call recursivly
    }

}


/* Copies last element to top. Used internally by remove_min */

void MinHeap::copy_last_to_top(int first, int last)
{
    min_heap[first] = min_heap[last]; // copies last element to first index
    min_heap.pop_back(); // delete the last element
}


/* Inserts new building node in minheap.
 * inserts new node at end and then
 * call heapify_up to adjust heap property
 * return type 0 - if error like capaicuty full
 *             1 - success */

int MinHeap::insert_new(RBNode * node)
{

    int new_index = min_heap.size();

    if(new_index == MAX_SIZE_MIN_HEAP)
    {
        // Heap already full
        cout<<"Error : Min heap capacity full\n"<<endl;
        return ERROR;
    }

    // always insert at last
    // min_heap[new_index] = &temp;
    min_heap.push_back(node);

    // might disturb the heap property of heapify up
    // starting from index = length
    heapify_up(new_index);

    print_min_heap();
    return SUCCESS;
}



 /* Remove min - pop topmost node and return it
    It will replace last element with node and then do heapify_down*/

RBNode * MinHeap::remove_min()
{

    if(min_heap.empty())
    {
        return NULL;
    }
    // copy min element to pointer
    RBNode * ret_node = min_heap.front();

    int last_index = min_heap.size() - 1;

    copy_last_to_top(FIRST_INDEX, last_index);

    // to adjust heap property
    heapify_down(FIRST_INDEX);
    //TODO delete this node from RBT also
    return ret_node;
}

/* Function to print heap while testing*/
void MinHeap::print_min_heap()
{
    int len = min_heap.size();
    cout<<"****************** MIN HEAP **************************"<<endl;
    cout <<"\nMin heap size = "<<len<<endl;
    for(int i = 0; i < len; i ++)
    {
        cout<<"Minheap["<<i<<"] = "<<"B_no : " <<min_heap[i]->get_building()->building_num<<" Exec time : "<<min_heap[i]->get_building()->executed_time<<endl;
    }
    cout<<"********************************************"<<endl;

}
