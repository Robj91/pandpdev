//for the purpose of streamlining, this script contains the code that is called in any moveable sprite script
//instead of copy pasting bulk loads of code into every sprites script that I want to add this system into.

void main(void)
{
 //decide on which base custom keys we are using (Dink, sprite, or none(default)
 //idle
 &save_y = sp_custom("base_idle", &current_sprite, -1);
 if (&save_y <= 0)
 {
  &save_y = sp_custom("base_idle", 1, -1);
  if (&save_y <= 0)
  {
   &save_y = 10;
  }
  sp_custom("base_idle", &current_sprite, &save_y);
 }

 //walk
 &save_y = sp_custom("base_walk", &current_sprite, -1);
 if (&save_y <= 0)
 {
  &save_y = sp_custom("base_walk", 1, -1);
  if (&save_y <= 0)
  {
   &save_y = 70;
  }
  sp_custom("base_walk", &current_sprite, &save_y);
 }

 //push
 &save_y = sp_custom("base_push", &current_sprite, -1);
 if (&save_y <= 0)
 {
  &save_y = sp_custom("base_push", 1, -1);
  if (&save_y <= 0)
  {
   &save_y = 310;
  }
  sp_custom("base_push", &current_sprite, &save_y);
 }

 //preload push sequence
 &save_y += 2;
 preload_seq(&save_y);
 &save_y += 2;
 preload_seq(&save_y);
 &save_y += 2;
 preload_seq(&save_y);
 &save_y += 2;
 preload_seq(&save_y);

 //make sure this sprite has a touch damage of -1, and it's hard.
 sp_touch_damage(&current_sprite, -1);
 sp_hard(&current_sprite, 0);
 
 //make sure the rock has a speed value
 &save_x = sp_speed(&current_sprite, -1);
 if (&save_x <= 0)
 {
  //player forgot to set a speed! we'll give it one..
  sp_speed(&current_sprite, 1);
 }
 
 //save the speed and timing of the sprite in case we need to change it
 &save_x = sp_speed(&current_sprite, -1);
 &save_y = sp_timing(&current_sprite, -1);
 sp_custom("PPoldspeed", &current_sprite, &save_x);
 sp_custom("PPoldtiming", &current_sprite, &save_y); 
 
 //we'll update map hardness just in case hardness wasn't set
 draw_hard_sprite(&current_sprite); 

 //if any of the &arg 1 - 4 vars are not equal to 0, the player has probably provided hardbox values. 
 //It's possible for one hardbox value to be 0.
 //So don't make the (!= 0) condition mandatory for &arg1 - 4.
 //If any of these return something other than 0, the player has attempted to pass hardbox values
 //If they didn't pass the properly, or missed one, that's their problem to fix.
 &save_x = 0;
 if (&arg1 != 0)
  &save_x = 1;
 
 if (&arg2 != 0)
  &save_x = 1;

 if (&arg3 != 0)
  &save_x = 1;
  
 if (&arg4 != 0)
  &save_x = 1;

 if (&save_x == 1)
 {
  //Let future scripts know that hardbox boundaries have been provided, so no need for automatic hardbox detection. Yay for no lag!
  sp_custom("PPHBOX", &current_sprite, 1);
 
  //let's save the hardbox boundaries for later use
  sp_custom("PPLEFT-BOX", &current_sprite, &arg1);
  sp_custom("PPTOP-BOX", &current_sprite, &arg2);
  sp_custom("PPRIGHT-BOX", &current_sprite, &arg3);
  sp_custom("PPBOTTOM-BOX", &current_sprite, &arg4);

  //Check whether to allow collision system or not
  &save_x = sp_custom("setcollision", &current_sprite, -1);
  if (&save_x > 0)
  {
   //allow collision
   sp_custom("PPAllowCollision", &current_sprite, 1);
  }
 }
 
 kill_this_task();
}

void touch(void)
{ 
 //manual termination has been called by author and push/pull has not been re-initiated. Do not proceed.
 &save_x = sp_custom("PPterminated", &current_sprite, -1);
 if (&save_x > 0)
  return;

 sp_touch_damage(&current_sprite, 0);

   //create a shadow sprite so we can easily retrieve it without messing with other sprites or using a global
   //Could use a custom key, but we want something that we can find with the least amount of looping through sprites.
   //We save the active sprite number of the retrievable shadow sprite in a custom key attached to &current_sprite
   //That way we can cross reference it - to avoid some rare bugs.
   &save_x = sp_custom("PP-Shadow", &current_sprite, -1);
   &save_y = sp_custom("PP-Parent", &save_x, -1);
   if (&save_y != &current_sprite)
   {
    //the shadow sprite doesn't currently exist, so we can go ahead and create one.
    &save_x = sp_pseq(&current_sprite, -1);
    &save_y = sp_pframe(&current_sprite, -1);
    &save_x = create_sprite(1, 1, 15, &save_x, &save_y);
    sp_brain(&save_x, 15);
    sp_brain_parm(&save_x, &current_sprite);
    sp_nodraw(&save_x, 1);
    sp_nohit(&save_x, 1);
    sp_custom("PP-Shadow", &current_sprite, &save_x);
    
    //also save this sprite in a custom key attached to the shadow sprite.
    //this allows us to cross reference. Just relying on retrieving "sp_brain_parm" of the shadow can cause bugs.
    //If the developer has attached more than 1 shadow to their moveable sprite.
    //Because if the shadow dies before "PP-Shadow" is reset, another shadow might take the same active sprite #
    //And if that gets detected as the "PP-Shadow" sprite, things will mess up.
    sp_custom("PP-Parent", &save_x, &current_sprite);
   }
   else
   {
    //shadow sprite already exists
    //somehow this has run twice, we don't want that, kill it off.
    //this shouldn't even really happen, but I'll leave it here for a fail safe just in case.
    kill_this_task();
   } 

   //decide on which base custom keys we are using (Dink, sprite, or none(default)
   //idle
   &save_y = sp_custom("base_idle", &current_sprite, -1);
   if (&save_y <= 0)
   {
    &save_y = sp_custom("base_idle", 1, -1);
    if (&save_y <= 0)
    {
     &save_y = 10;
    }
    sp_custom("base_idle", &current_sprite, &save_y);
   }

   //walk
   &save_y = sp_custom("base_walk", &current_sprite, -1);
   if (&save_y <= 0)
   {
    &save_y = sp_custom("base_walk", 1, -1);
    if (&save_y <= 0)
    {
     &save_y = 70;
    }
    sp_custom("base_walk", &current_sprite, &save_y);
   }

   //push
   &save_y = sp_custom("base_push", &current_sprite, -1);
   if (&save_y <= 0)
   {
    &save_y = sp_custom("base_push", 1, -1);
    if (&save_y <= 0)
    {
     &save_y = 310;
    }
    sp_custom("base_push", &current_sprite, &save_y);
   }

   //save the players directional sequence in a custom key so we can assure it hasn't changed later on.
   &save_x = sp_pseq(1, -1);
   &save_y = sp_custom("base_walk", &current_sprite, -1);
   sp_custom("PPpseq-origin", &current_sprite, &save_x);
   //check if seq is correct for pushing and pulling, and save result in custom key 
   if (&save_x > &save_y)
   {
    &save_y += 10;
    if (&save_x < &save_y)
    {
     &save_y = math_mod(&save_x, 2);
     if (&save_y == 0)
     {
      //Here we have determined that Dink's seq is a correct walk seq, and an even number (we don't want diags)
      sp_custom("PPCanPush", &current_sprite, 1);
     }
    }
   }
  
   &save_x = sp_custom("PPCanPush", &current_sprite, -1);
   if (&save_x <= 0)
   {
    //no point continuing if Dink can't push
    sp_custom("PPreset-required", &current_sprite, 1);    
    goto touchend; 
   }  

   //store dinks direction - this won't return any diags - that was filtered out above with the math_mod checks.
   &save_x = sp_dir(1, -1);
   sp_custom("pushdir", &current_sprite, &save_x);

   //work out the pulldir - it will be opposite the pushdir
   &save_x = sp_custom("pushdir", &current_sprite, -1);
   if (&save_x == 2) 
    sp_custom("pulldir", &current_sprite, 8);
    
   if (&save_x == 4)
    sp_custom("pulldir", &current_sprite, 6); 
    
   if (&save_x == 6)
    sp_custom("pulldir", &current_sprite, 4);
    
   if (&save_x == 8)
    sp_custom("pulldir", &current_sprite, 2);
   
   //and set the move-axis custom key. 1 = x axis. 2 = y axis.
   if (&save_x == 2)
    sp_custom("move-axis", &current_sprite, 2);
   
   if (&save_x == 4)
    sp_custom("move-axis", &current_sprite, 1);  
   
   if (&save_x == 6)
    sp_custom("move-axis", &current_sprite, 1);  
    
   if (&save_x == 8)
    sp_custom("move-axis", &current_sprite, 2);
    
   //set whether will be pushing in a positive or negative direction. (Adding or reducing X or Y value as we push)
   if (&save_x == 2)
    sp_custom("PushPosNeg", &current_sprite, 2);
   
   if (&save_x == 4)
    sp_custom("PushPosNeg", &current_sprite, 1);  
   
   if (&save_x == 6)
    sp_custom("PushPosNeg", &current_sprite, 2);  
    
   if (&save_x == 8)
    sp_custom("PushPosNeg", &current_sprite, 1);   

   //set whether will be pulling in a positive or negative direction. (Adding or reducing X or Y value as we push)
   &save_x = sp_custom("pulldir", &current_sprite, -1);
   if (&save_x == 2)
    sp_custom("PullPosNeg", &current_sprite, 2);
   
   if (&save_x == 4)
    sp_custom("PullPosNeg", &current_sprite, 1);  
   
   if (&save_x == 6)
    sp_custom("PullPosNeg", &current_sprite, 2);  
    
   if (&save_x == 8)
    sp_custom("PullPosNeg", &current_sprite, 1);  
  
   //store dinks coordinates
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);
   sp_custom("dinkox", &current_sprite, &save_x);
   sp_custom("dinkoy", &current_sprite, &save_y);

   //store current_sprite's coordinates
   &save_x = sp_x(&current_sprite, -1);
   &save_y = sp_y(&current_sprite, -1);
   sp_custom("spriteox", &current_sprite, &save_x);
   sp_custom("spriteoy", &current_sprite, &save_y);

   //copy push delays from relevant custom keys if they are set
   &save_x = sp_custom("push", &current_sprite, -1);
   if (&save_x > 1)
   {
    sp_custom("pushdelay", &current_sprite, &save_x);
   }
   &save_y = sp_custom("push_custom", &current_sprite, -1);
   if (&save_y > 1)
   {
    sp_custom("pushdelay", &current_sprite, &save_y);
   }

   /////////
   //TIMER//
   /////////
   //start the timer before push can activate
    //skip the rest of this if no pushdelay is set.
    &save_x = sp_custom("pushdelay", &current_sprite, -1);
    if (&save_x > 0)
    {
     sp_custom("PPtimerdone", &current_sprite, 0);
     &save_y = &current_sprite;
     &save_x = spawn("hup");
     sp_custom("PPtimerscript", &current_sprite, &save_x);
    }
    else
    {
     goto timercont;
    }

   timerwaitloop:
    wait(1);
   
    //retrieve the old x, compare it against the new x
    &save_x = sp_custom("dinkox", &current_sprite, -1);
    &save_y = sp_x(1, -1);
    if (&save_x == &save_y)
    { 
     //retrieve the old y, compare it against the new y
     &save_x = sp_custom("dinkoy", &current_sprite, -1);
     &save_y = sp_y(1, -1);
     if (&save_x == &save_y)
     { 
      //retrieve the old direction, compare it agianst the new direction
      &save_x = sp_custom("PPpseq-origin", &current_sprite, -1);
      &save_y = sp_pseq(1, -1);
      if (&save_x == &save_y)
      {
       //everything is still correct for push/pull
       //check if the timer is done and if not, loop again
       &save_x = sp_custom("PPtimerdone", &current_sprite, -1);
       if (&save_x > 0)
       {
        goto timercont;
       }
       else
       {
        goto timerwaitloop;
       }
      }
     }
    }

    //Dinks coords or sequence has changed, this tells us he's no longer pushing against the sprite
    &save_x = sp_custom("PPtimerscript", &current_sprite, -1);
    if (&save_x > 0)
    {
     run_script_by_number(&save_x, "killtimer");
    }
    sp_custom("PPreset-required", &current_sprite, 1);    
    goto touchend; 
   /////////////
   //TIMER END//
   /////////////
 
 timercont:
    //initiate push and pull
    external("PhisHyb", "hybrid", &arg1);

touchend: 
 //since this touch proc is the start of the external chain, everything will lead back here
 //so I just made a custom key that can be changed to let this part know whether to do the sprite reset.
 &save_x = sp_custom("PPreset-required", &current_sprite, -1);
 if (&save_x == 1)
 {  
  //reset the "PPreset-required" custom key to 0
  sp_custom("PPreset-required", &current_sprite, 0);

  //kill off the shadow sprite used to retrieve and identify this moveable object
  &save_x = sp_custom("PP-Shadow", &current_sprite, -1);
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  if (&save_y == &current_sprite)
   sp_active(&save_x, 0);
  
  //reset other custom keys
  sp_custom("PPCanPush", &current_sprite, 0);
  sp_custom("PPspeedlock", &current_sprite, 0);
  sp_custom("PPSkipSpeedReset", &current_sprite, 0);

  &save_x = sp_custom("PPterminated", &current_sprite, -1);
  if (&save_x <= 0)
  {
   //only reset touch damage if a manual termination hasn't been called
   sp_touch_damage(&current_sprite, -1);  
  } 
 }
 
 kill_this_task(); 
}

void terminate(void)
{ 
 //Push/Pull is being manually terminated out of course.
 //&arg1 = sprite being terminated (is passed), otherwise, it's &current_sprite.
 sp_custom("PPterminated", &current_sprite, 1);
 if (&arg1 > 0)
 {
  sp_touch_damage(&arg1, 0);
  external("PhisEnd", "end", 9, 0, 0, &arg1);
 }
 else
 {
  sp_touch_damage(&current_sprite, 0);
  external("PhisEnd", "end", 9, 0, 0, &current_sprite);
 }

 kill_this_task();
}

void initiate(void)
{
 //there used to be more involved - but now most of it is handled when the sprite is terminated.
 if (&arg1 > 0)
 {
  sp_touch_damage(&arg1, -1);
  sp_custom("PPterminated", &arg1, 0);
 }
 else
 {
  sp_touch_damage(&current_sprite, -1);
  sp_custom("PPterminated", &current_sprite, 0);
 }
 kill_this_task();
}

void MoveActive(void)
{
 //checks if Dink is currently moving a sprite 
 //if yes, sprite number will be returned
 if (&arg1 > 0)
 {
  goto movespriteactive;
 }

 //No specific sprite passed to proc - check if Dink is moving a sprite on this screen
 &save_x = 0;
moveactive:
 //get invisible shadow sprites, there is one for each moveable object that is currently being touched
 &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
 if (&save_x > 0)
 {
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  &save_y = sp_custom("PP-Shadow", &save_y, -1);
  if (&save_y == &save_x)
  {
   &save_y = sp_custom("PP-Parent", &save_x, -1);
   &save_y = sp_custom("PPhybactive", &save_y, -1);
   if (&save_y != 1)
   {
    goto moveactiveinc;
   }
   
   //this will run if any of the above return 1
   &save_y = sp_custom("PP-Parent", &save_x, -1);
   goto moveactiveend;
  }
  
 moveactiveinc:
  &save_x += 1;
  goto moveactive;
 }
 else
 {
  return(0); 
  kill_this_task();
 } 

//checking if Dink is pushing a particular sprite, stored in &arg1
movespriteactive:
 &save_x = sp_custom("PPhybactive", &arg1, -1);
 if (&save_x != 1)
 {
  return(0);   
  kill_this_task();
 }

moveactiveend:
 //return the sprite number of the sprite being moved.
 if (&arg1 > 0)
 {
  &save_y = &arg1;
 }
 return(&save_y);   
 kill_this_task();  
}

void talk(void)
{
//NO LONGER REQUIRED - Left in to maintain older push and pull version compatibility.
//So authors don't have to re-edit all their moveable sprite scripts.
 //determines if Dink is pushing the sprite, or isn't.
 //To be able to customise talk lines.
sp_custom("talkreturn", &current_sprite, 0); 
talkloop:
 &save_x = sp_custom("PPhybactive", &current_sprite, -1);
 if (&save_x != 1)
 { 
  sp_custom("talkreturn", &current_sprite, 1);
  kill_this_task();
 }

 sp_custom("talkreturn", &current_sprite, 2);
 kill_this_task();
}

void stopmove(void)
{
 //Stop an object from moving any further. Will be as if it's hit hardness (but it hasn't)
 //This proc isn't really required, since the custom key can be set directly.
 //But I think I used it in some push and pull puzzles in the demo dmod so I'm leaving it here.
 sp_custom("stopmove", &current_sprite, 1);
 kill_this_task();
}

void startmove(void)
{
 //undo the stopmove custom key (reset it to 0)
 //This proc isn't really required, since the custom key can be set directly.
 //But I think I used it in some push and pull puzzles in the demo dmod so I'm leaving it here.
 sp_custom("stopmove", &current_sprite, 0);
 kill_this_task();
}

void kill(void)
{
 kill_this_task();
}