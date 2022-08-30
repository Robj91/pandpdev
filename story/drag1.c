void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("drag1", &save_x, &current_sprite); 
 
 //check if puzzle is complete
 &save_x = sp_editor_num(&save_x);
 editor_type(&save_x, 0);
 &save_x = editor_seq(&save_x, -1); 
 if (&save_x == 1)
 {
  &save_x = editor_seq(2, -1);
  &save_y = editor_seq(3, -1);
  sp_x(&current_sprite, &save_x); 
  sp_y(&current_sprite, &save_y);
  sp_pframe(&current_sprite, 7);
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  kill_this_task();
 }

 wait(1);

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 20);
  
 external("phisbo", "main", -38, -18, 38, 18); 
 
 goto stopex;
}


void touch(void)
{
 external("phisbo", "touch"); 
 
 goto stopex;
}

void MoveDetectDuring(void)
{
 //an example of detecting if the player has moved the object to a certain spot on the screen.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 435, 180, 477, 214);
 if (&save_x == 1)
 {   
  sp_custom("insidebox", &current_sprite, 1);
  
  //run the procedure inside our brain 20 sign sprite that cheks if puzzle is solved
  &save_x = get_sprite_with_this_brain(20, 0);
  &save_y = is_script_attached(&save_x);
  if (&save_y > 0)
  {
   run_script_by_number(&save_y, "puzzle");
  }
 }
 else
 {
  sp_custom("insidebox", &current_sprite, 0);
 }

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
  say("A moveable dragon statue.. it looks lifelike!", 1);
 }

 goto stopex;
}

void SaveAndKill(void)
{
//custom procedure poked by sign06.c
 external("phisbo", "terminate");
 
 //store the x and y in this sprite and the fire ring it belongs to
 &save_x = sp_x(&current_sprite, -1);
 editor_seq(2, &save_x);
 &save_x = sp_y(&current_sprite, -1);
 editor_seq(3, &save_x);
  
 sp_hard(&current_sprite, 0);
 draw_hard_map();
  
 kill_this_task(); 
 
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}