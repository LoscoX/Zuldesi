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

struct money{
	int val; //ID
	int x; //x position of coin
	int y; //y position of coin
	money* next;
};

typedef money* mony;

typedef segment_el* seg_list_ptr;

class Map{
    protected:
		int nc; //number of coins
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

        //coins
    	mony head_insert_coin(mony h,int val,int x,int y);
    	bool updateCoins(int x,int y); //check if one coin has to be removed
    	mony removeCoins(mony h,int cod); //remove one coin
    	mony FallCoins(mony h); //avoid coins on the air

    	mony coins;
};
