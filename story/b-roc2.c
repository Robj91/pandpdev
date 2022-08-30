void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1); 
 
 sp_custom("setcollision", &current_sprite, 1);
  
 external("phisbo", "main", -30, -12, 19, 2); 
  
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