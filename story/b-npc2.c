void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 
 
 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 15);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 15);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -18, -9, 24, 14); 
 
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
 goto stopex;
}

void pull(void)
{
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