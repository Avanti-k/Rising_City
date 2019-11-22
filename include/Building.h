#ifndef BUILDING_H
#define BUILDING_H

#define MAX_EXEC_DAYS 5
class Building
{
    public:
        //Building(int building_num, int total_time);
        Building(int building_num, int total_time, int executed_time = 0);
        //Building();
        virtual ~Building();
        int get_building_num();
        int get_total_time();
        int get_executed_time();
        //void static Building * get_building(Building *);

        bool static compare_executed_time(Building * b1, Building * b2);
    //protected:

    //private:
    int building_num;
    int executed_time;
    int total_time;
    int RBT_index;
    //int MH_index;
};


#endif // BUILDING_H
