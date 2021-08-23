//allows pull to happen after all initial checks and setup is done.
//Constantly moves the sprite, locks dinks position relative to object he's pulling and detects when dink stops pulling the object

void main(void)
{ 
 //retrieve the current sprite being moved.
 int &pupsprite = &save_x;

 //store the player map for later, in case the player changes screens
 &save_x = &player_map; 
 sp_custom("screen", &pupsprite, &save_x);

 //reset the custom key which is used to tell this script to kill itself.
 sp_custom("pupkill", &pupsprite, 0);

 //update the "MovePosNeg" custom key
 &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
 sp_custom("MovePosNeg", &pupsprite, &save_x);

 //Using a local
 int &mco;

   //////////////////////////////////////////////////////////////////////////////////////////////////////
   //IF dink is already moving another sprite, cancel this - disable multiple moves, it causes problems//
   //////////////////////////////////////////////////////////////////////////////////////////////////////
    &save_x = 0;
   multipullKILL:
    &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
    if (&save_x > 0)
    {
     //now get the actual moveable sprite that the shadow is attached to
     &mco = sp_custom("PP-Parent", &save_x, -1);
     if (&mco == &pupsprite)
     {
      //if it's this sprite, loop again, we've already checked for that above
      &save_x += 1;
      goto multipullKILL;
     }
     else
     {
      &save_y = sp_custom("PP-Shadow", &mco, -1);
      if (&save_y == &save_x)
      {
       //make sure the pull procedure has actually run on the other detected object, or else cancel this
       &save_y = sp_custom("pullscript", &mco, -1);
       if (&save_y <= 0)
       {
        &save_x += 1;
        goto multipullKILL;
       }
       else
       {   
        //kill the sprite clone
        &save_x = sp_custom("PullSpriteClone", &pupsprite, -1);
        sp_active(&save_x, 0);       
       
        //poke the the phispull.c script, which is currently eternally looping to stay alive.
        //And kill off this script.
        run_script_by_number(&save_y, "multipullend");
        kill_this_task();
       }
      }
     }
    }
    //////////////////////////
    //multipullKILL COMPLETE//
    ////////////////////////// 

  //Check if "Move-Nohard" custom key is set, if so, make sprite ignore hardness
  //So only Dink will stop at hardness when he walks into it.
  &save_x = sp_custom("Move-Nohard", &pupsprite, -1);
  if (&save_x > 0)
   &save_x = sp_custom("Dink-Pull-Limit", &pupsprite, -1);
  else
   &save_x = sp_custom("pupmove", &pupsprite, -1); 

   //save the limit we'll be using in a new custom key so we only have to run this check once.
   sp_custom("puplimit", &pupsprite, &save_x);

 //MARKER - removed wait(0) - should no longer be required
loop: 

 if (&pupsprite > 0) 
 {   
  //update map hardness
  //draw_hard_map();  << not required - the sprite isn't hard anyway, otherwise it wouldn't be moving
  wait(1);

   //record if the sprite moves, if it doesn't move at all(dink grabs then releases), we can skip some stuff in phisend.c
   &save_x = sp_custom("PosAltered", &pupsprite, -1);
   if (&save_x <= 0)
   {
    &save_x = sp_custom("spriteox", &pupsprite, -1);
    &save_y = sp_x(&pupsprite, -1);
    if (&save_x != &save_y)
     sp_custom("PosAltered", &pupsprite, 1);
     
    &save_x = sp_custom("spriteoy", &pupsprite, -1);
    &save_y = sp_y(&pupsprite, -1);
    if (&save_x != &save_y)
     sp_custom("PosAltered", &pupsprite, 1);
   }
  
   //check if this sprite has already ran a phisend instance
   &save_x = sp_custom("Initiate-END", &pupsprite, -1);
   if (&save_x > 0)
   {
    //kill the sprite clone
    &save_x = sp_custom("PullSpriteClone", &pupsprite, -1);
    sp_active(&save_x, 0);     
   
    //Run the killpull procedure of Phispull.c if it's still alive
    &save_x = sp_custom("pullscript", &pupsprite, -1);
    if (&save_x > 0)
     run_script_by_number(&save_x, "killpull");    
      
    kill_this_task();
   }
 
    //Check if the player has changed screens
    &save_x = &player_map;
    &save_y = sp_custom("screen", &pupsprite, -1);
    if (&save_x != &save_y)
    {
     //we can just end it here - don't have to remotely kill off phispull.c
     //because it is not attached to 1000, so it'll die on screen change anyway.
     external("PhisEnd", "end", 1, 0, 0, &pupsprite);
     kill_this_task();
    }

  //BUGIFX SECTION REMOVED FROM HERE - no longer needed
  //location marked just in case. 

  //Check if Dink has opened his inventory since last speed/frame delay setup.
  &save_x = sp_custom("inventory", &pupsprite, -1);
  if (&save_x > 0)
  {
   //He has..
    external("DinkSpeed", "speedlock", &pupsprite);
    
    &save_x = sp_speed(&pupsprite, -1);
    
    if (&save_x >= 5)
     sp_frame_delay(1, 30);     
    
    if (&save_x <= 4)
      sp_frame_delay(1, 60);
         
    if (&save_x <= 2)
     sp_frame_delay(1, 0);

   //make clone sprite's speed match &pupsprite
   &save_y = sp_custom("PullSpriteClone", &pupsprite, -1);
   sp_speed(&save_y, &save_x);

   //assure dink's speed is set to -1, frame delay is correct for pull, and sprite speed is correct.
    set_dink_speed(-1);

   //reset inventory custom key.
   sp_custom("inventory", &pupsprite, 0);
  }

  	   /////////////////////////////////////////
           //ASSURE SPRITE HASN'T PASSED ITS LIMIT//
           /////////////////////////////////////////
           //don't need to run this the first time around. Skipping saves lag in older engines.
           &save_x = sp_custom("move-status", &pupsprite, -1);
           &save_y = 0;
           if (&save_x > 0)
           {
            //also don't run this if the sprite hasn't moved since last limit check..
            if (&save_x == 1)
            {
             //Dink is IDLE - check if should skip checks.
             &save_x = sp_custom("Idle-SkipChecks", &pupsprite, -1);
             if (&save_x == 1)
              &save_y = 1;
            }
            if (&save_y == 0)
            {
             //check for a override of move limit by dmod developer
             &mco = sp_custom("puplimit", &pupsprite, -1);
             &save_x = sp_custom("Enable-Limit", &pupsprite, -1);
             if (&save_x > 0)
             {
              //override detected limit- check move axis (x or y) and direction (positive or negative along axis)
              //and set manual limit accordingly
              &save_x = sp_custom("move-axis", &pupsprite, -1);
              if (&save_x == 1)
              {
               &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
               if (&save_x == 1)
                &save_y = sp_custom("setXmin", &pupsprite, -1);
               else
                &save_y = sp_custom("setXmax", &pupsprite, -1);
              }
              else
              {
               &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
               if (&save_x == 1)
                &save_y = sp_custom("setYmin", &pupsprite, -1);
               else
                &save_y = sp_custom("setYmax", &pupsprite, -1);
              }
              
              //check for ignore value set by dmod developer
              if (&save_y == 9999)
               &save_y = &mco;
              
              //check for "-1111" value to interpret as "-1"
              if (&save_y == -1111)
               &save_y = -1;
              
              //assure new limit does not breach our original detected hardness limits
              &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
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
             &save_x = sp_custom("PullSpriteClone", &pupsprite, -1); 
             &mco = sp_custom("move-axis", &pupsprite, -1);
             if (&mco == 1)
              &save_x = sp_x(&save_x, -1);
             else
              &save_x = sp_y(&save_x, -1);
              
             &mco = sp_custom("PullSpriteClone", &pupsprite, -1); 
             if (sp_custom("pupseq", &pupsprite, -1) == 312)
             {
              if (&save_x >= &save_y) 
               sp_y(&mco, &save_y);
             } 
             if (sp_custom("pupseq", &pupsprite, -1) == 314) 
             { 
              if (&save_x <= &save_y) 
               sp_x(&mco, &save_y);   
             } 
             if (sp_custom("pupseq", &pupsprite, -1) == 316) 
             {
              if (&save_x >= &save_y)  
               sp_x(&mco, &save_y); 
             }   
             if (sp_custom("pupseq", &pupsprite, -1) == 318) 
             {
              if (&save_x <= &save_y) 
               sp_y(&mco, &save_y);
             }
             
             //relock sprite to clone sprite
             &save_x = sp_x(&mco, -1);
             &save_y = sp_y(&mco, -1);
             sp_x(&pupsprite, &save_x);
             sp_y(&pupsprite, &save_y);
            }
           }
  	   /////////////////////////////
           //LIMIT PASS CHECK COMPLETE//
           /////////////////////////////

      //////////////////////////////////////
      //relock Dink relative to the sprite//
      //////////////////////////////////////
      //don't need to run this the first time around. Skipping saves lag in older engines.
      &save_x = sp_custom("move-status", &pupsprite, -1);
      &save_y = 0;
      if (&save_x > 0)
      {
       //also don't run this if the sprite hasn't moved since last limit check..
       if (&save_x == 1)
       {
        //Dink is IDLE - check if should skip checks.
        &save_x = sp_custom("Idle-SkipChecks", &pupsprite, -1);
        if (&save_x == 1)
         &save_y = 1;
       }
       if (&save_y == 0)
       {
        //Relock Dink relative to object - PULL
        &save_x = sp_custom("pupdiff", &pupsprite, -1);
        if (&save_x == -1111)
         &save_x = -1;
         
        //set whether to use x or y
        &mco = sp_custom("move-axis", &pupsprite, -1);
        if (&mco == 1)
         &save_y = sp_x(&pupsprite, -1);
        else
         &save_y = sp_y(&pupsprite, -1); 
        
        &mco = sp_custom("puplimit", &pupsprite, -1);
        if (sp_custom("pupseq", &pupsprite, -1) == 312)
        { 
         &save_y += &save_x;
      
         //assure we aren't locking dink to a position greater than the detected hard limit
         //&mco is the SPRITE's move limit, pupdiff is the difference between dink and the sprite
         //so we work out where dink would be when the sprite is at it's limit.
         &mco += &save_x;
         if (&save_y > &mco)
          &save_y = &mco;
         
         sp_y(1, &save_y);
        }
        if (sp_custom("pupseq", &pupsprite, -1) == 314)
        {
         &save_y += &save_x;
      
         //assure we aren't locking dink to a position greater than the detected hard limit
         &mco += &save_x;
         if (&save_y < &mco)
          &save_y = &mco;
         
         sp_x(1, &save_y);
        }
        if (sp_custom("pupseq", &pupsprite, -1) == 316)
        {
         &save_y += &save_x;
      
         &mco += &save_x;
         if (&save_y > &mco)
          &save_y = &mco;
          
         sp_x(1, &save_y);    
        } 
        if (sp_custom("pupseq", &pupsprite, -1) == 318)
        {
         &save_y += &save_x;
      
         &mco += &save_x;
         if (&save_y < &mco)
          &save_y = &mco;
          
         sp_y(1, &save_y);
        }    
       }
      }
      ///////////////////
      //RELOCK COMPLETE//
      ///////////////////
 
  	//SET "Idle-SkipChecks" custom key for next time
  	&save_x = sp_custom("move-status", &pupsprite, -1);
  	if (&save_x == 1)
  	{
   	 &save_x = sp_custom("Idle-SkipChecks", &pupsprite, -1);
   	 if (&save_x == 0)  
    	  sp_custom("Idle-SkipChecks", &pupsprite, 1); 
  	} 
      
  //run the MoveDetectDuring proc of the current sprite
  &save_x = is_script_attached(&pupsprite);
  if (&save_x > 0)
  {
   run_script_by_number(&save_x, "MoveDetectDuring");
  } 

   //check to see if the player has moved, if so his seq will change and we'll know dink has stopped pulling
   &save_x = sp_custom("pupseq", &pupsprite, -1);
   &save_y = sp_pseq(1, -1);
   if (&save_y != &save_x)
   {
     &save_x = sp_custom("pullstatic", &pupsprite, -1);
     if (&save_y != &save_x)
     { 
      //520 is Dink's temporary idle seq for pull, loaded over the top of pigfeed graphics.
      if (&save_y < 520)
       goto pupkill;
     }
   } 

  //a manual termination has occured and ended pull, kill off this script.  
  &save_x = sp_custom("pupkill", &pupsprite, -1);
  if (&save_x > 0)
  {
   //no need to kill off the phispull.c instance here.
   //the same script that called for this to be killed will handle that also.
   //kill the sprite clone and end this
   &save_x = sp_custom("PullSpriteClone", &pupsprite, -1);
   sp_active(&save_x, 0);
   kill_this_task();  
  }

  //"stopmove" custom key has been set, skip to limit so sprite can't move.
  &save_x = sp_custom("stopmove", &pupsprite, -1);
  if (&save_x > 0)
  {
   &mco = 0;
   goto limit;
  }

     	///////////////////////////////
     	//SPRITE LIMIT-REACHED? CHECK//
     	///////////////////////////////
      	     //all that hard work we did in the plimit procedure in Phulllim.c earlier boiled down to this.
      	     //Now we can check if dink or the sprite has hit any hardness and stop them. 
           &mco = sp_custom("puplimit", &pupsprite, -1);
           &save_x = sp_custom("Enable-Limit", &pupsprite, -1);
           if (&save_x > 0)
           {
            //override detected limit- check move axis (x or y) and direction (positive or negative along axis)
            //and set manual limit accordingly
            &save_x = sp_custom("move-axis", &pupsprite, -1);
            if (&save_x == 1)
            {
             &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
             if (&save_x == 1)
              &save_y = sp_custom("setXmin", &pupsprite, -1);
             else
              &save_y = sp_custom("setXmax", &pupsprite, -1);
            }
            else
            {
             &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
             if (&save_x == 1)
              &save_y = sp_custom("setYmin", &pupsprite, -1);
             else
              &save_y = sp_custom("setYmax", &pupsprite, -1);
            }
            
            //check for ignore value set by dmod developer
            if (&save_y == 9999)
             &save_y = &mco;
            
            //check for "-1111" value to interpret as "-1"
            if (&save_y == -1111)
             &save_y = -1;
            
            //assure new limit does not breach our original detected hardness limits
            &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
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
            
             &save_x = sp_custom("move-axis", &pupsprite, -1);
             if (&save_x == 1)
              &save_x = sp_x(&pupsprite, -1);
             else
              &save_x = sp_y(&pupsprite, -1);
 
             sp_custom("limitreached", &pupsprite, 0);               
             if (sp_custom("pupseq", &pupsprite, -1) == 312)
             {
              if (&save_x >= &save_y) 
               sp_custom("limitreached", &pupsprite, 1);
             } 
             if (sp_custom("pupseq", &pupsprite, -1) == 314) 
             { 
              if (&save_x <= &save_y) 
               sp_custom("limitreached", &pupsprite, 1); 
             } 
             if (sp_custom("pupseq", &pupsprite, -1) == 316) 
             {
              if (&save_x >= &save_y)  
               sp_custom("limitreached", &pupsprite, 1);
             }   
             if (sp_custom("pupseq", &pupsprite, -1) == 318) 
             {
              if (&save_x <= &save_y) 
               sp_custom("limitreached", &pupsprite, 1);
             }
     	////////////////////////////////////////
     	//SPRITE LIMIT REACHED? CHECK COMPLETE//
     	////////////////////////////////////////

  //reset &mco to 0
  &mco = 0;
 
  //make sure the pull seq is still correct and hasn't changed.
  &save_x = sp_custom("pupseq", &pupsprite, -1);      
  &save_y = sp_pseq(1, -1); 
  if (&save_x == &save_y)
  {
   //update the "MovePosNeg" custom key
   &save_x = sp_custom("PullPosNeg", &pupsprite, -1);
   sp_custom("MovePosNeg", &pupsprite, &save_x);
  
   //if limit is reached.. skip this.
   &save_x = sp_custom("limitreached", &pupsprite, -1);
   if (&save_x > 0)
    goto limit;

   //skip the move lines if the sprite is continuing in the same direction
   //this saves lag in older Dink engines
   &save_x = sp_custom("move-status", &pupsprite, -1);
   if (&save_x != 3)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("PullSpriteClone", &pupsprite, -1);
 
    //make object keep moving up to it's set move limit.
    &save_x = sp_custom("puplimit", &pupsprite, -1);
    if (sp_custom("pupseq", &pupsprite, -1) == 312)
     move(&save_y, 2, &save_x, 1);
 
    if (sp_custom("pupseq", &pupsprite, -1) == 314)
     move(&save_y, 4, &save_x, 1);
 
    if (sp_custom("pupseq", &pupsprite, -1) == 316)
     move(&save_y, 6, &save_x, 1);
     
    if (sp_custom("pupseq", &pupsprite, -1) == 318)
     move(&save_y, 8, &save_x, 1);
   }

   sp_custom("move-status", &pupsprite, 3);

   //to identify that move limit has not been reached and sprite should continue moving freely.   
   &mco = 1;
  }

limit: 
 
  if (&mco == 0)
  {
   //retrieve the clone sprite for movement handling without interruption
   &save_y = sp_custom("PullSpriteClone", &pupsprite, -1);   
  
   //Dink is idle, walking towards the sprite, or a move limit was reached - stop the sprite
   if (sp_custom("pupseq", &pupsprite, -1) == 316) 
    move(&save_y, 6, -200, 1);
   
   if (sp_custom("pupseq", &pupsprite, -1) == 314) 
    move(&save_y, 4, 750, 1);
   
   if (sp_custom("pupseq", &pupsprite, -1) == 312) 
    move(&save_y, 2, -200, 1);
   
   if (sp_custom("pupseq", &pupsprite, -1) == 318) 
    move(&save_y, 8, 600, 1);  

   &save_x = sp_custom("move-status", &pupsprite, -1);
   if (&save_x > 1)
   {
    //save status of push in "last-status" custom key
    sp_custom("last-status", &pupsprite, &save_x);
    //let script know limit checks and relock need to be performed.
    sp_custom("Idle-SkipChecks", &pupsprite, 0);
   }
    
   sp_custom("move-status", &pupsprite, 1); 

   //check player sequence, limitreached, and stopmove
   &save_y = 0;
   &save_x = sp_pseq(1, -1);
   &mco = sp_custom("pullstatic", &pupsprite, -1);
   if (&save_x > 520)
    &save_y += 11;
    
   if (&save_x == &mco) 
    &save_y += 11;
    
   &save_x = sp_custom("limitreached", &pupsprite, -1);
   if (&save_x > 0)
    &save_y += 1;

   &save_x = sp_custom("stopmove", &pupsprite, -1);   
   if (&save_x > 0)
    &save_y += 1; 

   if (&save_y >= 1)
   {
    //at least one of the above checks returned true - halt the move.
    //make dink a static frame when he's idle while still moving an object
    sp_frame(1, 0);
    if (&save_y < 11)
     external("dsmove", "limit", &pupsprite);
   }
   else
   {
    //Fail safe.. any other reason the object isn't moving.. just run the default say lines.
    //unless the player is idle
    external("dsmove", "limit", &pupsprite);
   }
  }
  else
  {
   //sprite is being moved successfully - make sure last-status is set on initial move.
   &save_x = sp_custom("last-status", &pupsprite, -1);
   &save_y = sp_custom("move-status", &pupsprite, -1);
   if (&save_y > 1)
   {
    if (&save_x != &save_y)
     sp_custom("last-status", &pupsprite, &save_y);
   }
  }
     
  goto loop;
 }
 
 goto pupkill;
}

void pupkill(void)
{
pupkill:

 //kill the sprite clone and end this
 &save_x = sp_custom("PullSpriteClone", &pupsprite, -1);
 sp_active(&save_x, 0);
 
    &save_x = sp_custom("pullscript", &pupsprite, -1);
    if (&save_x > 0)
    {  
     run_script_by_number(&save_x, "end");
    }
    
 kill_this_task();
} 