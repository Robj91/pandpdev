//fragile rock 1 on screen 47

void main(void)
{
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
 
 sp_custom("rock1", &save_x, &current_sprite);
 sp_custom("confirmsprite", &current_sprite, 1);
}

void hit(void)
{
 &save_x = compare_sprite_script(&missle_source, "dam-bomn");
 if (&save_x == 1)
 {
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_y(&current_sprite, -1);
  &val1 = create_sprite(&save_x, &save_y, 0, 97, 2);
  sp_que(&val1, -500);
  sp_nohit(&val1, 1);
  sp_hard(&current_sprite, 1);
  draw_hard_map();

  &val1 = &current_sprite;
  script_attach(0);
  sp_active(&val1, 0);
  &save_x = get_sprite_with_this_brain(20, 0);
  &save_y = sp_custom("rock2", &save_x, -1);
  &val1 = sp_custom("confirmsprite", &save_y, -1);
  if (&val1 != 1)
  {
   &save_y = sp_custom("rock3", &save_x, -1);
   &val1 = sp_custom("confirmsprite", &save_y, -1);
   if (&val1 != 1)
   {
    &save_y = sp_editor_num(&save_x);
    editor_type(&save_y, 0);
    editor_seq(&save_y, 1);   
   
    playsound(43, 22050,0,0,0);   

    wait(150);

    &save_x = create_sprite(202, 293, 7, 167, 1);
    sp_seq(&save_x, 167);
    playsound(24, 22052, 0, 0, 0); 

    &save_x = create_sprite(202, 293, 0, 89, 10);
    sp_script(&save_x, "stairs");
    kill_this_task(); 
   }
  }
  kill_this_task();
 }
}

void talk(void)
{
 say("This rock looks fragile. An explosive would get rid of it", 1);
}