void main(void)
{
 //This decides how fast the sprite will move when push/pulled. Dink will match this and keep up with the sprite, but will not exceed his current speed.
 //If this is set higher than Dinks speed, it will automatically be reduced by the push/pull system to match his current speed (handled by "Dinkspeed.c")
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 
 //ADD ANY MAIN PROCEDURE SCRIPTING FOR YOUR SPRITE HERE, Before the wait line.
 
 wait(1);

 sp_custom("setcollision", &current_sprite, 3);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 10);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 6);
 
 //assures sprite is hard, touch damage -1, and if no speed has been set, defaults it to 1.
 //also does other important checks to set the push/pull system up properly.
 //external("phisbo", "main", -21, -35, 23, 9); 
 external("phisbo", "main", -21, -35, 23, 9);
 
 goto stopex;
}

void touch(void)
{
 //ADD ANY TOUCH PROCEDURE STUFF HERE.

 external("phisbo", "touch", 1); 
 goto stopex;
}

void ppbypass(void)
{
 //return(99);
 
 //This procedure is used to trigger your own push/pull event, instead of the actual push/pull system activating.
 //Basically, if you uncomment the above return line, the push/pull system will detect the return value of '99'
 //and will ONLY execute it's script up to the point where it has determined that Dink is pushing against the sprite
 //then it will terminate the push/pull system and everything else in this procedure will execute. 
 //keep in mind that if you want the push/pull system to work again you will need to do: external("phisbo", "initiate");
 //You can use if statements with the above return line to make "ppbypass()" only run on certain conditions.
 
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

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return <= 0)
 {
  //ADD ANY TALK STUFF HERE.
  external("phisbo", "terminate", &current_sprite);
  external("phisbo", "initiate", &current_sprite);
 }
 else
 {
  external("dsmove", "main");
 }

 //required external line, to prevent bugs.
 external("phisbo", "touchreset");
 goto stopex;
}

void hit(void)
{
 //This external line is necessary to prevent bugs.
 external("phisbo", "hit");

 //required external line to prevent bugs
 external("phisbo", "touchreset");
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}