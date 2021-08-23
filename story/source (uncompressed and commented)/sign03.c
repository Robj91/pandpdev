void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -12, -9, 12, 9); 
 
 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
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
 
 if (sp_custom("talkreturn", &current_sprite, -1) == 2)
 {
  external("dsmove", "main");
 }
 if (sp_custom("talkreturn", &current_sprite, -1) == 1)
 {
  external("phisbo", "terminate");
  freeze(1);
  wait(0);
  say_stop("`%Welcome to the second part of the playground!", &current_sprite);
  say_stop("`%Move the people and objects around and make your own scene.", &current_sprite);
  unfreeze(1);
  external("phisbo", "initiate");
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