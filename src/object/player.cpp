#include <string>
#include <iostream>
#include "player.hpp"

// initialize parameter
Player::Player(float _x, float _y, float _speedX, float _speedy, std::string path, int w, int h): Object(_x, _y, _speedX, _speedy, path, w, h){
	this->hp = 100;
	this->bullet_power = 3;
	this->exp = 0;
	this->energy = 100;
	this->bullet_cool = 0;
	this->playerbullet_counter = 0;
	this->dash_cool = 0;
	this->invincible_time = 0;
	this->max_energy = 100;
	this->increase_speed_time = 0;
	this->energy_per_bullet = 20;
	this->no_limit_timer = 0;
	this->frozen_time = 0;
	this->corrosion_time = 0;
	this->corrosion_hp = 0;
	this->burning_time = 0;
}

// update new position and reset speed to avoid repeat move
bool Player::update() {
	this->x += this->speedX;
	this->y += this->speedY;
	this->speedX = 0;
	this->speedY = 0;
	return true;
}


