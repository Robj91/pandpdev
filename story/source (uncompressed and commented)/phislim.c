//Script for calculating the limit of Push and where the sprite should stop.
//Stop position of sprite is based on where either the sprite or Dink will hit hardness (whichever comes first).

void phislimit(void)
{
 //Similar to pullim, but detects the limit of push.
 
 //declare locals.
 int &val1;
 int &val2; 

 //check if any other sprite is currently performing it's phislimit proc
 &val1 = 0;
phispushfix:
 //get invisible shadow sprites, there is one for each moveable object that is currently being touched
 &val1 = get_next_sprite_with_this_brain(15, 0, &val1);
 if (&val1 > 0)
 {
  //now get the actual moveable sprite that the shadow is attached to
  &val2 = sp_custom("PP-Parent", &val1, -1);
  if (&val2 == &current_sprite)
  {
   //if it's this sprite, loop again, we've already checked for that above
   goto phispushfixend;
  }
  else
  {
   &val2 = sp_custom("PP-Parent", &val1, -1);
   &val2 = sp_custom("PP-Shadow", &val2, -1);
   if (&val2 == &val1)
   {
    &val2 = sp_custom("PP-Parent", &val1, -1);
    &val2 = sp_custom("phispushactive", &val2, -1);
    if (&val2 > 0)
    {
     //there is currently a direction proc running
     //we don't want to increment &val1 here, just throw in a wait and let it loop so it checks the same sprite again
     wait(1);
     goto phispushfix;
    }
   }
  }
 phispushfixend:
  &val1 += 1;
  goto phispushfix;
 } 

 //make sure only 1 direction proc from any moveable object can run at a time
 sp_custom("phispushactive", &current_sprite, 1);

 //If hardbox boundaries are set, let's set up the collision system!
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  //it is - spawn all scripts so we can just poke their procedures when we need
  &save_y = &current_sprite;
  &val1 = spawn("Col-Push");
  &val2 = spawn("Col-Ret");
  &save_x = spawn("Col-Fin");
  sp_custom("Col-Phis-Push", &current_sprite, &val1);
  sp_custom("Col-Phis-Ret", &current_sprite, &val2); 
  sp_custom("Col-Phis-Fin", &current_sprite, &save_x);  
  
  run_script_by_number(&val1, "PushCol");
  //external("Col-Push", "PushCol"); 
 }
 
 sp_custom("phislimit", &current_sprite, 0);
 sp_custom("phislimit2", &current_sprite, 0);
 sp_custom("PhisLim-Moved", &current_sprite, 0);
    
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
   sp_custom("DinkPhisTracker", &current_sprite, &val1);
   
   //bugfix - also save the current sprite in a custom key attached to the created sprite. 
   sp_custom("DinkPhisTrackerfix", &val1, &current_sprite);
   
   //create a tracker sprite for the moveable object as well
   &save_x = sp_x(&current_sprite, -1);
   &save_y = sp_y(&current_sprite, -1); 
   
   //if collision is enabled, put the tracker on the hardbox edge
   //and offset it based on the hardbox trim values (if applied)
   &val1 = sp_custom("AllowCollision", &current_sprite, -1);
   if (&val1 > 0)
   {  
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimbottom", &current_sprite, -1);
     if (&val1 > 0)
      &save_y -= &val1;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_x = sp_custom("LEFTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimleft", &current_sprite, -1);
     if (&val1 > 0)
      &save_x += &val1;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_x = sp_custom("RIGHTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimright", &current_sprite, -1);
     if (&val1 > 0)
      &save_x -= &val1;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_custom("TOPBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimtop", &current_sprite, -1);
     if (&val1 > 0)
      &save_y += &val1;
    }

    //make sure the position does not foul any hardbox edges, taking all trims into account.
    //These "BOX-POS" custom keys, already had the trim applied in "collpull.c"
    &val2 = sp_custom("BOTTOMBOX-POS", &current_sprite, -1);
    if (&save_y > &val2)
     &save_y = &val2;

    &val2 = sp_custom("LEFTBOX-POS", &current_sprite, -1);
    if (&save_x < &val2)
     &save_x = &val2;

    &val2 = sp_custom("RIGHTBOX-POS", &current_sprite, -1);
    if (&save_x > &val2)
     &save_x = &val2;

    &val2 = sp_custom("TOPBOX-POS", &current_sprite, -1);
    if (&save_y < &val2)
     &save_y = &val2;
   }
   
   &val1 = create_sprite(&save_x, &save_y, 0, 21, 1);  
   sp_speed(&val1, 1000);
   sp_nodraw(&val1, 1);
   sp_nohit(&val1, 1);
   
   sp_custom("ObjectPhisTracker", &current_sprite, &val1);
   sp_custom("ObjectPhisTrackerfix", &val1, &current_sprite);

 //So now we have Dink and Object trackers in custom keys "DinkPhisTracker" and "ObjectPhisTracker".
 
phislimitloop: 
 //check move axis
 &val2 = sp_custom("move-axis", &current_sprite, -1);

 //store the x or y for both tracker sprites, depending on the direction it's moving
 &val1 = sp_custom("DinkPhisTracker", &current_sprite, -1);
 &save_y = sp_custom("ObjectPhisTracker", &current_sprite, -1);
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

 //store the position, so we can compare after they move
 sp_custom("phislimittrack1", &current_sprite, &save_x);
 sp_custom("phislimittrack2", &current_sprite, &save_y);
 
 //Check if our collision tracker sprites exist, and if they do, store their position too. 
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
  //store the x or y of the tracker sprites before they move, depending on the direction the object will  be moving
   &save_y = sp_custom("move-axis", &current_sprite, -1);
   &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit1", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit2", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit3", &current_sprite, &save_x);
   }
    
   &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit4", &current_sprite, &save_x);
   }
    
   &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit5", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit6", &current_sprite, &save_x);
   }
   
   &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2) 
     &save_x = sp_y(&save_x, -1);
     
    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);
     
    sp_custom("TrackerPhisLimit7", &current_sprite, &save_x);
   }
 }

  &val1 = sp_custom("PhisLim-Moved", &current_sprite, -1);
  if (&val1 <= 0)
  {
   //don't process these lines if they have already been run once
    //might save lag in older engines.    
  
   //retrieve dinks push direction
   &val2 = sp_custom("pushdir", &current_sprite, -1);
  
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
   &val1 = sp_custom("DinkPhisTracker", &current_sprite, -1);
   &save_x = sp_custom("ObjectPhisTracker", &current_sprite, -1);
   move(&val1, &val2, &save_y, 0); 
   move(&save_x, &val2, &save_y, 0);
  
   //Check if our collision sprites exist and if so, move them too. 
   &save_x = sp_custom("AllowCollision", &current_sprite, -1);
   if (&save_x > 0) 
   {
     &val1 = sp_custom("pushdir", &current_sprite, -1);
     &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0); 
     
     &save_x = sp_custom("TrackerPhis2", &current_sprite, -1); 
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
    
     &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
     
     &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
   } 

   sp_custom("PhisLim-Moved", &current_sprite, 1);
  }
 
 //set appropriate wait times for whether collision is enabled & game version
 //this is necessary to prevent too much lag or locking up.
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

 //MARKER- removed bugfix scripting from here (NO LONGER REQUIRED).

 //check dinks original seq has not changed
  &save_x = sp_pseq(1, -1);
  &save_y = sp_custom("pseq-origin", &current_sprite, -1);
  if (&save_x != &save_y)
    goto phislimend;  

 /////////////////////////////////////////////////
 //check if the tracker sprites have stopped yet//
 /////////////////////////////////////////////////
 
 //Store new x or y position, depending on move axis
 &val1 = sp_custom("DinkPhisTracker", &current_sprite, -1);
 &val2 = sp_custom("ObjectPhisTracker", &current_sprite, -1);
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
     &save_y = sp_custom("phislimittrack1", &current_sprite, -1);
     if (&val1 == &save_y)
     {
      //Dink Limit has been found
      sp_custom("phislimit", &current_sprite, &val1);
      &save_x = sp_custom("DinkPhisTracker", &current_sprite, -1);
      sp_custom("done", &save_x, 1);
     }
     else
     {
      //Dink tracker is still moving - limit not yet found
      //assure if gone off screen, it dies, and limit is set to screen edge
      &save_x = sp_custom("pushdir", &current_sprite, -1);  
      &save_y = sp_custom("DinkPhisTracker", &current_sprite, -1);
      if (&save_x == 8) 
      {
       if (&val1 <= 0)
       {
        sp_custom("phislimit", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      }
      if (&save_x == 6) 
      {
       if (&val1 >= 620)
       {
        sp_custom("phislimit", &current_sprite, 700);
        sp_custom("done", &save_y, 1);
       }
      }  
      if (&save_x == 4) 
      {
       if (&val1 <= 20)
       {
        sp_custom("phislimit", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      } 
      if (&save_x == 2) 
      {
       if (&val1 >= 400)
       {
        sp_custom("phislimit", &current_sprite, 500);
        sp_custom("done", &save_y, 1);
       }
      } 
     }
 
     //check current sprite tracker
     &save_y = sp_custom("phislimittrack2", &current_sprite, -1);
     if (&val2 == &save_y)
     {
      //Object Limit has been found
      sp_custom("phislimit2", &current_sprite, &val2);
      &save_x = sp_custom("ObjectPhisTracker", &current_sprite, -1);
      sp_custom("done", &save_x, 1);
     }
     else
     {
      //sprite tracker is still moving - limit not yet found
      //assure if gone off screen, it dies, and limit is set to screen edge
      &save_x = sp_custom("pushdir", &current_sprite, -1);  
      &save_y = sp_custom("ObjectPhisTracker", &current_sprite, -1);
      if (&save_x == 8) 
      {
       if (&val2 <= 0)
       {
        sp_custom("phislimit2", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      }
      if (&save_x == 6) 
      {
       if (&val2 >= 620)
       {
        sp_custom("phislimit2", &current_sprite, 700);
        sp_custom("done", &save_y, 1);
       }
      }  
      if (&save_x == 4) 
      {
       if (&val2 <= 20)
       {
        sp_custom("phislimit2", &current_sprite, -100);
        sp_custom("done", &save_y, 1);
       }
      } 
      if (&save_x == 2) 
      {
       if (&val2 >= 400)
       {
        sp_custom("phislimit2", &current_sprite, 500);
        sp_custom("done", &save_y, 1);
       }
      } 
     } 

 //Check if our collision trackers exist, and if they do, check them too.
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
    //Tracker 1
     &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit1", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit1", &current_sprite, &save_y);
      }
      
      //check if current position is same as position stored in col-push.c "store" proc.
      //it will obviously be the same if a screen edge limit was set above.
      //but otherwise, comparison is required.
      &save_x = &save_y;
      &save_y = sp_custom("TrackerPhisLimit1", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit1-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 2
     &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit2", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit2", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerPhisLimit2", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit2-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
     
    //Tracker 3
     &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit3", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit3", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerPhisLimit3", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit3-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 4
     &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit4", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit4", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerPhisLimit4", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit4-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 5
     &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit5", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit5", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerPhisLimit5", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit5-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 6
     &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit6", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
        &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit6", &current_sprite, &save_y);
      }
     
      &save_x = &save_y;  
      &save_y = sp_custom("TrackerPhisLimit6", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit6-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
    
    //Tracker 7
     &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
     if (&save_x > 0)
     {
      if (sp_custom("pushdir", &current_sprite, -1) == 2) 
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y >= 400)
        sp_custom("TrackerPhisLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 4)
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y <= 20)
        sp_custom("TrackerPhisLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 6) 
      {
       &save_y = sp_x(&save_x, -1);
       if (&save_y >= 620)
        sp_custom("TrackerPhisLimit7", &current_sprite, &save_y);
      }
      if (sp_custom("pushdir", &current_sprite, -1) == 8)
      {
       &save_y = sp_y(&save_x, -1);
       if (&save_y <= 0)
        sp_custom("TrackerPhisLimit7", &current_sprite, &save_y);
      }
     
      &save_x = &save_y; 
      &save_y = sp_custom("TrackerPhisLimit7", &current_sprite, -1);
      if (&save_x == &save_y)
      {
       //Object Limit has been found
       sp_custom("TrackerPhisLimit7-ret", &current_sprite, &save_x);
       &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
       sp_custom("done", &save_x, 1);  
      }
     }
 }

 ///////////////////////////////////////
 //Tracker sprites stop-check complete//
 ///////////////////////////////////////
 
 //assure a limit was set, by checking the custom key "done" on the tracker sprites
 &val1 = sp_custom("DinkPhisTracker", &current_sprite, -1);
 &val2 = sp_custom("ObjectPhisTracker", &current_sprite, -1);
 &save_x = sp_custom("done", &val1, -1);
 &save_y = sp_custom("done", &val2, -1);
 &val1 = 0;

 //if not done, set &val1 to 1 and check it later, rather than using goto's.
 if (&save_x <= 0)
  &val1 = 1;

 if (&save_y <= 0)
  &val1 = 1;

 if (&val1 == 0)
 {
  //Check if our collision trackers exist, and if they do, check if they're done.
  &save_x = sp_custom("AllowCollision", &current_sprite, -1);
  if (&save_x > 0) 
  {
   &save_y = 1;
   
    //If the tracker sprites have found hardness, let the calling script know.
    //TrackerPhis1
     &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis2
     &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis3
     &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis4
     &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis5
     &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis6
     &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("done", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //TrackerPhis7
     &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
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
 
 //val1 now, if 1, we should loop the checks again.
 //else, the checks are complete.
 if (&val1 == 1)
 {
  //one or more tracker sprites are still moving.
  //check dinks original seq has not changed
  &save_x = sp_pseq(1, -1);
  &save_y = sp_custom("pseq-origin", &current_sprite, -1);
  if (&save_x != &save_y)
    goto phislimend;  
  
  goto phislimitloop;
 }
 else
 {
  //All tracker sprites have found hardness.
  
   //kill the tracking sprites
   &save_x = sp_custom("DinkPhisTracker", &current_sprite, -1);
   &save_y = sp_custom("DinkPhisTrackerfix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
   &save_x = sp_custom("ObjectPhisTracker", &current_sprite, -1);
   &save_y = sp_custom("ObjectPhisTrackerfix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

   //kill off our collision tracker sprites if they exist
   &save_x = sp_custom("AllowCollision", &current_sprite, -1);
   if (&save_x > 0) 
   {
    //kill off collision TrackerPhis sprites
    //TrackerPhis1
     &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis1fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
       
    //TrackerPhis2
     &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis2fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0); 
      
    //TrackerPhis3
     &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis3fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0); 
      
    //TrackerPhis4
     &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis4fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0); 
      
    //TrackerPhis5
     &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis5fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0); 
      
    //TrackerPhis6
     &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis6fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
      
    //TrackerPhis7
     &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
     &save_y = sp_custom("TrackerPhis7fix", &save_x, -1);
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
   &save_y = sp_custom("PushPosNeg", &current_sprite, -1);
   &save_x = sp_custom("Col-Phis-Fin", &current_sprite, -1); 
   if (&save_y == 2)
    run_script_by_number(&save_x, "PHISlessthan"); 
   else
    run_script_by_number(&save_x, "PHISgreaterthan"); 
           
   //external("Col-Fin", "Final", &save_x, &save_y, 1);
  }

  //OK SO NOW WE HAVE - Custom key Phislimit = position of next hardness in dinks path. 
  				 //Phislimit2 = position of next hardness in object's path.
  			
  //check if Dink's limit will be reached before the object's limit.
  &save_x = sp_custom("phislimit", &current_sprite, -1);
  &save_y = sp_custom("phislimit2", &current_sprite, -1);  
  if (&save_x != &save_y)
  {
   //it will, so work out where the object will be when dink reaches his limit, and set the limit accordingly.
   &save_x = sp_custom("phislimit", &current_sprite, -1);
   &save_y = sp_custom("hupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;
   
   &save_x -= &save_y;
   
   //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key. 
   if (&save_x == -1)
    &save_x = -1111;
    
   //re-store sprite's limit.
   &save_y = sp_custom("phislimit2", &current_sprite, -1);
   
   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("Dink-Push-Limit", &current_sprite, &save_x);
   sp_custom("Sprite-Push-Limit", &current_sprite, &save_y); 

   //check if Dink's PUSH limit will be reached before the object's limit.  
   &val1 = sp_custom("PushPosNeg", &current_sprite, -1);   
   if (&val1 == 1)
   {
    if (&save_x < &save_y)
     sp_custom("hupmove", &current_sprite, &save_y);
    else
     sp_custom("hupmove", &current_sprite, &save_x);
   }
   if (&val1 == 2)
   {
    if (&save_x > &save_y)
     sp_custom("hupmove", &current_sprite, &save_y);
    else
     sp_custom("hupmove", &current_sprite, &save_x);
   }
  }
  else
  {
   sp_custom("hupmove", &current_sprite, &save_x);
  
   //get difference again so we can store limit keys
   &save_x = sp_custom("phislimit", &current_sprite, -1);
   &save_y = sp_custom("hupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;
   
   &save_x -= &save_y;
   
   //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key. 
   if (&save_x == -1)
    &save_x = -1111;
    
   //re-store sprite limit
   &save_y = sp_custom("phislimit2", &current_sprite, -1);
   
   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("Dink-Push-Limit", &current_sprite, &save_x);
   sp_custom("Sprite-Push-Limit", &current_sprite, &save_y); 
  }

  //check if the object is already past it's detected move limit (been moved into another sprite and overlapping hardboxes?)
  &save_x = sp_custom("hupmove", &current_sprite, -1);
  &val1 = sp_custom("PushPosNeg", &current_sprite, -1);
  &val2 = sp_custom("move-axis", &current_sprite, -1);
  if (&val1 == 1)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
    
   if (&val2 == 2)
    &save_y = sp_y(&current_sprite, -1);
    
   if (&save_y < &save_x)
    sp_custom("hupmove", &current_sprite, &save_y);
  }
  if (&val1 == 2)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
    
   if (&val2 == 2)
    &save_y = sp_y(&current_sprite, -1);
               
   if (&save_y > &save_x)
    sp_custom("hupmove", &current_sprite, &save_y);
  }

  //MARKER - removed screen bound check - not needed anymore.

  //update hardness
  draw_hard_map();
  
  //kill off the spawned collision scripts, if they were active
  &save_x = sp_custom("AllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {  
   &val1 = sp_custom("Col-Phis-Push", &current_sprite, -1);
   &val2 = sp_custom("Col-Phis-Ret", &current_sprite, -1); 
   &save_x = sp_custom("Col-Phis-Fin", &current_sprite, -1);
   run_script_by_number(&val1, "KillColPush");
   run_script_by_number(&val2, "KillColRet"); 
   run_script_by_number(&save_x, "KillColFin");   
  }

  //return to where we cam from
  sp_custom("phispushactive", &current_sprite, 0); 
  
  kill_this_task();
 }
 
 //the below will kill off this script and let phispush.c know to cancel PUSH.
 phislimend:
 
 //kill off invisible sprites if still active
 &save_x = sp_custom("DinkPhisTracker", &current_sprite, -1);
 &save_y = sp_custom("DinkPhisTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);
  
 &save_x = sp_custom("ObjectPhisTracker", &current_sprite, -1);
 &save_y = sp_custom("ObjectPhisTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 //kill off our collision tracker sprites if they exist
 &save_x = sp_custom("AllowCollision", &current_sprite, -1);
 if (&save_x > 0) 
 {
  //kill off collision TrackerPhis sprites
  //TrackerPhis1
   &save_x = sp_custom("TrackerPhis1", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis1fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
     
  //TrackerPhis2
   &save_x = sp_custom("TrackerPhis2", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis2fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0); 
    
  //TrackerPhis3
   &save_x = sp_custom("TrackerPhis3", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis3fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0); 
    
  //TrackerPhis4
   &save_x = sp_custom("TrackerPhis4", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis4fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0); 
    
  //TrackerPhis5
   &save_x = sp_custom("TrackerPhis5", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis5fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0); 
    
  //TrackerPhis6
   &save_x = sp_custom("TrackerPhis6", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis6fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
    
  //TrackerPhis7
   &save_x = sp_custom("TrackerPhis7", &current_sprite, -1);
   &save_y = sp_custom("TrackerPhis7fix", &save_x, -1);
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
  &val1 = sp_custom("Col-Phis-Push", &current_sprite, -1);
  &val2 = sp_custom("Col-Phis-Ret", &current_sprite, -1); 
  &save_x = sp_custom("Col-Phis-Fin", &current_sprite, -1);
  run_script_by_number(&val1, "KillColPush");
  run_script_by_number(&val2, "KillColRet"); 
  run_script_by_number(&save_x, "KillColFin");   
 }

 //return and let phispush.c/phishyb.c know to terminate.
 sp_custom("phispushactive", &current_sprite, 0);    
 return(1);
 kill_this_task(); 
}