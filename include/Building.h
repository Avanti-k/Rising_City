#ifndef BUILDING_H
#define BUILDING_H

#define MAX_EXEC_DAYS 5
class Building
{
    public:
        Building(int building_num, int total_time, int executed_time = 0);
        virtual ~Building();
        int building_num;
        int executed_time;
        int total_time;
        int get_building_num();
        int get_total_time();
        int get_executed_time();

};


#endif // BUILDING_H
