/*
 * Game.hpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <typeinfo>
#include "Board.hpp"
#include "Map.hpp"

/**
 * Max number of power-up type gun.
 */
const int NUM_GUNS = 4;
/**
 * Max number of power-up type bonus.
 */
const int NUM_BONUS = 5;
/**
 * Max number of power-up type actionable.
 */
const int NUM_ACTIVE = 3;

struct map_el{
	int id{};
	Map map;
	map_el* next{};
	map_el* prev{};
};

typedef map_el* map_list;

class Game{
public:
    /**
     * Constructor with parameters.
     * @param height
     * @param width
     */
	Game(int height,int width);

    /**
     *
     * Function for the map.
     */
    /**
     * Restart the map.
     * @param difficulty
     */
	void restartMap(int difficulty);
    /**
     * Switch to the next map.
     * @param dir
     * @param difficulty
     */
	void nextMap(int dir, int difficulty);
    /**
     * Print the map.
     */
	void PrintMap();

	/**
	 * Main functions.
	 */

    /**
     * Main game.
     */
	void updateState();
    /**
     * Refresh the board.
     */
	void redraw();
    /**
     *
     * @return If the game is over.
     */
	bool isOver();

	/**
	 * Market function.
	 */
    /**
     * Initialize power-up.
     */
	void initializePowerUp();
    /**
     * Draw power-up.
     * @param pwp
     */
	void drawPowerUp(Powerup pwp[]);
    /**
     * Delete power-up.
     * @param pwp
     */
	void deletePowerup(Powerup pwp[]);
    /**
     * Activate market.
     */
	void market();
    /**
     * Build market.
     */
	void market_build();
    /**
     * Write power up's description.
     * @param i
     */
	void drawDescription(int i);
    /**
     * Remove power's up description.
     * @param i
     */
	void deleteDescription(int i);

    /**
     * Function for the movement
     */

    /**
     * Game interaction between player and structure map.
     * @param choice
     */
	void PlayerCanMove(int choice);
    /**
     * Game interaction between player and structure map when you fly.
     * @param choice
     */
	void PlayerCanFly(int choice);
    /**
     * Game interaction between enemy0 and structure map.
     * @param h
     */
	void Enemy0CanMove(listenm0 h);
    /**
     * Game interaction between enemy1 and structure map.
     * @param h
     */
	void Enemy1CanMove(listenm1 h);
    /**
     * Game interaction between enemy2 and structure map.
     * @param h
     */
	void Enemy2CanMove(listenm2 h);
    /**
     * Game interaction between enemy3 and structure map.
     * @param h
     */
	void Enemy3CanMove(listenm3 h);
    /**
     * Game interaction between enemy4 and structure map.
     * @param h
     */
	void Enemy4CanMove(listenm4 h);
    /**
     * Game interaction between enemy5 and structure map.
     * @param h
     */
	void Enemy5CanMove(listenm5 h);
    /**
     * Game interaction between enemy6 and structure map.
     * @param h
     */
	void Enemy6CanMove(listenm6 h);
    /**
     * Game interaction between enemy7 and structure map.
     * @param h
     */
	void Enemy7CanMove(listenm7 h);
    /**
     * Game interaction between enemy8 and structure map.
     * @param h
     */
	void Enemy8CanMove(listenm8 h);
    /**
     * Game interaction between enemy9 and structure map.
     * @param h
     */
	void Enemy9CanMove(listenm9 h);
    /**
     * Map movement.
     */
	void mapMovement();
    /**
     * Enemies movement.
     */
	void enemyMovement();
    /**
     * Manage player's gravity.
     */
	void PlayerDown();
    /**
     * Handle the direction of the enemy based on the position of the player.
     * @param e
     * @return
     */
	int directionSmartEnemy5(Enemy5 e);
    /**
     * Handle the direction of the enemy based on the position of the player.
     * @param e
     * @return
     */
	int directionSmartEnemy7(Enemy7 e);
    /**
     * Handle the direction of the enemy based on the position of the player.
     * @param e
     * @return
     */
	int directionSmartEnemy8(Enemy8 e);

    /**
     * Graphic function.
     */

    /**
     * Display life parameter user interface.
     */
	void displayLife();
    /**
     * Display wallet parameter user interface.
     */
	void displayCoins();
    /**
     * Display title user interface.
     */
	void displayGame();
    /**
     * Display bullets quantity parameter user interface.
     */
	void displayBullets();
    /**
     * Display points parameter user interface.
     */
	void displayPoints();
    /**
     * Display market title user interface.
     */
	void displayMarket();
    /**
     * Display power-up user interface.
     */
	void displayPowerup();

	/**
	 * function for collision
	 */

    /**
     * Game interaction between Enemy without gun and Player.
     * @param e
     */
	void interaction(Enemy0 e);

    /**
     * Enemy death for bullets.
     * @param tmp
     * @return
     */
	bool enemydeath(bullt tmp);
    /**
     * Enemy death for explosive bullets.
     * @param tmp
     * @return
     */
	bool enemydeath2(bullt tmp);

    /**
     * Function for bullets collision.
     */

    /**
     * Game interaction between Enemy with gun and Player.
     * @param tmp
     * @return
     */
	bool interactionBullet(bullt tmp);
    /**
     * Handle shooting.
     */
	void shooting();
    /**
     * Delete bullets of the Player.
     * @param tmp
     * @return
     */
	bullt deletePlayerBullets(bullt tmp);
    /**
     * Delete explosive bullets of the Player.
     * @param tmp
     * @return
     */
	bullt deletePlayerExplosiveBullets(bullt tmp);
    /**
     * Delete Enemy6's bullets.
     * @param tmp
     * @param e
     * @return
     */
	bullt deleteEnemy6Bullets(bullt tmp,listenm6 e);
    /**
     * Delete Enemy7's bullets.
     * @param tmp
     * @param e
     * @return
     */
	bullt deleteEnemy7Bullets(bullt tmp,listenm7 e);
    /**
     * Delete Enemy8's bullets.
     * @param tmp
     * @param e
     * @return
     */
	bullt deleteEnemy8Bullets(bullt tmp,listenm8 e);
    /**
     * Delete Enemy9's bullets.
     * @param tmp
     * @param e
     * @return
     */
	bullt deleteEnemy9Bullets(bullt tmp,listenm9 e);

	/**
	 * Handle coins part.
	 */
	void handleCoins();
    /**
     * Handle maps part, market part.
     */
	void handleMaps();
    /**
     * Handle displacement.
     */
	void handleDisplay();

    /**
     * Update functions.
     */

    /**
     * Redraw the board.
     */
	void UpdateBoard();
    /**
     * Update difficulty value.
     */
	void updateDifficulty();

	/**
	 * Save file.
	 */
	void save() const;

protected:
    /**
     * Power up spawned in the market.
     */
	Powerup spawn_powerup[3];

    /**
     * Power-ups
     */

    /**
     * Guns power-up.
     */
	Powerup guns[NUM_GUNS];
    /**
     * Bounds power-up.
     */
	Powerup bonus[NUM_BONUS];
    /**
     * Actionable power-up.
     */
	Powerup active[NUM_ACTIVE];

    /**
     * Variable for camera position.
     */
	int xMin;
    /**
     * Height of market power-ups.
     */
	int HEIGHT_MARKET;
	/**
	 * Constants for drawing.
	 */
	int draw_cost1;
	int draw_cost2;
	int draw_cost3;
    /**
     * Check if you're in the market.
     */
	bool Market_Active;
    /**
     * Check if you have to build the market.
     */
	bool Market_Build;
    /**
     * Check if you have bought one power-up.
     */
	bool bought1,bought2,bought3;
    /**
     * Game time parameter.
     */
	int time;
    /**
     * Level difficulty parameter. It depends on the number of power-up you have. It handles the generation of the map.
     */
	int difficulty;
    /**
     * Board.
     */
	Board board;
    /**
     * Player.
     */
	Player player;
    /**
     * Map.
     */
	Map map;
    /**
     * Map data structure matrix.
     */
	string* matrix{};
    /**
     * Check if game is over.
     */
	bool game_over;
    /**
     * List of maps.
     */
	map_list mapList;
};
