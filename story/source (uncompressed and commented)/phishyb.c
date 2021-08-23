void hybrid(void)
{
//HYBRID "Sticky push" system- gets all the stuff ready in preperation for push and pull, and spawns hybup.c
 //a custom key to mark this proc has proceeded
 sp_custom("Initiate-Hybrid", &current_sprite, 1);

 //assures dink's original sequence HAS NOT changed.
 &save_x = sp_pseq(1, -1);
 &save_y = sp_custom("pseq-origin", &current_sprite, -1);
 if (&save_x != &save_y)
 {
  //it has changed - end it
  sp_custom("reset-required", &current_sprite, 1);
  kill_this_task();
 }

 	//we need a couple of locals
 	int &val1 = 0;
 	int &val2 = 0; 

 //make sure Dink is trying to push the object, and not just idling
 &save_x = sp_custom("pseq-origin", &current_sprite, -1);
 if (&save_x > 10)
 { 
  if (&save_x < 20)
  {
   //he's idling - end this now.
   sp_custom("reset-required", &current_sprite, 1);
   kill_this_task();
  }
 }


 ///////////////////////////////////////
 //HARDBOX EDGE TOUCH AND LOOK - CHECK//
 ///////////////////////////////////////
  //If HBOX custom key is 0, no hardbox values have been passed to phisbo.c - so we'll have to figure them out.
   //If HBOX custom key is 0, no hardbox values have been passed to phisbo.c.
   &val1 = sp_custom("HBOX", &current_sprite, -1);
   if (&val1 == 0)
   {
    //Hardbox values not provided.. so this will be tricky to detect
    //but we'll manage..
    
     //check if any other sprite is currently performing it's phisdir proc
     &val1 = 0;
    phisdirfix: 
     //get invisible shadow sprites, there is one for each moveable object that is currently being touched
     &val1 = get_next_sprite_with_this_brain(15, 0, &val1);
     if (&val1 > 0)
     {
      //now get the actual moveable sprite that the shadow is attached to
      &val2 = sp_custom("PP-Parent", &val1, -1);
      if (&val2 == &current_sprite)
      {
       //if it's this sprite, loop again, we've already checked for that above
       goto phisdirfixend;
      }
      else
      {
       &val2 = sp_custom("PP-Parent", &val1, -1);
       &val2 = sp_custom("PP-Shadow", &val2, -1);
       if (&val2 == &val1)
       {
        &val2 = sp_custom("PP-Parent", &val1, -1);
        &val2 = sp_custom("dirphisactive", &val2, -1);
        if (&val2 > 0)
        {
         //there is currently a direction proc running
         //we don't want to increment &val1 here, just throw in a wait and let it loop so it checks the same sprite again
         wait(1);
         goto phisdirfix;
        }
       }
      }
     phisdirfixend:
      &val1 += 1;
      goto phisdirfix;
     } 
          
     //make sure only 1 direction procedure from any moveable object can run at a time
     sp_custom("dirphisactive", &current_sprite, 1); 
     
     //This saves the difference between dink and the object
     sp_custom("dirrelpx", &current_sprite, 0);
     sp_custom("dirrelpy", &current_sprite, 0); 
     &val1 = sp_x(1, -1);
     &val2 = sp_y(1, -1);
     &save_x = sp_x(&current_sprite, -1);
     &save_y = sp_y(&current_sprite, -1);
     &val1 -= &save_x;
     &val2 -= &save_y;
     
     //assure we are not trying to save a value of -1 in a custom key, since it can't be retrieved.
     if (&val1 == -1)
      &val1 = -1111;
    
     if (&val2 == -1)
      &val2 = -1111;
     
     sp_custom("dirrelpx", &current_sprite, &val1);
     sp_custom("dirrelpy", &current_sprite, &val2);
     
     &save_x = sp_custom("dirrelpx", &current_sprite, &val1);
     &save_y = sp_custom("dirrelpy", &current_sprite, &val2);
     
     //Check if Dink is facing towards the sprite, which is required to push it..
     &val2 = sp_custom("pushdir", &current_sprite, -1);
     if (&val2 == 4)
     {
      //dink facing west
      &save_x = sp_x(&current_sprite, -1);
      
      //check if Dink is facing the sprite
      &save_y = sp_x(1, -1);
      if (&save_y < &save_x)
       goto directionpushend;
     }
     if (&val2 == 6)
     {
      &save_x = sp_x(&current_sprite, -1);
      
      &save_y = sp_x(1, -1);
      if (&save_y > &save_x)
       goto directionpushend;
     }
     if (&val2 == 2)
     {
      &save_x = sp_y(&current_sprite, -1);  
      
      &save_y = sp_y(1, -1);
      if (&save_y > &save_x)
       goto directionpushend;
     } 
     if (&val2 == 8)
     {
      &save_x = sp_y(&current_sprite, -1);
      
      &save_y = sp_y(1, -1);
      if (&save_y < &save_x)
       goto directionpushend;
     }  
     
     //set up the starting coordinates for the 'location test' sprite
     //make it a location off-screen for best chance of initial success.
     &save_x = 50;
     &save_y = 50;
     sp_custom("findstartpx", &current_sprite, &save_x);
     sp_custom("findstartpy", &current_sprite, &save_y); 
     sp_custom("dirpfindtrue", &current_sprite, 0);
     sp_custom("dirphistrackrun", &current_sprite, 0);
     //loop to find suitable test place. 
    dirpushfindloop:
    
     //let's make it so the sprite knows WHERE to move to.
     &save_x = sp_custom("findstartpx", &current_sprite, -1);
     &save_y = sp_custom("findstartpy", &current_sprite, -1);
     &val2 = sp_custom("pushdir", &current_sprite, -1);
     if (&val2 == 2) 
     {
      &save_y += 200;
      &save_x = &save_y;
     }
     if (&val2 == 4)
      &save_x -= 200;
    
     if (&val2 == 6) 
      &save_x += 200;
    
     if (&val2 == 8) 
     {
      &save_y -= 200;
      &save_x = &save_y;
     }
     sp_custom("dirpmax", &current_sprite, &save_x);
    
     //if below is true, this is not the first loop - suitable place found. 
     //We need to spawn in the object so the real test is completed
     &val1 = sp_custom("dirpfindtrue", &current_sprite, -1);
     if (&val1 == 1)
     {
      //create the object in the correct place
      &val1 = sp_custom("dirrelpx", &current_sprite, -1);
      if (&val1 == -1111)
       &val1 = -1;
      
      &val2 = sp_custom("dirrelpy", &current_sprite, -1);
      if (&val2 == -1111)
       &val2 = -1;  
      
      
      &save_x = sp_custom("findstartpx", &current_sprite, -1);
      &save_y = sp_custom("findstartpy", &current_sprite, -1);   
      &save_x -= &val1;
      &save_y -= &val2;
      
      //set the seq and frame and create the object
      &val1 = sp_pseq(&current_sprite, -1);
      &val2 = sp_pframe(&current_sprite, -1);
      &val2 = create_sprite(&save_x, &save_y, 0, &val1, &val2);
      sp_hard(&val2, 0);
      sp_nodraw(&val2, 1);
      
      //store the created sprite in a custom key.
      sp_custom("phisdirtracker2", &current_sprite, &val2);
     
      //bugfix - also store current sprite in custom key of created sprite
      //so we can double check sprite against current_sprite
      sp_custom("phisdirtrackerfix", &val2, &current_sprite);
      
      draw_hard_map();
     }
    
     //set the x and y for the tracking sprite
     &save_x = sp_custom("findstartpx", &current_sprite, -1);
     &save_y = sp_custom("findstartpy", &current_sprite, -1);
     
     //Dink's seq
     &val1 = sp_custom("pushdir", &current_sprite, -1);
     &val1 += 70;
     &val1 = create_sprite(&save_x, &save_y, 0, &val1, 1);
     sp_base_walk(&val1, 70);
     sp_speed(&val1, 100);
     sp_nodraw(&val1, 1);
    
     //store the created sprite in a custom key.
     sp_custom("phisdirtracker", &current_sprite, &val1);
     
     //bugfix - also store current sprite in custom key of created sprite
     //so we can double check sprite against current_sprite
     sp_custom("phisdirtrackerfix", &val1, &current_sprite);
      
     //store the x and y of the fast sprite in a custom key for later retrieval
     &save_x = sp_x(&val1, -1);
     &save_y = sp_y(&val1, -1);
     sp_custom("dirptrack1", &current_sprite, &save_x);
     sp_custom("dirptrack2", &current_sprite, &save_y); 
    
     //set the position to move to
     &save_y = sp_custom("dirpmax", &current_sprite, -1);
    
     //set the direction
     &save_x = sp_custom("pushdir", &current_sprite, -1);
    
     //move the fast sprite
     move(&val1, &save_x, &save_y, 0);
     wait(0);
     
     //check which cordinate to compare
     &save_y = sp_custom("move-axis", &current_sprite, -1); 
     if (&save_y == 2)
     {
      //dink is facing north or south, store the old and new y position
      &save_x = sp_y(&val1, -1);
      &save_y = sp_custom("dirptrack2", &current_sprite, -1);
     }
     else
     {
      //dink is facing east or west, store the old and new x position
      &save_x = sp_x(&val1, -1);
      &save_y = sp_custom("dirptrack1", &current_sprite, -1);
     } 
    
     if (&save_x == &save_y) 
     {
      &save_x = sp_custom("dirpfindtrue", &current_sprite, -1);
      if (&save_x == 1)
      {
       //Dink is in correct position to move, kill off tracking sprites and return to where we came form
       &save_x = sp_custom("phisdirtracker", &current_sprite, -1);
       &save_y = sp_custom("phisdirtracker2", &current_sprite, -1);
       
       //assure we are killing off the correct sprite
       //and not a different sprite that has taken the same active sprite#
       //due to this sprite dying somehow.
       &val1 = sp_custom("phisdirtrackerfix", &save_x, -1);
       if (&val1 == &current_sprite)
        sp_active(&save_x, 0);
        
       &val1 = sp_custom("phisdirtrackerfix", &save_y, -1);
       if (&val1 == &current_sprite)  
        sp_active(&save_y, 0);
       
       sp_custom("dirphisactive", &current_sprite, 0);
       draw_hard_map(); 
       goto dirphiscalccont;
      }
       
      //the sprite is stuck against an interfering hardness, not a suitable place - better try a new spot
      &save_x = sp_custom("findstartpx", &current_sprite, -1);
      &save_y = sp_custom("findstartpy", &current_sprite, -1);
      //check whether to subtract or add
      &val2 = sp_custom("dirphistrackrun", &current_sprite, -1);
      if (&val2 <= 0)
      {
       &save_x += 50;
       &save_y += 30;
       goto dirscrcont;
      }
      if (&val2 == 1)
      {
       &save_x -= 50;
       &save_y += 30;
       goto dirscrcont;
      }
      if (&val2 == 2)
      {
       &save_y += 50;
       goto dirscrcont;
      }
    
    dirscrcont:  
      //make sure test will not run off screen, since hardness is NOT drawn off screen.  
      if (&save_y > 360)
      {
       if (&save_x > 100)
       {
        if (&save_x < 500)
        {
         //We have exhausted most of the screen... just warn the author the auto system is not suitable.
         wait(1);
         stop_entire_game(1);
         choice_start();
         set_y 280
         set_title_color 15
         title_start();
         There is an error with a PUSH/PULL sprite on this screen. 
         The automatic detection of hardbox is NOT working in this particularly situation.
         The hardness on this screen is too busy. 
         title_end();
         "Tell me what to do."
         choice_end(); 
         
         if (&result == 1)
         {
          //stop_entire_game(1);
          choice_start();
          set_y 280
          set_title_color 15
          title_start();
          If you are the author, pass the hardbox values of the sprite to the phisbo procedure,
          which is called in the Push/pull sprite's MAIN procedure.
          If you are a tester/player, please notify the author of this error.
          title_end();
          "Continue Playing - This sprite won't move as it should"
          "Exit Game"
          choice_end(); 
          
          if (&result == 1)
           goto directionpushend;
      
          if (&result == 2)
           kill_game(); 
         }     
        }
       }
       if (&save_x > 560)
       {
        &save_x = 570;
        &save_y = 50;
        sp_custom("dirphistrackrun", &current_sprite, 1);
       }
       if (&save_x < 60)
       {
        &save_x = 290;
        &save_y = 50;
        sp_custom("dirphistrackrun", &current_sprite, 2);
       }
      }
      
      sp_custom("findstartpx", &current_sprite, &save_x);
      sp_custom("findstartpy", &current_sprite, &save_y); 
     }
     else
     {
      &save_x = sp_custom("dirpfindtrue", &current_sprite, -1);
      if (&save_x == 1)
      {
       //Dink is not in correct position to move, kill off tracking sprites and return to where we came form
       &save_x = sp_custom("phisdirtracker", &current_sprite, -1);
       &save_y = sp_custom("phisdirtracker2", &current_sprite, -1);
    
       //assure we are killing off the correct sprite
       //and not a different sprite that has taken the same active sprite#
       //due to this sprite dying somehow.
       &val1 = sp_custom("phisdirtrackerfix", &save_x, -1);
       if (&val1 == &current_sprite)
        sp_active(&save_x, 0);
        
       &val1 = sp_custom("phisdirtrackerfix", &save_y, -1);  
       if (&val1 == &current_sprite)  
        sp_active(&save_y, 0);
    
       sp_custom("dirphisactive", &current_sprite, 0);    
       draw_hard_map();
       sp_custom("reset-required", &current_sprite, 1);
       sp_custom("FailPush-Nowait", &current_sprite, -1); 
       kill_this_task();
      }
      
      //Suitable location found - increment the "dirpfindtrue" custom key
      //so the real test proceeds.
      &save_x = sp_custom("findstartpx", &current_sprite, -1);
      &save_y = sp_custom("findstartpy", &current_sprite, -1);
      sp_custom("dirpfindtrue", &current_sprite, 1);
     }
     //kill the tracking sprite and run another one
     &save_x = sp_custom("phisdirtracker", &current_sprite, -1);
     &save_y = sp_custom("phisdirtrackerfix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
     
     goto dirpushfindloop; 
     
    directionpushend:
       sp_custom("dirphisactive", &current_sprite, 0);
       sp_custom("reset-required", &current_sprite, 1);
       sp_custom("FailPush-Nowait", &current_sprite, 1); 
       kill_this_task();
   }
   else
   {
    //Hard box boundary values are provided, so that makes things a little easier
    //Copied in from "dirnocalc" for 1 less proc call, reduces lag in 1.08 and DinkHD.
 
    //First let's get the current position of the sprites hardbox boundaries, and save them away
    &save_x = sp_x(&current_sprite, -1);
    &save_y = sp_y(&current_sprite, -1);
    
    //current position of left boundary
    &val1 = sp_custom("LEFT-BOX", &current_sprite, -1);
    &val1 += &save_x; 
    sp_custom("LEFTBOX-POS", &current_sprite, &val1);
    
    //current position of top boundary
    &val1 = sp_custom("TOP-BOX", &current_sprite, -1);
    &val1 += &save_y; 
    sp_custom("TOPBOX-POS", &current_sprite, &val1);
    
    //current position of right boundary
    &val1 = sp_custom("RIGHT-BOX", &current_sprite, -1);
    &val1 += &save_x; 
    &val1 -= 1;
    sp_custom("RIGHTBOX-POS", &current_sprite, &val1);
   
    //current position of bottom boundary
    &val1 = sp_custom("BOTTOM-BOX", &current_sprite, -1);
    &val1 += &save_y; 
    &val1 -= 1;
    sp_custom("BOTTOMBOX-POS", &current_sprite, &val1);
   
    //check if dink is in the correct position and facing the sprites hardness
    &save_x = sp_custom("pushdir", &current_sprite, -1);
    if (&save_x == 2)
    {
     //Dink is facing south, 
   
     //assure he is above the sprites hard box
     &save_y = sp_y(1, -1);
     &val1 = sp_custom("TOPBOX-POS", &current_sprite, -1);
     
     if (&save_y < &val1)
     {
      //there should only be 1 pixel difference if DInk is standing against eh hardbox edge, let's make sure.
      &val1 -= &save_y;
      if (&val1 == 1)
      {
       //now make sure he is not too far to the right or left (could be right on the corner)
       &save_y = sp_x(1, -1);
       &val1 = sp_custom("LEFTBOX-POS", &current_sprite, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("RIGHTBOX-POS", &current_sprite, -1);  
        if (&save_y <= &val1)
        {
         //Dink is in correct position.
         goto dirphiscalccont;
        }
       }
      }
     }    
    }
    //OK you get the idea, I will not comment for the other directions.
    if (&save_x == 4)
    {
     &save_y = sp_x(1, -1);
     &val1 = sp_custom("RIGHTBOX-POS", &current_sprite, -1);
      
     if (&save_y > &val1)
     {
      &save_y -= &val1;
      if (&save_y == 1)
      {
       &save_y = sp_y(1, -1);
       &val1 = sp_custom("TOPBOX-POS", &current_sprite, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);  
        if (&save_y <= &val1)
        {
         goto dirphiscalccont;
        }
       }
      }
     }   
    }
    if (&save_x == 6)
    {
     &save_y = sp_x(1, -1);
     &val1 = sp_custom("LEFTBOX-POS", &current_sprite, -1);
      
     if (&save_y < &val1)
     {
      &val1 -= &save_y;
      if (&val1 == 1)
      {
       &save_y = sp_y(1, -1);
       &val1 = sp_custom("TOPBOX-POS", &current_sprite, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
        if (&save_y <= &val1)
        {
         goto dirphiscalccont;
        }
       }
      }
     }   
    }
    if (&save_x == 8)
    {
     &save_y = sp_y(1, -1);
     &val1 = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
     
     if (&save_y > &val1)
     {
      &save_y -= &val1;
      if (&save_y == 1)
      {
       &save_y = sp_x(1, -1);
       &val1 = sp_custom("LEFTBOX-POS", &current_sprite, -1);
       if (&save_y >= &val1)
       {
        &val1 = sp_custom("RIGHTBOX-POS", &current_sprite, -1);  
        if (&save_y <= &val1)
        {
         goto dirphiscalccont;
        }
       }
      }
     } 
    }
   }    
   //the below will only be run  if any of the direction calculation checks failed.
   sp_custom("reset-required", &current_sprite, 1); 
   kill_this_task(); 
  /////////////////////////////////////////////////
  //HARDBOX EDGE TOUCH AND LOOK? - CHECK COMPLETE//
  /////////////////////////////////////////////////

dirphiscalccont: 
 //if direction calculation took place there was a wait, so let's run a seqcheck again.
 //assures dink's original sequence HAS NOT changed - or pullkey is held
 &val1 = sp_custom("HBOX", &current_sprite, -1);
 if (&val1 == 0) 
 {
  &save_x = sp_pseq(1, -1);
  &save_y = sp_custom("pseq-origin", &current_sprite, -1);
  if (&save_x != &save_y)
  {
   //it has changed - end it
   sp_custom("reset-required", &current_sprite, 1);
   kill_this_task();
  }
 }
     
   //let's store Dink's required push sequence away in a custom key
   &save_x = sp_custom("pushdir", &current_sprite, -1);
   &save_x += 310;
   sp_custom("hupseq", &current_sprite, &save_x);

   //Let's store Dink's required pull sequence away in a custom key
   //Dink's pull sequence will be the opposite to his push sequence
   //so if he would be pushing to the WEST, EAST is his pull sequence
   //eg. pushing west = seq 314, so pulling would be seq 316.
   //we achieve the "pulling"(facing west), even though he's moving east
   //because further down in the script we load over the top of sequences
   //eg. in above example, 314 gets loaded also into 316.
   //This way we can differentiate the players seq and dir, but visually it's the same.
   &save_x = sp_custom("pulldir", &current_sprite, -1);
   &save_x += 310;
   sp_custom("pupseq", &current_sprite, &save_x);
 
   //also set the "pullstatic" custom key.
   //this will be the sequence when Dink is trying to move towards the object
   //since he's pulling, nothing will happen - we will freeze his frame.
   &save_x = sp_custom("pushdir", &current_sprite, -1);
   &save_x += 310;
   sp_custom("pullstatic", &current_sprite, &save_x);

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
   sp_custom("hupdiff", &current_sprite, &save_y);
   sp_custom("pupdiff", &current_sprite, &save_y);

     //"dotchange" custom key - basically wanting to shift where the depth dot would be
      	//(without actually doing it)
     //the normal Dink push depth dot is at the FRONT of him.
     //but when pulling, we want him to stop when his back foot hits hardness
     //or it looks like he goes through hardness
     //so we just set an amount that can be ADDED onto the detected hardness location
     //to place Dink's actual location/depth dot where we want it to stop
     //so he stops some pixels before the detected hardness instead. 
       &save_x = sp_custom("pulldir", &current_sprite, -1);
       if (&save_x == 2)
        sp_custom("dotchange", &current_sprite, -20);

       if (&save_x == 4)
        sp_custom("dotchange", &current_sprite, 30);

       if (&save_x == 6)
        sp_custom("dotchange", &current_sprite, -30);

       if (&save_x == 8)
        sp_custom("dotchange", &current_sprite, 20);

 //Make it so dink can't move in preperation for limit checks initiation of smooth sprite move.
 set_dink_speed(-1);
 
 //NOTE - Dinks speed setting does not take effect until the next "wait()" AFTER it has been set.
 //there is a wait line in DinkSpeed, "speedlock" procedure to do this and prevent a bug of him moving 
   
 //assure the speed of the sprite isn't too fast, we don't want dink walking faster than his speed
 external("DinkSpeed", "speedlock", &current_sprite);
 
 sp_custom("speedlock", &current_sprite, 1);

 //assure Dink's frame delay is correct for sprite move speed
 &save_x = sp_speed(&current_sprite, -1);
 if (&save_x >= 5)
  sp_frame_delay(1, 30);     
 
 if (&save_x <= 4)
   sp_frame_delay(1, 60);
      
 if (&save_x <= 2)
  sp_frame_delay(1, 0);

 //set "inventory" custom key to 0. 
 //If Dink opens his inventory, this gets set to 1 in "button4.c".
 //Then the push/pull scripts know to recheck dink's speed because he may have changed items.
 sp_custom("inventory", &current_sprite, 0);
 
    //get the limit of how far the object can be pushed and pulled on the screen.
    external("HybLim", "hybridlimit");
 
    //check the outcome of the above called procedure and if we should continue or end push. 		
    &save_x = &return;
    if (&save_x > 0)
    {
     external("PhisEnd", "end", 7, 2, 0, &current_sprite);
     kill_this_task();
    }

   ////////////////////
   //FAIL SAFE CHECKS//
   ////////////////////                
   //check dinks original dir has not changed
   &save_x = sp_dir(1, -1);
   &save_y = sp_custom("pushdir", &current_sprite, -1);
   if (&save_x != &save_y)
   {
    external("PhisEnd", "end", 7, 2, 0, &current_sprite);
    kill_this_task();
   }   
   
   //check dinks position hasn't changed
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);
   &val1 = sp_custom("dinkox", &current_sprite, -1);
   &val2 = sp_custom("dinkoy", &current_sprite, -1);
   if (&save_x != &val1)
   {
    external("PhisEnd", "end", 7, 2, 0, &current_sprite);
    kill_this_task();
   }  
   if (&save_y != &val2)
   {
    external("PhisEnd", "end", 7, 2, 0, &current_sprite);
    kill_this_task();
   } 
   
   //assures dink's original sequence HAS NOT changed.
   &save_x = sp_pseq(1, -1);
   &save_y = sp_custom("pseq-origin", &current_sprite, -1);
   if (&save_x != &save_y)
   {
    //it has changed - end it
    external("PhisEnd", "end", 7, 2, 0, &current_sprite);
    kill_this_task();
   }
   ////////////////////////
   //END FAIL SAFE CHECKS//
   ////////////////////////

 //this is to store the fact that all checks have passed and 'Hybrid' is active.
 sp_custom("hybactive", &current_sprite, 1);  

 //generic active key, regardless of push, pull or sticky push for use in button4.c
 sp_custom("PPMoving", &current_sprite, 1); 

 //Make the sprite moveable - it can't move when it's set to hard
 sp_hard(&current_sprite, 1);
 draw_hard_map();

 //need something in diag, so the sequence actually changes and cancels the push - we'll never see these.
 init("load_sequence_now graphics\dink\walk\ds-w1- 311 43 38 72 -14 -9 14 9");
 init("load_sequence_now graphics\dink\walk\ds-w3- 313 43 38 72 -14 -9 14 9");
 init("load_sequence_now graphics\dink\walk\ds-w7- 317 43 38 72 -12 -10 12 10");
 init("load_sequence_now graphics\dink\walk\ds-w9- 319 43 38 72 -14 -9 14 9");
 
 //also load in the opposite directions since we're pulling.
 //e.g if Dink is pulling west, load the EAST push seq into 316 to achieve the pulling affect.
 //also load over pig feed/seed throw sequence and use it as the base idle so we can detect when dink is idle
 //all these loaded seqs are visually the same, but we can now detect what the player is doing
 //by running a "sp_pseq" check. Basically we can constantly and instantly check the players direction input
   //(or lack of direction input - if they aren't pressing anything).
 &val2 = sp_custom("pulldir", &current_sprite, -1);
 if (&val2 == 2)
 {
  init("load_sequence_now graphics\dink\push\ds-p8- 312 75 46 59 -9 5 12 24");
  init("load_sequence_now graphics\dink\push\ds-p8- 522 75 46 59 -9 5 12 24");
  init("load_sequence_now graphics\dink\push\ds-p8- 528 75 46 59 -9 5 12 24");
 }
 if (&val2 == 4)
 {
  init("load_sequence_now graphics\dink\push\ds-p6- 314 75 67 71 -21 -12 21");
  init("load_sequence_now graphics\dink\push\ds-p6- 524 75 67 71 -21 -12 21");
  init("load_sequence_now graphics\dink\push\ds-p6- 526 75 67 71 -21 -12 21");
 }
 if (&val2 == 6)
 {
  init("load_sequence_now graphics\dink\push\ds-p4- 316 75 36 69 3 -9 45 9");
  init("load_sequence_now graphics\dink\push\ds-p4- 526 75 36 69 3 -9 45 9");
  init("load_sequence_now graphics\dink\push\ds-p4- 524 75 36 69 3 -9 45 9"); 
 }
 if (&val2 == 8)
 {
  init("load_sequence_now graphics\dink\push\ds-p2- 318 75 45 79 -7 -21 13 -7");
  init("load_sequence_now graphics\dink\push\ds-p2- 528 75 45 79 -7 -21 13 -7");
  init("load_sequence_now graphics\dink\push\ds-p2- 522 75 45 79 -7 -21 13 -7"); 
 }
  
 //change base idle, and base walk
 sp_base_idle(1, 520);
 sp_base_walk(1, 310);
  
 //save the current script in custom key "pullscript"
 &save_x = &current_script;
 sp_custom("hybscript", &current_sprite, &save_x);

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
   sp_custom("HybSpriteClone", &current_sprite, &save_x);

 //reset the initiate end custom key
 sp_custom("Initiate-END", &current_sprite, 0);

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
 //Then retrieve it STRAIGHT AWAY in "hybup.c" before it can have a chance to change.
 &save_x = &current_sprite;
 
 //Spawn hybup.c - hybup.c does a few different things, see the comments in that script for more info
 spawn("hybup"); 

//loop forever until hybup.c pokes this script and ends it. Long ass wait time so this loop doesn't add to lag.
//shouldn't even get to loop once. It would take roughly 2 and half hours for this to loop.
loop: 
 wait(9999999);
 goto loop; 
 
 //this script will not loop forever.
 //it is killed off later by another script
 //it jumps to one of the procs below using run_script_by_number at the appropriate time.
}

void end(void)
{
 sp_custom("hybscript", &current_sprite, 0);
 external("PhisEnd", "end", 0, 0, 0, &current_sprite);
 
 kill_this_task();
}

void multipushend(void)
{
 sp_custom("hybscript", &current_sprite, 0);
 external("PhisEnd", "end", 10, 0, 0, &current_sprite);
 kill_this_task();
}

void killhyb(void)
{
 kill_this_task();
}