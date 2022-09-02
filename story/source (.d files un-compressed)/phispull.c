//this script will check if Dink is facing the sprites hardbox edge, and no more than 1 pixel from it.
//This is executed when hardbox values are NOT provided
//returns '1' to calling script if true.
//returns '0' to calling script if false.

void auto_detect(void)
{
 int &val1;
 int &val2;

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
        &val2 = sp_custom("PPdirphisactive", &val2, -1);
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
     sp_custom("PPdirphisactive", &current_sprite, 1); 
     
     //This saves the difference between dink and the object
     sp_custom("PPdirrelpx", &current_sprite, 0);
     sp_custom("PPdirrelpy", &current_sprite, 0); 
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
     
     sp_custom("PPdirrelpx", &current_sprite, &val1);
     sp_custom("PPdirrelpy", &current_sprite, &val2);
     
     &save_x = sp_custom("PPdirrelpx", &current_sprite, &val1);
     &save_y = sp_custom("PPdirrelpy", &current_sprite, &val2);
     
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
     sp_custom("PPfindstartpx", &current_sprite, &save_x);
     sp_custom("PPfindstartpy", &current_sprite, &save_y); 
     sp_custom("PPdirpfindtrue", &current_sprite, 0);
     sp_custom("PPdirphistrackrun", &current_sprite, 0);
     //loop to find suitable test place. 
    dirpushfindloop:
    
     //let's make it so the sprite knows WHERE to move to.
     &save_x = sp_custom("PPfindstartpx", &current_sprite, -1);
     &save_y = sp_custom("PPfindstartpy", &current_sprite, -1);
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
     sp_custom("PPdirpmax", &current_sprite, &save_x);
    
     //if below is true, this is not the first loop - suitable place found. 
     //We need to spawn in the object so the real test is completed
     &val1 = sp_custom("PPdirpfindtrue", &current_sprite, -1);
     if (&val1 == 1)
     {
      //create the object in the correct place
      &val1 = sp_custom("PPdirrelpx", &current_sprite, -1);
      if (&val1 == -1111)
       &val1 = -1;
      
      &val2 = sp_custom("PPdirrelpy", &current_sprite, -1);
      if (&val2 == -1111)
       &val2 = -1;  
      
      
      &save_x = sp_custom("PPfindstartpx", &current_sprite, -1);
      &save_y = sp_custom("PPfindstartpy", &current_sprite, -1);   
      &save_x -= &val1;
      &save_y -= &val2;
      
      //set the seq and frame and create the object
      &val1 = sp_pseq(&current_sprite, -1);
      &val2 = sp_pframe(&current_sprite, -1);
      &val2 = create_sprite(&save_x, &save_y, 0, &val1, &val2);
      sp_hard(&val2, 0);
      sp_nodraw(&val2, 1);
      
      //store the created sprite in a custom key.
      sp_custom("PPphisdirtracker2", &current_sprite, &val2);
     
      //bugfix - also store current sprite in custom key of created sprite
      //so we can double check sprite against current_sprite
      sp_custom("PPphisdirtrackerfix", &val2, &current_sprite);
      
      draw_hard_map();
     }
    
     //set the x and y for the tracking sprite
     &save_x = sp_custom("PPfindstartpx", &current_sprite, -1);
     &save_y = sp_custom("PPfindstartpy", &current_sprite, -1);
     
     //Dink's seq
     &val1 = sp_custom("pushdir", &current_sprite, -1);
     &val2 = sp_custom("base_walk", &current_sprite, -1);
     &val1 += &val2;
     &val1 = create_sprite(&save_x, &save_y, 0, &val1, 1);
     sp_base_walk(&val1, &val2);
     sp_speed(&val1, 100);
     sp_nodraw(&val1, 1);
    
     //store the created sprite in a custom key.
     sp_custom("PPphisdirtracker", &current_sprite, &val1);
     
     //bugfix - also store current sprite in custom key of created sprite
     //so we can double check sprite against current_sprite
     sp_custom("PPphisdirtrackerfix", &val1, &current_sprite);
      
     //store the x and y of the fast sprite in a custom key for later retrieval
     &save_x = sp_x(&val1, -1);
     &save_y = sp_y(&val1, -1);
     sp_custom("PPdirptrack1", &current_sprite, &save_x);
     sp_custom("PPdirptrack2", &current_sprite, &save_y); 
    
     //set the position to move to
     &save_y = sp_custom("PPdirpmax", &current_sprite, -1);
    
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
      &save_y = sp_custom("PPdirptrack2", &current_sprite, -1);
     }
     else
     {
      //dink is facing east or west, store the old and new x position
      &save_x = sp_x(&val1, -1);
      &save_y = sp_custom("PPdirptrack1", &current_sprite, -1);
     } 
    
     if (&save_x == &save_y) 
     {
      &save_x = sp_custom("PPdirpfindtrue", &current_sprite, -1);
      if (&save_x == 1)
      {
       //Dink is in correct position to move, kill off tracking sprites and return to where we came form
       &save_x = sp_custom("PPphisdirtracker", &current_sprite, -1);
       &save_y = sp_custom("PPphisdirtracker2", &current_sprite, -1);
       
       //assure we are killing off the correct sprite
       //and not a different sprite that has taken the same active sprite#
       //due to this sprite dying somehow.
       &val1 = sp_custom("PPphisdirtrackerfix", &save_x, -1);
       if (&val1 == &current_sprite)
        sp_active(&save_x, 0);
        
       &val1 = sp_custom("PPphisdirtrackerfix", &save_y, -1);
       if (&val1 == &current_sprite)  
        sp_active(&save_y, 0);
       
       sp_custom("PPdirphisactive", &current_sprite, 0);
       draw_hard_map(); 
       return(0);
      }
 
      //the sprite is stuck against an interfering hardness, not a suitable place - better try a new spot
      &save_x = sp_custom("PPfindstartpx", &current_sprite, -1);
      &save_y = sp_custom("PPfindstartpy", &current_sprite, -1);
      //check whether to subtract or add
      &val2 = sp_custom("PPdirphistrackrun", &current_sprite, -1);
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
          If you are a tester/player, please notify the author of this dmod.
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
        sp_custom("PPdirphistrackrun", &current_sprite, 1);
       }
       if (&save_x < 60)
       {
        &save_x = 290;
        &save_y = 50;
        sp_custom("PPdirphistrackrun", &current_sprite, 2);
       }
      }
      
      sp_custom("PPfindstartpx", &current_sprite, &save_x);
      sp_custom("PPfindstartpy", &current_sprite, &save_y); 
     }
     else
     {
      &save_x = sp_custom("PPdirpfindtrue", &current_sprite, -1);
      if (&save_x == 1)
      {
       //Dink is not in correct position to move, kill off tracking sprites and return to where we came form
       &save_x = sp_custom("PPphisdirtracker", &current_sprite, -1);
       &save_y = sp_custom("PPphisdirtracker2", &current_sprite, -1);
    
       //assure we are killing off the correct sprite
       //and not a different sprite that has taken the same active sprite#
       //due to this sprite dying somehow.
       &val1 = sp_custom("PPphisdirtrackerfix", &save_x, -1);
       if (&val1 == &current_sprite)
        sp_active(&save_x, 0);
        
       &val1 = sp_custom("PPphisdirtrackerfix", &save_y, -1);  
       if (&val1 == &current_sprite)  
        sp_active(&save_y, 0);
    
       sp_custom("PPdirphisactive", &current_sprite, 0);    
       draw_hard_map();
       return(1);
      }

      //Suitable location found - increment the "PPdirpfindtrue" custom key
      //so the real test proceeds.
      &save_x = sp_custom("PPfindstartpx", &current_sprite, -1);
      &save_y = sp_custom("PPfindstartpy", &current_sprite, -1);
      sp_custom("PPdirpfindtrue", &current_sprite, 1);
     }
     //kill the tracking sprite and run another one
     &save_x = sp_custom("PPphisdirtracker", &current_sprite, -1);
     &save_y = sp_custom("PPphisdirtrackerfix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
     
     goto dirpushfindloop; 
     
    directionpushend:
       sp_custom("PPdirphisactive", &current_sprite, 0);
       return(1);
}