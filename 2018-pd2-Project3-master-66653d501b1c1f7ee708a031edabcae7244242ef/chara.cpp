#include "chara.h"

chara::chara()
{

}

void chara::level_up(){
    if(bullet_mode!=2){
      bullet_mode++;
    }
}
chara::~chara(){
    delete this;
}
