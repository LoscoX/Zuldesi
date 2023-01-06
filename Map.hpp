#include "Segment.hpp"

const char _WALL = '#';
const char _PLATFORM = '-';
const char _GROUND = '-';
const char _CEILING = '-';
const char _SPIKE = '^';
const char _BULLET = '*';
const char _PLAYER = '@';
const char _HAT = '^';

struct segment_el{ //element of segment list
    int id;
	Segment seg; //map
	segment_el* next;
};

typedef segment_el* seg_list_ptr;

class Map{
    private:
        int dim_x, dim_y;
        int trigger_start, trigger_end;
        seg_list_ptr segList;
        //Enemy enemies[];
    public:
        Map();
        Map(int difficulty);
        bool isSolid(int x, int y);
        int getDim_x();
        int getDim_y();
        string* toString();
};
