void main(void)
{
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);	

 //retrieve the sign sprite, and save this sprite as a custom key inside it.
 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("rock", &save_x, &current_sprite);

 wait(1);

 sp_custom("setcollision", &current_sprite, 1);
 
 external("phisbo", "main", -50, -9, 52, 15); 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //everything is already setup to run in fireball.c's MoveDetectAfter, let's just run that
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("fireball", &save_x, -1);
 &save_x = is_script_attached(&save_x);
 if (&save_x > 0)
 {
  run_script_by_number(&save_x, "MoveDetectDuring");
 }

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

void stopex(void)
{
stopex:
 return;
}