void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("sign", &current_sprite, &save_x);
 sp_custom("rock3", &save_x, &current_sprite);

 //use 1 local variable.
 int &val1;
 int &val2;
 int &val3;

 //set rock to previous position it was left in
 &save_x = sp_editor_num(&current_sprite);
 &save_y = editor_frame(&save_x, -1);
 &save_x = editor_seq(&save_x, -1);
 if (&save_x > 0)
 {
  if (&save_y > 0)
  {
   if (&save_x > 900)
   {
    //y position was subtracted to stay in line with editor_frame limit
    //let's revert it!
    &save_x -= 1000;
    &save_y += 200;
   }
   sp_x(&current_sprite, &save_x); 
   sp_y(&current_sprite, &save_y);
   sp_hard(&current_sprite, 0);
   draw_hard_map();
  }
 }

 //make sure custom keys get set correctly - pass the value "1" as &arg1, so we know this is screen entry.
 MoveDetectDuring(1);

 //enable the limit override, so we can set a limitation on where the sprite can move later on
 sp_custom("Enable-Limit", &current_sprite, 1);

 //For now, set all limits to ignore - "9999" will be ignored by default.
 sp_custom("setXmax", &current_sprite, 9999);
 sp_custom("setXmin", &current_sprite, 9999);
 sp_custom("setYmax", &current_sprite, 9999);
 sp_custom("setYmin", &current_sprite, 9999);

 wait(1);

 //disable enforcing pullspace for this sprite - '0' would do nothing, it's the value of an unset key.
   //push and pull will interpret the value '-9999' as 0 in this case.
 sp_custom("enforce_pullspace", &current_sprite, -9999);

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimtop", &current_sprite, 10);
 sp_custom("trimbottom", &current_sprite, 6);
  
 external("phisbo", "main", -21, -35, 23, 9);
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //check if we need to declare &val1 - if this procedure is being called from the main proc we need to
 //This is because called procedures, even within the same script are treated as a separate script and do not share local variables.
 if (&arg1 == 1)
 {
  int &val1;
  int &val2;
  int &val3;
 }

 //store the "sign" sprite's active sprite number in &val1
 &val1 = sp_custom("sign", &current_sprite, -1);

 //This is basically just doing a bunch of x/y bound checks and setting the override move limits
 //So that the sprite cannot be moved outside of the purple/red grid.
 &val1 = sp_custom("sign", &current_sprite, -1);
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 
 //Start with all "ignore" values, so we can just set what we need to based on sprite position.
 sp_custom("setXmax", &current_sprite, 9999);
 sp_custom("setXmin", &current_sprite, 9999);
 sp_custom("setYmax", &current_sprite, 9999);
 sp_custom("setYmin", &current_sprite, 9999);

 //Here we are simply doing checks for each ROW of the grid.
 //Only working with rows, even if a row is just one tile on the grid.
 //So:  Row 1:  rcr
 //     Row 2:   c
 //     Row 3: rrcrcr
 //     Row 4:     c
 //     Row 5:   rrcrr
 
 //Row 1-3 (c's) - column 1
 //Row 3-5 (c's) - column 2
 
 //Row 1
 &val2 = inside_box(&save_x, &save_y, 170, 50, 320, 100);
 if (&val2 == 1)
 {
  sp_custom("setXmax", &current_sprite, 297);
  sp_custom("setXmin", &current_sprite, 193);
  sp_custom("setYmax", &current_sprite, 96);
  sp_custom("setYmin", &current_sprite, 78);
 } 

 //Row 2
 &val2 = inside_box(&save_x, &save_y, 220, 100, 270, 178);
 if (&val2 == 1)
 {
  sp_custom("setXmax", &current_sprite, 247);
  sp_custom("setXmin", &current_sprite, 243);
  sp_custom("setYmax", &current_sprite, 195);
  sp_custom("setYmin", &current_sprite, 78);
 }
 
 //Row 3
 &val2 = inside_box(&save_x, &save_y, 120, 150, 420, 200);
 if (&val2 == 1)
 {
  &val2 = inside_box(&save_x, &save_y, 220, 100, 270, 177);
  if (&val2 == 1)
  {
   sp_custom("setXmax", &current_sprite, 247);
   sp_custom("setXmin", &current_sprite, 243);
   sp_custom("setYmax", &current_sprite, 195);
   sp_custom("setYmin", &current_sprite, 78);
  }
  else
  {
   sp_custom("setXmax", &current_sprite, 397);
   sp_custom("setXmin", &current_sprite, 143);
   sp_custom("setYmax", &current_sprite, 196);
   sp_custom("setYmin", &current_sprite, 178);
  }
 } 
 
 //Row 4
 &val2 = inside_box(&save_x, &save_y, 320, 200, 370, 278);
 if (&val2 == 1)
 {
  sp_custom("setXmax", &current_sprite, 347);
  sp_custom("setXmin", &current_sprite, 343);
  sp_custom("setYmax", &current_sprite, 295);
  sp_custom("setYmin", &current_sprite, 178);
 }

 //Row 5
 &val2 = inside_box(&save_x, &save_y, 220, 250, 470, 300);
 if (&val2 == 1)
 {
  &val2 = inside_box(&save_x, &save_y, 320, 200, 370, 277);
  if (&val2 == 1)
  {
   sp_custom("setXmax", &current_sprite, 347);
   sp_custom("setXmin", &current_sprite, 343);
   sp_custom("setYmax", &current_sprite, 295);
   sp_custom("setYmin", &current_sprite, 178);
  }
  else
  {
   sp_custom("setXmax", &current_sprite, 447);
   sp_custom("setXmin", &current_sprite, 243);
   sp_custom("setYmax", &current_sprite, 296);
   sp_custom("setYmin", &current_sprite, 278);
  }
 } 

 //Column 1
 &val2 = inside_box(&save_x, &save_y, 239, 50, 249, 200);
 if (&val2 == 1)
 {
  sp_custom("setYmax", &current_sprite, 195);
  sp_custom("setYmin", &current_sprite, 78);
 }

 //Column 2
 &val2 = inside_box(&save_x, &save_y, 339, 150, 349, 300);
 if (&val2 == 1)
 {
  sp_custom("setYmax", &current_sprite, 295);
  sp_custom("setYmin", &current_sprite, 178);
 }  

 //check if rock is on a target area
 &val3 = 0;
 &val2 = inside_box(&save_x, &save_y, 120, 150, 157, 200);
 if (&val2 == 1)
 {
  &val3 += 1;
  sp_custom("target1", &val1, 1);
  sp_custom("target1", &current_sprite, 1);
 }
 &val2 = inside_box(&save_x, &save_y, 374, 150, 420, 200);
 if (&val2 == 1)
 {
  &val3 += 1;
  sp_custom("target2", &val1, 1);
  sp_custom("target2", &current_sprite, 1);
 }
 &val2 = inside_box(&save_x, &save_y, 170, 50, 218, 100);
 if (&val2 == 1)
 {
  &val3 += 1;
  sp_custom("target3", &val1, 1); 
  sp_custom("target3", &current_sprite, 1); 
 }

 if (&val3 == 0)
 {
  //this rock isn't in a target area, check if it was just removed from one and if it was, update the custom key to show it's no longer there
  &val2 = sp_custom("target1", &current_sprite, -1);
  if (&val2 == 1)
  {
   sp_custom("target1", &val1, 0);
   sp_custom("target1", &current_sprite, 0);   
  }
  &val2 = sp_custom("target2", &current_sprite, -1);
  if (&val2 == 1)
  {
   sp_custom("target2", &val1, 0);
   sp_custom("target2", &current_sprite, 0);   
  }
  &val2 = sp_custom("target3", &current_sprite, -1);
  if (&val2 == 1)
  {
   sp_custom("target3", &val1, 0);
   sp_custom("target3", &current_sprite, 0);   
  }
 }

 //if this is screen entry, no need to proceed to puzzle check.
 //"sign07.c" main procedure will take care of that.
 if (&arg1 == 1)
  goto stopex;

 //check if puzzle is solved.
 &save_y = sp_custom("target1", &val1, -1);
 if (&save_y > 0)
 {
  &save_y = sp_custom("target2", &val1, -1);
  if (&save_y > 0)
  {  
   &save_y = sp_custom("target3", &val1, -1);
   if (&save_y > 0)
   {
    &save_y = sp_editor_num(&val1);
    &save_y = editor_seq(&save_y, -1);
    if (&save_y <= 0)
    {
     //puzzle is solved
     &save_y = is_script_attached(&val1);
     if (&save_y > 0)
     {
      run_script_by_number(&save_y, "puzzle");
     }
      
     goto stopex;
    }
   }
   else
    goto undo;
  }
  else
   goto undo;
 }  
 else
  goto undo;
  
 goto stopex;
}

void undo(void)
{
undo:
 //puzzle is not solved
 &save_y = sp_editor_num(&val1);
 &save_y = editor_seq(&save_y, -1);
 if (&save_y >= 1)
 {
  &save_y = is_script_attached(&val1);
  if (&save_y > 0)
   run_script_by_number(&save_y, "Undo");    
 }  
}

void MoveDetectAfter(void)
{
 //let's use editor_seq and editor_frame to save the rocks position on the screen!
 //save the x value in editor_seq and y value in editor_frame of current sprite
 //editor_frame has a max value of 255 though, which is less than the max y value on screen.
 //SO, if y > 200, we will subtract 200 from it, and add 1000 to x as a marker so we know it happened.
 //Then on screen re-entry if x is greater than 900, we know we must add 200 to y and subtract 1000 from x.
 &val1 = sp_editor_num(&current_sprite);
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 if (&save_y > 200)
 {
  &save_x += 1000;
  &save_y -= 200;
 }
 
 //now we just store them
 editor_seq(&val1, &save_x);
 editor_frame(&val1, &save_y);
 
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return > 0)
 {
  //Dink is currently moving the sprite  - say a random 'moving a sprite' say line.
  external("dsmove", "main");
 }

 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}