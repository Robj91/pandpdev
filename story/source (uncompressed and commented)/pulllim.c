//Script for calculating the limit of Pull and where the sprite should stop.
//Stop position of sprite is based on where either the sprite or Dink will hit hardness (whichever comes first).
//There is some extra custom key calues that come into play for the pull limit, that aren't required in the push limit.
//These extra keys basically stop drink when his back foot hits hardness, for a more realistic look.
//so he doesn't appear as if he's stepping through hardness, basically.

void plimit(void)
{
//locals
 int &val1;
 int &val2;

 //check if any other sprite is currently performing it's plimit proc
 &val1 = 0;
phispullfix:
 //get invisible shadow sprites, there is one for each moveable object that is currently being touched
 &val1 = get_next_sprite_with_this_brain(15, 0, &val1);
 if (&val1 > 0)
 {
  //now get the actual moveable sprite that the shadow is attached to
  &val2 = sp_custom("PP-Parent", &val1, -1);
  if (&val2 == &current_sprite)
  {
   //if it's this sprite, loop again, we've already checked for that above
   goto phispullfixend;
  }
  else
  {
   &val2 = sp_custom("PP-Parent", &val1, -1);
   &val2 = sp_custom("PP-Shadow", &val2, -1);
   if (&val2 == &val1)
   {
    &val2 = sp_custom("PP-Parent", &val1, -1);
    &val2 = sp_custom("phispullactive", &val2, -1);
    if (&val2 > 0)
    {
     //there is currently a direction proc running
     //we don't want to increment &val1 here, just throw in a wait and let it loop so it checks the same sprite again
     wait(1);
     goto phispullfix;
    }
   }
  }
 phispullfixend:
  &val1 += 1;
  goto phispullfix;
 } 

 //make sure only 1 direction procedure from any moveable object can run at a time
 sp_custom("phispullactive", &current_sprite, 1);

 //If hardbox boundaries are set, let's set up the collision system!
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  //it is - spawn all scripts so we can just poke their procedures when we need
  &save_y = &current_sprite;
  &val1 = spawn("Col-Push");
  &val2 = spawn("Col-Ret");
  &save_x = spawn("Col-Fin");
  sp_custom("Col-Pull-Push", &current_sprite, &val1);
  sp_custom("Col-Pull-Ret", &current_sprite, &val2); 
  sp_custom("Col-Pull-Fin", &current_sprite, &save_x);  
  
  run_script_by_number(&val1, "PullCol");
  //external("Col-Push", "PushCol"); 
 }

 sp_custom("plimit", &current_sprite, 0);
 sp_custom("plimit2", &current_sprite, 0);
 sp_custom("PullLim-Moved", &current_sprite, 0);

   //store dinks position
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);   
     
   //Use an invisible duck for dink's tracker sprite (doesn't actualy matter what's used)
   &val1 = create_sprite(&save_x, &save_y, 0, 21, 1);
   
    //We want this thing to go FAST, so we can quickly find the hardness
    sp_speed(&val1, 1000);
    sp_nodraw(&val1, 1);
    sp_nohit(&val1, 1);
 
   //save above sprite in a custom key to retrieve later, avoids using another local variable
   sp_custom("DinkTracker", &current_sprite, &val1); 

   //bugfix - also save the current sprite in a custom key attached to the created sprite. 
   sp_custom("DinkTrackerfix", &val1, &current_sprite); 
 
   //create a tracker sprite for the moveable object as well
   &save_x = sp_x(&current_sprite, -1);
   &save_y = sp_y(&current_sprite, -1); 
   
   //if collision is enabled, put the tracker on the hardbox edge
   //and offset it based on the hardbox trim values (if applied)
   &val1 = sp_custom("AllowCollision", &current_sprite, -1);
   if (&val1 > 0)
   {  
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimbottom", &current_sprite, -1);
     if (&val1 > 0)
      &save_y -= &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_x = sp_custom("LEFTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimleft", &current_sprite, -1);
     if (&val1 > 0)
      &save_x += &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_x = sp_custom("RIGHTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimright", &current_sprite, -1);
     if (&val1 > 0)
      &save_x -= &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_custom("TOPBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimtop", &current_sprite, -1);
     if (&val1 > 0)
      &save_y += &val1;
    }

    //make sure the position does not foul any hardbox edges, taking all trims into account.
    //These "BOX-POS" custom keys, already had the trim applied in "collpull.c"
    &val1 = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
    if (&save_y > &val1)
     &save_y = &val1;

    &val1 = sp_custom("LEFTBOX-POS", &current_sprite, -1);
    if (&save_x < &val1)
     &save_x = &val1;

    &val1 = sp_custom("RIGHTBOX-POS", &current_sprite, -1);
    if (&save_x > &val1)
     &save_x = &val1;

    &val1 = sp_custom("TOPBOX-POS", &current_sprite, -1);
    if (&save_y < &val1)
     &save_y = &val1;
   }
   
   &val1 = create_sprite(&save_x, &save_y, 0, 21, 1);  
   sp_speed(&val1, 1000);
   sp_nodraw(&val1, 1);
   sp_nohit(&val1, 1);
   
   sp_custom("ObjectTracker", &current_sprite, &val1);
   sp_custom("ObjectTrackerfix", &val1, &current_sprite);    
    
 //So now we have Dink and Object trackers in custom keys "DinkTracker" and "ObjectTracker".
 //loop to to find hardness
plimitloop: 
 //check move axis
 &val2 = sp_custom("move-axis", &current_sprite, -1);

 //store the x or y for both tracker sprites, depending on the direction it's moving
 &val1 = sp_custom("DinkTracker", &current_sprite, -1);
 &save_y = sp_custom("ObjectTracker", &current_sprite, -1);
 if (&val2 == 2) 
 {
  &save_x = sp_y(&val1, -1);
  &save_y = sp_y(&save_y, -1);
 }
 if (&val2 == 1)
 {
  &save_x = sp_x(&val1, -1);
  &save_y = sp_x(&save_y, -1);
 }
 
 //store the position to compare after they move
 sp_custom("plimittrack1", &current_sprite, &save_x);
 sp_custom("plimittrack2", &current_sprite, &save_y);

 //Check if our collision tracker sprites exist, and if they do, store their position too. 
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
  //Store the x or y of the created trackers before they move, depending on direction object will be moving
   &save_y = sp_custom("move-axis", &current_sprite, -1);
   &save_x = sp_custom("Tracker1", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit1", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("Tracker2", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit2", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("Tracker3", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit3", &current_sprite, &save_x);
   }
    
   &save_x = sp_custom("Tracker4", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit4", &current_sprite, &save_x);
   }
    
   &save_x = sp_custom("Tracker5", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit5", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("Tracker6", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit6", &current_sprite, &save_x);
   }
   
    &save_x = sp_custom("Tracker7", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerLimit7", &current_sprite, &save_x);
   }
 }

  &val1 = sp_custom("PullLim-Moved", &current_sprite, -1);
  if (&val1 <= 0)
  {
   //don't process these lines if they have already been run once
    //might save lag in older engines.     
  
   //retrieve dinks pull direction
   &val2 = sp_custom("pulldir", &current_sprite, -1);

   //set the position for the tracking sprite to move to
   if (&val2 == 2) 
    &save_y = 445;
  
   if (&val2 == 4)
    &save_y = -45;
  
   if (&val2 == 6) 
    &save_y = 665;
  
   if (&val2 == 8) 
    &save_y = -50; 
   
   //make the sprite nohard
   sp_hard(&current_sprite, 1);
   draw_hard_map();
   
   //move the fast tracking sprites
   &val1 = sp_custom("DinkTracker", &current_sprite, -1);
   &save_x = sp_custom("ObjectTracker", &current_sprite, -1);
   move(&val1, &val2, &save_y, 0); 
   move(&save_x, &val2, &save_y, 0); 
   
   //Check if our collision sprites exist and if so, move them too. 
   &save_x = sp_custom("AllowCollision", &current_sprite, -1);
   if (&save_x > 0) 
   {
     &val1 = sp_custom("pulldir", &current_sprite, -1);
     &save_x = sp_custom("Tracker1", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0); 
     
     &save_x = sp_custom("Tracker2", &current_sprite, -1); 
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("Tracker3", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("Tracker4", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
    
     &save_x = sp_custom("Tracker5", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("Tracker6", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("Tracker7", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
   } 

   sp_custom("PullLim-Moved", &current_sprite, 1);
  }
  
  
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  &save_x = sp_custom("GameVersion", &current_sprite, -1); 
  if (&save_x == 108) 
   wait(0);
   
  if (&save_x == 110)
   wait(0);
   
  if (&save_x == 1096)
   wait(0);
   
  if (&save_x == 1084)
   wait(0); 
 }
 else
 {
  wait(0);
 }

 //check dinks original dir has not changed
 &save_x = sp_pseq(1, -1);
 &save_y = sp_custom("pseq-origin", &current_sprite, -1);
 if (&save_x != &save_y)
  goto pulllimend;  

 /////////////////////////////////////////////////
 //check if the tracker sprites have stopped yet//
 /////////////////////////////////////////////////
 
 //Store new x or y position, depending on move axis
 &val1 = sp_custom("DinkTracker", &current_sprite, -1);
 &val2 = sp_custom("ObjectTracker", &current_sprite, -1);
 &save_y = sp_custom("move-axis", &current_sprite, -1);
 if (&save_y == 2) 
 {
  &val1 = sp_y(&val1, -1);
  &val2 = sp_y(&val2, -1);
 }
 if (&save_y == 1)
 {
  &val1 = sp_x(&val1, -1);
  &val2 = sp_x(&val2, -1);
 }
 
     //check Dink tracker
     &save_y = sp_custom("plimittrack1", &current_sprite, -1);
     if (&val1 == &save_y)
     {
      //DINKS limit has been found first let's check dink has enough room to pull 
       //(30 pixels for east or west, 20 pixels for north or south)
      &save_y = sp_custom("pulldir", &current_sprite, -1);
      if (&save_y == 2)
      { 
       &save_y = sp_custom("dinkoy", &current_sprite, -1);
       &save_x = &val1;
       &save_x -= &save_y;
       &save_y = 20;
       goto 30pixend;
      }
      if (&save_y == 4)
      {
       &save_y = sp_custom("dinkox", &current_sprite, -1);
       &save_y -= &val1;
       &save_x = &save_y;
       &save_y = 30;
       goto 30pixend;
      }
      if (&save_y == 6) 
      {
       &save_y = sp_custom("dinkox", &current_sprite, -1);
       &save_x = &val1;
       &save_x -= &save_y;
       &save_y = 30;
       goto 30pixend;
      } 
      if (&save_y == 8) 
      {
       &save_y = sp_custom("dinkoy", &current_sprite, -1);
       &save_y -= &val1;
       &save_x = &save_y;
       &save_y = 20;
       goto 30pixend;
      }
      30pixend:
      
      if (&save_x <= &save_y)
      {
       //No point continuing anything, not enough room to pull the object
       say("Not enough room to pull it!", 1);
    
       goto pulllimend;
      } 
      
      //adjust where dinks depth dot would be when walking backwards, instead of actually changing it 
      //and set the pull limit to the exact coordinate of where the hardness was detected
      &save_x = sp_custom("DinkTracker", &current_sprite, -1);
      &save_y = sp_custom("dotchange", &current_sprite, -1);
      &val1 += &save_y;
      sp_custom("plimit", &current_sprite, &val1);
      sp_custom("done", &save_x, 1);
     }
     else
     {
      //Dink tracker is still moving - limit not yet found
      //assure if gone off screen, it dies, and limit is set to screen edge
      &save_x = sp_custom("pulldir", &current_sprite, -1);  
      &save_y = sp_custom("DinkTracker", &current_sprite, -1);
      if (&save_x == 8) 
      {
       if (&val1 <= 0)
       {
        sp_custom("plimit", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      }
      if (&save_x == 6) 
      {
       if (&val1 >= 620)
       {
        sp_custom("plimit", &current_sprite, 700);
        sp_custom("done", &save_y, 1);
       }
      }  
      if (&save_x == 4) 
      {
       if (&val1 <= 20)
       {
        sp_custom("plimit", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      } 
      if (&save_x == 2) 
      {
       if (&val1 >= 400)
       {
        sp_custom("plimit", &current_sprite, 500);
        sp_custom("done", &save_y, 1);
       }
      }  
     }
 
     //check current sprite tracker
     &save_y = sp_custom("plimittrack2", &current_sprite, -1);
     if (&val2 == &save_y)
     {
      //Object Limit has been found
      sp_custom("plimit2", &current_sprite, &val2);
      &save_x = sp_custom("ObjectTracker", &current_sprite, -1);
      sp_custom("done", &save_x, 1);  
     }
     else
     {
      //sprite tracker is still moving - limit not yet found
      //assure if gone off screen, it dies, and limit is set to screen edge
      &save_x = sp_custom("pulldir", &current_sprite, -1);  
      &save_y = sp_custom("ObjectTracker", &current_sprite, -1);
      if (&save_x == 8) 
      {
       if (&val2 <= 0)
       {
        sp_custom("plimit2", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      }
      if (&save_x == 6) 
      {
       if (&val2 >= 620)
       {
        sp_custom("plimit2", &current_sprite, 700);
        sp_custom("done", &save_y, 1);
       }
      }  
      if (&save_x == 4) 
      {
       if (&val2 <= 20)
       {
        sp_custom("plimit2", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      } 
      if (&save_x == 2) 
      {
       if (&val2 >= 400)
       {
        sp_custom("plimit2", &current_sprite, 500);
        sp_custom("done", &save_y, 1);
       }
      } 
     }

 //Check if our collision trackers exist, and if they do, check them too.
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
    //Tracker 1
     &save_x = sp_custom("Tracker1", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit1", &current_sprite, &save_y);
      }
      
      &save_x = &save_y;
      &save_y = sp_custom("TrackerLimit1", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit1-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker1", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 2
     &save_x = sp_custom("Tracker2", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit2", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerLimit2", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit2-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker2", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
     
    //Tracker 3
     &save_x = sp_custom("Tracker3", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit3", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerLimit3", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit3-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker3", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 4
     &save_x = sp_custom("Tracker4", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit4", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerLimit4", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit4-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker4", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 5
     &save_x = sp_custom("Tracker5", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit5", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerLimit5", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit5-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker5", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 6
     &save_x = sp_custom("Tracker6", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
        &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit6", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerLimit6", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit6-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker6", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 7
     &save_x = sp_custom("Tracker7", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pulldir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pulldir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerLimit7", &current_sprite, &save_y);
      }
     
      &save_x = &save_y; 
      &save_y = sp_custom("TrackerLimit7", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerLimit7-ret", &current_sprite, &save_x);
       &save_x = sp_custom("Tracker7", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
 }

 ///////////////////////////////////////
 //Tracker sprites stop-check complete//
 ///////////////////////////////////////

 //assure a limit was set, by checking the custom key "done" on the tracker sprites
 &val1 = sp_custom("DinkTracker", &current_sprite, -1);
 &val2 = sp_custom("ObjectTracker", &current_sprite, -1);
 &save_x = sp_custom("done", &val1, -1);
 &save_y = sp_custom("done", &val2, -1);
 &val1 = 0;

 if (&save_x <= 0)
  &val1 = 1;

 if (&save_y <= 0)
  &val1 = 1;

 if (&val1 == 0)
 {
  //Check if our collision trackers exist, and if they do, make sure they're done too
  &save_x = sp_custom("AllowCollision", &current_sprite, -1);
  if (&save_x > 0) 
  {
   &save_y = 1;

    //If trackers have found hardness, set custom keys to be able to identify this later
    //Tracker1
     &save_x = sp_custom("Tracker1", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker2
     &save_x = sp_custom("Tracker2", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker3
     &save_x = sp_custom("Tracker3", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker4
     &save_x = sp_custom("Tracker4", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker5
     &save_x = sp_custom("Tracker5", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker6
     &save_x = sp_custom("Tracker6", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //Tracker7
     &save_x = sp_custom("Tracker7", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
   
   if (&save_y <= 0)
    &val1 = 1;   
  }
 }
 
 if (&val1 == 1)
 {
  //one or more tracker sprites are still moving.
  //check dinks original seq has not changed
  &val2 = sp_pseq(1, -1);
  &save_y = sp_custom("pseq-origin", &current_sprite, -1);
  if (&val2 != &save_y)
   goto pulllimend; 
  
  goto plimitloop;
 }
 else
 {
  //All tracker sprites have found hardness.
 
   //kill the tracking sprites
   &save_x = sp_custom("DinkTracker", &current_sprite, -1);
   &save_y = sp_custom("DinkTrackerfix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
   &save_x = sp_custom("ObjectTracker", &current_sprite, -1);
   &save_y = sp_custom("ObjectTrackerfix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
 
   //kill off our collision tracker sprites if they exist
   &save_x = sp_custom("AllowCollision", &current_sprite, -1);
   if (&save_x > 0) 
   {
    //kill off collision tracker sprites
    //Tracker1
     &save_x = sp_custom("Tracker1", &current_sprite, -1);
     &save_y = sp_custom("Tracker1fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //Tracker2
     &save_x = sp_custom("Tracker2", &current_sprite, -1);
     &save_y = sp_custom("Tracker2fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //Tracker3
     &save_x = sp_custom("Tracker3", &current_sprite, -1);
     &save_y = sp_custom("Tracker3fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0); 
      
    //Tracker4
     &save_x = sp_custom("Tracker4", &current_sprite, -1);
     &save_y = sp_custom("Tracker4fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //Tracker5
     &save_x = sp_custom("Tracker5", &current_sprite, -1);
     &save_y = sp_custom("Tracker5fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //Tracker6
     &save_x = sp_custom("Tracker6", &current_sprite, -1);
     &save_y = sp_custom("Tracker6fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //Tracker7
     &save_x = sp_custom("Tracker7", &current_sprite, -1);
     &save_y = sp_custom("Tracker7fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
   }
  
   //make sprite hard again
   sp_hard(&current_sprite, 0);
   draw_hard_map();

  //If collision system was active, let's do the final calculation and overwrite the objects limit to the first detected stopped tracker sprite
  &save_x = sp_custom("AllowCollision", &current_sprite, -1);
  if (&save_x > 0) 
  { 
   &save_y = sp_custom("PullPosNeg", &current_sprite, -1);
   &save_x = sp_custom("Col-Pull-Fin", &current_sprite, -1); 
   if (&save_y == 2)
    run_script_by_number(&save_x, "lessthan"); 
   else
    run_script_by_number(&save_x, "greaterthan"); 
           
   //external("Col-Fin", "Final", &save_x, &save_y, 1);
  }

  //OK SO NOW WE HAVE - Custom key Plimit = position of next hardness in dinks path. 
  				 //Plimit2 = position of next hardness in object's path.

  //check if Dink's limit will be reached before the object's limit.
  //we approach this different to how push was processed, because dink will always be ahead of the sprite while pulling
  //So if Dink reaches his limit first, we just figure out where the object would be in relation and set the move limit to that
  //if the object reaches first, then set accordingly assuring there's 30 pixels difference to Dink's original limit (so Dink doesn't go to far and get stuck)
    //And also check if we stop the object at it's limit, after applying 30 pixel difference to dinks position, we have not passed dink's detected limit.
  &save_x = sp_custom("plimit", &current_sprite, -1);
  &save_y = sp_custom("plimit2", &current_sprite, -1); 
  if (&save_x != &save_y)
  {  
     //Figure out where the rock will be when dink has reached his hardness, and set the move limit accordingly
     &save_x = sp_custom("plimit", &current_sprite, -1);
     &save_y = sp_custom("pupdiff", &current_sprite, -1);
     if (&save_y == -1111)
      &save_y = -1;
  
     &save_x -= &save_y;
     
     //if value is "-1" change it to "-1111" instead, so it can be stored and retrieved in a custom key.  
     if (&save_x == -1)
      &save_x = -1111;
      
     //re-store sprite limit
     &save_y = sp_custom("plimit2", &current_sprite, -1); 

     //save limits in a more appropriately named custom key so we can use it later.
     sp_custom("Dink-Pull-Limit", &current_sprite, &save_x);
     sp_custom("Sprite-Pull-Limit", &current_sprite, &save_y); 

   //Check if sprite will reach limit before Dink
   &save_x = sp_custom("plimit", &current_sprite, -1);
   &save_y = sp_custom("plimit2", &current_sprite, -1);    
   &val1 = 0;
   &val2 = sp_custom("PullPosNeg", &current_sprite, -1);
   if (&val2 == 1)
   {
    if (&save_y > &save_x) 
     &val1 = 1;    
   }
   if (&val2 == 2)
   {
    if (&save_y < &save_x)
     &val1 = 1;    
   }
   
   if (&val1 == 1)
   {
    //Object will reach limit before Dink, set the move limit to that!
     &save_y = sp_custom("pupdiff", &current_sprite, -1);
     if (&save_y == -1111)
      &save_y = -1;
     
     //the two lines below will give us where Dink will be
     //When this sprite hits it's hardness limit.
     &save_x = sp_custom("plimit2", &current_sprite, -1);
     &val1 = &save_x;
     &save_x += &save_y;

     //now make sure this doesn't pass DINK's detected hardness limit
     &val2 = sp_custom("PullPosNeg", &current_sprite, -1);
     &save_y = sp_custom("plimit", &current_sprite, -1);
     if (&val2 == 1)
     {
      if (&save_x >= &save_y)
       sp_custom("pupmove", &current_sprite, &val1);
      else
       goto plimitcalc;     
     }
     if (&val2 == 2)
     {
      if (&save_x <= &save_y)     
       sp_custom("pupmove", &current_sprite, &val1);
      else
       goto plimitcalc;     
     }     
   }
   else
    goto plimitcalc;
  }
  else
  {
   plimitcalc:
   //Figure out where the rock will be when dink has reached his hardness, and set the move limit accordingly
   &save_x = sp_custom("plimit", &current_sprite, -1);
   &save_y = sp_custom("pupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;

   &save_x -= &save_y;
   
   //if value is "-1" change it to "-1111" instead, so it can be stored and retrieved in a custom key.  
   if (&save_x == -1)
    &save_x = -1111;

   sp_custom("pupmove", &current_sprite, &save_x);
 
   //re-store sprite limit
   &save_y = sp_custom("phislimit2", &current_sprite, -1);   
 
   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("Dink-Pull-Limit", &current_sprite, &save_x);
   sp_custom("Sprite-Pull-Limit", &current_sprite, &save_y);  
  }

  //check if the object is already past it's detected move limit (been moved into another sprite and overlapping hardboxes?)
  &save_x = sp_custom("pupmove", &current_sprite, -1);
  &val1 = sp_custom("PullPosNeg", &current_sprite, -1);
  &val2 = sp_custom("move-axis", &current_sprite, -1);
  if (&val1 == 1)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);
    
   if (&save_y < &save_x)
    sp_custom("pupmove", &current_sprite, &save_y);
  }
  if (&val1 == 2)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);
               
   if (&save_y > &save_x)
    sp_custom("pupmove", &current_sprite, &save_y);
  }

  //MARKER - removed screen bound check - not needed anymore.  
 
  //update hardness
  draw_hard_map();
 
  //kill off the spawned collision scripts, if they were active
  &save_x = sp_custom("AllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {  
   &val1 = sp_custom("Col-Pull-Push", &current_sprite, -1);
   &val2 = sp_custom("Col-Pull-Ret", &current_sprite, -1); 
   &save_x = sp_custom("Col-Pull-Fin", &current_sprite, -1);
   run_script_by_number(&val1, "KillColPush");
   run_script_by_number(&val2, "KillColRet"); 
   run_script_by_number(&save_x, "KillColFin");   
  }
  
  //return to where we cam from
  sp_custom("phispullactive", &current_sprite, 0);
  kill_this_task();
 }
 
 //the below will kill off this script and let phispull.c know to cancel PULL. 
 pulllimend:

 
 //kill off invisible sprites if still active
 &save_x = sp_custom("DinkTracker", &current_sprite, -1);
 &save_y = sp_custom("DinkTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);
  
 &save_x = sp_custom("ObjectTracker", &current_sprite, -1);
 &save_y = sp_custom("ObjectTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 //kill off our collision tracker sprites if they exist
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
  //kill off collision tracker sprites
  //Tracker1
   &save_x = sp_custom("Tracker1", &current_sprite, -1);
   &save_y = sp_custom("Tracker1fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //Tracker2
   &save_x = sp_custom("Tracker2", &current_sprite, -1);
   &save_y = sp_custom("Tracker2fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //Tracker3
   &save_x = sp_custom("Tracker3", &current_sprite, -1);
   &save_y = sp_custom("Tracker3fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0); 
    
  //Tracker4
   &save_x = sp_custom("Tracker4", &current_sprite, -1);
   &save_y = sp_custom("Tracker4fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //Tracker5
   &save_x = sp_custom("Tracker5", &current_sprite, -1);
   &save_y = sp_custom("Tracker5fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //Tracker6
   &save_x = sp_custom("Tracker6", &current_sprite, -1);
   &save_y = sp_custom("Tracker6fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //Tracker7
   &save_x = sp_custom("Tracker7", &current_sprite, -1);
   &save_y = sp_custom("Tracker7fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
 }

 //make sprite hard again
 sp_hard(&current_sprite, 0);
 draw_hard_map();

 //kill off the spawned collision scripts, if they were active
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {  
  &val1 = sp_custom("Col-Pull-Push", &current_sprite, -1);
  &val2 = sp_custom("Col-Pull-Ret", &current_sprite, -1); 
  &save_x = sp_custom("Col-Pull-Fin", &current_sprite, -1);
  run_script_by_number(&val1, "KillColPush");
  run_script_by_number(&val2, "KillColRet"); 
  run_script_by_number(&save_x, "KillColFin");   
 }

 //return and let phispull.c/phishyb.c know to terminate.  
 sp_custom("phispullactive", &current_sprite, 0);    
 return(1);
 kill_this_task(); 
}