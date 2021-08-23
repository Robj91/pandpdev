//YOU ONLY NEED TO TOUCH THIS SCRIPT IF YOU HAVE UNIQUE ITEMS, MAGICS, BUFFS OR DEBUFFS THAT ALTER DINKS SPEED IN YOUR DMOD. If so, read the comments, and add them into this script.
//Script that handles reducing sprites speed to match dinks when push/pull initiates, and resetting dinks speed when push/pull terminates.


void speedlock(void)
{
 //With this new system, the speed of the move is based on the sprite's speed, not Dink's. Dink's speed is set to "-1" (same as sp_speed of 0), and locked relative to the sprite.
 //so if a sprites speed is higher than Dinks current speed, we need to reduce it to match dink's, cause it would look weird if Dink moves faster than his current set speed.
 //If you have anything that affect dinks speed in your dmod (custom item, or buff system), add a check below, using the herb boots check as an exmaple (copy and paste it)

 //&arg1 = sprite currently being moved by Dink

 //necessary wait line.. to make sure Dink's speedlock of "-1" takes effect prior to running this.
 wait(0);
 
 //retrieve original speed of the sprite being moved
 &save_y = sp_custom("oldspeed", &arg1, -1);
 
//HERB BOOTS CHECK 
 //enter compare magic/weapon line for speed buff item
 &save_x = compare_weapon("item-bt");
 if (&save_x > 0)
 {
  //Dink has herb boots armed
  
  //set &save_x to the sp_speed equivelant of this item's "set_dink_speed" line. (see DinkC Reference for sp_speed equivelant of Dink speed settings).
  &save_x = 6;
  
  if (&save_y >= 6)
  {
   //the speed of this sprite is higher than 6 - reduce it to 6, to match Dink's speed when herb boots is equipped.
   sp_speed(&arg1, &save_x);
   sp_timing(&arg1, 0);
  }
  else
  {
   //Include this else section in your buffs/debuffs, this makes sure that if the player equips the item mid push/pull, the speed will update.
   external("DinkSpeed", "SpeedUpdate", &arg1, &save_x);
  }
  kill_this_task();
 }
//END OF HERB BOOTS CHECK

 //**ADD CHECKS BELOW**//
  //Add any checks here for speed magic, weapons, buffs and debuffs that affects dink speed. Then finish with with a kill_this_task(); 
  //Sprite being moved is stored in &arg1, use that. NOT &current_sprite.

//All checks must be before this point, this is what will run if all other checks return false. 
 if (&save_y >= 3)
 {
  //all other buff checks false, dink must be normal speed, this object's speed is greater so let's temporarily lower it
  sp_speed(&arg1, 3);
  sp_timing(&arg1, 0);
 }
 kill_this_task();
}

void resetspeed(void)
{
 //after push or pull has ended, this procedure is called to reset dinks speed. Unfortunately dink's speed is not able to be stored in a variable.
 //in most dmods it will be an item or magic that gives dink the speed boost. If you have anything else that affect dinks speed in your dmod (custom item, or buff system)
 //Then add a check for it below in the "ADD CHECKS HERE" section, indicicated by the clearly marked comment. That way, Dinks speed is reset correctly after push/pull terminates.

 //&arg1 = sprite currently being moved by Dink

 //HERB BOOTS - Copy and paste this section for each speed buff item/magic in your Dmod, and edit it to suit the item/magic.
 &save_x = compare_weapon("item-bt");
 if (&save_x > 0)
 {
  //dink has herb boots armed - reset his speed to herb boots speed
  set_dink_speed(2);
  sp_frame_delay(1, 30);
  kill_this_task();
 } 

 //**ADD CHECKS BELOW**//
  //Add any checks here for speed magic, weapons, buffs and debuffs that affects dink speed.
  //If for some reason you need to do anything related to the sprite that was being moved, Use &arg1 here. NOT &current_sprite.

 //All checks must be before this point, this is what will run if all other checks return false. 
 set_dink_speed(3);
 sp_frame_delay(1, 0);
 
 kill_this_task();
}

void SpeedUpdate(void)
{
 //No need to touch this procedure.

//&arg1 = sprite, &arg2 = speed of current buff/debuff.
 &save_x = sp_custom("oldspeed", &arg1, -1);
 if (&save_x <= &arg2)
  sp_speed(&arg1, &save_x);
 else
  sp_speed(&arg1, &arg2);
}