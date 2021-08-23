void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("drag4", &save_x, &current_sprite);

 //check if puzzle is complete
 &save_x = sp_editor_num(&save_x);
 editor_type(&save_x, 0);
 &save_x = editor_seq(&save_x, -1); 
 if (&save_x == 1)
 {
  &save_x = editor_seq(4, -1);
  &save_y = editor_seq(5, -1);
  sp_x(&current_sprite, &save_x); 
  sp_y(&current_sprite, &save_y);
  sp_pframe(&current_sprite, 7);
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  kill_this_task();
 }

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 20);
 sp_custom("trimtop", &current_sprite, 10);
 sp_custom("trimright", &current_sprite, 20);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -43, -18, 43, 18); 
 
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
 goto stopex;
}

void MoveDetectAfter(void)
{
//an example of detecting if the player has moved the object to a certain spot on the screen.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);

 &save_x = inside_box(&save_x, &save_y, 286, 265, 320, 294);
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
  say("A moveable dragon statue.. it looks lifelike!", 1);
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

void SaveAndKill(void)
{
//custom procedure poked in sign06.c using run_script_by_number, to terminate push/pull, save the x and y pos of this sprite and kill off this script.
//could have used external("phisbo", "remoteterminate"); in sign06.c, and passed this sprite as &arg1 to remotely terminate.
//But I have other stuff I wanted to do here, and poking my own custom procedure using run_script_by_number seemed cleaner.

 external("phisbo", "terminate");
 
 //store the x and y in this sprite and the fire ring it belongs to
 &save_x = sp_x(&current_sprite, -1);
 editor_seq(4, &save_x);
 &save_x = sp_y(&current_sprite, -1);
 editor_seq(5, &save_x); 
 
 //make this sprite hard and kill this script so it's no longer moveable.
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