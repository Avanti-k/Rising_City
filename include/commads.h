#ifndef COMMADS_H
#define COMMADS_H

/*
This class is to keep track of commands
every time a command comes it is parsed and stored in this
*/
class commads
{
    public:
        commads();
        virtual ~commads();

    protected:

    private:
    int time;       // arrival time of command
    //std::string cmd;     // insert / print / printbuilding
    int args[2];    // stores building num in case of print building  and in case of insert stores building num and completion time.
};

#endif // COMMADS_H
