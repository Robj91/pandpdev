//Script to end push, pull ,and hybrid (sticky push)
//Use &arg4 to refer to sprite NOT &arg4

void end(void)
{
//this procedure is used to end the push, pull, and hybrid(sticky push)
//it is called by phispush.c, phispull.c and phishyb.c
//Also called directly by a few other scripts for remote push/pull sprite termination.


//////////////////////////////////
//ARGUMENTS VALUES - DESCRIPTION//
//////////////////////////////////

//&arg1 = 0 - Push/Pull/Hybrid activated succesfully, and stopped by player.

//&arg1 = 9 - Manual Termination out of course. 

//&arg1 = 1 - Dink changed screens while pulling something
//&arg1 = 2 - Dink changed screens while pushing something
//&arg1 = 8 - Dink changed screens while hybrid system active

//&arg1 = 3 - Pull terminated during initiating checks due to one of the checks failing
//            &arg2 = 1 - Terminated prior to speedlock - not used or needed anymore.
//            &arg2 = 2 - Terminated after speedlock 

//&arg1 = 4 - Push terminated during initiating checks due to one of the checks failing
//            &arg2 = 1 - Terminated prior to speedlock - not used or needed anymore.
//            &arg2 = 2 - Terminated after speedlock
//            &arg2 = 3 - Terminated after speedlock, due to pullkey held.

//&arg1 = 7 - Hybrid terminated during initiating checks due to one of the checks failing
//            &arg2 = 1 - Terminated prior to speedlock - not used or needed anymore.
//            &arg2 = 2 - Terminated after speedlock 

//&arg1 = 5 - Push terminated due to stop Dink moving 2 objects at once.
//&arg1 = 6 - Pull terminated due to stop Dink moving 2 objects at once.
//&arg1 = 10 - Hybrid terminated due to stop Dink moving 2 objects at once.


//&arg4 = Sprite being ended.

//////////////////////////////////
//ARGUMENTS VALUES - DESCRIPTION//
//////////////////////////////////

 //if Dink's health is depleted, end this here.
 if (&life < 1) 
  return;

 //we need 1 local
 int &val1;

 //This is to indicate that an instance of Phisend.c has initiated.
 sp_custom("Initiate-END", &arg4, 1);

   //////////////////////////////////////////////////////////////////
   //Check if there are any sprites currently with push/pull active//
   //////////////////////////////////////////////////////////////////
   //So we can determine what stuff we should skip so we don't screw them up
   &save_x = 0;
  ENDspritecheck:
   //If any other moveable sprites are being touched, they will have an invisible shadow sprite.
   &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
   if (&save_y > 0)
   { 
    //Retrieve the parent sprite (The sprite the shadow is attached to).
    &save_y = sp_custom("PP-Parent", &save_x, -1);
    if (&save_y == &arg4)
    {  
     //we've retrieved the current sprite- loop and search for other sprites.
     &save_x += 1;
     goto ENDspritecheck;
    }
    else
    {
     //We've found another shadow sprite - let's make sure it's a moveable sprite's shadow
     //retrieve the parent sprite
     &save_y = sp_custom("PP-Parent", &save_x, -1);
     
     //If it's a moveable sprite, "PP-Shadow" will EQUAL the active sprite number of it's shadow sprite.
     &save_y = sp_custom("PP-Shadow", &save_y, -1);
     if (&save_y == &save_x)
     {
      //We have found another moveable sprite currently being touched by Dink
      //retrieve the parent sprite in &save_y again.
      &save_y = sp_custom("PP-Parent", &save_x, -1);
      
      //now check if speedlock has been applied to the parent sprite
      &save_y = sp_custom("speedlock", &save_y, -1);
      if (&save_y > 0)
      {
       //This tells us at least one other sprite has speedlock active.
       //that's all we need to know - set the custom key.
       sp_custom("SkipSpeedReset", &arg4, 1);
      }
      else
      {
       //no speedlock key set on this sprite - loop and find the next shadow sprite
       &save_x += 1;
       goto ENDspritecheck;
      }
     }
     else
     {
      //This is not a moveable sprite(maybe a missile or something else) - loop and find the next shadow sprite
      &save_x += 1;
      goto ENDspritecheck;
     }
    }
   }
   //////////////////////////////////////////////////////////////////
   //Check if there are any sprites currently with push/pull active//
   ////////////////////////////////////////////////////////////////// 

 if (&arg1 > 0)
 {
  if (&arg1 == 1)
  { 
   //load back in correct push graphics
   init("load_sequence_now graphics\dink\push\ds-p2- 312 75 45 79 -7 -21 13 -7");
   init("load_sequence_now graphics\dink\push\ds-p4- 314 75 36 69 3 -9 45 9");
   init("load_sequence_now graphics\dink\push\ds-p6- 316 75 67 71 -21 -12 21");
   init("load_sequence_now graphics\dink\push\ds-p8- 318 75 46 59 -9 5 12 24");
   
   //load back in correct pig feed graphics (borrowed for base idle)
   init("load_sequence graphics\dink\seed\ds-s2- 522 150 49 74 -14 -9 16 10");
   init("load_sequence graphics\dink\seed\ds-s4- 524 150 47 73 -16 -10 14 10");
   init("load_sequence graphics\dink\seed\ds-s6- 526 150 53 71 -16 -10 16 10");
   init("load_sequence graphics\dink\seed\ds-s8- 528 150 50 70 -16 -9 16 9 ");
   
   //corect dinks base idle
   sp_base_idle(1, 10); 
   sp_reverse(1, 0);
   sp_frame(1, 1);
   
   //reset dinks speed
   external("DinkSpeed", "resetspeed", &arg4); 

   //corect dinks base walk
   sp_base_walk(1, 70);
   kill_this_task();
  }
  if (&arg1 == 2)
  {
   //reset dinks speed
   external("DinkSpeed", "resetspeed", &arg4); 

   //corect dinks base walk
   sp_base_walk(1, 70);
   kill_this_task();
  }
  if (&arg1 == 3)
  {
   if (&arg2 == 2)
   {
    &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
    if (&save_x <= 0)
     external("DinkSpeed", "resetspeed", &arg4); 
   }

    sp_custom("reset-required", &arg4, 1);      
   kill_this_task();
  }
  if (&arg1 == 4)
  {
   if (&arg2 >= 2)
   {
    &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
    if (&save_x <= 0)
     external("DinkSpeed", "resetspeed", &arg4);
   } 

   if (&arg2 == 3)
    sp_custom("pushbypass", &arg4, 1);
   else
    sp_custom("reset-required", &arg4, 1);   
    
   kill_this_task();
  }
  if (&arg1 == 5)
  {
   //update hardness
   sp_hard(&arg4, 0);
   draw_hard_map();

   //reset the sprites speed and timing
   &save_x = sp_custom("oldspeed", &arg4, -1);
   &save_y = sp_custom("oldtiming", &arg4, -1);
   sp_speed(&arg4, &save_x);
   sp_timing(&arg4, &save_y); 
 
   goto keyresets;
 
   kill_this_task();
  }
  if (&arg1 == 6)
  {
   //update hardness
   sp_hard(&arg4, 0);
   draw_hard_map();

   //reset the sprites speed and timing
   &save_x = sp_custom("oldspeed", &arg4, -1);
   &save_y = sp_custom("oldtiming", &arg4, -1);
   sp_speed(&arg4, &save_x);
   sp_timing(&arg4, &save_y);
  
   goto keyresets;
    
   kill_this_task();
  }
  if (&arg1 == 7)
  {  
   if (&arg2 == 2)
   {
    &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
    if (&save_x <= 0)
     external("DinkSpeed", "resetspeed", &arg4);  
   } 

    sp_custom("reset-required", &arg4, 1); 
   kill_this_task();   
  }
  if (&arg1 == 8)
  {
   //load back in correct push graphics
   init("load_sequence_now graphics\dink\push\ds-p2- 312 75 45 79 -7 -21 13 -7");
   init("load_sequence_now graphics\dink\push\ds-p4- 314 75 36 69 3 -9 45 9");
   init("load_sequence_now graphics\dink\push\ds-p6- 316 75 67 71 -21 -12 21");
   init("load_sequence_now graphics\dink\push\ds-p8- 318 75 46 59 -9 5 12 24");
   
   //load back in correct pig feed graphics (borrowed for base idle)
   init("load_sequence graphics\dink\seed\ds-s2- 522 150 49 74 -14 -9 16 10");
   init("load_sequence graphics\dink\seed\ds-s4- 524 150 47 73 -16 -10 14 10");
   init("load_sequence graphics\dink\seed\ds-s6- 526 150 53 71 -16 -10 16 10");
   init("load_sequence graphics\dink\seed\ds-s8- 528 150 50 70 -16 -9 16 9 ");
   
   //corect dinks idle
   sp_base_idle(1, 10); 
   sp_reverse(1, 0);
   sp_frame(1, 1);
   
   //reset dinks speed
   external("DinkSpeed", "resetspeed", &arg4); 

   //corect dinks base walk
   sp_base_walk(1, 70);
   kill_this_task(); 
  } 
  if (&arg1 == 9)
  {
   //manual termination out of course, let's make sure any auto-update scripts are killed off.
   sp_custom("hybkill", &arg4, 1);
   sp_custom("pupkill", &arg4, 1);
   sp_custom("hupkill", &arg4, 1);
   
   //Also kill off the main script if it's been started
   &save_x = sp_custom("hybscript", &arg4, -1);
   if (&save_x > 0)
    run_script_by_number(&save_x, "killhyb");

   &save_x = sp_custom("pushscript", &arg4, -1);
   if (&save_x > 0)
    run_script_by_number(&save_x, "killpush"); 

   &save_x = sp_custom("pullscript", &arg4, -1);
   if (&save_x > 0)
    run_script_by_number(&save_x, "killpull");
  }
  if (&arg1 == 10)
  {
   //update hardness
   sp_hard(&arg4, 0);
   draw_hard_map();

   //reset the sprites speed and timing
   &save_x = sp_custom("oldspeed", &arg4, -1);
   &save_y = sp_custom("oldtiming", &arg4, -1);
   sp_speed(&arg4, &save_x);
   sp_timing(&arg4, &save_y);

   goto keyresets;
   
   kill_this_task();
  }
 }
 
//Initial &arg checks complete - continue with normal push and pull system Termination.. 

 //check if Dink is currently moving this sprite
 &save_x = sp_custom("pushactive", &arg4, -1);
 &save_y = sp_custom("pullactive", &arg4, -1);
 if (&save_x != 1)
 {
   if (&save_y != 1)
   {
    &save_x = sp_custom("hybactive", &arg4, -1);
    if (&save_x != 1)
    { 
     sp_custom("INACTIVE", &arg4, 1);
    }
   }
 }

 &save_y = sp_custom("pullactive", &arg4, -1); 
 if (&save_y == 1)
 {
  //DINK WAS PULLING THE OBJECT
   //load back in correct push graphics
   init("load_sequence_now graphics\dink\push\ds-p2- 312 75 45 79 -7 -21 13 -7");
   init("load_sequence_now graphics\dink\push\ds-p4- 314 75 36 69 3 -9 45 9");
   init("load_sequence_now graphics\dink\push\ds-p6- 316 75 67 71 -21 -12 21");
   init("load_sequence_now graphics\dink\push\ds-p8- 318 75 46 59 -9 5 12 24");
  
   //load back in correct pig feed graphics (borrowed for base idle)
   init("load_sequence graphics\dink\seed\ds-s2- 522 150 49 74 -14 -9 16 10");
   init("load_sequence graphics\dink\seed\ds-s4- 524 150 47 73 -16 -10 14 10");
   init("load_sequence graphics\dink\seed\ds-s6- 526 150 53 71 -16 -10 16 10");
   init("load_sequence graphics\dink\seed\ds-s8- 528 150 50 70 -16 -9 16 9 ");

   //corect dinks base idle
   sp_base_idle(1, 10);
   sp_reverse(1, 0);
   sp_frame(1, 1);
  
   //Dink stopped pulling so assure the obect stops too - just make it move forwards to a position that's backwards from whre it is. Lol. It works.
   &save_x = sp_custom("pupseq", &arg4, -1); 
   if (&save_x == 316) move(&arg4, 6, -200, 1);
   if (&save_x == 314) move(&arg4, 4, 750, 1);
   if (&save_x == 312) move(&arg4, 2, -200, 1);
   if (&save_x == 318) move(&arg4, 8, 600, 1);
   
   //resume dinks original dir, facing the sprite
   &save_x = sp_custom("pushdir", &arg4, -1);
   sp_dir(1, &save_x);
 }
 
 &save_y = sp_custom("pushactive", &arg4, -1); 
 if (&save_y == 1) 
 {
  // Dink stopped pushing so assure the obect stops too - just make it move forwards to a position that's backwards from whre it is. Lol. It works.
  &save_x = sp_custom("hupseq", &arg4, -1);  
  if (&save_x == 316) move(&arg4, 6, -200, 1);
  if (&save_x == 314) move(&arg4, 4, 750, 1);
  if (&save_x == 312) move(&arg4, 2, -200, 1);
  if (&save_x == 318) move(&arg4, 8, 600, 1);
 } 
 
 &save_y = sp_custom("hybactive", &arg4, -1);
 if (&save_y == 1)
 {
  //HYBRID SYSTEM IN USE (STICKY PUSH)
  
  //load back in correct push graphics
  init("load_sequence_now graphics\dink\push\ds-p2- 312 75 45 79 -7 -21 13 -7");
  init("load_sequence_now graphics\dink\push\ds-p4- 314 75 36 69 3 -9 45 9");
  init("load_sequence_now graphics\dink\push\ds-p6- 316 75 67 71 -21 -12 21");
  init("load_sequence_now graphics\dink\push\ds-p8- 318 75 46 59 -9 5 12 24");
  
  //load back in correct pig feed graphics (borrowed for base idle)
  init("load_sequence graphics\dink\seed\ds-s2- 522 150 49 74 -14 -9 16 10");
  init("load_sequence graphics\dink\seed\ds-s4- 524 150 47 73 -16 -10 14 10");
  init("load_sequence graphics\dink\seed\ds-s6- 526 150 53 71 -16 -10 16 10");
  init("load_sequence graphics\dink\seed\ds-s8- 528 150 50 70 -16 -9 16 9 ");

  //corect dinks base idle
  sp_base_idle(1, 10);
  sp_reverse(1, 0);
  sp_frame(1, 1);

  //Dink stopped pulling so assure the obect stops too - just make it move forwards to a position that's backwards from whre it is. Lol. It works.
  &save_x = sp_custom("pupseq", &arg4, -1); 
  if (&save_x == 316) move(&arg4, 6, -200, 1);
  if (&save_x == 314) move(&arg4, 4, 750, 1);
  if (&save_x == 312) move(&arg4, 2, -200, 1);
  if (&save_x == 318) move(&arg4, 8, 600, 1);
 }

    &save_x = sp_xutom("PosAltered", &arg4, -1);
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
 
  //reset dink speed
  &save_x = sp_custom("SkipSpeedReset", &arg4, -1);
  if (&save_x <= 0)
   external("dinkspeed", "resetspeed", &arg4);

  //reset the sprites speed and timing
  &save_x = sp_custom("oldspeed", &arg4, -1);
  &save_y = sp_custom("oldtiming", &arg4, -1);
  sp_speed(&arg4, &save_x);
  sp_timing(&arg4, &save_y);
 }

 if (&arg1 <= 0)
 {
  //poke the MoveDetectAfter proc if this was a succesfully activated push/pull.
  &save_x = is_script_attached(&arg4);
  if (&save_x > 0)
  {
   run_script_by_number(&save_x, "MoveDetectAfter");
  }
 }

keyresets:
 //reset custom keys
 sp_custom("Pbutton", &arg4, 0);
 sp_custom("pushbypass", &arg4, 0);
 sp_custom("pullkeyheld", &arg4, 0);
 sp_custom("touching", &arg4, 0);

 sp_custom("PPMoving", &arg4, 0); 
 sp_custom("hybactive", &arg4, 0); 
 sp_custom("pushactive", &arg4, 0);
 sp_custom("pullactive", &arg4, 0); 
 sp_custom("pushscript", &arg4, 0);
 sp_custom("pullscript", &arg4, 0);
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
 sp_custom("CanPull", &arg4, 0);
 sp_custom("speedlock", &arg4, 0);
 sp_custom("SkipSpeedReset", &arg4, 0);

 sp_custom("move-status", &arg4, 0);
 sp_custom("Idle-SkipChecks", &arg4, 0);
 sp_custom("INACTIVE", &arg4, 0);

 //let phisbo.c "touch" proc know to reset the sprite. 
 //unless manual termination by author, then just run the killshadow.
 if (&arg1 != 9)
 {
  sp_custom("reset-required", &arg4, 1);
 }
 else
 {
  &save_x = sp_custom("PP-Shadow", &arg4, -1);
  &save_y = sp_custom("PP-Parent", &save_x, -1);
  if (&save_y == &arg4)
   sp_active(&save_x, 0);
 }
 
 kill_this_task();
}