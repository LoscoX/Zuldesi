#include "Segment.hpp"
#include "Enemy.hpp"

//legend for the character in the map
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

struct listenemy0{ //list of enemies type 0
	int val; //ID
	Enemy0 enemy; //enemy
	listenemy0* next;
};
struct listenemy1{ //list of enemies type1
	int val; //ID
	Enemy1 enemy; //enemy
	listenemy1* next;
};
struct listenemy2{ //list of enemies type2
	int val; //ID
	Enemy2 enemy; //enemy
	listenemy2* next;
};
struct listenemy3{ //list of enemies type3
	int val; //ID
	Enemy3 enemy; //enemy
	listenemy3* next;
};
struct listenemy4{ //list of enemies type4
	int val; //ID
	Enemy4 enemy; //enemy
	listenemy4* next;
};
struct listenemy5{ //list of enemies type5
	int val; //ID
	Enemy5 enemy; //enemy
	listenemy5* next;
};
struct listenemy6{ //list of enemies type6
	int val; //ID
	Enemy6 enemy; //enemy
	listenemy6* next;
};
struct listenemy7{ //list of enemies type7
	int val; //ID
	Enemy7 enemy; //enemy
	listenemy7* next;
};
struct listenemy8{ //list of enemies type8
	int val; //ID
	Enemy8 enemy; //enemy
	listenemy8* next;
};
struct listenemy9{ //list of enemies type8
	int val; //ID
	Enemy9 enemy; //enemy
	listenemy9* next;
};


typedef listenemy0* listenm0;
typedef listenemy1* listenm1;
typedef listenemy2* listenm2;
typedef listenemy3* listenm3;
typedef listenemy4* listenm4;
typedef listenemy5* listenm5;
typedef listenemy6* listenm6;
typedef listenemy7* listenm7;
typedef listenemy8* listenm8;
typedef listenemy9* listenm9;

typedef money* mony;

typedef segment_el* seg_list_ptr;

class Map{
    protected:
		int n0,n1,n2,n3,n4,n5,n6,n7,n8,n9; //number of enemies
		int nc; //number of coins
        int dim_x, dim_y; //dimension of the map
        int trigger_start, trigger_end; //trigger points (to pass from one map to another one)
        int trigger_market; //(for the market level)
        seg_list_ptr segList; //list of segments
    public:
        Map();
        Map(int difficulty); //map depends of difficulty
        bool isSolid(int x, int y); //check if your movement is ok with the respsect of structures of map
        bool isDanger(int x,int y); //check if your movement is danger
        int getDim_x(); //take dimension x
        int getDim_y(); //take dimension y
        string* toString(); //return the matrix of the map
		int get_trigger_start(); //take trigger start
		int get_trigger_end(); //take trigger end
		int get_trigger_market(); //take trigger market

        //coins
    	mony head_insert_coin(mony h,int val,int x,int y); //insert one coin in the list
    	bool updateCoins(int x,int y); //check if one coin has to be removed
    	mony removeCoins(mony h,int cod); //remove one coin
    	mony FallCoins(mony h); //avoid coins on the air

    	//Enemies

        //Enemies
    	listenm0 enemies0; //list of enemies type 0
    	listenm1 enemies1; //list of enemies type 1
    	listenm2 enemies2; //list of enemies type 2
    	listenm3 enemies3; //list of enemies type 3
    	listenm4 enemies4; //list of enemies type 4
    	listenm5 enemies5; //list of enemies type 5
    	listenm6 enemies6; //list of enemies type 6
    	listenm7 enemies7; //list of enemies type 7
    	listenm8 enemies8; //list of enemies type 8
    	listenm9 enemies9; //list of enemies type 8

    	listenm0 head_insert_enemy0(listenm0 h,Enemy0 e, int val); //add one enemy type0
    	listenm1 head_insert_enemy1(listenm1 h,Enemy1 e, int val); //add one enemy type1
    	listenm2 head_insert_enemy2(listenm2 h,Enemy2 e, int val); //add one enemy type2
    	listenm3 head_insert_enemy3(listenm3 h,Enemy3 e, int val); //add one enemy type3
    	listenm4 head_insert_enemy4(listenm4 h,Enemy4 e, int val); //add one enemy type4
    	listenm5 head_insert_enemy5(listenm5 h,Enemy5 e, int val); //add one enemy type5
    	listenm6 head_insert_enemy6(listenm6 h,Enemy6 e, int val); //add one enemy type6
    	listenm7 head_insert_enemy7(listenm7 h,Enemy7 e, int val); //add one enemy type7
    	listenm8 head_insert_enemy8(listenm8 h,Enemy8 e, int val); //add one enemy type8
    	listenm9 head_insert_enemy9(listenm9 h,Enemy9 e, int val); //add one enemy type9

    	listenm0 obj_remove_enemy0(listenm0 h,int cod,bool head); //delete one enemy type0 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm1 obj_remove_enemy1(listenm1 h,int cod,bool head); //delete one enemy type1 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm2 obj_remove_enemy2(listenm2 h,int cod,bool head); //delete one enemy type2 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm3 obj_remove_enemy3(listenm3 h,int cod,bool head); //delete one enemy type3 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm4 obj_remove_enemy4(listenm4 h,int cod,bool head); //delete one enemy type4 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm5 obj_remove_enemy5(listenm5 h,int cod,bool head); //delete one enemy type5 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm6 obj_remove_enemy6(listenm6 h,int cod,bool head); //delete one enemy type6 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm7 obj_remove_enemy7(listenm7 h,int cod,bool head); //delete one enemy type7 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm8 obj_remove_enemy8(listenm8 h,int cod,bool head); //delete one enemy type8 (head == true, clean memory when delete an element in the head, otherwise not)
    	listenm9 obj_remove_enemy9(listenm9 h,int cod,bool head); //delete one enemy type9 (head == true, clean memory when delete an element in the head, otherwise not)

    	string* initializeEnemies(string* mat); //initalize enemies

    	mony coins; //coins
};
