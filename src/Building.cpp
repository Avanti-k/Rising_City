#include "Building.h"
#include <iostream>
using namespace std;

/* Parameterised constructor */
Building::Building(int building_num, int total_time, int executed_time)
{
    this->building_num = building_num;
    this->total_time = total_time;
    this->executed_time = executed_time;
}

/* Gives building id */
int Building::get_building_num()
{
    return this->building_num;
}

/* Gives already executed time for bulding */
int Building::get_executed_time()
{
    return this->executed_time;
}

/* Gives total time for building */
int Building::get_total_time()
{
    return this->total_time;
}

Building::~Building()
{
    //dtor
}

// return true if b1 < b2
bool Building::compare_executed_time(Building * b1, Building * b2)
{
    if(b1->executed_time < b2->executed_time)
    {
        return true;
    }
    else if (b1->executed_time > b2->executed_time)
    {
        return false;
    }
    else if(b1->executed_time == b2->executed_time)
    {
        return (b1->building_num < b2->building_num)?true: false;
    }

}
