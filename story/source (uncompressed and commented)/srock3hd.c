void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("rock3", &save_x, &current_sprite);

 //set rock to previous position it was left in
 &save_x = editor_seq(2, -1);
 &save_y = editor_seq(5, -1);
 if (&save_x > 0)
 {
  if (&save_y > 0)
  {
   sp_x(&current_sprite, &save_x); 
   sp_y(&current_sprite, &save_y);
   sp_hard(&current_sprite, 0);
   draw_hard_map();
  }
 }

 //put the rocks back in the position they were moved to before, if the player has already moved them.
 MoveDetectDuring();

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 3);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
  
 external("phisbo", "main", -21, -35, 23, 9);
 
 goto stopex;
}


void touch(void)
{
 &save_x = sp_custom("initiated", &current_sprite, -1);
 if (&save_x > 0)
 {
  sp_touch_damage(&current_sprite, 0);
  wait(&save_x);
  sp_custom("initiated", &current_sprite, 0);
 }
 external("phisbo", "touch"); 
 wait(200);
 external("phisbo", "touchreset");
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //tucked this away in it's own procedure. Lot's of position checking to do.
 //I already did this script, and then found out DinkHD lags when calling things from external.
 //proven by push and pull, when this constantly runs, it makes the push sequence take a huge performance hit
 //so thank goodness for version checker. We can make a DinkHD version of this script with goto's instead.
 goto rockposition;
 rockpositioncont:

 //You can use functions in if statements if comparing them to a number and not a variable.
 if (sp_custom("rockpos", &current_sprite, -1) == 1)
 {
  //the player is trying to push the rock out of the designated area
  //let's make the rock unable to move any further.
  sp_custom("stopmove", &current_sprite, 1);
 }
 if (sp_custom("rockpos", &current_sprite, -1) == 0)
 {
  //the player is trying to push the rock within the designated area
  //must call startmove to make the rock moveable again.
  sp_custom("stopmove", &current_sprite, 0);
 }
 &save_x = sp_custom("insidebox", &current_sprite, -1);
 if (&save_x == 1)
 {
  &save_x = get_sprite_with_this_brain(20, 0);
  &save_x = sp_editor_num(&save_x);
  editor_type(&save_x, 0);
  &save_x = editor_seq(&save_x, -1); 
  
  if (&save_x <= 0)
  {
   //run the procedure inside our brain 20 sign sprite that checks if puzzle is solved
   &save_x = get_sprite_with_this_brain(20, 0);
   &save_y = is_script_attached(&save_x);
   if (&save_y > 0)
   {
    run_script_by_number(&save_y, "puzzle");
   }  
  }
 }
 else
 {
  &save_x = get_sprite_with_this_brain(20, 0);
  &save_x = sp_editor_num(&save_x);
  editor_type(&save_x, 0);
  &save_x = editor_seq(&save_x, -1);
  
  if (&save_x == 1)
  {
   &save_x = get_sprite_with_this_brain(20, 0);
   &save_x = sp_editor_num(&save_x);
   editor_type(&save_x, 0);
   &save_x = editor_seq(&save_x, -1); 
   
   //run the procedure inside our brain 20 sign sprite to undo puzzle completion
   &save_x = get_sprite_with_this_brain(20, 0);
   &save_y = is_script_attached(&save_x);
   if (&save_y > 0)
   {
    run_script_by_number(&save_y, "Undo");
   }     
  }
 }
  
 goto stopex;
}

void MoveDetectAfter(void)
{
 //store the x and y in this sprite and the designated invisible poster sprite
 &save_x = sp_x(&current_sprite, -1);
 editor_seq(2, &save_x);
 &save_x = sp_y(&current_sprite, -1);
 editor_seq(5, &save_x); 
 
 goto stopex;
}

void pull(void)
{
 //call the pull procedure from phisbo
 external("phisbo", "pkey");

 goto stopex;
}

void talk(void)
{
 external("phisbo", "talk");
 &val1 = sp_custom("talkreturn", &current_sprite, -1);

 if (&val1 == 2)
 {
  external("dsmove", "main");
 }
 if (&val1 == 1)
 {
 }

 external("phisbo", "touchreset");
 goto stopex;
}

void hit(void)
{
 external("phisbo", "hit");

 external("phisbo", "touchreset");
 goto stopex;
}

void SavePos(void)
{
//custom procedure poked by sign07.c
 
 //store the x and y in this sprite and the designated invisible poster sprite
 &save_x = sp_x(&current_sprite, -1);
 editor_seq(2, &save_x);
 &save_x = sp_y(&current_sprite, -1);
 editor_seq(5, &save_x);  
 
 goto stopex;
}

void rockposition(void)
{
rockposition:
 //called by external in srock#.c scripts, check rock position.
 sp_custom("rockpos", &current_sprite, 0);
 sp_custom("insidebox", &current_sprite, 0);

 //BOTTOM ROW 
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 235, 272, 449, 299);
 if (&save_x > 0)
 {
  //the rock is on the bottom row
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 340, 272, 347, 299);
  if (&save_x > 0)
  {
   //the rock is in the junction on the bottom row
   goto column2;
  }
  
  //the rock is NOT in the junction on the bottom row
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_dir(1, -1);
  if (&save_x <= 241)
  {
   //the rock is all the way to the left on the bottom row
   if (&save_y == 4)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_x >= 443)
  {
   //the rock is all the way to the right on the bottom row
   if (&save_y == 6)
    sp_custom("rockpos", &current_sprite, 1); 
  }
  &save_y = sp_y(&current_sprite, -1);
  &save_x = sp_dir(1, -1);   
  if (&save_y <= 278)
  {
   if (&save_x == 8)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_y >= 293)
  {
   if (&save_x == 2)
    sp_custom("rockpos", &current_sprite, 1);  
  } 
  
  goto rockpositioncont;
 }

 //Middle ROW 
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 139, 172, 399, 199);
 if (&save_x > 0)
 {
  //the rock is on the middle row
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 340, 172, 347, 199);
  if (&save_x > 0)
  {
   //the rock is in the right junction on the middle row
   goto column2;
  }
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 240, 172, 247, 199);
  if (&save_x > 0)
  {
   //the rock is in the left junction on the middle row
   goto column1;
  }
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 139, 172, 151, 199);
  if (&save_x > 0)
  {
   //the rock is in the LEFT target area on the middle row
   sp_custom("insidebox", &current_sprite, 1);
  }
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 387, 172, 399, 199);
  if (&save_x > 0)
  {
   //the rock is in the RIGHT target area on the middle row
   sp_custom("insidebox", &current_sprite, 1);
  }

  //the rock is NOT in any junctions
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_dir(1, -1);
  if (&save_x <= 145)
  {
   //the rock is all the way to the left on the middle row
   if (&save_y == 4)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_x >= 393)
  {
   //the rock is all the way to the right on the middle row
   if (&save_y == 6)
    sp_custom("rockpos", &current_sprite, 1); 
  }
  &save_y = sp_y(&current_sprite, -1);
  &save_x = sp_dir(1, -1);   
  if (&save_y <= 178)
  {
   if (&save_x == 8)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_y >= 193)
  {
   if (&save_x == 2)
    sp_custom("rockpos", &current_sprite, 1);  
  } 
  
  goto rockpositioncont;
 } 

 //TOP ROW 
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 189, 72, 299, 99);
 if (&save_x > 0)
 {
  //the rock is on the top row
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 240, 72, 247, 99);
  if (&save_x > 0)
  {
   //the rock is in the junction on the top row
   goto column1;
  }
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &save_x = inside_box(&save_x, &save_y, 189, 72, 201, 99);
  if (&save_x > 0)
  {
   //the rock is in the target area on the top row
   sp_custom("insidebox", &current_sprite, 1);
  }

  //the rock is NOT in any junctions or the target area
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_dir(1, -1);
  if (&save_x <= 195)
  {
   //the rock is all the way to the left on the middle row
   if (&save_y == 4)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_x >= 293)
  {
   //the rock is all the way to the right on the middle row
   if (&save_y == 6)
    sp_custom("rockpos", &current_sprite, 1); 
  }
  &save_y = sp_y(&current_sprite, -1);
  &save_x = sp_dir(1, -1);   
  if (&save_y <= 78)
  {
   if (&save_x == 8)
    sp_custom("rockpos", &current_sprite, 1);  
  }
  if (&save_y >= 93)
  {
   if (&save_x == 2)
    sp_custom("rockpos", &current_sprite, 1);  
  } 
  
  goto rockpositioncont;
 } 

column1:
 //LEFT COLUMN (column1)
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 235, 72, 252, 199);
 if (&save_x > 0)
 {
  &save_x = sp_dir(1, -1);
  &save_y = sp_y(&current_sprite, -1);
  if (&save_y >= 193)
  {
   if (&save_x == 2)
    sp_custom("rockpos", &current_sprite, 1);    
  }
  if (&save_y <= 78)
  {
   if (&save_x == 8)
    sp_custom("rockpos", &current_sprite, 1);    
  }
  if (&save_y < 177)
  {
   if (&save_y >= 95)
   {
    &save_y = sp_dir(1, -1);
    &save_x = sp_x(&current_sprite, -1);    
    if (&save_x <= 241)
    {
     if (&save_y == 4)
      sp_custom("rockpos", &current_sprite, 1);  
    }
    if (&save_x >= 246)
    {
     if (&save_y == 6)
      sp_custom("rockpos", &current_sprite, 1);  
    }
   }
  }
  goto rockpositioncont;
 }
 
 //RIGHT COLUMN (column2)
column2:
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 335, 172, 352, 299); 
 if (&save_x > 0)
 {
  &save_x = sp_dir(1, -1);
  &save_y = sp_y(&current_sprite, -1);
  if (&save_y >= 293)
  {
   if (&save_x == 2)
    sp_custom("rockpos", &current_sprite, 1);    
  }
  if (&save_y <= 178)
  {
   if (&save_x == 8)
    sp_custom("rockpos", &current_sprite, 1);    
  }
  if (&save_y < 277)
  {
   if (&save_y >= 195)
   {
    &save_y = sp_dir(1, -1);
    &save_x = sp_x(&current_sprite, -1);    
    if (&save_x <= 341)
    {
     if (&save_y == 4)
      sp_custom("rockpos", &current_sprite, 1);  
    }
    if (&save_x >= 346)
    {
     if (&save_y == 6)
      sp_custom("rockpos", &current_sprite, 1);  
    }
   }
  }
  goto rockpositioncont;
 }
}

void stopex(void)
{
stopex:
 return;
}