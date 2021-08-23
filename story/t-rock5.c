void main(void)
{
 //check if we're using DinkHD, if so, use the DinkHD specific script so we don't have bugs
 if (&vcheck == 110)
 {
  &save_x = &current_sprite;
  script_attach(0);
  sp_script(&save_x, "t-rock5HD");
  kill_this_task();
 }

 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 2);

 sp_custom("trimleft", &current_sprite, 10);
 sp_custom("trimtop", &current_sprite, 10);
 sp_custom("trimright", &current_sprite, 10);
 sp_custom("trimbottom", &current_sprite, 10);
 
 external("phisbo", "main", -21, -35, 23, 9); 
 
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
 external("tutorial", "boxmove", -21, -35, 23, 9, &current_sprite);
 
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
 }
 if (&val1 == 1)
 {
  say("A moveable rock with collision activated for all versions + all hardbox edges trimmed by 10.", 1);
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