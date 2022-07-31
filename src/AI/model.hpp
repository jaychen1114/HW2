#ifndef _MODEL_HPP
#define _MODEL_HPP
#include "../utils/log.hpp"
#include "../utils/imageProcess.hpp"
#include "../object/object.hpp"
#include "../object/player.hpp"
#include "../object/bullet.hpp"
#include "../object/asteroid.hpp"
#include "../object/potion.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <random>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


extern const int width;
extern const int height;


class Model{
	public:
		// called by game start
		void initial();
		// called by every update time
		// GameMap is current game status
		// return integer array is as same as the key_state array
		int update(std::list<Object*> object_list  , Player *player , Player *player2 ,Player *teammate , int type);
};

#endif