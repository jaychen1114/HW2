#include "../engine/mainGame.hpp"
#include "../utils/log.hpp"
#include "../utils/imageProcess.hpp"
#include "../object/object.hpp"
#include "../object/player.hpp"
#include "../object/bullet.hpp"
#include "../object/asteroid.hpp"
#include "../object/potion.hpp"
#include "../AI/model.hpp"
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

int counter = 0;
int isPotion = 0;
int last_player2_x = 40;
int timer = 100;
int max = 100;
bool flag = 0;
bool is_repeat = false;
int repeat_timer = 0;
int repeat_angle = 0;

int counter2 = 0;
int isPotion2 = 0;
int last_player4_x = 20;
int timer2 = 100;
int max2 = 100;
bool flag2 = 0;
bool is_repeat2 = false;
int repeat_timer2 = 0;
int repeat_angle2 = 0;
void Model::initial(){}
int Model:: update(std::list<Object*> object_list , Player *player , Player *player2 , Player *teammate ,int type){ 
    if(type == 1){
    isPotion = 0;
    timer -= 1;
    max = player->max_energy;
    if(timer <= -100){
        timer = 0;
    }
    if(player->x >= teammate->x - 1){
        if(player->x <= teammate->x + 1){
        repeat_timer += 1;
        }
        else{
        repeat_timer = 0;
        }
    }
    else{
        repeat_timer = 0;
    }
    if(repeat_timer >= 50){
        is_repeat = true;
    }
    if(!is_repeat){
    for(auto from = object_list.begin() ; from != object_list.end() ;){
        if(dynamic_cast<Bullet*> (*from)){
            Bullet *bu = dynamic_cast<Bullet*> (*from);
            if(bu->type == 1){
                timer = 100;
            }
        }
        if(dynamic_cast<Potion*> (*from) ){
            Potion *pt = dynamic_cast<Potion*> (*from);
            if(pt->y <= 12 && pt->type == 0 && player->hp <= 70){
                key_state[ALLEGRO_KEY_RIGHT] = 0;
                key_state[ALLEGRO_KEY_LEFT] = 0;
                key_state[ALLEGRO_KEY_DOWN] = 0;
                key_state[ALLEGRO_KEY_UP] = 0;
                if(pt->x > player->x){
                    key_state[ALLEGRO_KEY_RIGHT] = 1;
                }
                if(pt->x < player->x){
                    key_state[ALLEGRO_KEY_LEFT] = 1;
                }
                if(pt->y >player->y + 2){
                        key_state[ALLEGRO_KEY_DOWN] = 1;
                    }
                if(pt->y < player->y){
                    key_state[ALLEGRO_KEY_UP] = 1;
                }
                isPotion = 1;
                break;
            }
            else if(pt->y <= 12 && pt->type != 0){
                key_state[ALLEGRO_KEY_RIGHT] = 0;
                key_state[ALLEGRO_KEY_LEFT] = 0;
                key_state[ALLEGRO_KEY_DOWN] = 0;
                key_state[ALLEGRO_KEY_UP] = 0;
                if(pt->x > player->x){
                    key_state[ALLEGRO_KEY_RIGHT] = 1;
                }
                if(pt->x < player->x){
                    key_state[ALLEGRO_KEY_LEFT] = 1;
                }
                if(pt->y >player->y){
                        key_state[ALLEGRO_KEY_DOWN] = 1;
                    }
                if(pt->y < player->y){
                    key_state[ALLEGRO_KEY_UP] = 1;
                }
                isPotion = 1;
                break;
            }
            else{
                    from ++;
                    counter = 1;
                }
        }
        if(counter == 0){
            from ++;
        }
        counter = 0;
    }
    if(timer <= 0 && isPotion == 0){
        key_state[ALLEGRO_KEY_RIGHT] = 0;
        key_state[ALLEGRO_KEY_LEFT] = 0;
        if(player->energy == max){
           key_state[ALLEGRO_KEY_ENTER] = 1;
           flag = 1;
        }
        if(player->energy <= 20){
            key_state[ALLEGRO_KEY_ENTER] = 0;
            flag = 0;
        }
        if(flag){
            if(player->x > player2->x){
                key_state[ALLEGRO_KEY_LEFT] = 1;
            }
            if(player->x < player2->x){
                key_state[ALLEGRO_KEY_RIGHT] = 1;
            }
        }
        else{
            if(player->x > player2->x + 5){
                key_state[ALLEGRO_KEY_LEFT] = 1;
            }
            if(player->x < player2->x - 5){
                key_state[ALLEGRO_KEY_RIGHT] = 1;
            }
            if(player->x < player2->x + 5 && player->x >= player2->x && player->x <= 75){
                key_state[ALLEGRO_KEY_RIGHT] = 1;
            }
            if(player->x > player2->x - 5 && player->x < player2->x && player->x >= 2){
                key_state[ALLEGRO_KEY_LEFT] = 1;
            }
        }
    }
    if(timer > 0 && isPotion == 0){
        for(auto from = object_list.begin() ; from != object_list.end() ; from ++){
		    for(auto to = object_list.begin() ; to != object_list.end() ; to ++){
                if(dynamic_cast<Player*> (*from) && dynamic_cast<Bullet*> (*to)){
				    auto bu = dynamic_cast<Bullet*> (*to);
                    auto pl = dynamic_cast<Player*> (*from);
                    if(bu->type == 1 && pl == player){
                        if(player->x > player2->x && player2->x - last_player2_x < 0){
                            key_state[ALLEGRO_KEY_RIGHT] = 0;
                            key_state[ALLEGRO_KEY_LEFT] = 0;
                            key_state[ALLEGRO_KEY_DOWN] = 0;
                            key_state[ALLEGRO_KEY_UP] = 0;
                            player->dash_cool = 1;
                        }
                        if(player->x < player2->x && player2->x - last_player2_x > 0){
                            key_state[ALLEGRO_KEY_RIGHT] = 0;
                            key_state[ALLEGRO_KEY_LEFT] = 0;
                            key_state[ALLEGRO_KEY_DOWN] = 0;
                            key_state[ALLEGRO_KEY_UP] = 0;
                            player->dash_cool = 1;
                        }
                    }
                }
            }
        }
    }
    if(isPotion == 0 && player->dash_cool == 0 && timer > 0){
        key_state[ALLEGRO_KEY_RIGHT] = 0;
        key_state[ALLEGRO_KEY_LEFT] = 0;
        key_state[ALLEGRO_KEY_DOWN] = 0;
        key_state[ALLEGRO_KEY_UP] = 0;
            if(player->x > player2->x + 12){
                key_state[ALLEGRO_KEY_LEFT] = 1;
            }
            if(player->x < player2->x - 12){
                key_state[ALLEGRO_KEY_RIGHT] = 1;
            }
            if(player->x < player2->x + 12 && player->x >= player2->x && player->x <= 73){
                key_state[ALLEGRO_KEY_RIGHT] = 1;
            }
            if(player->x > player2->x - 12 && player->x < player2->x && player->x >= 4){
                key_state[ALLEGRO_KEY_LEFT] = 1;
            }
            if(player2->y - player->y > 14){
                key_state[ALLEGRO_KEY_DOWN] = 1;
            }
            if(player2->y - player->y < 14){
                key_state[ALLEGRO_KEY_UP] = 1;
            }
    }
    }
    else{
        key_state[ALLEGRO_KEY_RIGHT] = 0;
        key_state[ALLEGRO_KEY_LEFT] = 0;
        key_state[ALLEGRO_KEY_DOWN] = 0;
        key_state[ALLEGRO_KEY_UP] = 0;
        if(player->x <= player2->x){
            repeat_angle = 1;
        }
        if(player->x <= player2->x && repeat_angle == 1){
            key_state[ALLEGRO_KEY_RIGHT] = 1;
        }
        else if(repeat_angle == 1){
            is_repeat = false;
            repeat_angle = 0;
        }
        if(player->x > player2->x){
            repeat_angle = 2;
        }
        if(player->x > player2->x && repeat_angle == 2){
            key_state[ALLEGRO_KEY_LEFT] = 1;
        }
        else if(repeat_angle == 2){
            is_repeat = false;
            repeat_angle = 0;
        }
    }
    if(timer > 0){
        if(player->energy ==  max){
            key_state[ALLEGRO_KEY_ENTER] = 1;
        }
        if(player->energy <= 20){
            key_state[ALLEGRO_KEY_ENTER] = 0;
        }
    }
    last_player2_x = player2->x;
}




if(type == 2){
    isPotion2 = 0;
    timer2 -= 1;
    max2 = player->max_energy;
    if(timer2 == -100){
        timer2 = 0;
    }
    if(teammate->x >= player->x - 1){
        if(teammate->x <= player->x + 1){
        repeat_timer2 += 1;
        }
        else{
        repeat_timer2 = 0;
        }
    }
    else{
        repeat_timer2 = 0;
    }
    if(repeat_timer2 >= 50){
        std:: cout << repeat_timer2 << std::endl;
        is_repeat2 = true;
    }
    if(!is_repeat2){
    for(auto from = object_list.begin() ; from != object_list.end() ;){
        if(dynamic_cast<Bullet*> (*from)){
            Bullet *bu = dynamic_cast<Bullet*> (*from);
            if(bu->type == 3){
                timer2 = 100;
            }
        }
        if(dynamic_cast<Potion*> (*from) ){
            Potion *pt = dynamic_cast<Potion*> (*from);
            if(pt->y <= 12 && pt->type == 0 && player->hp <= 70){
                key_state[ALLEGRO_KEY_L] = 0;
                key_state[ALLEGRO_KEY_J] = 0;
                key_state[ALLEGRO_KEY_K] = 0;
                key_state[ALLEGRO_KEY_I] = 0;
                if(pt->x > player->x){
                    key_state[ALLEGRO_KEY_L] = 1;
                }
                if(pt->x < player->x){
                    key_state[ALLEGRO_KEY_J] = 1;
                }
                if(pt->y >player->y + 2){
                        key_state[ALLEGRO_KEY_K] = 1;
                    }
                if(pt->y < player->y){
                    key_state[ALLEGRO_KEY_I] = 1;
                }
                isPotion2 = 1;
                break;
            }
            else if(pt->y <= 12 && pt->type != 0){
                key_state[ALLEGRO_KEY_L] = 0;
                key_state[ALLEGRO_KEY_J] = 0;
                key_state[ALLEGRO_KEY_K] = 0;
                key_state[ALLEGRO_KEY_I] = 0;
                if(pt->x > player->x){
                    key_state[ALLEGRO_KEY_L] = 1;
                }
                if(pt->x < player->x){
                    key_state[ALLEGRO_KEY_J] = 1;
                }
                if(pt->y >player->y){
                        key_state[ALLEGRO_KEY_K] = 1;
                    }
                if(pt->y < player->y){
                    key_state[ALLEGRO_KEY_I] = 1;
                }
                isPotion2 = 1;
                break;
            }
            else{
                    from ++;
                    counter2 = 1;
                }
        }
        if(counter2 == 0){
            from ++;
        }
        counter2 = 0;
    }
    if(timer2 <= 0 && isPotion2 == 0){
        key_state[ALLEGRO_KEY_L] = 0;
        key_state[ALLEGRO_KEY_J] = 0;
        if(player->energy == max2){
           key_state[ALLEGRO_KEY_P] = 1;
           flag = 1;
        }
        if(player->energy <= 20){
            key_state[ALLEGRO_KEY_P] = 0;
            flag = 0;
        }
        if(flag){
            if(player->x > player2->x){
                key_state[ALLEGRO_KEY_J] = 1;
            }
            if(player->x < player2->x){
                key_state[ALLEGRO_KEY_L] = 1;
            }
        }
        else{
            if(player->x > player2->x + 5){
                key_state[ALLEGRO_KEY_J] = 1;
            }
            if(player->x < player2->x - 5){
                key_state[ALLEGRO_KEY_L] = 1;
            }
            if(player->x < player2->x + 5 && player->x >= player2->x && player->x <= 75){
                key_state[ALLEGRO_KEY_L] = 1;
            }
            if(player->x > player2->x - 5 && player->x < player2->x && player->x >= 2){
                key_state[ALLEGRO_KEY_J] = 1;
            }
        }
    }
    if(timer2 > 0 && isPotion2 == 0){
        for(auto from = object_list.begin() ; from != object_list.end() ; from ++){
		    for(auto to = object_list.begin() ; to != object_list.end() ; to ++){
                if(dynamic_cast<Player*> (*from) && dynamic_cast<Bullet*> (*to)){
				    auto bu = dynamic_cast<Bullet*> (*to);
                    auto pl = dynamic_cast<Player*> (*from);
                    if(bu->type == 3 && pl == player){
                        if(player->x > player2->x && player2->x - last_player4_x < 0){
                            key_state[ALLEGRO_KEY_L] = 0;
                            key_state[ALLEGRO_KEY_J] = 0;
                            key_state[ALLEGRO_KEY_K] = 0;
                            key_state[ALLEGRO_KEY_I] = 0;
                            player->dash_cool = 1;
                        }
                        if(player->x < player2->x && player2->x - last_player4_x > 0){
                            key_state[ALLEGRO_KEY_L] = 0;
                            key_state[ALLEGRO_KEY_J] = 0;
                            key_state[ALLEGRO_KEY_K] = 0;
                            key_state[ALLEGRO_KEY_I] = 0;
                            player->dash_cool = 1;
                        }
                    }
                }
            }
        }
    }
    if(isPotion2 == 0 && player->dash_cool == 0 && timer2 > 0){
        key_state[ALLEGRO_KEY_L] = 0;
        key_state[ALLEGRO_KEY_J] = 0;
        key_state[ALLEGRO_KEY_K] = 0;
        key_state[ALLEGRO_KEY_I] = 0;
            if(player->x > player2->x + 12){
                key_state[ALLEGRO_KEY_J] = 1;
            }
            if(player->x < player2->x - 12){
                key_state[ALLEGRO_KEY_L] = 1;
            }
            if(player->x < player2->x + 12 && player->x >= player2->x && player->x <= 73){
                key_state[ALLEGRO_KEY_L] = 1;
            }
            if(player->x > player2->x - 12 && player->x < player2->x && player->x >= 4){
                key_state[ALLEGRO_KEY_J] = 1;
            }
            if(player2->y - player->y > 14){
                key_state[ALLEGRO_KEY_K] = 1;
            }
            if(player2->y - player->y < 14){
                key_state[ALLEGRO_KEY_I] = 1;
            }
    }
    }
    else{
        key_state[ALLEGRO_KEY_L] = 0;
        key_state[ALLEGRO_KEY_J] = 0;
        key_state[ALLEGRO_KEY_K] = 0;
        key_state[ALLEGRO_KEY_I] = 0;
        if(player->x >= player2->x){
            repeat_angle2 = 1;
        }
        if(player->x >= player2->x && repeat_angle2 == 1){
            key_state[ALLEGRO_KEY_J] = 1;
        }
        else if(repeat_angle2 == 1){
            is_repeat2 = false;
            repeat_angle2 = 0;
        }
        if(player->x < player2->x){
            repeat_angle2 = 2;
        }
        if(player->x < player2->x && repeat_angle2 == 2){
            key_state[ALLEGRO_KEY_L] = 1;
        }
        else if(repeat_angle2 == 2){
            is_repeat2 = false;
            repeat_angle2 = 0;
        }
    }
    if(timer2 > 0){
        if(player->energy ==  max2){
            key_state[ALLEGRO_KEY_P] = 1;
        }
        if(player->energy <= 20){
            key_state[ALLEGRO_KEY_P] = 0;
        }
    }
    last_player4_x = player2->x;
    }
    return 0;
}

