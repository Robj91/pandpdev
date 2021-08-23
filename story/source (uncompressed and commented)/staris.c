//moveable stairs that lead to cavern of the great unknown.

void main(void)
{
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);	

 //And if this object is on the 'X' on screen entry, make it a warp sprite.
 //can use a simple global check, but rather than wasting a global I take advantage of the editor_seq value of the sign and bone sprite to store the new x and y.
 //this is just so the sign can change it's say lines based on this info, otherwise could just use the editor seq and frame of this sprite. 
 //you could use this same idea to save the position of a sprite moved around on a screen, rather than have it reset each time
 
 //retrieve the bones
 int &spritevar;
 &save_x = get_sprite_with_this_brain(20, 0);
 
 &spritevar = sp_editor_num(&save_x);
 editor_type(&spritevar, 0);
 int &spriteseq = editor_seq(&spritevar, -1);
 
 if (&spriteseq > 0)
 {
  sp_x(&current_sprite, &spriteseq);
  
  //the y is stored in the signs editor_seq so let's retrieve that
  &save_x = get_sprite_with_this_brain(21, 0);
  
  &spritevar = sp_editor_num(&save_x);
  editor_type(&spritevar, 0);
  &spriteseq = editor_seq(&spritevar, -1);  
  sp_y(&current_sprite, &spriteseq);
  
  sp_touch_damage(&current_sprite, -1);
  
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  
  return;
 }
 
 wait(1);
 
 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 
 
 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -33, -23, 13, 3);
 
 goto stopex;
}


void touch(void)
{
 //Check if the stairs are in correct position for warp
 &save_x = get_sprite_with_this_brain(20, 0);
 
 &spritevar = sp_editor_num(&save_x);
 editor_type(&spritevar, 0);
 &spriteseq = editor_seq(&spritevar, -1);
 
 if (&spriteseq > 0)
 {
  //they are in correct position, let's make them warp instead of moveable.
   if (&life < 1) return;
   freeze(1);
   sp_touch_damage(&current_sprite, 0);
   playsound(39, 16000, 0, 0, 0);
   script_attach(1000);
   fade_down();
   &player_map = 16;
   sp_x(1, 326);
   sp_y(1, 113);
   sp_dir(1, 2);
   load_screen(704);
   draw_screen();
   fade_up();
   kill_this_task();  
  }

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
 //an example of detecting if the player has moved the object to a certain spot on the screen.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 531, 79, 555, 99);
 if (&save_x == 1)
 { 
  //it's reached it's destination, stop the push/pull in it's tracks and assure touch damage does not reset to -1.
  external("phisbo", "terminate");
  
  freeze(1);
  //lets store the x and y of this sprite using editor seq of the fence and sign sprite
  //editor_frame isn't much of an option since it only goes up to 255
  
  //store the x in the bones sprite
  &spriteseq = sp_x(&current_sprite, -1);
  editor_seq(&spritevar, &spriteseq);
  
  //now retrieve the sign sprite and store the y
  &save_x = get_sprite_with_this_brain(21, 0);
  
  &spritevar = sp_editor_num(&save_x);
  editor_type(&spritevar, 0);
  &spriteseq = sp_y(&current_sprite, -1);
  editor_seq(&spritevar, &spriteseq);  
  
  //play the secret sound!
  playsound(43, 22050,0,0,0);
  //make this sprite hard.
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  
  //reset the touch damage to -1, since we will want this sprite to warp now.
  sp_touch_damage(&current_sprite, -1);
  
  unfreeze(1);
 }

 goto stopex;
}

void MoveDetectAfter(void)
{
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
  say("Moveable stairs? .. Strange.", 1);
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