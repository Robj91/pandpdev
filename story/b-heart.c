//Moveable heart sprite that looks like a collectible but isn't

void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);
 
 sp_custom("setcollision", &current_sprite, 1);
 
 external("phisbo", "main", -25, -11, 24, 11); 
 
 goto stopex;
}


void touch(void)
{
 //make this heart talk and let dink know it's not collectible the first time he touches it.
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &save_y = editor_seq(&save_x, -1);
 if (&save_y <= 0)
 {
  sp_touch_damage(&current_sprite, 0);
  freeze(1);
  say_stop("`1HA! FOOLED YA!", &current_sprite);
  wait(200);
  say_stop("What the..", 1);
  wait(200);
  say_Stop("`1I'm not collectable.. just move-able.", &current_sprite);
  wait(200);
  say_stop("Right..", 1);
  &save_x = sp_editor_num(&current_sprite);
  editor_seq(&save_x, 1); 
  unfreeze(1);
  sp_touch_damage(&current_sprite, -1);
 }

 external("phisbo", "touch"); 
 
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return > 0)
 {
  //Dink is currently moving the sprite  - say a random 'moving a sprite' say line.
  external("dsmove", "main");
 }

 goto stopex;
}

void hit(void)
{
 say("I'm a heartbreaker!", 1);
}

void stopex(void)
{
stopex:
 return;
}