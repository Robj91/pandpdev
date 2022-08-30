void main(void)
{
 sp_speed(&current_sprite, 3);
 sp_timing(&current_sprite, 0);	

 wait(1); 

 sp_custom("setcollision", &current_sprite, 1);
 
 external("phisbo", "main", -49, -27, 30, 9); 
 
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