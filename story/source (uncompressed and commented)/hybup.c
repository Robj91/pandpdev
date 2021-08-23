//This script is a tweaked, merged version of pup.c and hup.c so when sticky push is enabled it can swap between push and pull
//Constantly updates hardness, moves the object, changes dinks sequence, and detects when the player stops pushing o pulling the object

void main(void)
{ 
 //retrieve the current sprite being moved. 
 int &hybsprite = &save_x;

 //store the player map for later, in case the player changes screens
 &save_x = &player_map; 
 sp_custom("screen", &hybsprite, &save_x);

 //reset the custom key which is used to tell this script to kill itself.
 sp_custom("hybkill", &hybsprite, 0);

 //update the "MovePosNeg" custom key
 &save_x = sp_custom("PushPosNeg", &hybsprite, -1);
 sp_custom("MovePosNeg", &hybsprite, &save_x);

 //using a local 
 int &mco;

   //////////////////////////////////////////////////////////////////////////////////////////////////////
   //IF dink is already moving another sprite, cancel this - disable multiple moves, it causes problems//
   //////////////////////////////////////////////////////////////////////////////////////////////////////
    &save_x = 0;
   multipushKILL:
    &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
    if (&save_x > 0)
    {
     //now get the actual moveable sprite that the shadow is attached to
     &mco = sp_custom("PP-Parent", &save_x, -1);
     if (&mco == &hybsprite)
     {
      //if it's this sprite, loop again, we've already checked for that above
      &save_x += 1;
      goto multipushKILL;
     }
     else
     {
      &save_y = sp_custom("PP-Shadow", &mco, -1);
      if (&save_y == &save_x)
      {
       //make sure the push procedure has actually run on the other detected object, or else cancel this
       &save_y = sp_custom("hybscript", &mco, -1);
       if (&save_y <= 0)
       {
        &save_x += 1;
        goto multipushKILL;
       }
       else
       { 
        //kill the sprite clone
        &save_x = sp_custom("HybSpriteClone", &hybsprite, -1);
        sp_active(&save_x, 0);     
  
        //poke the the phispush.c script, which is currently eternally looping to stay alive.
        //And kill off this script.
        run_script_by_number(&save_y, "multipushend");
        kill_this_task();
       }
      }
     }
    }
    //////////////////////////
    //MULTIPUSHKILL COMPLETE//
    //////////////////////////

	/////////////////////////////////////////////////////////
        //CHECK IF ENOUGH ROOM TO PULL ON INITAL GRAB OF OBJECT//
        /////////////////////////////////////////////////////////
        //Retrieve the FIRST known hardness, in DINK'S pull path
        &save_x = sp_custom("plimittrack1", &hybsprite, -1); 
        
        //if it's less than 0, hardness tracker sprite exited screen bound and no hardness was found
        //In this case, skip it.
        if (&save_x <= 0)
        {
         sp_custom("NoRoomStart", &hybsprite, 0);        
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
  	   sp_custom("NoRoomStart", &hybsprite, 0);
          else
  	   sp_custom("NoRoomStart", &hybsprite, 1);
         }
         else
  	   sp_custom("NoRoomStart", &hybsprite, 0);
        }
	////////////////////////////
        //PULLSPACE CHECK COMPLETE//
        ////////////////////////////     

  //Check if "Move-Nohard" custom key is set, if so, make sprite ignore hardness
  //So only Dink will stop at hardness when he walks into it.
  &save_x = sp_custom("Move-Nohard", &hybsprite, -1);
  if (&save_x > 0)
  {
   &save_x = sp_custom("Dink-Push-Limit", &hybsprite, -1);
   &save_y = sp_custom("Dink-Pull-Limit", &hybsprite, -1);   
  }
  else
  {
   &save_x = sp_custom("hupmove", &hybsprite, -1); 
   &save_y = sp_custom("pupmove", &hybsprite, -1); 
  }

  //save the limit we'll be using in a new custom key so we only have to run this check once.
  sp_custom("huplimit", &hybsprite, &save_x);
  sp_custom("puplimit", &hybsprite, &save_y);
        
 //MARKER - removed wait(0) - should no longer be required
loop: 

 if (&hybsprite > 0)
 {
  //update map hardness
  //draw_hard_map();  << not required - the sprite isn't hard anyway, otherwise it wouldn't be moving
  &mco = 0;
  wait(1); 

   //record if the sprite moves, if it doesn't move at all(dink grabs then releases), we can skip some stuff in phisend.c
   &save_x = sp_custom("PosAltered", &hybsprite, -1);
   if (&save_x <= 0)
   {
    &save_x = sp_custom("spriteox", &hybsprite, -1);
    &save_y = sp_x(&hybsprite, -1);
    if (&save_x != &save_y)
     sp_custom("PosAltered", &hybsprite, 1);
     
    &save_x = sp_custom("spriteoy", &hybsprite, -1);
    &save_y = sp_y(&hybsprite, -1);
    if (&save_x != &save_y)
     sp_custom("PosAltered", &hybsprite, 1);
   }

   //check if this sprite has already ran a phisend instance
   &save_x = sp_custom("Initiate-END", &hybsprite, -1);
   if (&save_x > 0)
   {
    //kill the sprite clone
    &save_x = sp_custom("HybSpriteClone", &hybsprite, -1);
    sp_active(&save_x, 0);     
   
    //Run the killpush procedure of Phispush.c if it's still alive
    &save_x = sp_custom("hybscript", &hybsprite, -1);
    if (&save_x > 0)
     run_script_by_number(&save_x, "killhyb");    
      
    kill_this_task();
   }

   //Check if the player has changed screens
   &save_x = &player_map;
   &save_y = sp_custom("screen", &hybsprite, -1);
   if (&save_x != &save_y)
   {
    //we can just end it here - don't have to remotely kill off phishyb.c
    //because it is not attached to 1000, so it'll die on screen change anyway.
    external("PhisEnd", "end", 8, 0, 0, &hybsprite);
    kill_this_task();
   }

  //BUGIFX SECTION REMOVED FROM HERE - no longer needed
  //location marked just in case. 

  //Check if Dink has opened his inventory since last speed/frame delay setup.
  &save_x = sp_custom("inventory", &hybsprite, -1);
  if (&save_x > 0)
  {
   //He has opened inventory..

    external("DinkSpeed", "speedlock", &hybsprite);
    
    &save_x = sp_speed(&hybsprite, -1);
    
    if (&save_x >= 5)
     sp_frame_delay(1, 30);     
    
    if (&save_x <= 4)
      sp_frame_delay(1, 60);
         
    if (&save_x <= 2)
     sp_frame_delay(1, 0);

   //make clone sprite's speed match &hybsprite
   &save_y = sp_custom("HybSpriteClone", &hybsprite, -1);
   sp_speed(&save_y, &save_x);

   //assure dink's speed is set to -1, frame delay is correct for push/pull, and sprite speed is correct.
   set_dink_speed(-1);

   //reset inventory custom key.
   sp_custom("inventory", &hybsprite, 0);
  }
 
          /////////////////////////////////////////
          //ASSURE SPRITE HASN'T PASSED ITS LIMIT//
          ///////////////////////////////////////// 
          //don't need to run this the first time around. Skipping saves lag in older engines.           
          &mco = sp_custom("move-status", &hybsprite, -1);
          &save_y = 0; 
          if (&mco > 0)
          {
           //also don't run this if the sprite hasn't moved since last limit check..
           if (&mco == 1)
           {
            //Dink is IDLE - check if should skip checks.
            &save_x = sp_custom("Idle-SkipChecks", &hybsprite, -1);
            if (&save_x == 1)
             &save_y = 1;
           }   
           if (&save_y == 0)
           {      
            //The calculations will be the same for each respective direction for both push and pull
            //So we just need to retrieve the correct seq and move limit. 
            //Direction checks can be used as is. 
            //Remember: hupseq and pupseq are opposite seqs so we can't just use one or the other.   

            if (sp_custom("last-status", &hybsprite, -1) == 2)
             &mco = sp_custom("huplimit", &hybsprite, -1);

            if (sp_custom("last-status", &hybsprite, -1) == 3)
             &mco = sp_custom("puplimit", &hybsprite, -1);   

            &save_x = sp_custom("Enable-Limit", &hybsprite, -1);
            if (&save_x > 0)
            {
             //override detected limit- check move axis (x or y) and direction (positive or negative along axis)
             //and set manual limit accordingly
             &save_x = sp_custom("move-axis", &hybsprite, -1);
             if (&save_x == 1)
             {
              &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setXmin", &hybsprite, -1);
              else
               &save_y = sp_custom("setXmax", &hybsprite, -1);
             }
             else
             {
              &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setYmin", &hybsprite, -1);
              else
               &save_y = sp_custom("setYmax", &hybsprite, -1);
             }
             
             //check for ignore value set by dmod developer
             if (&save_y == 9999)
              &save_y = &mco;
             
             //check for "-1111" value to interpret as "-1"
             if (&save_y == -1111)
              &save_y = -1;
             
             //assure new limit does not breach our original detected hardness limits
             &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
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
            &save_x = sp_custom("HybSpriteClone", &hybsprite, -1);
            &mco = sp_custom("move-axis", &hybsprite, -1);
            if (&mco == 1)
             &save_x = sp_x(&save_x, -1);
            else
             &save_x = sp_y(&save_x, -1);

            if (sp_custom("last-status", &hybsprite, -1) == 2)
             &mco = sp_custom("hupseq", &hybsprite, -1);

            if (sp_custom("last-status", &hybsprite, -1) == 3)
             &mco = sp_custom("pupseq", &hybsprite, -1);
           
            if (sp_custom("last-status", &hypsprite, -1) <= 0)
            {
             //Dink was neither pushing or pulling.
             //just don't let any of the if statements below run.
             &mco = 9999;
            }
            
            //below is a lot of dupe lines, but I'm doing it to save declaring more locals.
            //I use mco=9999 to skip if statements instead of using a goto.. less lag in older engines.
            if (&mco == 312)
            {
             if (&save_x >= &save_y) 
             {
              &mco = sp_custom("HybSpriteClone", &hybsprite, -1);
              sp_y(&mco, &save_y);
              &mco = 9999;
             }
            } 
            if (&mco == 314) 
            { 
             if (&save_x <= &save_y) 
             {
              &mco = sp_custom("HybSpriteClone", &hybsprite, -1);
              sp_x(&mco, &save_y); 
              &mco = 9999; 
             }     
            } 
            if (&mco == 316) 
            {
             if (&save_x >= &save_y) 
             { 
              &mco = sp_custom("HybSpriteClone", &hybsprite, -1);
              sp_x(&mco, &save_y);  
              &mco = 9999;           
             }  
            }   
            if (&mco == 318) 
            {
             if (&save_x <= &save_y) 
             {
              &mco = sp_custom("HybSpriteClone", &hybsprite, -1);             
              sp_y(&mco, &save_y);
              &mco = 9999;                 
             }
            }
            
            //relock sprite to clone sprite
            &mco = sp_custom("HybSpriteClone", &hybsprite, -1); 
            &save_x = sp_x(&mco, -1);
            &save_y = sp_y(&mco, -1);
            sp_x(&hybsprite, &save_x);
            sp_y(&hybsprite, &save_y); 
           }
          }
    	  /////////////////////////////
          //LIMIT PASS CHECK COMPLETE//
          ///////////////////////////// 

      //////////////////////////////////////
      //relock Dink relative to the sprite//
      //////////////////////////////////////
      //don't need to run this the first time around. Skipping saves lag in older engines.   
      &save_x = sp_custom("move-status", &hybsprite, -1);
      &save_y = 0;
      if (&save_x > 0)
      {
       //also don't run this if the sprite hasn't moved since last limit check..
       if (&save_x == 1)
       {
        //Dink is IDLE - check if should skip checks.
        &save_x = sp_custom("Idle-SkipChecks", &hybsprite, -1);
        if (&save_x == 1)
         &save_y = 1;
       }      
       if (&save_y == 0)
       {
        //Relock Dink relative to object - push and pull
        //hupdiff and pupdiff are the same, so doesn't matter which one we run.
        &save_x = sp_custom("hupdiff", &hybsprite, -1);
        if (&save_x == -1111)
         &save_x = -1;
        
        //The calculations will be the same for each respective direction for both push and pull
        //So we just need to retrieve the correct seq and move limit. 
        //Direction checks can be used as is. 
        //Remember: hupseq and pupseq are opposite seqs so we can't just use one or the other.
        if (sp_custom("last-status", &hybsprite, -1) == 2)
        {
         //pushing - do some juggling in a new custom key so we don't have to declare another variable.
         &save_y = sp_custom("hupseq", &hybsprite, -1);
         sp_custom("RelockSeq", &hybsprite, &save_y);
         &mco = sp_custom("huplimit", &hybsprite, -1);
        }
        if (sp_custom("last-status", &hybsprite, -1) == 3)
        {
         //pulling - do some juggling in a new custom key so we don't have to declare another variable.
         &save_y = sp_custom("pupseq", &hybsprite, -1);
         sp_custom("RelockSeq", &hybsprite, &save_y);
         &mco = sp_custom("puplimit", &hybsprite, -1);   
        }
        if (sp_custom("last-status", &hybsprite, -1) <= 0)
        {
         //Dink was neither pushing or pulling.
         //just don't let any of the if statements below run.
         sp_custom("RelockSeq", &hybsprite, 9999);
        }

        //set whether to use x or y
        &save_y = sp_custom("move-axis", &hybsprite, -1);
        if (&save_y == 1)
         &save_y = sp_x(&hybsprite, -1);
        else
         &save_y = sp_y(&hybsprite, -1); 
        
        if (sp_custom("RelockSeq", &hybsprite, -1) == 312)
        {
         &save_y += &save_x;
         
         //assure we aren't locking dink to a position greater than the detected hard limit
         &mco += &save_x;
         if (&save_y > &mco)
          &save_y = &mco;
          
         sp_y(1, &save_y);
        }
        if (sp_custom("RelockSeq", &hybsprite, -1) == 314)
        {
         &save_y += &save_x;
         
         &mco += &save_x;
         if (&save_y < &mco)
          &save_y = &mco;
          
         sp_x(1, &save_y);
        }
        if (sp_custom("RelockSeq", &hybsprite, -1) == 316)
        {
         &save_y += &save_x;
         
         &mco += &save_x;
         if (&save_y > &mco)
          &save_y = &mco;
          
         sp_x(1, &save_y);
        } 
        if (sp_custom("RelockSeq", &hybsprite, -1) == 318)
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
  	&save_x = sp_custom("move-status", &hybsprite, -1);
  	if (&save_x == 1)
  	{
   	 &save_x = sp_custom("Idle-SkipChecks", &hybsprite, -1);
   	 if (&save_x == 0)  
    	  sp_custom("Idle-SkipChecks", &hybsprite, 1); 
  	}
 
  //run the MoveDetectDuring proc of the hybsprite
  &save_x = is_script_attached(&hybsprite);
  if (&save_x > 0)
  {
   run_script_by_number(&save_x, "MoveDetectDuring");
  }
  
   //check to see if the player has moved, if so his seq will change and we'll know dink has stopped
   &save_x = sp_custom("pupseq", &hybsprite, -1);
   &save_y = sp_pseq(1, -1);
   if (&save_y != &save_x)
   {
     &save_x = sp_custom("pullstatic", &hybsprite, -1);
     if (&save_y != &save_x)
     {
      //pullstatic is the same as hupseq, so we don't need to check that here.
      if (&save_y < 520)
      { 
       //520 is Dink's temporary base idle seq for pull, loaded over the top of pigfeed graphics.     
       goto hybkill;
       kill_this_task();
      }
     }
   }

  //a manual termination has occured and ended push/pull, kill off this script.  
  &save_x = sp_custom("hybkill", &hybsprite, -1);
  if (&save_x > 0)
  {
   //no need to kill off the phispush.c instance here.
   //the same script that called for this to be killed will handle that also.
   //kill the sprite clone and end this
   &save_x = sp_custom("HybSpriteClone", &hybsprite, -1);
   sp_active(&save_x, 0);
   kill_this_task();
  }

  //"stopmove" custom key has been set, skip to limit so sprite can't move.
  &save_x = sp_custom("stopmove", &hybsprite, -1);
  if (&save_x > 0)
  {
   &mco = 0;
   goto limit;
  }

     	///////////////////////////////
     	//SPRITE LIMIT-REACHED? CHECK//
     	///////////////////////////////
       	   //all that hard work we did in the plimit procedure in Phislim.c earlier boiled down to this.
       	   //Now we can check if dink or the sprite has hit any hardness and stop them.     
       	   
            //The calculations will be the same for each respective direction for both push and pull
            //So we just need to retrieve the correct seq and move limit. 
            //Direction checks can be used as is. 
            //Remember: hupseq and pupseq are opposite seqs so we can't just use one or the other.   
            if (sp_custom("move-status", &hybsprite, -1) == 2)
             &mco = sp_custom("huplimit", &hybsprite, -1);
             
            if (sp_custom("move-status", &hybsprite, -1) == 3)
             &mco = sp_custom("puplimit", &hybsprite, -1);   

            if (sp_custom("move-status", &hybsprite, -1) <= 0)
            {
             //make sure Dink isn't actually pushing or pulling but move-status hasn't updated yet
             &mco = sp_pseq(1, -1);
             if (sp_custom("hupseq", &hybsprite, -1) == &mco)  
              &mco = sp_custom("huplimit", &hybsprite, -1);                        
             else
             {
              if (sp_custom("pupseq", &hybsprite, -1) == &mco)  
               &mco = sp_custom("puplimit", &hybsprite, -1);     
             }   
            }

            &save_x = sp_custom("Enable-Limit", &hybsprite, -1);
            if (&save_x > 0)
            {
             //override detected limit- check move axis (x or y) and direction (positive or negative along axis)
             //and set manual limit accordingly
             &save_x = sp_custom("move-axis", &hybsprite, -1);
             if (&save_x == 1)
             {
              &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setXmin", &hybsprite, -1);
              else
               &save_y = sp_custom("setXmax", &hybsprite, -1);
             }
             else
             {
              &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
              if (&save_x == 1)
               &save_y = sp_custom("setYmin", &hybsprite, -1);
              else
               &save_y = sp_custom("setYmax", &hybsprite, -1);
             }
             
             //check for ignore value set by dmod developer
             if (&save_y == 9999)
              &save_y = &mco;
             
             //check for "-1111" value to interpret as "-1"
             if (&save_y == -1111)
              &save_y = -1;
             
             //assure new limit does not breach our original detected hardness limits
             &save_x = sp_custom("MovePosNeg", &hybsprite, -1);
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
            &mco = sp_custom("move-axis", &hybsprite, -1);
            if (&mco == 1)
             &save_x = sp_x(&hybsprite, -1);
            else
             &save_x = sp_y(&hybsprite, -1);

            if (sp_custom("move-status", &hybsprite, -1) == 2)
             &mco = sp_custom("hupseq", &hybsprite, -1);
             
            if (sp_custom("move-status", &hybsprite, -1) == 3)
             &mco = sp_custom("pupseq", &hybsprite, -1);   

            if (sp_custom("move-status", &hybsprite, -1) <= 0)
            {
             //make sure Dink isn't actually pushing or pulling but move-status hasn't updated yet
             &mco = sp_pseq(1, -1);
             if (sp_custom("hupseq", &hybsprite, -1) == &mco)  
              &mco = sp_custom("hupseq", &hybsprite, -1);                        
             else
             {
              if (sp_custom("pupseq", &hybsprite, -1) == &mco)  
               &mco = sp_custom("pupseq", &hybsprite, -1);  
             } 
             
             if (sp_custom("hupseq", &hybsprite, -1) != &mco) 
             {
              if (sp_custom("pupseq", &hybsprite, -1) != &mco)
              {
               //Dink was neither pushing or pulling.
               //just don't let any of the if statements below run.
               &mco = 9999;
              }
             }                   
            } 

            sp_custom("limitreached", &hybsprite, 0);       
            if (&mco == 312)
            {
             if (&save_x >= &save_y) 
              sp_custom("limitreached", &hybsprite, 1);
            } 
            if (&mco == 314) 
            { 
             if (&save_x <= &save_y) 
              sp_custom("limitreached", &hybsprite, 1);   
            } 
            if (&mco == 316) 
            {
             if (&save_x >= &save_y)  
              sp_custom("limitreached", &hybsprite, 1);  
            }   
            if (&mco == 318) 
            {
             if (&save_x <= &save_y) 
              sp_custom("limitreached", &hybsprite, 1);
            } 
     	////////////////////////////////////////
     	//SPRITE LIMIT REACHED? CHECK COMPLETE//
    	 //////////////////////////////////////// 

 //reset &mco to 0
  &mco = 0; 

  //Check if Dink is pushing the sprite 
  &save_x = sp_custom("hupseq", &hybsprite, -1);   
  &save_y = sp_pseq(1, -1); 
  if (&save_x == &save_y)
  {
   //make the anim play normal since Dink is pushing.
   sp_reverse(1, 0);

   //update the "MovePosNeg" custom key
   &save_x = sp_custom("PushPosNeg", &hybsprite, -1);
   sp_custom("MovePosNeg", &hybsprite, &save_x);
 
   //if limit is reached, skip this.
   &save_x = sp_custom("limitreached", &hybsprite, -1);
   if (&save_x > 0)
    goto limit;

   //skip the move lines if the sprite is continuing in the same direction
   //this saves lag in older Dink engines
   &save_x = sp_custom("move-status", &hybsprite, -1);
   if (&save_x != 2)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("HybSpriteClone", &hybsprite, -1);
    
    //make object keep moving up to it's set PUSH limit.
    &save_x = sp_custom("huplimit", &hybsprite, -1);
    if (sp_custom("hupseq", &hybsprite, -1) == 312)
     move(&save_y, 2, &save_x, 1);
 
    if (sp_custom("hupseq", &hybsprite, -1) == 314)
     move(&save_y, 4, &save_x, 1);
 
    if (sp_custom("hupseq", &hybsprite, -1) == 316)
     move(&save_y, 6, &save_x, 1); 
 
    if (sp_custom("hupseq", &hybsprite, -1) == 318)
     move(&save_y, 8, &save_x, 1);
   }

   sp_custom("move-status", &hybsprite, 2);
   
   //to identify that move limit has not been reached and sprite should continue moving freely. 
   &mco = 1; 
  }

  &save_x = sp_custom("pupseq", &hybsprite, -1);  
  &save_y = sp_pseq(1, -1); 
  if (&save_x == &save_y)
  {
   //Check "NoRoomStart" key, which will tell us if Dink has clearance to pull
   &save_x = sp_custom("NoRoomStart", &hybsprite, -1);
   if (&save_x > 0)
   {
	//////////////////////
        //Re-Check pullspace//
        //////////////////////
        //Retrieve the FIRST known hardness, in DINK'S pull path
        &save_x = sp_custom("plimittrack1", &hybsprite, -1); 
        
        //if it's less than 0, hardness tracker sprite exited screen bound and no hardness was found
        //In this case, skip it.
        if (&save_x <= 0)
        {
         sp_custom("NoRoomStart", &hybsprite, 0);        
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
  	   sp_custom("NoRoomStart", &hybsprite, 0);
          else
          {
  	   sp_custom("NoRoomStart", &hybsprite, 1);
           say("Not enough room to pull it.", 1);
           sp_custom("limitreached", &hybsprite, 1);
           &mco = 0;
           goto limit;
  	  }
         }
         else
  	   sp_custom("NoRoomStart", &hybsprite, 0);
        }
	/////////////////////////////////////
        //RE-CHECK PULLSPACE CHECK COMPLETE//
        /////////////////////////////////////
   }

   //Make Dink's Push anim play in reverse, for pulling effect.
   sp_reverse(1, 1);

   //update the "MovePosNeg" custom key
   &save_x = sp_custom("PullPosNeg", &hybsprite, -1);
   sp_custom("MovePosNeg", &hybsprite, &save_x);
   
   //if limit is reached.. skip this.
   &save_x = sp_custom("limitreached", &hybsprite, -1);
   if (&save_x > 0)
    goto limit;

   //skip the move lines if the sprite is continuing in the same direction
   //this saves lag in older Dink engines
   &save_x = sp_custom("move-status", &hybsprite, -1);
   if (&save_x != 3)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("HybSpriteClone", &hybsprite, -1);
 
    //make object keep moving up to it's set move limit.
    &save_x = sp_custom("puplimit", &hybsprite, -1);
    if (sp_custom("pupseq", &hybsprite, -1) == 312)
     move(&save_y, 2, &save_x, 1);
 
    if (sp_custom("pupseq", &hybsprite, -1) == 314)
     move(&save_y, 4, &save_x, 1);
 
    if (sp_custom("pupseq", &hybsprite, -1) == 316)
     move(&save_y, 6, &save_x, 1);
     
    if (sp_custom("pupseq", &hybsprite, -1) == 318)
     move(&save_y, 8, &save_x, 1);
   }

   sp_custom("move-status", &hybsprite, 3);
   
   //to identify that move limit has not been reached and sprite should continue moving freely.     
   &mco = 1;
  }  
  
limit:  

   if (&mco == 0)
   {
    //retrieve the clone sprite for movement handling without interruption
    &save_y = sp_custom("HybSpriteClone", &hybsprite, -1);  

    //Dink is idle, walking towards the sprite, or a move limit was reached - stop the sprite
    //just use pupseq - either way we are stopping the sprite so doesn't matter.
     if (sp_custom("pupseq", &hybsprite, -1) == 316) 
      move(&save_y, 6, -200, 0);
    
     if (sp_custom("pupseq", &hybsprite, -1) == 314) 
      move(&save_y, 4, 750, 1);
    
     if (sp_custom("pupseq", &hybsprite, -1) == 312) 
      move(&save_y, 2, -200, 1);
    
     if (sp_custom("pupseq", &hybsprite, -1) == 318) 
      move(&save_y, 8, 600, 1); 
     
    &save_x = sp_custom("move-status", &hybsprite, -1);
    if (&save_x > 1)
    {
     //save status of push in "last-status" custom key
     sp_custom("last-status", &hybsprite, &save_x);
     //let script know limit checks and relock need to be performed.
     sp_custom("Idle-SkipChecks", &hybsprite, 0);
    }
     
    sp_custom("move-status", &hybsprite, 1);       
 
   //check player sequence, limitreached, and stopmove
   &save_y = 0;
   &save_x = sp_pseq(1, -1);
   if (&save_x > 520)
    &save_y += 11;
    
   &save_x = sp_custom("limitreached", &hybsprite, -1);
   if (&save_x > 0)
    &save_y += 1;
   
   &save_x = sp_custom("stopmove", &hybsprite, -1);   
   if (&save_x > 0)
   {
    &save_y += 1;   
   }  

   if (&save_y >= 1)
   {
    //at least one of the above checks returned true - halt the move.
    //make dink a static frame when he's idle while still moving an object
    sp_frame(1, 0);
    if (&save_y < 11)
     external("dsmove", "limit", &hybsprite);
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
     sp_custom("last-status", &hybsprite, &save_y);
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
 &save_x = sp_custom("HybSpriteClone", &hybsprite, -1);
 sp_active(&save_x, 0);
   
    &save_x = sp_custom("hybscript", &hybsprite, -1);
    if (&save_x > 0)
    { 
     run_script_by_number(&save_x, "end");
    }
    
 kill_this_task();
}