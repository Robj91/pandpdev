void main(void)
{
 //The sprite's speed will decied how fast Dink can move it.
 //If you set this higher than Dinks speed, it will only move as fast as Dink current speed though.
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 
 //Add any normal Main procedure stuff you want here.
 
 //required wait line
 wait(1);

 //external line below to call "main" proc in "phisbo.c", to make this sprite move-able.
 //Please pass the hardbox values as &arg1-&arg4. 
 //It expects them in the same order as they are written in dink.ini, so you can just copy & paste the 4 hardbox values for your sprite.
 external("phisbo", "main"); 

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}

void touch(void)
{
 //ADD ANY TOUCH PROCEDURE STUFF HERE.

 //external line to make push/pull detection work
 external("phisbo", "touch"); 

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}

//STOPEX PROCEDURE - external bugfix. Please make sure this remains the LAST procedure in this script.
void stopex(void)
{
stopex:
 return;
}