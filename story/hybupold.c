//This script is a tweaked, merged version of pup.c and hup.c so when sticky push is enabled it can swap between push and pull
 //hup.c and pup.c have been re-cycled, they do other stuff now.. they were part of the hold to pull method in the old version, and that's been abolished.
  
//What this script does among other stuff:
//Constantly updates hardness, moves the object, changes dinks sequence, and detects when the player stops pushing or pulling the object

void main(void)
{ 
 //retrieve the current sprite being moved. 
 int &hybsprite = &save_x;

 //store the player map for later, in case the player changes screens
 &save_x = &player_map; 
 sp_custom("PPscreen", &hybsprite, &save_x);

 //store the player original speed and frame delay. If not using freedink 109.6, two more local variables required for this.
 if (&vcheck <= 1084)
 {
  int &dspeed = sp_custom("PPd-speed", &hybsprite, -1);
  int &dframed = sp_custom("PPdink-fd", &hybsprite, -1);
 }
 else
 {
  &save_x = sp_custom("PPd-speed", &hybsprite, -1);
  &save_y = sp_custom("PPdink-fd", &hybsprite, -1);
  sp_custom("PPd-speed", 1, &save_x);
  sp_custom("PPdink-fd", 1, &save_y);
 }

 //reset the custom key which is used to tell this script to kill itself.
 sp_custom("PPhybkill", &hybsprite, 0);

 //reset PPlimitreached custom key
 sp_custom("PPlimitreached", &hybsprite, 0);  

 //update the "MovePosNeg" custom key
 &save_x = sp_custom("PushPosNeg", &hybsprite, -1);
 sp_custom("MovePosNeg", &hybsprite, &save_x);

 //declare locals
 int &mco;
 int &val1;

	/////////////////////////////////////////////////////////
        //CHECK IF ENOUGH ROOM TO PULL ON INITAL GRAB OF OBJECT//
        /////////////////////////////////////////////////////////
        //Retrieve the FIRST known hardness in DINK'S pull path
        &save_x = sp_custom("PPplimittrack1", &hybsprite, -1); 
        
        //if it's less than 0, hardness tracker sprite exited screen bound and no hardness was found
        //In this case, skip it.
        if (&save_x <= 0)
        {
         sp_custom("PPNoRoomStart", &hybsprite, 0);        
        }
        else
        {
         //set whether to use x or y
         &mco = sp_custom("move-axis", &hybsprite, -1);
         if (&mco == 1)
         {
          &save_y = sp_x(1, -1);
         }
         else
         {
          &save_y = sp_y(1, -1); 
         }
         
         &val1 = sp_custom("pulldir", &hybsprite, -1);    
         if (&val1 == 2)
         { 
          &save_x -= &save_y;
          &save_y = 20;
         }
         if (&val1 == 4)
         {
          &save_y -= &save_x
          &save_x = &save_y;
          &save_y = 30;
         }
         if (&val1 == 6) 
         {
          &save_x -= &save_y;
          &save_y = 30;
         } 
         if (&val1 == 8) 
         {
          &save_y -= &save_x;
          &save_x = &save_y;
          &save_y = 20;
         }
         
         if (&save_x <= &save_y) 
         {
           //**MARKER (in case of error) - Removed redundant if statement**//
  	   sp_custom("PPNoRoomStart", &hybsprite, 1);
         }
         else
         {
  	  sp_custom("PPNoRoomStart", &hybsprite, 0);
  	 }
        }
	////////////////////////////
        //PULLSPACE CHECK COMPLETE//
        ////////////////////////////     

  //Check if "move_nohard" custom key is set, if so, make sprite ignore hardness
  //So only Dink will stop at hardness when he walks into it.
  &save_x = sp_custom("move_nohard", &hybsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("PPDink-Push-Limit", &hybsprite, -1);
   &save_y = sp_custom("PPDink-Pull-Limit", &hybsprite, -1);   
  }
  else
  {
   sp_custom("move_nohard", &hybsprite, 0);
   &save_x = sp_custom("PPhupmove", &hybsprite, -1); 
   &save_y = sp_custom("PPpupmove", &hybsprite, -1); 
  }

  //save the limit we'll be using in a new custom key so we only have to run this check once.
  sp_custom("PPhuplimit", &hybsprite, &save_x);
  sp_custom("PPpuplimit", &hybsprite, &save_y);

  //save the old move_nohard value in a custom key
  &save_x = sp_custom("move_nohard", &hybsprite, -1);
  sp_custom("PPold_move_nohard", &hybsprite, &save_x);
        
 //MARKER - removed wait(0) - should no longer be required
loop: 
 if (&hybsprite > 0)
 {
  //update map hardness
  //draw_hard_map();  << not required - the sprite isn't hard anyway, otherwise it wouldn't be moving
  &mco = 0;
  wait(1); 

  //Check if "move_nohard" custom key is set, if so, make sprite ignore hardness
  //So only Dink will stop at hardness when he walks into it.
  &save_x = sp_custom("move_nohard", &hybsprite, -1);
  &save_y = sp_custom("PPold_move_nohard", &hybsprite, -1);
  if (&save_x != &save_y)
  {
   if (&save_x > 0)
   {
    &save_x = sp_custom("PPDink-Push-Limit", &hybsprite, -1);
    &save_y = sp_custom("PPDink-Pull-Limit", &hybsprite, -1);   
   }
   else
   {
    sp_custom("move_nohard", &hybsprite, 0);
    &save_x = sp_custom("PPhupmove", &hybsprite, -1); 
    &save_y = sp_custom("PPpupmove", &hybsprite, -1); 
   }
 
   //save the limit we'll be using in a new custom key so we only have to run this check once.
   sp_custom("PPhuplimit", &hybsprite, &save_x);
   sp_custom("PPpuplimit", &hybsprite, &save_y);
   
   //save the old move_nohard value in a custom key
   &save_x = sp_custom("move_nohard", &hybsprite, -1);
   sp_custom("PPold_move_nohard", &hybsprite, &save_x);
   
   //make sure the move lines are run again for the sprite
   sp_custom("PPre-move", &hybsprite, 1);
  }

   //record if the sprite moves. If it doesn't move at all(dink grabs then releases), we can skip some stuff in phisend.c
   &save_x = sp_custom("PPPosAltered", &hybsprite, -1);
   if (&save_x <= 0)
   {
    &save_x = sp_custom("spriteox", &hybsprite, -1);
    &save_y = sp_x(&hybsprite, -1);
    if (&save_x != &save_y)
    {
     sp_custom("PPPosAltered", &hybsprite, 1);
    }
     
    &save_x = sp_custom("spriteoy", &hybsprite, -1);
    &save_y = sp_y(&hybsprite, -1);
    if (&save_x != &save_y)
    {
     sp_custom("PPPosAltered", &hybsprite, 1);
    }
   }

   //check if this sprite has already run a phisend instance
   &save_x = sp_custom("PPInitiate-END", &hybsprite, -1);
   if (&save_x > 0)
   {
    //kill the sprite clone
    &save_x = sp_custom("PPHybSpriteClone", &hybsprite, -1);
    sp_active(&save_x, 0);     
   
    //Run the killpush procedure of Phishyb.c if it's still alive
    &save_x = sp_custom("PPhybscript", &hybsprite, -1);
    if (&save_x > 0)
    {
     run_script_by_number(&save_x, "killhyb"); 
    }   
      
    kill_this_task();
   }

   //Check if the player has changed screens
   &save_x = &player_map;
   &save_y = sp_custom("PPscreen", &hybsprite, -1);
   if (&save_x != &save_y)
   {
    //player changed screens
    if (&vcheck > 1084)
    {
     &save_x = sp_custom("PPd-speed", 1, -1);
     &save_y = sp_custom("PPdink-fd", 1, -1);
     debug("hybup dink RETRIEVE FREEDINK SPEED is &save_x");
    }
    else
    {
     &save_x = &dspeed;
     &save_y = &dframed;
     debug("hybup dink RETRIEVE DINK SPEED is &dspeed");
    }
    external("PhisEnd", "end", 8, 0, 0, &hybsprite, &save_x, &save_y);
    kill_this_task();
   }

  //**MARKER - BUGIFX SECTION REMOVED FROM HERE - no longer needed**//
  

  //Check if Dink's speed has changed (maybe he changed weapons and increased speed)
    //while holding the sprite.
  &save_x = sp_custom("PPd-sp_speed", &hybsprite, -1);
  &save_y = sp_speed(1, -1);
  if (&save_y > 0)
  {
   //Dink's speed has been changed from 0! (set_dink_speed equivelant of -1)
   //Check if sprite speed should be adjusted and then set dink's speed back to 0.
   if (&save_x != &save_y)
   {
    //assure the speed of the sprite isn't too fast, we don't want dink walking faster than his speed
    &save_x = sp_speed(1, -1);
    &save_y = sp_custom("PPoldspeed", &hybsprite, -1);
    if (&save_y > &save_x)
    {
     //Sprite's original speed is higher than Dinks new speed, set it's current speed to match Dink's
       //since sprite speed determines the push/pull speed.
     sp_speed(&hybsprite, &save_y);
     sp_timing(&hybsprite, 0);
    }
    else
    {
     //Original sprite speed is lower than or equal to Dink's new speed
      //Set the sprite BACK to it's original speed to maintain it's intended move speed.
     sp_speed(&hybsprite, &save_y);
    }
   
    //update Dink's frame delay to match the sprite  move speed.
    &save_x = sp_speed(&hybsprite, -1);
    if (&save_x >= 5)
    {
     sp_frame_delay(1, 30);   
    }  
    if (&save_x <= 4)
    {
      sp_frame_delay(1, 60);
    } 
    if (&save_x <= 2)
    {
     sp_frame_delay(1, 0);
    }
    
    //copy frame delay to fakedink sprite
    &save_x = sp_custom("PPfdink", &hybsprite, -1);
    &save_y = sp_frame_delay(1, -1);
    sp_frame_delay(&save_x, &save_y);
    
    //make clone sprite's speed match &hybsprite
    &save_y = sp_custom("PPHybSpriteClone", &hybsprite, -1);
    sp_speed(&save_y, &save_x);
    
    //store dink's new speed
    &save_x = sp_speed(1, -1);
    sp_custom("PPd-sp_speed", &hybsprite, &save_x);
    
    //convert it to "set_dink_speed" equivelant and store that as well
    if (&save_x == 1)
    {
     &save_x = 4;
    }
    if (&save_x == 6)
    {
     &save_x = 2;
    }
    if (&save_x == 9)
    {
     &save_x = 1;
    }
    if (&save_x == 0)
    {
     &save_x = -1111;
    }
    sp_custom("PPd-speed", &hybsprite, &save_x);
        
    //set dink's speed back to -1.
    set_dink_speed(-1);
   }
  }
 
     /////////////////////////////////////////
     //ASSURE SPRITE HASN'T PASSED ITS LIMIT//
     ///////////////////////////////////////// 
     //don't need to run this the first time around.       
     &mco = sp_custom("move-status", &hybsprite, -1);
     &save_y = 0;
     if (&mco > 0)
     {
      //also don't run this if the sprite hasn't moved since last limit check..
      if (&mco == 1)
      {
       //Dink is IDLE - check if should skip checks.
       &save_x = sp_custom("PPIdle-SkipChecks", &hybsprite, -1);
       if (&save_x == 1)
       {
        &save_y = 1;
       }
      }
      if (&save_y == 0)
      {
       //The calculations will be the same for each respective direction for both push and pull
       //So we just need to retrieve the correct seq and move limit. 
       //Direction checks can be used as is. 
       //Remember: PPhupseq and PPpupseq are opposite seqs so we can't just use one or the other. 
       &mco = 0;  
       &val1 = sp_custom("last-status", &hybsprite, -1);
       if (&val1 >= 2)
       {
        if (&val1 == 2)
        {
         &mco = sp_custom("PPhupseq", &hybsprite, -1);
         &save_y = sp_custom("PPhuplimit", &hybsprite, -1);
        }
        if (&val1 == 3)
        {
         &mco = sp_custom("PPpupseq", &hybsprite, -1);
         &save_y = sp_custom("PPpuplimit", &hybsprite, -1);   
        }
        
        if (&mco > 0)
        { 
         &save_x = sp_custom("Enable-Limit", &hybsprite, -1);
         if (&save_x > 0)
         {
          //starting &save_x value for detection whether usable value was saved
          &save_x = 9999;           
         
          //save the current move limit in a custom key and return the value to &val1
          &val1 = sp_custom("PPSLR-limit", &hybsprite, &save_y);     
         
          //override move limit with custom specification
          //and make sure overrided limit does not breach original detected limit.
          if (&mco == 312)
          {
           &save_y = sp_custom("setYmax", &hybsprite, -1);
           if (&save_y >= &val1)
           {
            &save_x = &val1;
           }
          } 
          if (&mco == 314) 
          { 
           &save_y = sp_custom("setXmin", &hybsprite, -1); 
           if (&save_y <= &val1)
           {
            &save_x = &val1;
           }  
          } 
          if (&mco == 316) 
          {
           &save_y = sp_custom("setXmax", &hybsprite, -1);
           if (&save_y >= &val1)
           {
            &save_x = &val1;
           }
          }   
          if (&mco == 318) 
          {
           &save_y = sp_custom("setYmin", &hybsprite, -1);
           if (&save_y <= &val1)
           {
            &save_x = &val1;
           }
          } 
          
          //check for ignore value set by dmod developer
          &val1 = sp_custom("Enable-Limit", &hybsprite, -1);
          if (&val1 == 2)
          {
           &val1 = sp_custom("PPSLR-limit", &hybsprite, -1);
           if (&save_y == 0)
           {
            &save_x = &val1;
           }
           if (&save_y == -1)
           {
            &save_x = &val1;
           }
          }
          &val1 = sp_custom("PPSLR-limit", &hybsprite, -1);
          if (&save_y == 9999)
          {
           &save_x = &val1;
          }  
          //check for "-1111" value to interpret as "-1"
          if (&save_y == -1111)
          {
           &save_x = -1;
          }
          
          if (&save_x != 9999)
          {
           &save_y = &save_x;
          }
         }          
         
          //set whether to use x or y
         &val1 = sp_custom("move-axis", &hybsprite, -1);
         if (&val1 == 1)
         {
          &save_x = sp_x(&hybsprite, -1);
         }
         else
         {
          &save_x = sp_y(&hybsprite, -1);
         }
         
         //Check if sprite is passed it's limit, and if so, shift+lock it's position accordingly.
         &val1 = sp_custom("PPHybSpriteClone", &hybsprite, -1);
         if (&mco == 312)
         {
          if (&save_x >= &save_y) 
          {
           sp_y(&val1, &save_y);
          }
         } 
         if (&mco == 314) 
         { 
          if (&save_x <= &save_y) 
          {
           sp_x(&val1, &save_y); 
          }     
         } 
         if (&mco == 316) 
         {
          if (&save_x >= &save_y) 
          { 
           sp_x(&val1, &save_y);       
          }  
         }   
         if (&mco == 318) 
         {
          if (&save_x <= &save_y) 
          {            
           sp_y(&val1, &save_y);                
          }
         }
         
         //relock sprite to clone sprite
         &mco = sp_custom("PPHybSpriteClone", &hybsprite, -1); 
         &save_x = sp_x(&mco, -1);
         &save_y = sp_y(&mco, -1);
         sp_x(&hybsprite, &save_x);
         sp_y(&hybsprite, &save_y);
        }
       } 
      }       
     }
     /////////////////////////////
     //LIMIT PASS CHECK COMPLETE//
     ///////////////////////////// 

      //////////////////////////////////////
      //relock Dink relative to the sprite//
      //////////////////////////////////////
      //don't need to run this the first time around.
      &save_x = sp_custom("move-status", &hybsprite, -1);
      &save_y = 0;
      &val1 = 0;
      if (&save_x > 0)
      {
       //also don't run this if the sprite hasn't moved since last limit check..
       if (&save_x == 1)
       {
        //Dink is IDLE - check if should skip checks.
        &save_x = sp_custom("PPIdle-SkipChecks", &hybsprite, -1);
        if (&save_x == 1)
        {
         &save_y = 1;
        }
       }
       if (&save_y <= 0)
       {
        //Relock Dink relative to object - push and pull
        
        //The calculations will be the same for each respective direction for both push and pull
        //So we just need to retrieve the correct seq and move limit. 
        //Direction checks can be used as is. 
        //Remember: PPhupseq and PPpupseq are opposite seqs so we can't just use one or the other.
        &save_x = sp_custom("last-status", &hybsprite, -1);
        if (&save_x >= 2)
        {
         if (&save_x == 2)
         {
          //pushing - do some juggling in a new custom key so we don't have to declare another variable.
          &save_y = sp_custom("PPhupseq", &hybsprite, -1);
          &mco = sp_custom("PPhuplimit", &hybsprite, -1);
         }
         if (&save_x == 3)
         {
          //pulling - do some juggling in a new custom key so we don't have to declare another variable.
          &save_y = sp_custom("PPpupseq", &hybsprite, -1);
          &mco = sp_custom("PPpuplimit", &hybsprite, -1);   
         }
         
         //set whether to use x or y
         &val1 = sp_custom("move-axis", &hybsprite, -1);
         if (&val1 == 1)
         {
          &val1 = sp_x(&hybsprite, -1);
         }
         else
         {
          &val1 = sp_y(&hybsprite, -1); 
         }
         
         //PPhupdiff and PPpupdiff are the same, so doesn't matter which one we run.
         &save_x = sp_custom("PPhupdiff", &hybsprite, -1);
         if (&save_x == -1111)
         {
          &save_x = -1;
         }
         
         if (&save_y == 312)
         {
          &val1 += &save_x;
          
          //assure we aren't locking dink to a position greater than the detected hard limit
          &mco += &save_x;
          if (&val1 > &mco)
          {
           &val1 = &mco;
          } 
          
          sp_y(1, &val1);
         }
         if (&save_y == 314)
         {
          &val1 += &save_x;
          &mco += &save_x;
          if (&val1 < &mco)
          {
           &val1 = &mco;
          }
          sp_x(1, &val1);
         }
         if (&save_y == 316)
         {
          &val1 += &save_x;
          &mco += &save_x;
          if (&val1 > &mco)
          {
           &val1 = &mco;
          } 
          sp_x(1, &val1);
         } 
         if (&save_y == 318)
         {
          &val1 += &save_x;
          &mco += &save_x;
          if (&val1 < &mco)
          {
           &val1 = &mco;
          }
          sp_y(1, &val1);
         } 
        }
       }        
      }
      ///////////////////
      //RELOCK COMPLETE//
      ///////////////////
      
  //SET "PPIdle-SkipChecks" custom key for next time
  //This makes it so the above checks only run ONCE when Dink is idle (holding the object but not moving it)
   //But will re-run as soon as he starts moving it again.
  &save_x = sp_custom("move-status", &hybsprite, -1);
  if (&save_x == 1)
  {
   &save_x = sp_custom("PPIdle-SkipChecks", &hybsprite, -1);
   if (&save_x == 0)  
   {
    sp_custom("PPIdle-SkipChecks", &hybsprite, 1); 
   }
  }

  //Check if the author has the "move_during_idle" or "move_idle" custom key set.
  &save_y = 0;
  &val1 = 0;
  &save_x = sp_custom("move_during_idle", &hybsprite, -1);
  if (&save_x > 0)
  {
   &val1 = 1;
  }
  &save_x = sp_custom("move_idle", &hybsprite, -1);
  if (&save_x > 0)
  {
   &val1 = 1;
  }
  if (&val1 == 1)
  {
   //the player does have one of the above custom keys set. If the sprite hasn't moved, skip the MoveDetectDuring procedure.
   //initial check to block movedetectduring from running initially
   &save_x = sp_custom("PPPosAltered", &hybsprite, -1);
   if (&save_x <= 0)
   {
    &save_y = 1;
   }
   //constant check for the duration of Dink holding the sprite
   &save_x = sp_custom("PPIdle-SkipChecks", &hybsprite, -1);
   if (&save_x == 1)
   {
    &save_y = 1;
   }
  }

  if (&save_y == 0)
  {
   //run the MoveDetectDuring proc of the hybsprite.
   &save_x = is_script_attached(&hybsprite);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "MoveDetectDuring");
   }
  }
  else
  {
   //run the IdleDetectDuring proc of the hybsprite.
   &save_x = is_script_attached(&hybsprite);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "IdleDetectDuring");
   }
  }

  //Check if the sprite's speed has changed(maybe the author changed it as part of the "movedetectduring" procedure)
  &save_x = sp_speed(&hybsprite, -1);
  &save_y = sp_custom("PPoldspeed", &hybsprite, -1);
  if (&save_x != &save_y)
  {
   //update the visible clone sprite to the new speed too.
   &save_y = sp_custom("PPHybSpriteClone", &hybsprite, -1);
   sp_speed(&save_y, &save_x);

   //update Dink's frame delay to match the sprite  move speed.
   &save_x = sp_speed(&hybsprite, -1);
   if (&save_x >= 5)
   {
    sp_frame_delay(1, 30);   
   }  
   if (&save_x <= 4)
   {
     sp_frame_delay(1, 60);
   } 
   if (&save_x <= 2)
   {
    sp_frame_delay(1, 0);
   }
   
   //copy frame delay to fakedink sprite
   &save_x = sp_custom("PPfdink", &hybsprite, -1);
   &save_y = sp_frame_delay(1, -1);
   sp_frame_delay(&save_x, &save_y);
  }

   //check to see if the player has disengaged, if so the seq will not match the expected push, pull or holding-idle seq.
   &save_x = sp_custom("PPpupseq", &hybsprite, -1);
   &save_x -= 240;
   &save_y = sp_pseq(1, -1);
   if (&save_y != &save_x)
   {
     &save_x = sp_custom("PPhupseq", &hybsprite, -1);
     &save_x -= 240;
     if (&save_y != &save_x)
     {
      //522 - 528 is Dink's temporary base idle seq for sticky push, loaded over the top of pigfeed graphics. 
      if (&save_y < 12)
      { 
       goto hybkill;
       kill_this_task();
      }
      if (&save_y > 18)
      {    
       goto hybkill;
       kill_this_task();
      }
     }
   }

  //a manual termination has occured and ended push/pull, kill off this script.  
  &save_x = sp_custom("PPhybkill", &hybsprite, -1);
  if (&save_x > 0)
  {
   //no need to kill off the phishyb.c instance here.
   //the same script that called for this to be killed will handle that also.
   //kill the sprite clone and end this
   &save_x = sp_custom("PPHybSpriteClone", &hybsprite, -1);
   sp_active(&save_x, 0);
   kill_this_task();
  }

  //"stopmove" custom key has been set, set &mco to 0 and goto limit so sprite can't move.
  &save_x = sp_custom("stopmove", &hybsprite, -1);
  if (&save_x > 0)
  {
   &mco = 0;
   goto limit;
  }

     	///////////////////////////////
     	//SPRITE LIMIT-REACHED? CHECK//
     	///////////////////////////////
     	//This is different to the "assure sprite hasn't passed it's limit" check
     	  //That check fixes timing issues where the sprite might move 1 pixel too far.
     	  //This check let's us know if Dink and the object sohuld stop because they've reached hardness.
     	  //has to be approached differently because IT NEEDS to run on initial engagement of sprite.
     	   
        //The calculations will be the same for each respective direction for both push and pull
        //So we just need to retrieve the correct seq and move limit. 
        //Direction checks can be used as is. 
        //Remember: PPhupseq and PPpupseq are opposite seqs so we can't just use one or the other. 
        &mco = 0;
        sp_custom("PPSLR-limit", &hybsprite, 0);
        &val1 = sp_custom("move-status", &hybsprite, -1);
        if (&val1 <= 1)
        {
         //make sure Dink isn't actually pushing or pulling(could be initilising or move-status hasn't updated yet)
         &save_y = sp_pseq(1, -1);
         &save_y += 240;
         &save_x = sp_custom("PPhupseq", &hybsprite, -1);
         if (&save_x == &save_y)  
         {
          &mco = sp_custom("PPhupseq", &hybsprite, -1);  
          &save_y = sp_custom("PPhuplimit", &hybsprite, -1);  
         }                     
         else
         {
          &save_x = sp_custom("PPpupseq", &hybsprite, -1);
          if (&save_x == &save_y)  
          {
           &mco = sp_custom("PPpupseq", &hybsprite, -1);
           &save_y = sp_custom("PPpuplimit", &hybsprite, -1);  
          }   
         }   
        }
        if (&val1 == 2)
        {
         &mco = sp_custom("PPhupseq", &hybsprite, -1);
         &save_y = sp_custom("PPhuplimit", &hybsprite, -1);
        }  
        if (&val1 == 3)
        {
         &mco = sp_custom("PPpupseq", &hybsprite, -1); 
         &save_y = sp_custom("PPpuplimit", &hybsprite, -1);   
        } 
     
        if (&mco > 0)
        {
         &save_x = sp_custom("Enable-Limit", &hybsprite, -1);
         if (&save_x > 0)
         {
          //starting &save_x value for detection whether usable value was saved
          &save_x = 9999;
         
          //save the current move limit in a custom key and return the value to &val1
          &val1 = sp_custom("PPSLR-limit", &hybsprite, &save_y);
          
          //override move limit with custom specification
          //and make sure overrided limit does not breach original detected limit.
          if (&mco == 312)
          {
           &save_y = sp_custom("setYmax", &hybsprite, -1);
           if (&save_y >= &val1)
           {
            &save_x = &val1;
           }
          } 
          if (&mco == 314) 
          { 
           &save_y = sp_custom("setXmin", &hybsprite, -1); 
           if (&save_y <= &val1)
           {
            &save_x = &val1;
           }  
          } 
          if (&mco == 316) 
          {
           &save_y = sp_custom("setXmax", &hybsprite, -1);
           if (&save_y >= &val1)
           {
            &save_x = &val1;
           }
          }   
          if (&mco == 318) 
          {
           &save_y = sp_custom("setYmin", &hybsprite, -1);
           if (&save_y <= &val1)
           {
            &save_x = &val1;
           }
          }         
         
          //check for ignore value set by dmod developer
          &val1 = sp_custom("Enable-Limit", &hybsprite, -1);
          if (&val1 == 2)
          {
           &val1 = sp_custom("PPSLR-limit", &hybsprite, -1);
           if (&save_y == 0)
           {
            &save_x = &val1;
           }
           if (&save_y == -1)
           {
            &save_x = &val1;
           }
          }
          &val1 = sp_custom("PPSLR-limit", &hybsprite, -1);
          if (&save_y == 9999)
          {
           &save_x = &val1;
          }
          //check for "-1111" value to interpret as "-1"
          if (&save_y == -1111)
          {
           &save_x = -1;
          }
          
          if (&save_x != 9999)
          {
           &save_y = &save_x;
          }
         }  
         
         //set whether to use x or y
         &val1 = sp_custom("move-axis", &hybsprite, -1);
         if (&val1 == 1)
         {
          &save_x = sp_x(&hybsprite, -1);
         }
         else
         {
          &save_x = sp_y(&hybsprite, -1);
         }
         
         //reset PPlimitreached to 0 (default)
         //and then run checks to see if move limit has been reached.
         sp_custom("PPlimitreached", &hybsprite, 0);       
         if (&mco == 312)
         {
          if (&save_x >= &save_y) 
          {
           sp_custom("PPlimitreached", &hybsprite, 1);
          }
         } 
         if (&mco == 314) 
         { 
          if (&save_x <= &save_y) 
          {
           sp_custom("PPlimitreached", &hybsprite, 1); 
          }
         } 
         if (&mco == 316) 
         {
          if (&save_x >= &save_y)  
          {
           sp_custom("PPlimitreached", &hybsprite, 1); 
          }
         }   
         if (&mco == 318) 
         {
          if (&save_x <= &save_y) 
          {
           sp_custom("PPlimitreached", &hybsprite, 1);
          }
         } 
        }
     	////////////////////////////////////////
     	//SPRITE LIMIT REACHED? CHECK COMPLETE//
    	 //////////////////////////////////////// 

 //reset &mco to 0
  &mco = 0; 

  //Check if Dink is pushing the sprite 
  &save_x = sp_custom("PPhupseq", &hybsprite, -1); 
  &save_x -= 240;
  &save_y = sp_pseq(1, -1); 
  if (&save_x == &save_y)
  {
   //update the "MovePosNeg" custom key
   &save_x = sp_custom("PushPosNeg", &hybsprite, -1);
   sp_custom("MovePosNeg", &hybsprite, &save_x);
 
   //if limit is reached, skip this.
   &save_x = sp_custom("PPlimitreached", &hybsprite, -1);
   if (&save_x > 0)
    goto limit;

   //change the fake dink to push seq
   &save_x = sp_custom("PPfdink", &hybsprite, -1);
   &save_y = sp_custom("PPhupseq", &hybsprite, -1); 
   sp_brain(&save_x, 6);
   sp_seq(&save_x, &save_y);
   sp_brain(&save_x, 15);
   sp_brain_parm(&save_x, 1);
   sp_reverse(&save_x, 0);

   //skip the move lines if the sprite is continuing in the same direction, unless the move limit has changed
   &save_y = 0;
   &save_x = sp_custom("move-status", &hybsprite, -1);
   if (&save_x == 2)
   {
    &save_x = sp_custom("PPre-move", &hybsprite, -1);
    if (&save_x <= 0)
    {
     //Sprite is already moving, and limit does not need updating - we can skip the move lines
     &save_y = 1;
    }
   }
   if (&save_y == 0)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("PPHybSpriteClone", &hybsprite, -1);
    
    //make object keep moving up to it's set PUSH limit.
    &save_x = sp_custom("PPhuplimit", &hybsprite, -1);
    if (sp_custom("PPhupseq", &hybsprite, -1) == 312)
     move(&save_y, 2, &save_x, 1);
 
    if (sp_custom("PPhupseq", &hybsprite, -1) == 314)
     move(&save_y, 4, &save_x, 1);
 
    if (sp_custom("PPhupseq", &hybsprite, -1) == 316)
     move(&save_y, 6, &save_x, 1); 
 
    if (sp_custom("PPhupseq", &hybsprite, -1) == 318)
     move(&save_y, 8, &save_x, 1);

    //reset the "PPre-move" custom key, so we know we have run the move line again after the move limit was updated
    sp_custom("PPre-move", &hybsprite, 0);
   }

   sp_custom("move-status", &hybsprite, 2);
   
   //to identify that move limit has not been reached and sprite should continue moving freely. 
   &mco = 1; 
  }

  &save_x = sp_custom("PPpupseq", &hybsprite, -1); 
  &save_x -= 240; 
  &save_y = sp_pseq(1, -1); 
  if (&save_x == &save_y)
  {
   //Check "PPNoRoomStart" key, which will tell us if Dink has clearance to pull
   &save_x = sp_custom("PPNoRoomStart", &hybsprite, -1);
   if (&save_x > 0)
   {
	//////////////////////
        //Re-Check pullspace//
        //////////////////////
        //Retrieve the FIRST known hardness, in DINK'S pull path
        &save_x = sp_custom("PPplimittrack1", &hybsprite, -1); 
        
        //if it's less than 0, hardness tracker sprite exited screen bound and no hardness was found
        //In this case, skip it.
        if (&save_x <= 0)
        {
         sp_custom("PPNoRoomStart", &hybsprite, 0);        
        }
        else
        {
         //set whether to use x or y
         &mco = sp_custom("move-axis", &hybsprite, -1);
         if (&mco == 1)
          &save_y = sp_x(1, -1);
         else
          &save_y = sp_y(1, -1); 
                  
         if (sp_custom("pulldir", &hybsprite, -1) == 2)
         { 
          &save_x -= &save_y;
          &save_y = 20;
         }
         
         if (sp_custom("pulldir", &hybsprite, -1) == 4)
         {
          &save_y -= &save_x
          &save_x = &save_y;
          &save_y = 30;
         }
         
         if (sp_custom("pulldir", &hybsprite, -1) == 6) 
         {
          &save_x -= &save_y;
          &save_y = 30;
         } 
         
         if (sp_custom("pulldir", &hybsprite, -1) == 8) 
         {
          &save_y -= &save_x;
          &save_x = &save_y;
          &save_y = 20;
         }
         
         if (&save_x <= &save_y) 
         {
          if (&save_x <= 0)
  	   sp_custom("PPNoRoomStart", &hybsprite, 0);
          else
          {
  	   sp_custom("PPNoRoomStart", &hybsprite, 1);
           say("Not enough room to pull it.", 1);
           sp_custom("PPlimitreached", &hybsprite, 1);
           &mco = 0;
           goto limit;
  	  }
         }
         else
  	   sp_custom("PPNoRoomStart", &hybsprite, 0);
        }
	/////////////////////////////////////
        //RE-CHECK PULLSPACE CHECK COMPLETE//
        /////////////////////////////////////
   }

   //update the "MovePosNeg" custom key
   &save_x = sp_custom("PullPosNeg", &hybsprite, -1);
   sp_custom("MovePosNeg", &hybsprite, &save_x);
   
   //if limit is reached.. skip this.
   &save_x = sp_custom("PPlimitreached", &hybsprite, -1);
   if (&save_x > 0)
    goto limit;

   //change the fake dink to pull seq
   &save_x = sp_custom("PPfdink", &hybsprite, -1);
   &save_y = sp_custom("PPhupseq", &hybsprite, -1); 
   sp_brain(&save_x, 6);
   sp_seq(&save_x, &save_y);
   sp_brain(&save_x, 15);
   sp_brain_parm(&save_x, 1); 
   sp_reverse(&save_x, 1); 

   //skip the move lines if the sprite is continuing in the same direction, unless the move limit has changed
   &save_y = 0;
   &save_x = sp_custom("move-status", &hybsprite, -1);
   if (&save_x == 3)
   {
    &save_x = sp_custom("PPre-move", &hybsprite, -1);
    if (&save_x <= 0)
    {
     //Sprite is already moving, and limit does not need updating - we can skip the move lines
     &save_y = 1;
    }
   }
   if (&save_y == 0)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("PPHybSpriteClone", &hybsprite, -1);
 
    //make object keep moving up to it's set move limit.
    &save_x = sp_custom("PPpuplimit", &hybsprite, -1);
    if (sp_custom("PPpupseq", &hybsprite, -1) == 312)
     move(&save_y, 2, &save_x, 1);
 
    if (sp_custom("PPpupseq", &hybsprite, -1) == 314)
     move(&save_y, 4, &save_x, 1);
 
    if (sp_custom("PPpupseq", &hybsprite, -1) == 316)
     move(&save_y, 6, &save_x, 1);
     
    if (sp_custom("PPpupseq", &hybsprite, -1) == 318)
     move(&save_y, 8, &save_x, 1);
     
    //reset the "PPre-move" custom key, so we know we have run the move line again after the move limit was updated
    sp_custom("PPre-move", &hybsprite, 0);
   }

   sp_custom("move-status", &hybsprite, 3);
   
   //to identify that move limit has not been reached and sprite should continue moving freely.     
   &mco = 1;
  }  
  
limit:  

   if (&mco == 0)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("PPHybSpriteClone", &hybsprite, -1);  

    //Dink is idle, walking towards the sprite, or a move limit was reached - stop the sprite
    //just use PPpupseq - either way we are stopping the sprite so doesn't matter.
     if (sp_custom("PPpupseq", &hybsprite, -1) == 316) 
      move(&save_y, 6, -200, 0);
    
     if (sp_custom("PPpupseq", &hybsprite, -1) == 314) 
      move(&save_y, 4, 750, 1);
    
     if (sp_custom("PPpupseq", &hybsprite, -1) == 312) 
      move(&save_y, 2, -200, 1);
    
     if (sp_custom("PPpupseq", &hybsprite, -1) == 318) 
      move(&save_y, 8, 600, 1);
     
    sp_custom("move-status", &hybsprite, 1);       
 
   //check player sequence, PPlimitreached, and stopmove
   &save_y = 0;
   &save_x = sp_pseq(1, -1);
   if (&save_x >= 12)
   {
    if (&save_x <= 18)
    {
     &save_y += 11;
    }
   }
    
   &save_x = sp_custom("PPlimitreached", &hybsprite, -1);
   if (&save_x > 0)
   {
    &save_y += 1;
   }
   
   &save_x = sp_custom("stopmove", &hybsprite, -1);   
   if (&save_x > 0)
   {
    &save_y += 1;   
   }  

   if (&save_y >= 1)
   {
    //at least one of the above checks returned true - halt the move.
    //make fake dink a static frame when he's idle while still moving an object
       //change the fake dink to pull seq
    &save_x = sp_custom("PPfdink", &hybsprite, -1);
    sp_seq(&save_x, 0);
    sp_frame(&save_x, 0);
    sp_brain(&save_x, 0);
    sp_pframe(&save_x, 10);
    
    if (&save_y < 11)
    {
     external("dsmove", "limit", &hybsprite);
    }
   }
   else
   {
    //Fail safe.. any other reason the object isn't moving.. just run the default say lines.
    external("dsmove", "limit", &hybsprite);
   }
  }
  else
  {
   //sprite is being moved successfully - make sure last-status is set on initial move.
   &save_x = sp_custom("last-status", &hybsprite, -1);
   &save_y = sp_custom("move-status", &hybsprite, -1);
   if (&save_y > 1)
   {
    if (&save_x != &save_y)
    {
     //save status of push/pull in "last-status" custom key
     sp_custom("last-status", &hybsprite, &save_y);
    }

    //let script know limit checks and relock need to be performed.
    sp_custom("PPIdle-SkipChecks", &hybsprite, 0);
   }
  }



  goto loop; 
 }
 
 goto hybkill;
 kill_this_task();
}

void hybkill(void)
{
hybkill: 

 //kill the sprite clone and end this
 &save_x = sp_custom("PPHybSpriteClone", &hybsprite, -1);
 sp_active(&save_x, 0);
   
 &save_x = sp_custom("PPterminated", &hybsprite, -1);
 if (&save_x <= 0)
 { 
  //kill the fakedink and deactivate nodraw on dink
  &save_x = sp_custom("PPfdink", &hybsprite, -1);
  sp_active(&save_x, 0);
  sp_nodraw(1, 0); 
  if (&vcheck > 1084)
  {
   &save_x = sp_custom("PPd-speed", 1, -1);
   &save_y = sp_custom("PPdink-fd", 1, -1);
   debug("hybup - hybkill - dink RETRIEVE FREEDINK SPEED is &save_x");
  }
  else
  {
   &save_x = &dspeed;
   &save_y = &dframed;
   debug("hybup - hybkill - dink RETRIEVE DINK SPEED is &dspeed");
  }
  external("PhisEnd", "end", 0, 0, 0, &hybsprite, &save_x, &save_y);
 }
    
 kill_this_task();
}