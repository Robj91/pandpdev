//"Z" key
//"Hold to pull key" - rename this to another key code to change the key the player must hold

void main(void)
{
 if (&spush > 0)
 {
  //Sticky push is active.
  kill_this_task();
 }

 //retrieve the correct sprite, and if one doesn't exist, kill this off
 
 //declare local var for later and reset globals
 int &store;
 &save_x = 0;
retrieveloop:
 &save_y = 0;
 &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
 if (&save_x > 0)
 {
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  &save_y = sp_custom("PP-Shadow", &save_y, -1);
  if (&save_y == &save_x)
  {
   &save_y = sp_custom("PP-Parent", &save_x, -1);
   &save_y = sp_custom("touching", &save_y, -1);
   if (&save_y <= 0)
   {
    &save_x += 1;
    goto retrieveloop;
   }
   else
   {
    &save_y = sp_custom("PP-Parent", &save_x, -1);
    sp_custom("SpriteNum", &save_y, &save_x);
   }
  }
  else
  {
   //found a shadow from a missile or something else, we don't want it.
   &save_x += 1;
   goto retrieveloop;
  }   
 }

 if (&save_y <= 0)
  kill_this_task();

  //let's make sure a sprite is trying to be pulled before letting it do anything
  //check if push is active, if not we'll allow this to continue
  &save_x = sp_custom("pushactive", &save_y, -1);
  if (&save_x == 1)
   kill_this_task();
  
  //Has pull already been initiated on this sprite? If so.. don't do it again.
  &save_x = sp_custom("PButton", &save_y, -1);
  if (&save_x > 0)
   kill_this_task();

   //Retrieve that objects script number and run the pull procedure
   &save_x = is_script_attached(&save_y);
   if (&save_x > 0)
   {
    &store = &save_y;
    
    run_script_by_number(&save_x, "pull");


    //If Dink is touching more than one sprite at the same time let's make sure it activates too.
    //basically makes it so if Dink is touching two moveable sprites at once
    //He will actually be able to move the one he is facing towards and trying to pull
    //instead of possibly just retrieving one of them and then killing this off.
    //.. if that makes sense.
    &save_x = sp_custom("SpriteNum", &store, -1)
    if (&save_x > 0)
    {
     &save_x += 1;
     goto retrieveloop;     
    }

    kill_this_task();
   }
 
 kill_this_task();
}
 
