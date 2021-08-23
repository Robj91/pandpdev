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
 
 sp_custom("chair3", &save_x, &current_sprite);

 //the bomb hard box is no good for moveability, not big enough
 //Instead fo editing it's hard box, I'm using a chair sprite, which has a good harbox for the bomb
 //then I create the bomb and lock it to it, can't use shadow though because I need to alter the x and y slightly
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x += 4;
 &save_y -= 2;
 &save_x = create_sprite(&save_x, &save_y, 6, 420, 1);
 sp_script(&save_x, "explo3");
 sp_nohit(&save_x, 1);
 &save_y = sp_y(&current_sprite, -1);
 sp_que(&save_x, &save_y);
 sp_custom("bomb", &current_sprite, &save_x); 

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 0);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -17, -15, 17, 6);  
 
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
 //check to see if bomb has exploded
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("chair3", &save_x, -1);
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
 &save_x = sp_custom("chair3", &save_x, -1);
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
 &save_x = sp_custom("chair3", &save_x, -1);
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

void MoveDetectAfter(void)
{
 goto stopex;
}

void pull(void)
{
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
  say("It's gonna blow! I better move it quick!", 1);
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

void stopex(void)
{
stopex:
 return;
}