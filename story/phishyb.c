void hybrid(void)
{
//HYBRID "Sticky push" system- gets all the stuff ready in preperation for push and pull, and spawns hybup.c
 //a custom key to mark this proc has proceeded
 sp_custom("PPInitiate-Hybrid", &current_sprite, 1);

 //assures dink's original sequence HAS NOT changed.
 &save_x = sp_pseq(1, -1);
 &save_y = sp_custom("PPpseq-origin", &current_sprite, -1);
 if (&save_x != &save_y)
 {
  //it has changed - end it
  sp_custom("PPreset-required", &current_sprite, 1);
  kill_this_task();
 }

 	//we need a couple of locals
 	int &val1 = 0;
 	int &val2 = 0; 

 //make sure Dink is trying to push the object, and not just idling
 &save_x = sp_custom("PPpseq-origin", &current_sprite, -1);
 &save_y = sp_custom("base_idle", &current_sprite, -1);
 if (&save_x > &save_y)
 { 
  &save_y += 10;
  if (&save_x < &save_y)
  {
   //he's idling - end this now.
   sp_custom("PPreset-required", &current_sprite, 1);
   kill_this_task();
  }
 }

  //If HBOX custom key is 0, no hardbox values have been passed to phisbo.c - so we'll have to call a script to figure out if Dink is standing next to the hardbox
   &val1 = sp_custom("PPHBOX", &current_sprite, -1);
   if (&val1 == 0)
   {
    external("phispull", "auto_detect");
    &save_x = &return;
    if (&save_x == 1)
    {
     sp_custom("PPreset-required", &current_sprite, 1);
     kill_this_task();
    }
   }
   else
   {
    external("phispush", "quick_check");
    &save_x = &return;
    if (&save_x == 1)
    {
     sp_custom("PPreset-required", &current_sprite, 1);
     kill_this_task();
    }
   }    

 //if direction calculation took place there was a wait, so let's run a seqcheck again.
 //assures dink's original sequence HAS NOT changed.
 //and also assure his position and direction haven't changed
 &val1 = sp_custom("PPHBOX", &current_sprite, -1);
 if (&val1 == 0) 
 {
  //seq check
  &save_x = sp_pseq(1, -1);
  &save_y = sp_custom("PPpseq-origin", &current_sprite, -1);
  if (&save_x != &save_y)
  {
   //it has changed - end it
   sp_custom("PPreset-required", &current_sprite, 1);
   kill_this_task();
  }

  //pos check
  &save_x = sp_x(1, -1);
  &save_y = sp_y(1, -1);
  &val1 = sp_custom("dinkox", &current_sprite, -1);
  &val2 = sp_custom("dinkoy", &current_sprite, -1);
  if (&save_x != &val1)
  {
   //it has changed - end it
   sp_custom("PPreset-required", &current_sprite, 1);
   kill_this_task();
  }  
  if (&save_y != &val2)
  {
   //it has changed - end it
   sp_custom("PPreset-required", &current_sprite, 1);
   kill_this_task();
  } 
 
  //dir check
  &save_x = sp_dir(1, -1);
  &save_y = sp_custom("pushdir", &current_sprite, -1);
  if (&save_x != &save_y)
  {
   //it has changed - end it
   sp_custom("PPreset-required", &current_sprite, 1);
   kill_this_task();  
  }  
 }

 //If author has chosen to run the push procedure
 &save_x = sp_custom("push", &current_sprite, -1);
 if (&save_x == 0)
 {
  sp_custom("push", 1, -1);
 }
 if (&save_x > 0)
 {
   //The push custom key is set - cancel this and run push procedure on the current sprite
   //make it reset everything but act as if terminated so player must initiate it again for it to re-activate
   sp_custom("PPreset-required", &current_sprite, 1);
   sp_custom("PPterminated", &current_sprite, 1);
   &save_y = is_script_attached(&current_sprite);
   if (&save_y > 0)
   {
    //play the push animation
    &save_x = sp_custom("pushdir", &current_sprite, -1);
    &val1 = sp_custom("base_push", &current_sprite, -1);
    &save_x += &val1;
    sp_seq(1, &save_x);
    sp_frame(1, 1);
    sp_kill_wait(1);
    sp_nocontrol(1, 1);
    run_script_by_number(&save_y, "push");
   }
   kill_this_task();
 }
 
 //If author has chosen to run the push_custom() procedure
 &save_x = sp_custom("push_custom", &current_sprite, -1);
 if (&save_x == 0)
 {
  sp_custom("push_custom", 1, -1);
 }
 if (&save_x > 0)
 {
   //The push_custom custom key is set - cancel this and run push_custom procedure on the current sprite
   //make it reset everything  but act as if terminated so player must initiate it again for it to re-activate
   sp_custom("PPreset-required", &current_sprite, 1);
   sp_custom("PPterminated", &current_sprite, 1);
   &save_y = is_script_attached(&current_sprite);
   if (&save_y > 0)
   {
    run_script_by_number(&save_y, "push_custom");
   }
   kill_this_task();
 }
     
   //let's store Dink's required push sequence away in a custom key
   &val1 = sp_custom("base_push", &current_sprite, -1);
   &save_x = sp_custom("pushdir", &current_sprite, -1);
   &save_x += &val1;
   sp_custom("PPhupseq", &current_sprite, &save_x);

   //Let's store Dink's required pull sequence away in a custom key
   //Dink's pull sequence will be the opposite to his push sequence
   //so if he would be pushing to the WEST, EAST is his pull sequence
   //eg. pushing west = seq 314, so pulling would be seq 316.
   //we achieve the "pulling"(facing west), even though he's moving east
   //because further down in the script we load over the top of sequences
   //eg. in above example, 314 gets loaded also into 316.
   //This way we can differentiate the players seq and dir, but visually it's the same.
   &save_x = sp_custom("pulldir", &current_sprite, -1);
   &save_x += &val1;
   sp_custom("PPpupseq", &current_sprite, &save_x);

   //let's get the difference between the object and dink
   //First we check if we need the x or y coordinate
   &val1 = sp_custom("move-axis", &current_sprite, -1);
   if (&val1 == 2)
   {
    &save_y = sp_y(1, -1);
    &save_x = sp_y(&current_sprite, -1);
   }
   if (&val1 == 1)
   {
    &save_y = sp_x(1, -1);
    &save_x = sp_x(&current_sprite, -1);
   }
   
   //now get the difference
   &save_y -= &save_x;
   
   //Fix "-1" issue (can't store a value of "-1" in a custom key)
   if (&save_y == -1)
    &save_y = -1111;
   
   //save the difference between dink and the object for later
   sp_custom("PPhupdiff", &current_sprite, &save_y);
   sp_custom("PPpupdiff", &current_sprite, &save_y);

     //////////////////////////////////////////////////////////////////////////////////////
     //"PPdotchange" custom key - basically wanting to shift where the depth dot would be//
     //////////////////////////////////////////////////////////////////////////////////////
      	//(without actually doing it)
     //the normal Dink push depth dot is at the FRONT of him.
     //but when pulling, we want him to stop when his back foot hits hardness
     //or it looks like he goes through hardness
     //so we just set an amount that can be ADDED onto the detected hardness location
     //to place Dink's actual location/depth dot where we want him to stop
     //so he stops some pixels before the detected hardness instead. 
       &save_y = sp_custom("pull_dd_adjust", &current_sprite, -1);
       if (&save_y == 0)
       {
        &save_y = sp_custom("pull_dd_adjust", 1, -1);
       }
       if (&save_y == -1111)
       {
        &save_y = -1;
       }
       
       &val2 = 0;
       &save_x = sp_custom("pulldir", &current_sprite, -1);
       if (&save_x == 2)
       {
        if (&save_y != 0)
        {
         if (&save_y != -9999)
         {
          &save_y *= -1;
         }
        }
       
        &val1 = sp_custom("pull_dd_adjust_2", &current_sprite, -1);
        if (&val1 == 0)
        {
         &val1 = sp_custom("pull_dd_adjust_2", 1, -1);
        }
        if (&val1 == -1111)
        {
         &val1 = -1;
        }
        if (&val1 != 0)
        {
         if (&val1 != -9999)
         {
          &val1 *= -1;
         }
        }
        else
        {
         &val1 = &save_y;
        }
 
        if (&val1 == 0)
        {
         &val1 = -20;
        }       
       }

       if (&save_x == 4)
       {
        &val1 = sp_custom("pull_dd_adjust_4", &current_sprite, -1);
        if (&val1 == 0)
        {
         &val1 = sp_custom("pull_dd_adjust_4", 1, -1);
        }
        if (&val1 == -1111)
        {
         &val1 = -1;
        }
        if (&val1 != 0)
        {
         if (&val1 != -9999)
         {
          &val1 *= -1;
         }
        }
        else
        {
         &val1 = &save_y;
        }
 
        if (&val1 == 0)
        {
         &val1 = 30;
        }       
       }

       if (&save_x == 6)
       {
        if (&save_y != 0)
        {
         if (&save_y != -9999)
         {
          &save_y *= -1;
         }
        }
        
        &val1 = sp_custom("pull_dd_adjust_6", &current_sprite, -1);
        if (&val1 == 0)
        {
         &val1 = sp_custom("pull_dd_adjust_6", 1, -1);
        }
        if (&val1 == -1111)
        {
         &val1 = -1;
        }
        if (&val1 != 0)
        {
         if (&val1 != -9999)
         {
          &val1 *= -1;
         }
        }
        else
        {
         &val1 = &save_y;
        }
 
        if (&val1 == 0)
        {
         &val1 = -30;
        }      
       }

       if (&save_x == 8)
       {
        &val1 = sp_custom("pull_dd_adjust_8", &current_sprite, -1);
        if (&val1 == 0)
        {
         &val1 = sp_custom("pull_dd_adjust_8", 1, -1);
        }
        if (&val1 == -1111)
        {
         &val1 = -1;
        }
        if (&val1 != 0)
        {
         if (&val1 != -9999)
         {
          &val1 *= -1;
         }
        }
        else
        {
         &val1 = &save_y;
        }
 
        if (&val1 == 0)
        {
         &val1 = 20;
        }     
       }

       if (&val1 == -9999)
       {
        sp_custom("PPdotchange", &current_sprite, 0);
       }
       else
       {
        sp_custom("PPdotchange", &current_sprite, &val1);
       }  

       if (&val1 != 0)
       {
        if (&val1 < 0)
        {
         if (&val1 == -9999)
         {
          sp_custom("PPpullspace_required", &current_sprite, 0);
         }
         else
         {
          &val1 *= -1;
          sp_custom("PPpullspace_required", &current_sprite, &val1);
         }
        }
       }
     /////////////////////
     //PPdotchange END//  
     /////////////////////

 //Store Dink's speed in a custom key for later retrieval
 //we can retrieve the sp_speed equivelant of Dink and convert it to dink_speed value.
   //save both values in custom keys.
   
 external("dinkspeed", "getspeed");
 &val1 = &return;
 sp_custom("PPd-sp_speed", &current_sprite, &val1);
 debug("phishyb dink CHECK SPEED is &val1 on &current_sprite");
 if (&val1 == 1)
 {
  &val1 = 4;
 }
 if (&val1 == 6)
 {
  &val1 = 2;
 }
 if (&val1 == 9)
 {
  &val1 = 1;
 }
 if (&val1 == 0)
 {
  &val1 = -1111;
 }
 sp_custom("PPd-speed", &current_sprite, &val1);
 
 //NOTE - Dinks speed setting does not take effect until the next "wait()" AFTER it has been set.
   //The next wait occurs in hyblim.c.
     //Checks are conducted there to assure player hasn't moved >= 1 pixel into sprite hardbox.

 //Make it so dink can't move in preperation for limit checks initiation of smooth sprite move. 
 set_dink_speed(-1);
   
 //save the speed and timing of the sprite in case we need to change it
 &save_x = sp_speed(&current_sprite, -1);
 &save_y = sp_timing(&current_sprite, -1);
 sp_custom("PPoldspeed", &current_sprite, &save_x);
 sp_custom("PPoldtiming", &current_sprite, &save_y);    
   
 //assure the speed of the sprite isn't too fast, we don't want dink walking faster than his speed
   //We COULD check dink's speed directly, since a wait line hasn't occured since setting it to -1
    //but for good practice, we'll just retrieve it from the custom key we stored it in.
 &save_x = sp_custom("PPd-sp_speed", &current_sprite, -1);
 &save_y = sp_speed(&current_sprite, -1);
 if (&save_y > &save_x)
 {
  //Sprite's speed is higher than Dinks, reduce it to match 
    //since sprite speed determines the push/pull speed.
  sp_speed(&current_sprite, &save_x);
  sp_timing(&current_sprite, 0);
 }
 
 sp_custom("PPspeedlock", &current_sprite, 1);
 
 //failsafe speedlock check
 &save_x = sp_custom("PPspeedlock", 1, -1);
 if (&save_x <= 0)
 {
  &save_x = 0;
 }
 &save_x += 1;
 sp_custom("PPspeedlock", 1, &save_x); 

 //assure Dink's frame delay is correct for sprite move speed
 //also store dink's frame delay in a custom key for later retrieval
 &val1 = sp_frame_delay(1, -1);
 sp_custom("PPdink-fd", &current_sprite, &val1);
 
 &save_x = sp_speed(&current_sprite, -1);
 if (&save_x >= 5)
  sp_frame_delay(1, 30);     
 
 if (&save_x <= 4)
   sp_frame_delay(1, 60);
      
 if (&save_x <= 2)
  sp_frame_delay(1, 0);

    //get the limit of how far the object can be pushed and pulled on the screen.
    external("HybLim", "hybridlimit");		
    &save_x = &return;
    sp_custom("PP-hyblim-return", &current_sprite, &save_x);
    
    //check if we should continue or end push. 
    &save_x = sp_custom("PP-hyblim-return", &current_sprite, -1);
    if (&save_x > 0)
    {
     //trigger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     debug("getspeed phishyb DINKSPEED is &val1 on &current_sprite");
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
     kill_this_task();
    }

    //check if pullspace should be enforced when grabbing a sprite
    &save_x = sp_custom("enforce_pullspace", &current_sprite, -1);
    if (&save_x == 0)
    {
     &save_x = sp_custom("enforce_pullspace", 1, -1);
    }
    if (&save_x == 1)
    {
     //Retrieve the FIRST known hardness in DINK'S pull path
     &save_x = sp_custom("PPplimittrack1", &current_sprite, -1); 
     
     //if it's less than 0, hardness tracker sprite exited screen bound and no hardness was found
     //In this case, skip it.
     if (&save_x <= 0)
     {
      sp_custom("PPNoRoomStart", &current_sprite, 0);        
     }        
     else
     {
      //set whether to use x or y
      &val1 = sp_custom("move-axis", &current_sprite, -1);
      if (&val1 == 1)
      {
       &save_y = sp_x(1, -1);
      }
      else
      {
       &save_y = sp_y(1, -1); 
      }
      
      &val1 = sp_custom("pulldir", &current_sprite, -1); 
      &val2 = sp_custom("PPpullspace_required", &current_sprite, -1); 
      
      //subtract 1 here.. so Dink can grab it with exactly enough room as well.
      &val2 -= 1;
      if (&val1 == 2)
      { 
       &save_x -= &save_y;
      }
      if (&val1 == 4)
      {
       &save_y -= &save_x
       &save_x = &save_y;
      }
      if (&val1 == 6) 
      {
       &save_x -= &save_y;
      } 
      if (&val1 == 8) 
      {
       &save_y -= &save_x;
       &save_x = &save_y;
      }
      
      if (&save_x <= &val2) 
      {
       //trigger the end, and pass dink's original speed and frame_delay to the procedure
       &val1 = sp_custom("PPd-speed", &current_sprite, -1);
       &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
       external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
       external("dsmove", "space");
       kill_this_task();
      }
     } 
    }   
    

   ////////////////////
   //FAIL SAFE CHECKS//
   ////////////////////               
   //check dinks original dir has not changed
   &save_x = sp_dir(1, -1);
   &save_y = sp_custom("pushdir", &current_sprite, -1);
   if (&save_x != &save_y)
   {
     //trigger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }   
   //check dinks position hasn't changed
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);
   &val1 = sp_custom("dinkox", &current_sprite, -1);
   &val2 = sp_custom("dinkoy", &current_sprite, -1);
   if (&save_x != &val1)
   {
     //triger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }  
   if (&save_y != &val2)
   {
     //triger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   } 
   //assures dink's original sequence HAS NOT changed.
   &save_x = sp_pseq(1, -1);
   &save_y = sp_custom("PPpseq-origin", &current_sprite, -1);
   if (&save_x != &save_y)
   {
     //trigger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }
   ////////////////////////
   //END FAIL SAFE CHECKS//
   ////////////////////////

   //////////////////////////////////////////////////////////////////////////////////////////////////////
   //IF dink is already moving another sprite, cancel this - disable multiple moves, it causes problems//
   //////////////////////////////////////////////////////////////////////////////////////////////////////
    &save_x = 0;
   multipushKILL:
    &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
    if (&save_x > 0)
    {
     //now get the actual moveable sprite that the shadow is attached to
     &val1 = sp_custom("PP-Parent", &save_x, -1);
     if (&val1 == &current_sprite)
     {
      //if it's this sprite, loop again, we've already checked for that above
      &save_x += 1;
      goto multipushKILL;
     }
     else
     {
      &save_y = sp_custom("PP-Shadow", &val1, -1);
      if (&save_y == &save_x)
      {
       //make sure the push procedure has actually run on the other detected object, or else cancel this
       &save_y = sp_custom("PPhybactive", &val1, -1);
       if (&save_y <= 0)
       {
        &save_x += 1;
        goto multipushKILL;
       }
       else
       { 
        //Dink is moving another sprite - end this.
        &val1 = sp_custom("PPd-speed", &current_sprite, -1);
        &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
        external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
 	kill_this_task();
       }
      }
     }
    }
    //////////////////////////
    //MULTIPUSHKILL COMPLETE//
    //////////////////////////

 //this is to store the fact that all checks have passed and 'Hybrid' is active.
 sp_custom("PPhybactive", &current_sprite, 1);  

 //generic active key, regardless of push, pull or sticky push for use in button4.c
 sp_custom("PPMoving", &current_sprite, 1); 

 //Make the sprite moveable - it can't move when it's set to hard
 sp_hard(&current_sprite, 1);
 draw_hard_map();
 
 //MARKER - "INIT" Lines removed in favor of fakedink creation sprite.

 //create the fake dink and shadow it to dink
 &save_y = sp_custom("PPhupseq", &current_sprite, -1);
 &val1 = sp_x(1, -1);
 &val2 = sp_y(1, -1);
 &save_x = create_sprite(&val1, &val2, 6, &save_y, 1);
 sp_seq(&save_x, &save_y);
 sp_brain(&save_x, 15);
 sp_brain_parm(&save_x, 1);
 sp_custom("PPfdink", &current_sprite, &save_x);
 &save_y = sp_frame_delay(1, -1);
 sp_frame_delay(&save_x, &save_y);

 //nodraw dink
 sp_nodraw(1, 1);
  
 //save the current script in custom key "pullscript"
 &save_x = &current_script;
 sp_custom("PPhybscript", &current_sprite, &save_x);

   //create a clone of this sprite to handle the moving so it won't get interrupted by procedures.
   &save_x = sp_pseq(&current_sprite, -1);
   &save_y = sp_pframe(&current_sprite, -1);
   &val1 = sp_x(&current_sprite, -1);
   &val2 = sp_y(&current_sprite, -1);
   &save_x = create_sprite(&val1, &val2, 0, &save_x, &save_y);  
   sp_brain(&save_x, 0);
   sp_nodraw(&save_x, 1);
   sp_nohit(&save_x, 1);
   &val1 = sp_speed(&current_sprite, -1);
   &val2 = sp_timing(&current_sprite, -1);
   sp_speed(&save_x, &val1);
   sp_timing(&save_x, &val2);
   sp_custom("PPHybSpriteClone", &current_sprite, &save_x);

 //reset the initiate end custom key
 sp_custom("PPInitiate-END", &current_sprite, 0);

 //update the x and y coordinate custom keys to retain last position before move
 &save_x = sp_x(1, -1);
 &save_y = sp_y(1, -1);
 &val1 = sp_x(&current_sprite, -1);
 &val2 = sp_y(&current_sprite, -1);
 sp_custom("move-dinkx", &current_sprite, &save_x);
 sp_custom("move-dinky", &current_sprite, &save_y);
 sp_custom("move-sprx", &current_sprite, &val1);
 sp_custom("move-spry", &current_sprite, &val2);

 //can't pass args to spawned scripts.. so pass over the current_sprite using a global.
 //Then retrieve it immediately in "hybup.c" before it can have a chance to change.
 &save_x = &current_sprite;
 
 //Spawn hybup.c - hybup.c does a few different things, see the comments in that script for more info
 spawn("hybup"); 
 
 sp_custom("PPhybscript", &current_sprite, 0); 
 kill_this_task();
}

void killhyb(void)
{
 sp_custom("PPhybscript", &current_sprite, 0); 
 kill_this_task();
}