#include <iostream>
#include <fstream>
#include "Building.h"
#include "MinHeap.h"
#include "RBTree.h"

using namespace std;

#define MAX_EXEC_TIME 5

/* function to input file*/
/*
int input_read()
{
   har data[100];
    ifstream ip_file;
    ip_file.open("../project_material/input.txt");
    string line;
    while (getline(ip_file, line)) {
        // using printf() in all tests for consistency
        printf("%s\n", line.c_str());
    }

    return 0;

}
*/

int main()
{
    cout << "Hello world!" << endl;
    MinHeap mh;
    RBTree RBT;
    Building b(7,30);
    Building b1 (6,10);
    Building b2 (5,40);
    Building b3 (4,20);
    Building b4 (3,50);
    Building b5 (2,50);
    Building b6 (1,50);


    RBNode r(&b);
    RBT.RBTree_insert(&r);

     RBNode r1(&b1);
    RBT.RBTree_insert(&r1);

     RBNode r2(&b2);
    RBT.RBTree_insert(&r2);

     RBNode r3(&b3);
    RBT.RBTree_insert(&r3);

     RBNode r4(&b4);
    RBT.RBTree_insert(&r4);

    RBNode r5(&b5);
    RBT.RBTree_insert(&r5);

    RBNode r6(&b6);
    RBT.RBTree_insert(&r6);

    cout<<"RBTREE root = "<<RBT.RBRoot->get_building()->building_num<<endl;
    cout<<"\nPrinting tree in order"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\nLevel order"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);


    RBT.deleteByVal(4);
    cout<<"\nPrinting after DELETE tree in order"<<endl;
    RBT.inorderHelper(RBT.RBRoot);
    cout<<"\nLevel order"<<endl;
    RBT.levelOrderHelper(RBT.RBRoot);
    //RBNode r1(&b1, nullptr,nullptr,nullptr,BLACK);
    //RBTree_insert(&r1);
    //cout<<"done"<<endl;
   /* mh.insert_new(&b);
    mh.insert_new(&b1);
    mh.insert_new(&b2);
    mh.insert_new(&b3);
    mh.insert_new(&b4);


    cout<<" 0: "<<mh.min_heap[0]->building_num<<endl;
    cout<<" 1: "<<mh.min_heap[1]->building_num<<endl;
    cout<<" 2: "<<mh.min_heap[2]->building_num<<endl;
    cout<<" 3: "<<mh.min_heap[3]->building_num<<endl;
    cout<<" 4: "<<mh.min_heap[4]->building_num<<endl;

    for( int i = 0; i < mh.min_heap.size(); i ++)
    {
        cout<<i<<" = "<< mh.min_heap[i]->building_num<<endl;
    }

    /*int bid = b.Building::get_building_num();
    cout << "bid = "<<bid<<endl;
    cout<<" total time = "<<b.Building::get_total_time();
    cout<<"exec time = "<< b.Building::get_executed_time();
    */
   /* Building * temp = mh.remove_min();
    cout<< "Removed min building id = "<< temp->building_num<< "ET = "<<temp->executed_time<<endl;


    for( int i = 0; i < mh.min_heap.size(); i ++)
    {
        cout<<i<<" = "<< mh.min_heap[i]->building_num<<endl;
    }*/

    return 0;
}

/*
void executeBuilding(int bid)
{
 int start = global_timer;
 int target = bid.completeion_time - bid.executed_time;
 while(1)
 {
    global_timer ++;
    if(global_timer - start == MAX_EXEC_TIME)
    {
        // execution time reached 5 so update executed time of bldn in data structures and break
        // update executed time
        bid.executed_time += MAX_EXEC_TIME;
        // update this bid in MIN Heap
        break;
    }
    else if(global_timer - start == target)
    {
        // building got completed
        // Print it
        // remove from data strucures.
        break;
    }
 }

}
*/
