 //This script detects the limit of push and pull when using sticky push.
 //commented as best as I possibly could for those interested in how it works.
 //hybrid simply means push/pull combined or sticky push as it's called in game.

void hybridlimit(void)
{
 //declare locals.
 int &val1;
 int &val2;

 //check if any other sprite is currently executing a hybridlimit proc
 &val1 = 0;
phishybridfix:
 //get invisible shadow sprites, there is one for each moveable object that is currently being touched
 &val1 = get_next_sprite_with_this_brain(15, 0, &val1);
 if (&val1 > 0)
 {
  //now get the actual moveable sprite that the shadow is attached to
  &val2 = sp_custom("PP-Parent", &val1, -1);
  if (&val2 == &current_sprite)
  {
   //if it's this sprite, skip it.
   goto phishybridfixend;
  }
  else
  {
   &val2 = sp_custom("PP-Parent", &val1, -1);
   &val2 = sp_custom("PP-Shadow", &val2, -1);
   if (&val2 == &val1)
   {
    &val2 = sp_custom("PP-Parent", &val1, -1);
    &val2 = sp_custom("PPphishybridactive", &val2, -1);
    if (&val2 > 0)
    {
     //there is currently a hybridlimit procedure running
     //we don't want to increment &val1 here, just throw in a wait and let it loop so it checks the same sprite again  
     wait(1);
     goto phishybridfix;
    }
   }
  }
 phishybridfixend:
  &val1 += 1;
  goto phishybridfix;
 }

 //make sure only 1 direction procedure from any moveable object can run at a time or there will be bugs!
 sp_custom("PPphishybridactive", &current_sprite, 1);

 //If hardbox boundaries are set, let's set up the collision system!
 &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  //it is - spawn all scripts so we can just poke their procedures when we need
  &save_y = &current_sprite;
  &val1 = spawn("Col-Pull");
  &save_x = spawn("Col-Fin");
  sp_custom("PPCol-Hyb-Pull", &current_sprite, &val1);
  sp_custom("PPCol-Hyb-Fin", &current_sprite, &save_x);

  run_script_by_number(&val1, "HybCol");
 }

 sp_custom("PPphislimit", &current_sprite, 0);
 sp_custom("PPphislimit2", &current_sprite, 0);
 sp_custom("PPplimit", &current_sprite, 0);
 sp_custom("PPplimit2", &current_sprite, 0);
 sp_custom("PPHybLim-Moved", &current_sprite, 0);

   //store dinks position
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);

   //Use an invisible duck for dink's tracker sprite's (doesn't actualy matter what's uses)
   &val1 = create_sprite(&save_x, &save_y, 0, 21, 1);
   &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);

   //We want these things to go FAST, so we can quickly find the hardness
    sp_speed(&val1, 1000);
    sp_nodraw(&val1, 1);
    sp_nohit(&val1, 1);
    sp_speed(&val2, 1000);
    sp_nodraw(&val2, 1);
    sp_nohit(&val2, 1);

   //save above sprite's in custom keys to retrieve later, avoids using another local variable
   sp_custom("PPDinkTracker", &current_sprite, &val1);
   sp_custom("PPDinkPhisTracker", &current_sprite, &val2);

   //bugfix - also save the current sprite in a custom key attached to the created sprite's.
   sp_custom("PPDinkTrackerfix", &val1, &current_sprite);
   sp_custom("PPDinkPhisTrackerfix", &val2, &current_sprite);

   //create a tracker sprite for the moveable object as well
   &save_x = sp_x(&current_sprite, -1);
   &save_y = sp_y(&current_sprite, -1);

   //PULL - if collision is enabled, put the tracker on the hardbox edge
   //       and offset it based on the hardbox trim values (if applied)
   &val1 = sp_custom("PPAllowCollision", &current_sprite, -1);
   if (&val1 > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_custom("PPBOTTOMBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimbottom", &current_sprite, -1);
     if (&val1 > 0)
      &save_y -= &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_x = sp_custom("PPLEFTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimleft", &current_sprite, -1);
     if (&val1 > 0)
      &save_x += &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_x = sp_custom("PPRIGHTBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimright", &current_sprite, -1);
     if (&val1 > 0)
      &save_x -= &val1;
    }

    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_custom("PPTOPBOX-POS", &current_sprite, -1);
     &val1 = sp_custom("trimtop", &current_sprite, -1);
     if (&val1 > 0)
      &save_y += &val1;
    }

    //make sure the position does not foul any hardbox edges, taking all trims into account.
    //These "BOX-POS" custom keys, already had the trim applied in "col-pull.c"
    &val1 = sp_custom("PPBOTTOMBOX-POS", &current_sprite, -1);
    if (&save_y > &val1)
     &save_y = &val1;

    &val1 = sp_custom("PPLEFTBOX-POS", &current_sprite, -1);
    if (&save_x < &val1)
     &save_x = &val1;

    &val1 = sp_custom("PPRIGHTBOX-POS", &current_sprite, -1);
    if (&save_x > &val1)
     &save_x = &val1;

    &val1 = sp_custom("PPTOPBOX-POS", &current_sprite, -1);
    if (&save_y < &val1)
     &save_y = &val1;
   }

   &val1 = create_sprite(&save_x, &save_y, 0, 21, 1);

   //PUSH - if collision is enabled, put the tracker on the hardbox edge
   //and offset it based on the hardbox trim values (if applied)
   &val2 = sp_custom("PPAllowCollision", &current_sprite, -1);
   if (&val2 > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_custom("PPBOTTOMBOX-POS", &current_sprite, -1);
     &val2 = sp_custom("trimbottom", &current_sprite, -1);
     if (&val2 > 0)
      &save_y -= &val2;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_x = sp_custom("PPLEFTBOX-POS", &current_sprite, -1);
     &val2 = sp_custom("trimleft", &current_sprite, -1);
     if (&val2 > 0)
      &save_x += &val2;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_x = sp_custom("PPRIGHTBOX-POS", &current_sprite, -1);
     &val2 = sp_custom("trimright", &current_sprite, -1);
     if (&val2 > 0)
      &save_x -= &val2;
    }

    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_custom("PPTOPBOX-POS", &current_sprite, -1);
     &val2 = sp_custom("trimbottom", &current_sprite, -1);
     if (&val2 > 0)
      &save_y += &val2;
    }

    //make sure the position does not foul any hardbox edges, taking all trims into account.
    //These "BOX-POS" custom keys, already had the trim applied in "collpull.c"
    &val2 = sp_custom("PPBOTTOMBOX-POS", &current_sprite, -1);
    if (&save_y > &val2)
     &save_y = &val2;

    &val2 = sp_custom("PPLEFTBOX-POS", &current_sprite, -1);
    if (&save_x < &val2)
     &save_x = &val2;

    &val2 = sp_custom("PPRIGHTBOX-POS", &current_sprite, -1);
    if (&save_x > &val2)
     &save_x = &val2;

    &val2 = sp_custom("PPTOPBOX-POS", &current_sprite, -1);
    if (&save_y < &val2)
     &save_y = &val2;
   }

   &val2 = create_sprite(&save_x, &save_y, 0, 21, 1);
   sp_speed(&val1, 1000);
   sp_nodraw(&val1, 1);
   sp_nohit(&val1, 1);
   sp_speed(&val2, 1000);
   sp_nodraw(&val2, 1);
   sp_nohit(&val2, 1);

   sp_custom("PPObjectTracker", &current_sprite, &val1);
   sp_custom("PPObjectPhisTracker", &current_sprite, &val2);
   sp_custom("PPObjectTrackerfix", &val1, &current_sprite);
   sp_custom("PPObjectPhisTrackerfix", &val2, &current_sprite);

 //So now we have Dink and Object trackers in custom keys.
 //loop to to find hardness
hyblimitloop:

 //store the x or y for all tracker sprites, depending on the direction they're moving
 &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
 &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
 &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
 &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);

 if (sp_custom("move-axis", &current_sprite, -1) == 2)
 {
  &val1 = sp_y(&val1, -1);
  &val2 = sp_y(&val2, -1);
  &save_x = sp_y(&save_x, -1);
  &save_y = sp_y(&save_y, -1);
 }
 if (sp_custom("move-axis", &current_sprite, -1) == 1)
 {
  &val1 = sp_x(&val1, -1);
  &val2 = sp_x(&val2, -1);
  &save_x = sp_x(&save_x, -1);
  &save_y = sp_x(&save_y, -1);
 }

 //store the position to compare after they move
 sp_custom("PPplimittrack1", &current_sprite, &val1);
 sp_custom("PPphislimittrack1", &current_sprite, &val2);
 sp_custom("PPplimittrack2", &current_sprite, &save_x);
 sp_custom("PPphislimittrack2", &current_sprite, &save_y);

 //Check if our collision tracker sprites exist, and if they do, store their position too.
 &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  //PULL - Store the x or y of the created trackers before they move, depending on direction object will be moving
   &save_y = sp_custom("move-axis", &current_sprite, -1);
   &save_x = sp_custom("PPTracker1", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit1", &current_sprite, &save_x);
   }

   &save_x = sp_custom("PPTracker2", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit2", &current_sprite, &save_x);
   }

   &save_x = sp_custom("PPTracker3", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit3", &current_sprite, &save_x);
   }

   &save_x = sp_custom("PPTracker4", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit4", &current_sprite, &save_x);
   }

   &save_x = sp_custom("PPTracker5", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit5", &current_sprite, &save_x);
   }

   &save_x = sp_custom("PPTracker6", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit6", &current_sprite, &save_x);
   }

    &save_x = sp_custom("PPTracker7", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (&save_y == 2)
     &save_x = sp_y(&save_x, -1);

    if (&save_y == 1)
     &save_x = sp_x(&save_x, -1);

    sp_custom("PPTrackerLimit7", &current_sprite, &save_x);
   }

  //PUSH - store the x or y of the tracker sprites before they move, depending on the direction the object will  be moving
   &save_y = sp_custom("move-axis", &current_sprite, -1);
   &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
   if (&save_x > 0)
   {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit1", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit2", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit3", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit4", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit5", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit6", &current_sprite, &save_x);
    }

    &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
    if (&save_x > 0)
    {
     if (&save_y == 2)
      &save_x = sp_y(&save_x, -1);

     if (&save_y == 1)
      &save_x = sp_x(&save_x, -1);

     sp_custom("PPTrackerPhisLimit7", &current_sprite, &save_x);
    }
 }

  &val1 = sp_custom("PPHybLim-Moved", &current_sprite, -1);
  if (&val1 <= 0)
  {
   //retrieve dinks direction
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
   
   //move the fast tracking PUSH sprites
   &val1 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
   &save_x = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
   move(&val1, &val2, &save_y, 0);
   move(&save_x, &val2, &save_y, 0);

   //Check if our collision sprites exist and if so, move them too.
   &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
   if (&save_x > 0)
   {
     &val1 = sp_custom("pushdir", &current_sprite, -1);
     &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
   }

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

   //move the fast tracking PULL sprites
   &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
   &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
   move(&val1, &val2, &save_y, 0);
   move(&save_x, &val2, &save_y, 0);

   //Check if our collision sprites exist and if so, move them too.
   &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
   if (&save_x > 0)
   {
     &val1 = sp_custom("pulldir", &current_sprite, -1);
     &save_x = sp_custom("PPTracker1", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker2", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker3", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker4", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker5", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker6", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);

     &save_x = sp_custom("PPTracker7", &current_sprite, -1);
     if (&save_x > 0)
      move(&save_x, &val1, &save_y, 0);
   }

   sp_custom("PPHybLim-Moved", &current_sprite, 1);
  }

 wait(1);
 &val1 = sp_custom("PPHybLim-Moved", &current_sprite, -1); 
 if (&val1 <= 1)
 {
  //assure the player hasn't managed to move into the sprite hardbox before speed change took effect.
  &save_x = sp_custom("PushPosNeg", &current_sprite, -1);
  &save_y = sp_custom("move-axis", &current_sprite, -1);
  if (&save_y == 1)
  {
   &save_y = sp_custom("dinkox", &current_sprite, -1);
   &val1 = sp_x(1, -1);
   if (&save_x == 1)
   {
    if (&val1 < &save_y)
    {
     sp_x(1, &save_y);
     &save_y = sp_custom("dinkoy", &current_sprite, -1);
     sp_y(1, &save_y);
    }
   }
   else
   {
    if (&val1 > &save_y)
    {
     sp_x(1, &save_y);
     &save_y = sp_custom("dinkoy", &current_sprite, -1);
     sp_y(1, &save_y);
    }
   }
  }
  else
  {
   &save_y = sp_custom("dinkoy", &current_sprite, -1);
   &val1 = sp_y(1, -1);
   if (&save_x == 1)
   {
    if (&val1 < &save_y)
    {
     sp_y(1, &save_y);
     &save_y = sp_custom("dinkox", &current_sprite, -1);
     sp_x(1, &save_y);
    }
   }
   else
   {
    if (&val1 > &save_y)
    {
     sp_y(1, &save_y);
     &save_y = sp_custom("dinkox", &current_sprite, -1);
     sp_x(1, &save_y);
    }
   }  
  }
 
  sp_custom("PPHybLim-Moved", &current_sprite, 2);
 }

 //check dinks original seq has not changed
 &save_x = sp_pseq(1, -1);
 &save_y = sp_custom("PPpseq-origin", &current_sprite, -1);
 if (&save_x != &save_y)
 {
  goto hyblimend;
 }

 /////////////////////////////////////////////////
 //check if the tracker sprites have stopped yet//
 /////////////////////////////////////////////////
 //PUSH
      //Store new x or y position, depending on move axis
      &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
      &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
      &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
      &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);

      if (sp_custom("move-axis", &current_sprite, -1) == 2)
      {
       &val1 = sp_y(&val1, -1);
       &val2 = sp_y(&val2, -1);
       &save_x = sp_y(&save_x, -1);
       &save_y = sp_y(&save_y, -1);
      }
      if (sp_custom("move-axis", &current_sprite, -1) == 1)
      {
       &val1 = sp_x(&val1, -1);
       &val2 = sp_x(&val2, -1);
       &save_x = sp_x(&save_x, -1);
       &save_y = sp_x(&save_y, -1);
      }

      //check Dink PULL tracker
      if (sp_custom("PPplimittrack1", &current_sprite, -1) == &val1)
      {
       //DINKS limit has been found
       //adjust where dinks depth dot would be when walking backwards, instead of actually changing it
       //and set the pull limit to the exact coordinate of where the hardness was detected
       &val1 += sp_custom("PPdotchange", &current_sprite, -1);
       sp_custom("PPplimit", &current_sprite, &val1);
       &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
       sp_custom("PPdone", &val1, 1);
      }
      else
      {
       //Dink tracker is still moving - limit not yet found
       //assure if gone off screen, it dies, and limit is set to screen edge
       if (sp_custom("pulldir", &current_sprite, -1) == 8)
       {
        if (&val1 <= 0)
        {
         &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
         sp_custom("PPplimit", &current_sprite, -100);
         sp_custom("PPdone", &val1, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 6)
       {
        if (&val1 >= 620)
        {
         &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
         sp_custom("PPplimit", &current_sprite, 700);
         sp_custom("PPdone", &val1, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 4)
       {
        if (&val1 <= 20)
        {
         &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
         sp_custom("PPplimit", &current_sprite, -100);
         sp_custom("PPdone", &val1, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 2)
       {
        if (&val1 >= 400)
        {
         &val1 = sp_custom("PPDinkTracker", &current_sprite, -1);
         sp_custom("PPplimit", &current_sprite, 500);
         sp_custom("PPdone", &val1, 1);
        }
       }
      }

      //check Dink PUSH tracker
      if (sp_custom("PPphislimittrack1", &current_sprite, -1) == &val2)
      {
       sp_custom("PPphislimit", &current_sprite, &val2);
       &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
       sp_custom("PPdone", &val2, 1);
      }
      else
      {
       if (sp_custom("pushdir", &current_sprite, -1) == 8)
       {
        if (&val2 <= 0)
        {
         &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit", &current_sprite, -100);
         sp_custom("PPdone", &val2, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 6)
       {
        if (&val2 >= 620)
        {
         &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit", &current_sprite, 700);
         sp_custom("PPdone", &val2, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 4)
       {
        if (&val2 <= 20)
        {
         &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit", &current_sprite, -100);
         sp_custom("PPdone", &val2, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 2)
       {
        if (&val2 >= 400)
        {
         &val2 = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit", &current_sprite, 500);
         sp_custom("PPdone", &val2, 1);
        }
       }
      }

      //check current sprite PULL tracker
      if (sp_custom("PPplimittrack2", &current_sprite, -1) == &save_x)
      {
       sp_custom("PPplimit2", &current_sprite, &save_x);
       &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
       sp_custom("PPdone", &save_x, 1);
      }
      else
      {
       if (sp_custom("pulldir", &current_sprite, -1) == 8)
       {
        if (&save_x <= 0)
        {
         &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
         sp_custom("PPplimit2", &current_sprite, -100);
         sp_custom("PPdone", &save_x, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 6)
       {
        if (&save_x >= 620)
        {
         &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
         sp_custom("PPplimit2", &current_sprite, 700);
         sp_custom("PPdone", &save_x, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 4)
       {
        if (&save_x <= 20)
        {
         &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
         sp_custom("PPplimit2", &current_sprite, -100);
         sp_custom("PPdone", &save_x, 1);
        }
       }
       if (sp_custom("pulldir", &current_sprite, -1) == 2)
       {
        if (&save_x >= 400)
        {
         &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
         sp_custom("PPplimit2", &current_sprite, 500);
         sp_custom("PPdone", &save_x, 1);
        }
       }
      }

      //check current sprite PUSH tracker
      if (sp_custom("PPphislimittrack2", &current_sprite, -1) == &save_y)
      {
       sp_custom("PPphislimit2", &current_sprite, &save_y);
       &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
       sp_custom("PPdone", &save_y, 1);
      }
      else
      {
       if (sp_custom("pushdir", &current_sprite, -1) == 8)
       {
        if (&save_y <= 0)
        {
         &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit2", &current_sprite, -100);
         sp_custom("PPdone", &save_y, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 6)
       {
        if (&save_y >= 620)
        {
         &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit2", &current_sprite, 700);
         sp_custom("PPdone", &save_y, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 4)
       {
        if (&save_y <= 20)
        {
         &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit2", &current_sprite, -100);
         sp_custom("PPdone", &save_y, 1);
        }
       }
       if (sp_custom("pushdir", &current_sprite, -1) == 2)
       {
        if (&save_y >= 400)
        {
         &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
         sp_custom("PPphislimit2", &current_sprite, 500);
         sp_custom("PPdone", &save_y, 1);
        }
       }
      }


 //Check if our collision trackers exist, and if they do, check them too.
 &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
   //PUSH

  //Tracker 1
   &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit1", &current_sprite, &save_y);
    }

    //check if current position is same as position stored in col-pull.c "store" proc.
    //it will obviously be the same if a screen edge limit was set above.
    //but otherwise, comparison is required.
    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit1", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit1-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 2
   &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit2", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit2", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit2-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 3
   &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit3", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit3", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit3-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 4
   &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit4", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit4", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit4-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 5
   &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit5", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit5", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit5-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 6
   &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
      &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit6", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit6", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit6-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 7
   &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pushdir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerPhisLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerPhisLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerPhisLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pushdir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerPhisLimit7", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerPhisLimit7", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerPhisLimit7-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

   //PULL
  //Tracker 1
   &save_x = sp_custom("PPTracker1", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit1", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit1", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit1", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit1-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker1", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 2
   &save_x = sp_custom("PPTracker2", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit2", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit2", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit2", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit2-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker2", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 3
   &save_x = sp_custom("PPTracker3", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit3", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit3", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit3", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit3-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker3", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 4
   &save_x = sp_custom("PPTracker4", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit4", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit4", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit4", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit4-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker4", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 5
   &save_x = sp_custom("PPTracker5", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit5", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit5", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit5", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit5-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker5", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 6
   &save_x = sp_custom("PPTracker6", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit6", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
      &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit6", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit6", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit6-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker6", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }

  //Tracker 7
   &save_x = sp_custom("PPTracker7", &current_sprite, -1);
   if (&save_x > 0)
   {
    if (sp_custom("pulldir", &current_sprite, -1) == 2)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y >= 400)
      sp_custom("PPTrackerLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 4)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y <= 20)
      sp_custom("PPTrackerLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 6)
    {
     &save_y = sp_x(&save_x, -1);
     if (&save_y >= 620)
      sp_custom("PPTrackerLimit7", &current_sprite, &save_y);
    }
    if (sp_custom("pulldir", &current_sprite, -1) == 8)
    {
     &save_y = sp_y(&save_x, -1);
     if (&save_y <= 0)
      sp_custom("PPTrackerLimit7", &current_sprite, &save_y);
    }

    &save_x = &save_y;
    &save_y = sp_custom("PPTrackerLimit7", &current_sprite, -1);
    if (&save_x == &save_y)
    {
     //Object Limit has been found
     sp_custom("PPTrackerLimit7-ret", &current_sprite, &save_x);
     &save_x = sp_custom("PPTracker7", &current_sprite, -1);
     sp_custom("PPdone", &save_x, 1);
    }
   }
 }
 ///////////////////////////////////////
 //Tracker sprites stop-check complete//
 ///////////////////////////////////////

 //assure a limit was set, by checking the custom key "PPdone" on the tracker sprites
 &val1 = 0;
 &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
 &save_y = sp_custom("PPObjectPhisTracker", &current_sprite, -1);

 if (sp_custom("PPdone", &save_x, -1) <= 0)
  &val1 = 1;

 if (sp_custom("PPdone", &save_y, -1) <= 0)
  &val1 = 1;

 &save_x = sp_custom("PPDinkTracker", &current_sprite, -1);
 &save_y = sp_custom("PPDinkPhisTracker", &current_sprite, -1);

 if (sp_custom("PPdone", &save_x, -1) <= 0)
  &val1 = 1;

 if (sp_custom("PPdone", &save_y, -1) <= 0)
  &val1 = 1;

 if (&val1 == 0)
 {
  //Check if our collision trackers exist, and if they do, make sure they're done too
  &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {
   &save_y = 1;

    //PUSH - If trackers have found hardness, set custom keys to be able to identify this later
    //PPTracker1
     &save_x = sp_custom("PPTracker1", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker2
     &save_x = sp_custom("PPTracker2", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker3
     &save_x = sp_custom("PPTracker3", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker4
     &save_x = sp_custom("PPTracker4", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker5
     &save_x = sp_custom("PPTracker5", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker6
     &save_x = sp_custom("PPTracker6", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTracker7
     &save_x = sp_custom("PPTracker7", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }

    //PULL - If the tracker sprites have found hardness, let the calling script know.
    //PPTrackerPhis1
     &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis2
     &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis3
     &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis4
     &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis5
     &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis6
     &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }
    //PPTrackerPhis7
     &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
     if (&save_x > 0)
     {
      &save_x = sp_custom("PPdone", &save_x, -1);
      if (&save_x <= 0)
       &save_y = 0;
     }

   if (&save_y <= 0)
    &val1 = 1;
  }
 }

 if (&val1 == 1)
 {
  //check dinks original dir has not changed
  &val2 = sp_pseq(1, -1);
  &save_y = sp_custom("PPpseq-origin", &current_sprite, -1);
  if (&val2 != &save_y)
   goto hyblimend;

  goto hyblimitloop;
 }
 else
 {
  //All tracker sprites have found hardness.

   //kill the tracking sprites
    &save_x = sp_custom("PPDinkTracker", &current_sprite, -1);
    &save_y = sp_custom("PPDinkTrackerfix", &save_x, -1);
    if (&save_y == &current_sprite)
     sp_active(&save_x, 0);

    &save_x = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
    &save_y = sp_custom("PPDinkPhisTrackerfix", &save_x, -1);
    if (&save_y == &current_sprite)
     sp_active(&save_x, 0);

    &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
    &save_y = sp_custom("PPObjectTrackerfix", &save_x, -1);
    if (&save_y == &current_sprite)
     sp_active(&save_x, 0);

    &save_x = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
    &save_y = sp_custom("PPObjectPhisTrackerfix", &save_x, -1);
    if (&save_y == &current_sprite)
     sp_active(&save_x, 0);

   //kill off our collision tracker sprites if they exist
   &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
   if (&save_x > 0)
   {
    //kill off collision tracker sprites
    //PPTracker1
     &save_x = sp_custom("PPTracker1", &current_sprite, -1);
     &save_y = sp_custom("PPTracker1fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker2
     &save_x = sp_custom("PPTracker2", &current_sprite, -1);
     &save_y = sp_custom("PPTracker2fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker3
     &save_x = sp_custom("PPTracker3", &current_sprite, -1);
     &save_y = sp_custom("PPTracker3fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker4
     &save_x = sp_custom("PPTracker4", &current_sprite, -1);
     &save_y = sp_custom("PPTracker4fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker5
     &save_x = sp_custom("PPTracker5", &current_sprite, -1);
     &save_y = sp_custom("PPTracker5fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker6
     &save_x = sp_custom("PPTracker6", &current_sprite, -1);
     &save_y = sp_custom("PPTracker6fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTracker7
     &save_x = sp_custom("PPTracker7", &current_sprite, -1);
     &save_y = sp_custom("PPTracker7fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //kill off collision PPTrackerPhis sprites
    //PPTrackerPhis1
     &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis1fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis2
     &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis2fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis3
     &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis3fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis4
     &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis4fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis5
     &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis5fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis6
     &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis6fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);

    //PPTrackerPhis7
     &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
     &save_y = sp_custom("PPTrackerPhis7fix", &save_x, -1);
     if (&save_y == &current_sprite)
      sp_active(&save_x, 0);
   }

  //make sprite hard again
  sp_hard(&current_sprite, 0);
  draw_hard_map();

  //If collision system was active, let's do the final calculation and overwrite the objects limit to the first detected stopped tracker sprite
  &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {
   &save_y = sp_custom("PushPosNeg", &current_sprite, -1);
   &save_x = sp_custom("PPCol-Hyb-Fin", &current_sprite, -1);
   if (&save_y == 2)
    run_script_by_number(&save_x, "PHISlessthan");
   else
    run_script_by_number(&save_x, "PHISgreaterthan");

   &save_y = sp_custom("PullPosNeg", &current_sprite, -1);
   &save_x = sp_custom("PPCol-Hyb-Fin", &current_sprite, -1);
   if (&save_y == 2)
    run_script_by_number(&save_x, "lessthan");
   else
    run_script_by_number(&save_x, "greaterthan");
  }

  //OK SO NOW WE HAVE - Custom key Plimit = position of next hardness in dinks pull path.
  				 //Phislimit = position of next hardness in dinks push path.
  				 //Plimit2 = position of next hardness in object's pull path.
  				 //Phislimit2 = position of next hardness in object's push path.

  //PUSH
  //check if Dink's limit will be reached before the object's limit.
  &save_x = sp_custom("PPphislimit", &current_sprite, -1);
  &save_y = sp_custom("PPphislimit2", &current_sprite, -1);
  if (&save_x != &save_y)
  {
   //it will, so work out where the object will be when dink reaches his limit, and set the objects limit accordingly.
   &save_x = sp_custom("PPphislimit", &current_sprite, -1);
   &save_y = sp_custom("PPhupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;

   &save_x -= &save_y;

   //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key.
   if (&save_x == -1)
    &save_x = -1111;

   //re-store sprite's limit.
   &save_y = sp_custom("PPphislimit2", &current_sprite, -1);

   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("PPDink-Push-Limit", &current_sprite, &save_x);
   sp_custom("PPSprite-Push-Limit", &current_sprite, &save_y);

   //check if Dink's PUSH limit will be reached before the object's limit.
   &val1 = sp_custom("PushPosNeg", &current_sprite, -1);
   if (&val1 == 1)
   {
    if (&save_x < &save_y)
     sp_custom("PPhupmove", &current_sprite, &save_y);
    else
     sp_custom("PPhupmove", &current_sprite, &save_x);
   }
   if (&val1 == 2)
   {
    if (&save_x > &save_y)
     sp_custom("PPhupmove", &current_sprite, &save_y);
    else
     sp_custom("PPhupmove", &current_sprite, &save_x);
   }
  }
  else
  {
   sp_custom("PPhupmove", &current_sprite, &save_x);

   //get difference again so we can store limit keys
   &save_x = sp_custom("PPphislimit", &current_sprite, -1);
   &save_y = sp_custom("PPhupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;

   &save_x -= &save_y;

   //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key.
   if (&save_x == -1)
    &save_x = -1111;

   //re-store sprite limit
   &save_y = sp_custom("PPphislimit2", &current_sprite, -1);

   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("PPDink-Push-Limit", &current_sprite, &save_x);
   sp_custom("PPSprite-Push-Limit", &current_sprite, &save_y);
  }

  //check if the object is already past it's detected move limit (been moved into another sprite and overlapping hardboxes?)
  &save_x = sp_custom("PPhupmove", &current_sprite, -1);
  &val1 = sp_custom("PushPosNeg", &current_sprite, -1);
  &val2 = sp_custom("move-axis", &current_sprite, -1);
  if (&val1 == 1)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);

   if (&save_y < &save_x)
    sp_custom("PPhupmove", &current_sprite, &save_y);
  }
  if (&val1 == 2)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);

   if (&save_y > &save_x)
    sp_custom("PPhupmove", &current_sprite, &save_y);
  }

  //check if Dink's PULL limit will be reached before the object's limit.
  &save_x = sp_custom("PPplimit", &current_sprite, -1);
  &save_y = sp_custom("PPplimit2", &current_sprite, -1);
  if (&save_x != &save_y)
  {
     //Figure out where the rock will be when dink has reached his hardness, and set the move limit accordingly
     &save_x = sp_custom("PPplimit", &current_sprite, -1);
     &save_y = sp_custom("PPpupdiff", &current_sprite, -1);
     if (&save_y == -1111)
      &save_y = -1;

     &save_x -= &save_y;

     //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key.
     if (&save_x == -1)
      &save_x = -1111;

     //re-store sprite limit
     &save_y = sp_custom("PPplimit2", &current_sprite, -1);

     //save limits in a more appropriately named custom key so we can use it later.
     sp_custom("PPDink-Pull-Limit", &current_sprite, &save_x);
     sp_custom("PPSprite-Pull-Limit", &current_sprite, &save_y);

   //Check if sprite will reach limit before Dink
   &save_x = sp_custom("PPplimit", &current_sprite, -1);
   &save_y = sp_custom("PPplimit2", &current_sprite, -1);
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
     &save_y = sp_custom("PPpupdiff", &current_sprite, -1);
     if (&save_y == -1111)
      &save_y = -1;

     //the two lines below will give us where Dink will be
     //When this sprite hits it's hardness limit.
     &save_x = sp_custom("PPplimit2", &current_sprite, -1);
     &val1 = &save_x;
     &save_x += &save_y;
     //now make sure this doesn't pass DINK's detected hardness limit
     &val2 = sp_custom("PullPosNeg", &current_sprite, -1);
     &save_y = sp_custom("PPplimit", &current_sprite, -1);
     if (&val2 == 1)
     {
      if (&save_x >= &save_y)
       sp_custom("PPpupmove", &current_sprite, &val1);
      else
       goto plimitcalc;
     }
     if (&val2 == 2)
     {
      if (&save_x <= &save_y)
       sp_custom("PPpupmove", &current_sprite, &val1);
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
   //Limits are equal, figure out where the rock will be when dink has reached his hardness, and set the move limit accordingly
   &save_x = sp_custom("PPplimit", &current_sprite, -1);
   &save_y = sp_custom("PPpupdiff", &current_sprite, -1);
   if (&save_y == -1111)
    &save_y = -1;

   &save_x -= &save_y;

   //If value equals "-1" change it to "-1111" so it can be retrieved from a custom key.
   if (&save_x == -1)
    &save_x = -1111;

   sp_custom("PPpupmove", &current_sprite, &save_x);

   //re-store sprite limit
   &save_y = sp_custom("PPplimit2", &current_sprite, -1);

   //save limits in a more appropriately named custom key so we can use it later.
   sp_custom("PPDink-Pull-Limit", &current_sprite, &save_x);
   sp_custom("PPSprite-Pull-Limit", &current_sprite, &save_y);
  }

  //check if the object is already past it's detected move limit (been moved into another sprite and overlapping hardboxes?)
  &save_x = sp_custom("PPpupmove", &current_sprite, -1);
  &val1 = sp_custom("PullPosNeg", &current_sprite, -1);
  &val2 = sp_custom("move-axis", &current_sprite, -1);
  if (&val1 == 1)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);

   if (&save_y < &save_x)
    sp_custom("PPpupmove", &current_sprite, &save_y);
  }
  if (&val1 == 2)
  {
   if (&val2 == 1)
    &save_y = sp_x(&current_sprite, -1);
   else
    &save_y = sp_y(&current_sprite, -1);

   if (&save_y > &save_x)
    sp_custom("PPpupmove", &current_sprite, &save_y);
  }

  //MARKER - removed screen bound check - not needed anymore.

  //update hardness
  draw_hard_map();

  //kill off the spawned collision scripts, if they were active
  &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {
   &val1 = sp_custom("PPCol-Hyb-Pull", &current_sprite, -1);
   &save_x = sp_custom("PPCol-Hyb-Fin", &current_sprite, -1);
   run_script_by_number(&val1, "KillColPull");
   run_script_by_number(&save_x, "KillColFin");
  }

  //return to where we cam from
  sp_custom("PPphishybridactive", &current_sprite, 0);
  kill_this_task();
 }

 //the below will kill off this script and let phishyb.c know to cancel PULL.
 hyblimend:

 //kill off invisible sprites if still active
 &save_x = sp_custom("PPDinkTracker", &current_sprite, -1);
 &save_y = sp_custom("PPDinkTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 &save_x = sp_custom("PPDinkPhisTracker", &current_sprite, -1);
 &save_y = sp_custom("PPDinkPhisTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 &save_x = sp_custom("PPObjectTracker", &current_sprite, -1);
 &save_y = sp_custom("PPObjectTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 &save_x = sp_custom("PPObjectPhisTracker", &current_sprite, -1);
 &save_y = sp_custom("PPObjectPhisTrackerfix", &save_x, -1);
 if (&save_y == &current_sprite)
  sp_active(&save_x, 0);

 //kill off our collision tracker sprites if they exist
 &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
 if (&save_x > 0)
 {
  //kill off collision tracker sprites
  //PPTracker1
   &save_x = sp_custom("PPTracker1", &current_sprite, -1);
   &save_y = sp_custom("PPTracker1fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker2
   &save_x = sp_custom("PPTracker2", &current_sprite, -1);
   &save_y = sp_custom("PPTracker2fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker3
   &save_x = sp_custom("PPTracker3", &current_sprite, -1);
   &save_y = sp_custom("PPTracker3fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker4
   &save_x = sp_custom("PPTracker4", &current_sprite, -1);
   &save_y = sp_custom("PPTracker4fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker5
   &save_x = sp_custom("PPTracker5", &current_sprite, -1);
   &save_y = sp_custom("PPTracker5fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker6
   &save_x = sp_custom("PPTracker6", &current_sprite, -1);
   &save_y = sp_custom("PPTracker6fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTracker7
   &save_x = sp_custom("PPTracker7", &current_sprite, -1);
   &save_y = sp_custom("PPTracker7fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //kill off collision PPTrackerPhis sprites
  //PPTrackerPhis1
   &save_x = sp_custom("PPTrackerPhis1", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis1fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis2
   &save_x = sp_custom("PPTrackerPhis2", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis2fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis3
   &save_x = sp_custom("PPTrackerPhis3", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis3fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis4
   &save_x = sp_custom("PPTrackerPhis4", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis4fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis5
   &save_x = sp_custom("PPTrackerPhis5", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis5fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis6
   &save_x = sp_custom("PPTrackerPhis6", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis6fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);

  //PPTrackerPhis7
   &save_x = sp_custom("PPTrackerPhis7", &current_sprite, -1);
   &save_y = sp_custom("PPTrackerPhis7fix", &save_x, -1);
   if (&save_y == &current_sprite)
    sp_active(&save_x, 0);
 }

 //make sprite hard again
 sp_hard(&current_sprite, 0);
 draw_hard_map();

  //kill off the spawned collision scripts, if they were active
  &save_x = sp_custom("PPAllowCollision", &current_sprite, -1);
  if (&save_x > 0)
  {
   &val1 = sp_custom("PPCol-Hyb-Pull", &current_sprite, -1);
   &save_x = sp_custom("PPCol-Hyb-Fin", &current_sprite, -1);
   run_script_by_number(&val1, "KillColPull");
   run_script_by_number(&save_x, "KillColFin");
  }

 //return and let phishyb.c know to terminate.
 sp_custom("PPphishybridactive", &current_sprite, 0);
 return(1);
 kill_this_task();
}