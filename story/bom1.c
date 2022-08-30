void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 sp_nodraw(&current_sprite, 1);
 int &val1;

 &save_x = get_sprite_with_this_brain(20, 0);

 //check if this puzzle is already complete
 &save_y = sp_editor_num(&save_x);
 editor_type(&save_y, 0);
 &save_y = editor_seq(&save_y, -1);

 if (&save_y == 1)
 {
  &save_y = sp_editor_num(&current_sprite);
  if (&save_y != 0)
  editor_type(&save_y, 1);
  sp_hard(&current_sprite, 1);
  draw_hard_map();
  sp_active(&current_sprite, 0);
  kill_this_task();
 } 
 
 sp_custom("chair1", &save_x, &current_sprite);

 //the bomb hard box is no good for moveability, not big enough
 //Instead of editing it's hard box, I'm using a chair sprite, which has a good harbox for the bomb
 //then I create the bomb and adjust it's position as it moves, can't use shadow though because I need to alter the x and y slightly
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x += 4;
 &save_y -= 2;
 &save_x = create_sprite(&save_x, &save_y, 6, 420, 1);
 sp_script(&save_x, "explo1");
 sp_nohit(&save_x, 1);
 &save_y = sp_y(&current_sprite, -1);
 sp_que(&save_x, &save_y);
 sp_custom("bomb", &current_sprite, &save_x);

 wait(1);

 //disable enforcing pullspace for this sprite - '0' would do nothing, it's the value of an unset key.
   //push and pull will interpret the value '-9999' as 0 in this case.
 sp_custom("enforce_pullspace", &current_sprite, -9999);

 external("phisbo", "main", -17, -15, 17, 6); 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //check to see if bomb has exploded
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("chair1", &save_x, -1);
 &save_x = sp_custom("bomb", &save_x, -1);
 &save_x = sp_custom("spark", &save_x, -1);
 &save_x = sp_active(&save_x, -1); 
 if (&save_x != 1)
 {
  //bomb is exploding.. stop moving now!
  external("phisbo", "terminate"); 
  &val1 = &current_sprite;
  script_attach(0);
  sp_active(&val1, 0);
  draw_hard_map();
  kill_this_task();
 }

 //relock bomb to this sprite
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("chair1", &save_x, -1);
 &val1 = sp_custom("bomb", &save_x, -1);
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 sp_que(&val1, &save_y);
 &save_x += 4;
 &save_y -= 2;
 sp_x(&val1, &save_x);
 sp_y(&val1, &save_y);   
 
 //relock spark to bomb
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("chair1", &save_x, -1);
 &save_x = sp_custom("bomb", &save_x, -1);
 &val1 = sp_custom("spark", &save_x, -1);
 
  //setting the spark to it's correct position along the wick.
  &save_y = sp_y(&save_x, -1);
  sp_custom("bomby", &val1, &save_y);
  &save_y = sp_custom("smove", &save_x, -1);
  if (&save_y > 9)
   &save_y = 9;
  &save_x = sp_x(&save_x, -1);
  &save_x -= 18;
  &save_x += &save_y;
  sp_x(&val1, &save_x);
  
  &save_x = &save_y;
  &save_y = sp_custom("bomby", &val1, -1);
  &save_y -= 25;
  &save_y += &save_x;
  sp_y(&val1, &save_y);
 
  //set the que of the spark
  &save_y = sp_custom("bomby", &val1, -1); 
  &save_y += 2;
  sp_que(&val1, &save_y); 
 
 goto stopex;
}

void talk(void)
{
 external("phisbo", "moveactive");
 if (&return > 0)
 {
  external("dsmove", "main");
 }
 else
 {
  say("It's gonna blow! I better move it quick!", 1);
 }

 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}