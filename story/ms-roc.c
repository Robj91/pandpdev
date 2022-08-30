void main(void)
{
 //The sprite's speed will decied how fast Dink can move it.
 //If you set this higher than Dinks speed, it will cap it while push/pull is happening so DInk doesn't get an unnatural speed boost for no reason.
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1); 
 
 //set collision on this sprite
 sp_custom("setcollision", &current_sprite, 1);

 //make trim the hardbox to make our own fake "push/pull" collision box.
 sp_custom("trimleft", &current_sprite, 10);
 sp_custom("trimtop", &current_sprite, 20);
 sp_custom("trimright", &current_sprite, 10);
 sp_custom("trimbottom", &current_sprite, 6);

 //external line below to call "main" proc in "phisbo.c", to make this sprite move-able.
 //Please pass the hardbox values as &arg1-&arg4. 
 //It expects them in the same order as they are written in dink.ini, so you can just copy & paste the 4 hardbox values for your sprite. 
 external("phisbo", "main", -21, -35, 23, 9); 

 //do not delete "goto stopex;" line. It is there to prevent bugs.  
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