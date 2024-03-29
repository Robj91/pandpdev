void main(void)
{
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);	
 sp_nodraw(&current_sprite, 1);
 sp_nohit(&current_sprite, 1);

 //retrieve the sign sprite, and save this sprite as a custom key inside it.
 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("rubble", &save_x, &current_sprite);

 //example of moving multiple sprites as 1, with a fake hardbox, without creating a new sprite!
 //use this sprite as an invisible moveable sprite and spawn 5 rubble sprites that lock to it
 //this sprites hardbox is the right size to cover all 4 rubble sprites.
 int &rubble;
 
 //First rubble sprite
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x -= 13;
 &save_y -= 16;
 &rubble = create_sprite(&save_x, &save_y, 0, 97, 2);
 sp_nohit(&rubble, 1);
 sp_que(&rubble, -500);
 //save the sprite in a custom key to retrieve it later
 sp_custom("rubble1", &current_sprite, &rubble);
 
 //second rubble sprite
 &save_x += 48;
 &rubble = create_sprite(&save_x, &save_y, 0, 97, 2);
 sp_nohit(&rubble, 1);
 sp_que(&rubble, -500);
 sp_custom("rubble2", &current_sprite, &rubble);
 
 //third rubble sprite
 &save_y += 19;
 &rubble = create_sprite(&save_x, &save_y, 0, 97, 2);
 sp_nohit(&rubble, 1);
 sp_que(&rubble, -500);
 sp_custom("rubble3", &current_sprite, &rubble);

 //fourth rubble sprite
 &save_x -= 48;
 &rubble = create_sprite(&save_x, &save_y, 0, 97, 2);
 sp_nohit(&rubble, 1);
 sp_que(&rubble, -500);
 sp_custom("rubble4", &current_sprite, &rubble);

 //fifth rubble sprite
 &save_x += 31;
 &save_y -= 8;
 &rubble = create_sprite(&save_x, &save_y, 0, 97, 2);
 sp_nohit(&rubble, 1);
 sp_que(&rubble, -500);
 sp_custom("rubble5", &current_sprite, &rubble);

 wait(1);

 sp_custom("setcollision", &current_sprite, 1);
 
 external("phisbo", "main", -57, -43, 59, 7); 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //ADJUST position of rubble sprites to re-lock to invisible moving object.
 //First rubble sprite
 &rubble = sp_custom("rubble1", &current_sprite, -1); 
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x -= 13;
 &save_y -= 16;
 sp_x(&rubble, &save_x);
 sp_y(&rubble, &save_y);

 //second rubble sprite
 &rubble = sp_custom("rubble2", &current_sprite, -1); 
 &save_x += 48;
 sp_x(&rubble, &save_x);
 sp_y(&rubble, &save_y);
 
 //third rubble sprite
 &rubble = sp_custom("rubble3", &current_sprite, -1); 
 &save_y += 19;
 sp_x(&rubble, &save_x);
 sp_y(&rubble, &save_y);

 //fourth rubble sprite
 &rubble = sp_custom("rubble4", &current_sprite, -1); 
 &save_x -= 48;
 sp_x(&rubble, &save_x);
 sp_y(&rubble, &save_y);

 //fifth rubble sprite
 &rubble = sp_custom("rubble5", &current_sprite, -1); 
 &save_x += 31;
 &save_y -= 8;
 sp_x(&rubble, &save_x);
 sp_y(&rubble, &save_y);

 //everything is already setup to run in fireball.c's MoveDetectDuring, let's just run that
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