//script attached to a bomb shadowing an invisible pushable sprite (so it looks like the bomb is the pushable sprite :=), causes countdown and explosion

void main(void)
{
 wait(0);
 
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x -= 18;
 &save_y -= 25;
 &save_x = create_sprite(&save_x, &save_y, 6, 166, 1);
 sp_seq(&save_x, 166);
 sp_size(&save_x, 125);
 &save_y = sp_y(&current_sprite, -1);
 &save_y += 2;
 sp_que(&save_x, &save_y);
 sp_custom("spark", &current_sprite, &save_x);
 sp_custom("smove", &current_sprite, 0);
 sp_custom("timerset", &current_sprite, 5);

 //calling sprite
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("chair2", &save_x, -1); 
 sp_custom("callingsprite", &current_sprite, &save_x);
 
 int &timer = sp_custom("timerset", &current_sprite, -1);
 int &txt;
timerloop:
 playsound(50, 25052, 0, &current_sprite, 0); 
 //set x and y pos of text
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x -= 320;
 &save_y -= 30;
 
 //create text
 &txt = say_xy("`%&timer", &save_x, &save_y);
 sp_kill(&txt, 0);
 sp_speed(&txt, 1);
 sp_custom("txt", &current_sprite, &txt);
 
 //move text up and make it die after 1 second
 move(&txt, 8, 0, 1);
 wait(1000);
 sp_active(&txt, 0);
 
 //move spark unless it's already at the end of the bombs wick
 &save_x = sp_custom("smove", &current_sprite, -1);
 &save_y = sp_custom("timerset", &current_sprite, -1);
 &save_x += 1;
 if (&save_x < 9)
 {
  sp_custom("smove", &current_sprite, &save_x);
  &txt = sp_custom("spark", &current_sprite, -1);
  &save_x = sp_x(&txt, -1);
  &save_y = sp_y(&txt, -1);
  &save_x += 1;
  &save_y += 1;
  sp_x(&txt, &save_x);
  sp_y(&txt, &save_y); 
  &save_x = sp_size(&txt, -1);
  if (&save_x < 150)
  {
   &save_x += 5;
   sp_size(&txt, &save_x);
  }
 }
 else
 {
  sp_custom("smove", &current_sprite, &save_x);
 }
 
 //increment timer
 &timer -= 1;
 
 if (&timer < 4)
 {
  &save_x = sp_pframe(&current_sprite, -1);
  if (&save_x < 4)
  {
   &save_x += 1;
   sp_pframe(&current_sprite, &save_x);
  }
 }
 
 if (&timer < 0)
 {
  &txt = sp_custom("spark", &current_sprite, -1);
  sp_active(&txt, 0);
 
  &txt = sp_custom("callingsprite", &current_sprite, -1); 
  &save_x = sp_active(&txt, -1);
  if (&save_x == 1)
  {
   &save_x = is_script_attached(&txt);
   if (&save_x > 0)
   {
    run_script_by_number(&save_x, "MoveDetectDuring");
   }
  }
  
  &txt = &current_sprite;
  script_attach(0);
  sp_script(&txt, "dam-bomn");  
  
  sp_range(&txt, 30);
  sp_brain(&txt, 17);
  playsound(6, 22050, 0,0,0);
  sp_seq(&txt, 161);
  sp_strength(&txt, 8);
  kill_this_task();
 }
 
 goto timerloop;
}