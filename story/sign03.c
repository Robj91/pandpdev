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
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return > 0)
 {
  external("dsmove", "main");
 }
 else
 {
  external("phisbo", "terminate");
  freeze(1);
  wait(0);
  say_stop("`%Welcome to the second part of the playground!", &current_sprite);
  say_stop("`%Move the people and objects around and make your own scene.", &current_sprite);
  unfreeze(1);
  external("phisbo", "initiate");
 }

 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}