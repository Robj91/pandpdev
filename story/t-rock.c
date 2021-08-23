void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 0);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
  
 external("phisbo", "main"); 
 
 goto stopex;
}


void touch(void)
{
 &save_x = sp_custom("initiated", &current_sprite, -1);
 if (&save_x > 0)
 {
  sp_touch_damage(&current_sprite, 0);
  wait(&save_x);
  sp_custom("initiated", &current_sprite, 0);
 }
 external("phisbo", "touch"); 
 wait(200);
 external("phisbo", "touchreset");
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //an example of detecting if the player has moved the object to a certain spot on the screen.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 464, 204, 502, 222);
 if (&save_x == 1)
 { 
  //it's reached it's destination, stop the push/pull in it's tracks and assure touch damage does not reset to -1.
  external("phisbo", "terminate");
  
  freeze(1);
  
  //now retrieve the sign sprite and store the y
  &save_x = get_sprite_with_this_brain(20, 0);
  &save_x = is_script_attached(&save_x);
  if (&save_x > 0)
  {
   run_script_by_number(&save_x, "phase1");
  }
  
  //make this sprite moveable again
  external("phisbo", "initiate");
 }  
 
 goto stopex;
}

void MoveDetectAfter(void)
{
 goto stopex;
}

void pull(void)
{
 //call the pull procedure from phisbo
 external("phisbo", "pkey");

 goto stopex;
}

void talk(void)
{
 external("phisbo", "talk");
 &val1 = sp_custom("talkreturn", &current_sprite, -1);

 if (&val1 == 2)
 {
  external("dsmove", "main");
 }
 if (&val1 == 1)
 {
 } 

 external("phisbo", "touchreset");
 goto stopex;
}

void hit(void)
{
 external("phisbo", "hit");

 external("phisbo", "touchreset");
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}