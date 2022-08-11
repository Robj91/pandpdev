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

 sp_custom("move_idle", &current_sprite, 1);

 //sp_custom("push_custom", &current_sprite, 400);
 
 //assures sprite is hard, touch damage -1, and if no speed has been set, defaults it to 1.
 //also does other important checks to set the push/pull system up properly.
 //external("phisbo", "main", -21, -35, 23, 9); 
 external("phisbo", "main", -21, -35, 23, 9);
 
 goto stopex;
}

void touch(void)
{
 //ADD ANY TOUCH PROCEDURE STUFF HERE.

 external("phisbo", "touch"); 
 goto stopex;
}

void push(void)
{
  return;  //Don't delete - required to stop it this procedure running twice, due to run_script_by_number, and then external returning to where it left off in this script

 //To use this, you need to set set "sp_custom("push", &current_sprite, 1);", in the main procedure(before the phisbo external line)
 //it will not use the push/pull system at all, and will instead run this procedure when Dink pushes the sprite

 //please note, to run this procedure, the push/pull system entirely terminates itself
 //so at the end of this procedure, to enable push/pull deteciton on the sprite again, do: external("phisbo", "initiate");
 goto stopex;
}

void push_custom(void)
{
  return;  //Don't delete - required to stop it this procedure running twice, due to run_script_by_number, and then external returning to where it left off in this script

 //To use this, you need to set set "sp_custom("push_custom", &current_sprite, 1);", in the main procedure(before the phisbo external line)
 //it will not use the push/pull system at all, and will instead run this procedure when Dink pushes the sprite
   // (won't even play dink pushing anim by default - this is your own push procedure built from scratch)

 //please note, to run this procedure, the push/pull system entirely terminates itself
  //so at the end of this procedure, to enable push/pull deteciton on the sprite again, do: external("phisbo", "initiate");
 goto stopex;
}

void MoveDetectDuring(void)
{
 goto stopex;
}

void IdleDetectDuring(void)
{
 goto stopex;
}

void MoveDetectAfter(void)
{
 //probably best to run external("phisbo", "terminate"); first up here to remove interruption from the push/pullsystem
   //Then at the end, to make the sprite move-able again do: external("phisbo", "initiate");
 goto stopex;
}

void IdleDetectAfter(void)
{
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return <= 0)
 {
  //ADD ANY TALK STUFF HERE.
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