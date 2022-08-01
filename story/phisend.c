//This script deals with any ending or termination of push/pull
//Sprite of which push/pull is being ended/terminated is stored in &arg4 in all circumstances.

void end(void)
{
//this procedure is used to end push/pull, it is called phishyb.c.
//Also called directly by a few other scripts for remote push/pull sprite termination.

//////////////////////////////////
//ARGUMENTS VALUES - DESCRIPTION//
//////////////////////////////////

//Some values are no longer in use, but I've kept the same values for the ones that are
//to maintain backwards compatiblity with authors push/pull scripts when updating.

//&arg1 = 0 - Push/Pull activated succesfully, and stopped by player.

//&arg1 = 1-6 - NO LONGER USED

//&arg1 = 7 - Sticky push terminated during initiating checks due to one of the checks failing
//            &arg2 = 1 - Terminated prior to speedlock - not used or needed anymore.
//            &arg2 = 2 - Terminated after speedlock

//&arg1 = 8 - Dink changed screens while sticky push system active

//&arg1 = 9 - Manual Termination out of course. 

//&arg1 = 10 - NO LONGER USED

//&arg3 = NO LONGER USED

//&arg4 = Sprite being ended.

//&arg5 = Dink's speed BEFORE push/pull commenced and changed it.

//&arg6 = Dink's frame delay BEFORE push/pull commenced and changed it.

//////////////////////////////////
//ARGUMENTS VALUES - DESCRIPTION//
//////////////////////////////////

 //if Dink's health is depleted, end this here.
 if (&life < 1) 
  return;

 //we need 1 local
 int &val1;

 DEBUG("Phisend speed is &arg5");

 //This is to indicate that an instance of Phisend.c has initiated.
 sp_custom("Initiate-END", &arg4, 1);

   //failsafe speedlock check
   &save_x = sp_custom("speedlock", 1, -1);
   &save_x -= 1;
   sp_custom("speedlock", 1, &save_x);  
   if (&save_x > 0)
   {
    sp_custom("SkipSpeedReset", &arg4, 1); 
   }    

 if (&arg1 > 0)
 {
  //set up &val1 for dink speed value to be used in all &arg checks
  if (&arg5 == -1111)
  {
   &val1 = -1;
  }
  else
  {
   &val1 = &arg5;
  }
 
  if (&arg1 == 7)
  {  
   if (&arg2 == 2)
   {
    &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
    if (&save_x <= 0)
    {
     debug("Phisend confirm(1) DINKSPEED IS &val1 on &current_sprite");
     set_dink_speed(&val1);
     sp_frame_delay(1, &arg6);
    }

    //reset the sprites speed and timing
    debug("Phisend confirm(1) ARG4 SET TO &arg4");
    &save_x = sp_custom("oldspeed", &arg4, -1);
    &save_y = sp_custom("oldtiming", &arg4, -1);
    sp_speed(&arg4, &save_x);
    sp_timing(&arg4, &save_y);
   } 

   goto keyresets;   
  }
  
  if (&arg1 == 8)
  {
   //corect dinks idle
   sp_base_idle(1, 10); 
   sp_reverse(1, 0);
   sp_frame(1, 1);
   
   //reset dinks speed
   debug("Phisend confirm(2) DINKSPEED IS &val1");
   set_dink_speed(&val1);
   sp_frame_delay(1, &arg6);

   sp_nodraw(1, 0);

   //corect dinks base walk
   sp_base_walk(1, 70);
   kill_this_task(); 
  } 
  if (&arg1 == 9)
  {
   //manual termination out of course, let's make sure any auto-update scripts are killed off.
   sp_custom("hybkill", &arg4, 1);
   
   //Also kill off the main script if it's been started
   &save_x = sp_custom("hybscript", &arg4, -1);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "killhyb");
   }
  }
 }
 
//Initial &arg checks complete - continue with normal push and pull system Termination.. 

 //check if Dink is currently moving this sprite
 &save_x = sp_custom("hybactive", &arg4, -1);
 if (&save_x != 1)
 { 
  sp_custom("INACTIVE", &arg4, 1);
 }
 else
 {
  //HYBRID SYSTEM IN USE (STICKY PUSH)
  //corect dinks base idle
  sp_base_idle(1, 10);
  sp_reverse(1, 0);
  sp_frame(1, 1);

  //Dink stopped pulling so assure the obect stops too - just make it move forwards to a position behind it  - Lol. It works.
  &save_x = sp_custom("pupseq", &arg4, -1); 
  if (&save_x == 316) move(&arg4, 6, -200, 1);
  if (&save_x == 314) move(&arg4, 4, 750, 1);
  if (&save_x == 312) move(&arg4, 2, -200, 1);
  if (&save_x == 318) move(&arg4, 8, 600, 1);
 }

    &save_x = sp_custom("PosAltered", &arg4, -1);
    if (&save_x > 0)
    {

          /////////////////////////////////////////
          //ASSURE SPRITE HASN'T PASSED ITS LIMIT//
          /////////////////////////////////////////      
           //The calculations will be the same for each respective direction for both push and pull
           //So we just need to retrieve the correct seq and move limit. 
           //Direction checks can be used as is. 
           //Remember: hupseq and pupseq are opposite seqs so we can't just use one or the other.   
           &save_x = sp_custom("move-status", &arg4, -1);
           if (&save_x > 0)
           {
            if (sp_custom("last-status", &arg4, -1) == 2)
             &mco = sp_custom("huplimit", &arg4, -1);

            if (sp_custom("last-status", &arg4, -1) == 3)
             &mco = sp_custom("puplimit", &arg4, -1); 

            &save_x = sp_custom("Enable-Limit", &arg4, -1);
            if (&save_x > 0)
            {
             //override detected limit- check move axis (x or y) and direction (positive or negative along axis)
             //and set manual limit accordingly
             &save_x = sp_custom("move-axis", &arg4, -1);
             if (&save_x == 1)
             {
              &save_x = sp_custom("MovePosNeg", &arg4, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setXmin", &arg4, -1);
              else
               &save_y = sp_custom("setXmax", &arg4, -1);
             }
             else
             {
              &save_x = sp_custom("MovePosNeg", &arg4, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setYmin", &arg4, -1);
              else
               &save_y = sp_custom("setYmax", &arg4, -1);
             }
             
             //check for ignore value set by dmod developer
             if (&save_y == 9999)
              &save_y = &mco;
             
             //check for "-1111" value to interpret as "-1"
             if (&save_y == -1111)
              &save_y = -1;
             
             //assure new limit does not breach our original detected hardness limits
             &save_x = sp_custom("MovePosNeg", &arg4, -1);
             if (&save_x == 1)
             {
              if (&save_y <= &mco)
               &save_y = &mco;
             }
             else
             {
              if (&save_y >= &mco)
               &save_y = &mco;
             }
            }  
            else
             &save_y = &mco; 
 
           //set whether to use x or y
           &val1 = sp_custom("move-axis", &arg4, -1);
           if (&val1 == 1)
            &save_x = sp_x(&arg4, -1);
           else
            &save_x = sp_y(&arg4, -1); 

            if (sp_custom("last-status", &arg4, -1) == 2)
             &mco = sp_custom("hupseq", &arg4, -1);

            if (sp_custom("last-status", &arg4, -1) == 3)
             &mco = sp_custom("pupseq", &arg4, -1);
             
           if (sp_custom("last-status", &arg4, -1) <= 0)
           {
            //Dink was neither pushing or pulling.
            //just don't let any of the if statements below run.
            &val1 = 9999;
           }
             
           if (&val1 == 312)
           {
            if (&save_x >= &save_y) 
             sp_y(&arg4, &save_y);
           } 
           if (&val1 == 314) 
           { 
            if (&save_x <= &save_y) 
             sp_x(&arg4, &save_y);       
           } 
           if (&val1 == 316) 
           {
            if (&save_x >= &save_y)  
             sp_x(&arg4, &save_y);    
           }   
           if (&val1 == 318) 
           {
            if (&save_x <= &save_y) 
             sp_y(&arg4, &save_y);
           } 
          }
    	  /////////////////////////////
          //LIMIT PASS CHECK COMPLETE//
          /////////////////////////////  

      //////////////////////////////////////
      //relock Dink relative to the sprite//
      //////////////////////////////////////
       //Relock Dink relative to object - push and pull.
       //The calculations will be the same for each respective direction for both push and pull
       //So we just need to retrieve the correct seq and move limit. 
       //Direction checks can be used as is. 
       //Remember: hupseq and pupseq are opposite seqs so we can't just use one or the other.
       &save_x = sp_x(1, -1);
       &save_x = sp_custom("move-status", &arg4, -1);
       &save_y = 0;
       if (&save_x > 0)
       {
        if (sp_custom("last-status", &arg4, -1) == 2)
        {
         //pushing - do some juggling in a new custom key so we don't have to declare another variable.
         &save_x = sp_custom("hupdiff", &arg4, -1);
         if (&save_x == -1111)
          &save_x = -1;
 
         &save_y = sp_custom("hupseq", &arg4, -1);
         sp_custom("RelockSeq", &arg4, &save_y);
         &val1 = sp_custom("huplimit", &arg4, -1);
        }
        if (sp_custom("last-status", &arg4, -1) == 3)
        {
         //pulling - do some juggling in a new custom key so we don't have to declare another variable.
         &save_x = sp_custom("pupdiff", &arg4, -1);
         if (&save_x == -1111)
          &save_x = -1;
          
         &save_y = sp_custom("pupseq", &arg4, -1);
         sp_custom("RelockSeq", &arg4, &save_y);
         &val1 = sp_custom("puplimit", &arg4, -1);   
        }
        if (sp_custom("last-status", &arg4, -1) <= 0)
        {
         //Dink was neither pushing or pulling.
         //just don't let any of the if statements below run.
         sp_custom("RelockSeq", &arg4, 9999);
        }
  
        //set whether to use x or y
        &save_y = sp_custom("move-axis", &arg4, -1);
        if (&save_y == 1)
         &save_y = sp_x(&arg4, -1);
        else
         &save_y = sp_y(&arg4, -1); 
        
        if (sp_custom("RelockSeq", &arg4, -1) == 312)
        {
         &save_y += &save_x;
         
         //assure we aren't locking dink to a position greater than the detected hard limit
         &val1 += &save_x;
         if (&save_y > &val1)
          &save_y = &val1;
          
         sp_y(1, &save_y);
        }
        if (sp_custom("RelockSeq", &arg4, -1) == 314)
        {
         &save_y += &save_x;
         
         &val1 += &save_x;
         if (&save_y < &val1)
          &save_y = &val1;
          
         sp_x(1, &save_y);
        }
        if (sp_custom("RelockSeq", &arg4, -1) == 316)
        {
         &save_y += &save_x;
         
         &val1 += &save_x;
         if (&save_y > &val1)
          &save_y = &val1;

         sp_x(1, &save_y);
        } 
        if (sp_custom("RelockSeq", &arg4, -1) == 318)
        {
         &save_y += &save_x;
         
         &val1 += &save_x;
         if (&save_y < &val1)
          &save_y = &val1;
          
         sp_y(1, &save_y);
        }   
       }
      ///////////////////
      //RELOCK COMPLETE//
      ///////////////////
    }
 
 &save_x = sp_custom("INACTIVE", &arg4, -1);
 if (&save_x <= 0)
 {
  //Dink is currently moving this object
  //so revert it back to it's old stats.
  //update hardness
  sp_hard(&arg4, 0);
  draw_hard_map();
  &save_x = sp_hard(&arg4, -1);
 
  //update dink's base walk
  sp_base_walk(1, 70);

  //kill the fakedink and deactivate nodraw on dink
  &save_x = sp_custom("fdink", &arg4, -1);
  sp_active(&save_x, 0);
  sp_nodraw(1, 0);    
 
  //reset dink speed
  &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
  if (&save_x <= 0)
  {
   if (&arg1 == 9)
   {
    &val1 = sp_custom("PPd-speed", &arg4, -1);
    &save_x = sp_custom("PPdink-fd", &arg4, -1);    
   }
   else
   {
    //get dink_speed value
    if (&arg5 == -1111)
    {
     &val1 = -1;
    }
    else
    {
     &val1 = &arg5;
    }
 
    &save_x = &arg6;
   }

   &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
   if (&save_x <= 0)
   {   
    debug("Phisend confirm(3) DINKSPEED IS &val1");
    set_dink_speed(&val1);
    sp_frame_delay(1, &save_x);
   }
  }

  //reset the sprites speed and timing
  &save_x = sp_custom("oldspeed", &arg4, -1);
  &save_y = sp_custom("oldtiming", &arg4, -1);
  debug("Phisend confirm(1) ARG4 SET TO &arg4");
  sp_speed(&arg4, &save_x);
  sp_timing(&arg4, &save_y);
 }

 if (&arg1 <= 0)
 {
  //Check if the author has the "move_after_idle" or "move_idle" custom key set.
  &save_y = 0;
  &val1 = 0;
  &save_x = sp_custom("move_after_idle", &arg4, -1);
  if (&save_x > 0)
  {
   &val1 = 1;
  }
  &save_x = sp_custom("move_idle", &arg4, -1);
  if (&save_x > 0)
  {
   &val1 = 1;
  }
  if (&val1 == 1)
  {
   //the player does have it set, if the sprite hasn't moved, skip the MoveDetectAfter procedure.
   &save_x = sp_custom("PosAltered", &arg4, -1);
   if (&save_x <= 0)
   {
    &save_y = 1;
   }
  }
  if (&save_y == 0)
  {
   //poke the MoveDetectAfter proc if this was a succesfully activated push/pull.
   &save_x = is_script_attached(&arg4);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "MoveDetectAfter");
   }
  }
  else
  {
   //poke the IdleDetectAfter proc if this was a succesfully activated push/pull.
   &save_x = is_script_attached(&arg4);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "IdleDetectAfter");
   }
  }
 }

keyresets:
 //reset custom keys
 sp_custom("PPMoving", &arg4, 0); 
 sp_custom("hybactive", &arg4, 0); 
 sp_custom("hybscript", &arg4, 0);
 
 sp_custom("hupmove", &arg4, 0);
 sp_custom("huplimit", &arg4, 0);
 sp_custom("hupseq", &arg4, 0);
 sp_custom("hupdiff", &arg4, 0);

 sp_custom("pupmove", &arg4, 0);
 sp_custom("puplimit", &arg4, 0);
 sp_custom("pupseq", &arg4, 0);
 sp_custom("pupdiff", &arg4, 0);
 
 sp_custom("CanPush", &arg4, 0);
 sp_custom("speedlock", &arg4, 0);
 sp_custom("SkipSpeedReset", &arg4, 0);

 sp_custom("move-status", &arg4, 0);
 sp_custom("Idle-SkipChecks", &arg4, 0);
 sp_custom("INACTIVE", &arg4, 0);
 sp_custom("PPd-sp_speed", &arg4, 0);
 sp_custom("PPd-speed", &arg4, 0);
 sp_custom("PosAltered", &arg4, 0);

 //let phisbo.c "touch" proc know to reset the sprite. 
 //unless manual termination by author, then just run the killshadow.
 if (&arg1 != 9)
 {
  //kill off the shadow sprite used to retrieve and identify this moveable object
  &save_x = sp_custom("PP-Shadow", &arg4, -1);
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  if (&save_y == &arg4)
  {
   sp_active(&save_x, 0);
  }
  
  //reset other custom keys
  sp_custom("CanPush", &arg4, 0);
  sp_custom("speedlock", &arg4, 0);
  sp_custom("SkipSpeedReset", &arg4, 0);
 
  &save_x = sp_custom("terminated", &arg4, -1);
  if (&save_x <= 0)
  {
   //only reset touch damage if a manual termination hasn't been called
   sp_touch_damage(&arg4, -1); 
  }
 }
 else
 {
  //kill the sprite's invisible shaodw sprite.
  &save_x = sp_custom("PP-Shadow", &arg4, -1);
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  if (&save_y == &arg4)
   sp_active(&save_x, 0);
 }
 
 kill_this_task();
}