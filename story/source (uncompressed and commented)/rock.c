void main(void)
{
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);	

 //retrieve the sign sprite, and save this sprite as a custom key inside it.
 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("rock", &save_x, &current_sprite);

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -50, -9, 52, 15); 
 
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
 goto stopex;
}

void MoveDetectAfter(void)
{
 //everything is already setup to run in fireball.c's MoveDetectAfter, let's just run that
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("fireball", &save_x, -1);
 &save_x = is_script_attached(&save_x);
 if (&save_x > 0)
 {
  run_script_by_number(&save_x, "MoveDetectAfter");
 }

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