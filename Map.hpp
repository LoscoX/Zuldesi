#include "Segment.hpp"
#include "Enemy.hpp"
#include "Primenumbers.hpp"

//
/**
 * Legend for the character in the map.
 */

const char _WALL = '#';
const char _PLATFORM = '-';
const char _GROUND = '-';
const char _CEILING = '-';
const char _SPIKE = '^';
const char _BULLET = '*';
const char _PLAYER = '@';
const char _HAT = '^';

/**
 * Element of segment list.
 */
struct segment_el{
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

/**
 * List of enemies type 0.
 */
struct listenemy0{
	int val; //ID
	Enemy0 enemy; //enemy
	listenemy0* next;
};
/**
 * List of enemies type1.
 */
struct listenemy1{
	int val; //ID
	Enemy1 enemy; //enemy
	listenemy1* next;
};
/**
 * List of enemies type2.
 */
struct listenemy2{
	int val; //ID
	Enemy2 enemy; //enemy
	listenemy2* next;
};
/**
 * List of enemies type3.
 */
struct listenemy3{
	int val; //ID
	Enemy3 enemy; //enemy
	listenemy3* next;
};
/**
 * List of enemies type4.
 */
struct listenemy4{
	int val; //ID
	Enemy4 enemy; //enemy
	listenemy4* next;
};
/**
 * List of enemies type5.
 */
struct listenemy5{
	int val; //ID
	Enemy5 enemy; //enemy
	listenemy5* next;
};
/**
 * List of enemies type6.
 */
struct listenemy6{
	int val; //ID
	Enemy6 enemy; //enemy
	listenemy6* next;
};
/**
 * List of enemies type7.
 */
struct listenemy7{
	int val; //ID
	Enemy7 enemy; //enemy
	listenemy7* next;
};
/**
 * List of enemies type8.
 */
struct listenemy8{
	int val; //ID
	Enemy8 enemy; //enemy
	listenemy8* next;
};
/**
 * List of enemies type8.
 */
struct listenemy9{
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
        /**
         * number of enemies.
         */
		int n0,n1,n2,n3,n4,n5,n6,n7,n8,n9;
        /**
         * coins quantity.
         */
		int nc;
        /**
         * Map size.
         */
        int dim_x, dim_y;
        /**
         * Trigger points (to pass from one map to another one).
         */
        int trigger_start, trigger_end;
        /**
         * Market level trigger.
         */
        int trigger_market;
        /**
         * List of segments.
         */
        seg_list_ptr segList;
        /**
         * Variables enemies and coins generation.
         */
        int gen_x, gen_y;

        /**
         * Enemies.
         */

        /**
         * List of enemies type 0l
         */
    	listenm0 enemies0;
        /**
         * List of type 1 enemies.
         */
    	listenm1 enemies1;
        /**
         * List of type 2 enemies.
         */
    	listenm2 enemies2;
        /**
         * List of type 3 enemies.
         */
    	listenm3 enemies3;
        /**
         * List of type 4 enemies.
         */
    	listenm4 enemies4;
        /**
         * List of type 5 enemies.
         */
    	listenm5 enemies5;
        /**
         * List of type 6 enemies.
         */
    	listenm6 enemies6;
        /**
         * List of type 7 enemies.
         */
    	listenm7 enemies7;
        /**
         * List of type 8 enemies.
         */
    	listenm8 enemies8;
        /**
         * List of type 9 enemies.
         */
    	listenm9 enemies9;
        /**
         * Coins.
         */
       	mony coins;

    public:
        /**
         * Constructor.
         */
        Map();

        /**
         *
         * @param difficulty : map depends on difficulty.
         */
        Map(int difficulty);
        /**
         *
         * @param x
         * @param y
         * @return check if your movement is right within the respect of structures of map.
         */
        bool isSolid(int x, int y);
        /**
         *
         * @param x
         * @param y
         * @return check if your movement is dangerous.
         */
        bool isDanger(int x,int y);
        /**
         *
         * @return x dimension.
         */
        int getDim_x();
        /**
         *
         * @return y dimension.
         */
        int getDim_y();
        /**
         *
         * @return Matrix of the map.
         */
        string* toString();
        /**
         *
         * @return start trigger.
         */
		int get_trigger_start();
        /**
         *
         * @return end trigger.
         */
		int get_trigger_end();
        /**
         *
         * @return market trigger.
         */
		int get_trigger_market();
        /**
         * generate two admissible coordinates.
         * @param iniz_x
         * @param iniz_y
         * @param fin_x
         * @param fin_y
         */
		void generationRandom(int iniz_x,int iniz_y,int fin_x,int fin_y);
        /**
         *
         * @return randomly a segment to generate.
         */

        /**
         *  Coins.
         */

        /**
         *
         * @param h
         * @param val
         * @param x
         * @param y
         * @return insert one coin in the list.
         */
    	mony head_insert_coin(mony h,int val,int x,int y);
        /**
         *
         * @param x
         * @param y
         * @return check if one coin has to be removed.
         */
    	bool updateCoins(int x,int y);
        /**
         *
         * @param h
         * @param cod
         * @return remove one coin.
         */
    	mony removeCoins(mony h,int cod);
        /**
         *
         * @param h
         * @return avoid coins in the air.
         */
    	mony FallCoins(mony h);

        /**
         * Enemies.
         */

        /**
         *
         * @return list of enemies type 0.
         */
    	listenm0 getEnemies0();
        /**
         *
         * @return list of enemies type 1.
         */
    	listenm1 getEnemies1();
        /**
         *
         * @return list of enemies type 2.
         */
    	listenm2 getEnemies2();
        /**
         *
         * @return list of enemies type 3.
         */
    	listenm3 getEnemies3();
        /**
         *
         * @return list of enemies type 4.
         */
    	listenm4 getEnemies4();
        /**
         *
         * @return list of enemies type 5.
         */
    	listenm5 getEnemies5();
        /**
         *
         * @return list of enemies type 6.
         */
    	listenm6 getEnemies6();
        /**
         *
         * @return list of enemies type 7.
         */
    	listenm7 getEnemies7();
        /**
         *
         * @return list of enemies type 8.
         */
    	listenm8 getEnemies8();
        /**
         *
         * @return list of enemies type 9.
         */
    	listenm9 getEnemies9();

        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm0 setEnemies0(listenm0 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm1 setEnemies1(listenm1 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm2 setEnemies2(listenm2 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm3 setEnemies3(listenm3 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm4 setEnemies4(listenm4 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm5 setEnemies5(listenm5 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm6 setEnemies6(listenm6 tmp,int cod);
        /**
         * Update list of enemies type 0.
         * @param tmp
         * @param cod
         * @return
         */
    	listenm7 setEnemies7(listenm7 tmp,int cod);
        /**
        * Update list of enemies type 0.
        * @param tmp
        * @param cod
        * @return
        */
    	listenm8 setEnemies8(listenm8 tmp,int cod);
    	/**
        * Update list of enemies type 0.
        * @param tmp
        * @param cod
        * @return
        */
    	listenm9 setEnemies9(listenm9 tmp,int cod);

        /**
         * Add one enemy type0.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm0 head_insert_enemy0(listenm0 h,Enemy0 e, int val);
        /**
         * Add one enemy type1.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm1 head_insert_enemy1(listenm1 h,Enemy1 e, int val);
        /**
         * Add one enemy type2.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm2 head_insert_enemy2(listenm2 h,Enemy2 e, int val);
        /**
         * Add one enemy type3.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm3 head_insert_enemy3(listenm3 h,Enemy3 e, int val);
        /**
         * Add one enemy type4.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm4 head_insert_enemy4(listenm4 h,Enemy4 e, int val);
        /**
         * Add one enemy type5.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm5 head_insert_enemy5(listenm5 h,Enemy5 e, int val);
        /**
         * Add one enemy type6.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm6 head_insert_enemy6(listenm6 h,Enemy6 e, int val);
        /**
         * Add one enemy type7.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm7 head_insert_enemy7(listenm7 h,Enemy7 e, int val);
        /**
         * Add one enemy type8.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm8 head_insert_enemy8(listenm8 h,Enemy8 e, int val);
        /**
         * Add one enemy type9.
         * @param h
         * @param e
         * @param val
         * @return
         */
    	listenm9 head_insert_enemy9(listenm9 h,Enemy9 e, int val);


        /**
         * delete one enemy type0 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm0 obj_remove_enemy0(listenm0 h,int cod,bool head);
        /**
         * delete one enemy type1 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm1 obj_remove_enemy1(listenm1 h,int cod,bool head);
        /**
         * delete one enemy type2 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm2 obj_remove_enemy2(listenm2 h,int cod,bool head);
        /**
         * delete one enemy type3(head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm3 obj_remove_enemy3(listenm3 h,int cod,bool head);
        /**
         * delete one enemy type4 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm4 obj_remove_enemy4(listenm4 h,int cod,bool head);
        /**
         * delete one enemy type5 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm5 obj_remove_enemy5(listenm5 h,int cod,bool head);
        /**
         * delete one enemy type6 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm6 obj_remove_enemy6(listenm6 h,int cod,bool head);
        /**
         * delete one enemy type7 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm7 obj_remove_enemy7(listenm7 h,int cod,bool head);
        /**
         * delete one enemy type8 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm8 obj_remove_enemy8(listenm8 h,int cod,bool head);
        /**
         * delete one enemy type9 (head == true, clean memory when delete an element in the head, otherwise not)
         * @param h
         * @param cod
         * @param head
         * @return
         */
    	listenm9 obj_remove_enemy9(listenm9 h,int cod,bool head);

        /**
         * Initialize enemies.
         * @param mat
         * @return
         */
    	string* initializeEnemies(string* mat);

        /**
         * Take coins.
         * @return coins.
         */
    	mony getCoins();

};
