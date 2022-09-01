void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);
 
 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 15);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 15);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -22, -14, 23, 14); 
 
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
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}