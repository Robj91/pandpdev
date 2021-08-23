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

 //Check if author has chosen to run the ppbypass
 if (&arg1 == 1)
 {
  &save_x = is_script_attached(&current_sprite);
  if (&save_x > 0)
  {
   run_script_by_number(&save_x, "ppbypass");
   
   if (&return == 99)
   {
    //The ppbypass procedure exists - cancel this and run it.
    //make it reset everything  but act as if terminated so player must initiate it again for it to re-activate
    sp_custom("reset-required", &current_sprite, 1);   
    sp_custom("terminated", &current_sprite, 1);
    kill_this_task();
   }
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
     //to place Dink's actual location/depth dot where we want him to stop
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

 //Store Dink's speed in a custom key for later retrieval
 //we can retrieve the sp_speed equivelant of Dink and convert it to dink_speed value.
   //save both values in custom keys.
 &val1 = sp_speed(1, -1);
 sp_custom("PPd-sp_speed", &current_sprite, &val1);
 debug("phishyb dink CHECK SPEED is &val1");
 if (&val1 == 1)
 {
  &val1 = 4;
 }
 if (&val1 == 6)
 {
  &val1 = 2;
 }
 if (&val1 == 9)
 {
  &val1 = 1;
 }
 if (&val1 == 0)
 {
  &val1 = -1111;
 }
 sp_custom("PPd-speed", &current_sprite, &val1);

 //Make it so dink can't move in preperation for limit checks initiation of smooth sprite move. 
 set_dink_speed(-1);
 
 //NOTE - Dinks speed setting does not take effect until the next "wait()" AFTER it has been set.
   //The next wait occurs in hyblim.c.
     //Checks are conducted there to assure player hasn't moved >= 1 pixel into sprite hardbox.
   
 //save the speed and timing of the sprite in case we need to change it
 &save_x = sp_speed(&current_sprite, -1);
 &save_y = sp_timing(&current_sprite, -1);
 sp_custom("oldspeed", &current_sprite, &save_x);
 sp_custom("oldtiming", &current_sprite, &save_y);    
   
 //assure the speed of the sprite isn't too fast, we don't want dink walking faster than his speed
   //We COULD check dink's speed directly, since a wait line hasn't occured since setting it to -1
    //but for good practice, we'll just retrieve it from the custom key we stored it in.
 &save_x = sp_custom("PPd-sp_speed", &current_sprite, -1);
 &save_y = sp_speed(&current_sprite, -1);
 if (&save_y > &save_x)
 {
  //Sprite's speed is higher than Dinks, reduce it to match 
    //since sprite speed determines the push/pull speed.
  sp_speed(&current_sprite, &save_x);
  sp_timing(&current_sprite, 0);
 }
 
 sp_custom("speedlock", &current_sprite, 1);

 //assure Dink's frame delay is correct for sprite move speed
 //also store dink's frame delay in a custom key for later retrieval
 &val1 = sp_frame_delay(1, -1);
 sp_custom("PPdink-fd", &current_sprite, &val1);
 
 &save_x = sp_speed(&current_sprite, -1);
 if (&save_x >= 5)
  sp_frame_delay(1, 30);     
 
 if (&save_x <= 4)
   sp_frame_delay(1, 60);
      
 if (&save_x <= 2)
  sp_frame_delay(1, 0);
 
    //get the limit of how far the object can be pushed and pulled on the screen.
    external("HybLim", "hybridlimit");

    //check the outcome of the above called procedure and if we should continue or end push. 		
    &save_x = &return;
    if (&save_x > 0)
    {
     //triger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
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
     //trigger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }   
   
   //check dinks position hasn't changed
   &save_x = sp_x(1, -1);
   &save_y = sp_y(1, -1);
   &val1 = sp_custom("dinkox", &current_sprite, -1);
   &val2 = sp_custom("dinkoy", &current_sprite, -1);
   if (&save_x != &val1)
   {
     //triger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }  
   if (&save_y != &val2)
   {
     //triger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   } 
   
   //assures dink's original sequence HAS NOT changed.
   &save_x = sp_pseq(1, -1);
   &save_y = sp_custom("pseq-origin", &current_sprite, -1);
   if (&save_x != &save_y)
   {
     //trigger the end, and pass dink's original speed and frame_delay to the procedure
     &val1 = sp_custom("PPd-speed", &current_sprite, -1);
     &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
     external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
    kill_this_task();
   }
   ////////////////////////
   //END FAIL SAFE CHECKS//
   ////////////////////////

   //////////////////////////////////////////////////////////////////////////////////////////////////////
   //IF dink is already moving another sprite, cancel this - disable multiple moves, it causes problems//
   //////////////////////////////////////////////////////////////////////////////////////////////////////
    &save_x = 0;
   multipushKILL:
    &save_x = get_next_sprite_with_this_brain(15, 0, &save_x);
    if (&save_x > 0)
    {
     //now get the actual moveable sprite that the shadow is attached to
     &val1 = sp_custom("PP-Parent", &save_x, -1);
     if (&val1 == &current_sprite)
     {
      //if it's this sprite, loop again, we've already checked for that above
      &save_x += 1;
      goto multipushKILL;
     }
     else
     {
      &save_y = sp_custom("PP-Shadow", &val1, -1);
      if (&save_y == &save_x)
      {
       //make sure the push procedure has actually run on the other detected object, or else cancel this
       &save_y = sp_custom("hybactive", &val1, -1);
       if (&save_y <= 0)
       {
        &save_x += 1;
        goto multipushKILL;
       }
       else
       { 
        //Dink is moving another sprite - end this.
        &val1 = sp_custom("PPd-speed", &current_sprite, -1);
        &val2 = sp_custom("PPdink-fd", &current_sprite, -1);
        external("PhisEnd", "end", 7, 2, 0, &current_sprite, &val1, &val2);
 	kill_this_task();
       }
      }
     }
    }
    //////////////////////////
    //MULTIPUSHKILL COMPLETE//
    //////////////////////////

 //this is to store the fact that all checks have passed and 'Hybrid' is active.
 sp_custom("hybactive", &current_sprite, 1);  

 //generic active key, regardless of push, pull or sticky push for use in button4.c
 sp_custom("PPMoving", &current_sprite, 1); 

 //Make the sprite moveable - it can't move when it's set to hard
 sp_hard(&current_sprite, 1);
 draw_hard_map();
 
 //MARKER - "INIT" Lines removed in favor of fakedink creation sprite.

 //create the fake dink and shadow it to dink
 &save_y = sp_custom("hupseq", &current_sprite, -1);
 &val1 = sp_x(1, -1);
 &val2 = sp_y(1, -1);
 &save_x = create_sprite(&val1, &val2, 6, &save_y, 1);
 sp_seq(&save_x, &save_y);
 sp_brain(&save_x, 15);
 sp_brain_parm(&save_x, 1);
 sp_custom("fdink", &current_sprite, &save_x);
 &save_y = sp_frame_delay(1, -1);
 sp_frame_delay(&save_x, &save_y);

 //nodraw dink
 sp_nodraw(1, 1);
  
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
 //Then retrieve it immediately in "hybup.c" before it can have a chance to change.
 &save_x = &current_sprite;
 
 //Spawn hybup.c - hybup.c does a few different things, see the comments in that script for more info
 spawn("hybup"); 
 
 sp_custom("hybscript", &current_sprite, 0); 
 kill_this_task();
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
 sp_custom("hybscript", &current_sprite, 0); 
 kill_this_task();
}