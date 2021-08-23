void main(void)
{
 sp_nodraw(&current_sprite, 1);
 sp_nohit(&current_sprite, 1);
 
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &save_x = editor_seq(&save_x, -1);
 if (&save_x == 1)
 {
  &save_x = create_sprite(504, 276, 0, 89, 10);
  sp_que(&save_x, -500);
  sp_custom("stairs", &current_sprite, &save_x);
  sp_script(&save_x, "stairs3");    
 }
 
 return;
}

void puzzle(void)
{
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 editor_seq(&save_x, 1);

 playsound(43, 22050,0,0,0);         
  
 &save_x = create_sprite(504, 276, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 
 &save_x = create_sprite(504, 276, 0, 89, 10);
 sp_que(&save_x, -500);
 sp_custom("stairs", &current_sprite, &save_x);
 sp_script(&save_x, "stairs3");    
 
 return;
}

void Undo(void)
{
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 editor_seq(&save_x, 0);

 &save_x = create_sprite(504, 276, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 

 &save_x = sp_custom("stairs", &current_sprite, -1);
 sp_active(&save_x, 0);
 draw_hard_map();  
 
 return;
}