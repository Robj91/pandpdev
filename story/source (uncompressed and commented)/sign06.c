void main(void)
{
 sp_nodraw(&current_sprite, 1);
 sp_nohit(&current_sprite, 1);
 
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &save_x = editor_seq(&save_x, -1);
 if (&save_x == 1)
 {
  &save_x = sp(1);
  sp_pseq(&save_x, 89);
  sp_pframe(&save_x, 10);
  sp_script(&save_x, "stairs2");
  draw_hard_map();
  return;
 }

 wait(1000);
 say("Hmmm... what's going on here..", 1);
}

void puzzle(void)
{
 &save_x = sp_custom("drag1", &current_sprite, -1);
 &save_x = sp_custom("insidebox", &save_x, -1);
 if (&save_x == 1)
 {
  &save_x = sp_custom("drag2", &current_sprite, -1);
  &save_x = sp_custom("insidebox", &save_x, -1);  
  if (&save_x == 1)
  {  
   &save_x = sp_custom("drag3", &current_sprite, -1);
   &save_x = sp_custom("insidebox", &save_x, -1);  
   if (&save_x == 1)
   { 
    &save_x = sp_custom("drag4", &current_sprite, -1);
    &save_x = sp_custom("insidebox", &save_x, -1);  
    if (&save_x == 1)
    { 
     &save_x = sp_custom("drag1", &current_sprite, -1);  
     &save_x = is_script_attached(&save_x);
     if (&save_x > 0)
      run_script_by_number(&save_x, "SaveAndKill");

     &save_x = sp_custom("drag2", &current_sprite, -1);  
     &save_x = is_script_attached(&save_x);
     if (&save_x > 0)
      run_script_by_number(&save_x, "SaveAndKill");

     &save_x = sp_custom("drag3", &current_sprite, -1);  
     &save_x = is_script_attached(&save_x);
     if (&save_x > 0)
      run_script_by_number(&save_x, "SaveAndKill");
      
     &save_x = sp_custom("drag4", &current_sprite, -1);  
     &save_x = is_script_attached(&save_x);
     if (&save_x > 0)
      run_script_by_number(&save_x, "SaveAndKill");
      
     //play the roar sound!
     playsound(28, 16000, 0, 0, 0); 
     
     //make each dragon play through sequence
     &save_x = sp_custom("drag1", &current_sprite, -1);
     sp_frame_delay(&save_x, 150);
     sp_brain(&save_x, 6); 
     sp_frame(&save_x, 1);
     &save_x = sp_custom("drag2", &current_sprite, -1);
     sp_frame_delay(&save_x, 150); 
     sp_brain(&save_x, 6);
     sp_frame(&save_x, 1);
     &save_x = sp_custom("drag3", &current_sprite, -1);
     sp_frame_delay(&save_x, 150); 
     sp_brain(&save_x, 6);
     sp_frame(&save_x, 1);
     &save_x = sp_custom("drag4", &current_sprite, -1);
     sp_frame_delay(&save_x, 150); 
     sp_brain(&save_x, 6);
     sp_frame(&save_x, 1);
     wait(300);
     
     //make each dragon static again
     &save_x = sp_custom("drag1", &current_sprite, -1);
     sp_brain(&save_x, 0);  
     &save_x = sp_custom("drag2", &current_sprite, -1);
     sp_brain(&save_x, 0);  
     &save_x = sp_custom("drag3", &current_sprite, -1);
     sp_brain(&save_x, 0);  
     &save_x = sp_custom("drag4", &current_sprite, -1);
     sp_brain(&save_x, 0); 
     
     //create explosion
     &save_x = create_sprite(295, 181, 7, 70, 1);
     sp_size(&save_x, 150);
     sp_seq(&save_x, 70);
     sp_que(&save_x, 201);
     playsound(18, 8000,0,0,0);
     wait(200);
     
     //burn tree    
     &save_x = sp(1);
     &save_x = is_script_attached(&save_x);
     if (&save_x > 0)
     {
      run_script_by_number(&save_x, "die");
     } 

     &save_x = sp_editor_num(&current_sprite);
     editor_type(&save_x, 0);
     editor_seq(&save_x, 1);
     kill_this_task();
    }
   }
  }
 } 
}