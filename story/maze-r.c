//Same as sprite.c, but attached to the rock on the maze screen - demonstrates sort of a "rock push onto button" type system.
//see sprite.c for a fully commented script for everything else.


void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 
 //If this object is on the 'X' on screen entry, make it a normal hard sprite that can't be moved, by simply killing off this script
 //can use a simple global check, but rather than wasting a global I take advantage of the editor_seq value of the sign and the fence sprites to store the new x and y.
 //this is just so the sign can change it's say lines based on this info, otherwise could just use the editor seq and frame of this sprite. 
 //you could use this same idea to save the position of a sprite moved around on a screen, rather than have it reset each time
 
 //retrieve the sign
 int &spritevar;
 &save_x = get_sprite_with_this_brain(20, 0);
 
 &spritevar = sp_editor_num(&save_x);
 editor_type(&spritevar, 0);
 int &spriteseq = editor_seq(&spritevar, -1);
 
 if (&spriteseq > 0)
 {
  sp_x(&current_sprite, &spriteseq);
  
  //the y is stored in the fences editor_seq so let's retrieve that
  &save_x = get_sprite_with_this_brain(21, 0);
  
  &spritevar = sp_editor_num(&save_x);
  editor_type(&spritevar, 0);
  &spriteseq = editor_seq(&spritevar, -1);  
  sp_y(&current_sprite, &spriteseq);
  
  //kill the fence and invisible hard sprite
  &spritevar = get_sprite_with_this_brain(21, 0);
  &spriteseq = get_sprite_with_this_brain(22, 0);
  sp_active(&spritevar, 0);
  sp_active(&spriteseq, 0);   
  
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  kill_this_task();
 }

 wait(1);

 //disable enforcing pullspace for this sprite - '0' would do nothing, it's the value of an unset key.
   //push and pull will interpret the value '-9999' as 0 in this case.
 sp_custom("enforce_pullspace", &current_sprite, -9999);

 //set collision on this sprite
 sp_custom("setcollision", &current_sprite, 1);

 //make trim the hardbox to make our own fake "push/pull" collision box.
 sp_custom("trimleft", &current_sprite, 10);
 sp_custom("trimtop", &current_sprite, 20);
 sp_custom("trimright", &current_sprite, 10);
 sp_custom("trimbottom", &current_sprite, 6);

 external("phisbo", "main", -21, -35, 23, 9);
 
 goto stopex;
}

void touch(void)
{
 external("phisbo", "touch"); 
 
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

void MoveDetectDuring(void)
{
 //an example of detecting if the player has moved the object to a certain spot on the screen.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = inside_box(&save_x, &save_y, 145, 329, 177, 351);
 if (&save_x == 1)
 { 
  //push/pull would have already ended since we are detecting after it's moved but we can run this to assure touch damage will not reset to -1
  external("phisbo", "terminate");
  //rock is on the 'X', it's in position!
  
  freeze(1);
  //lets store the x and y of this sprite using editor seq of the fence and sign sprite
  //editor_frame isn't much of an option since it only goes up to 255
  
  //store the x
  &spriteseq = sp_x(&current_sprite, -1);
  editor_seq(&spritevar, &spriteseq);
  
  //now retrieve the fence sprite and store the y
  &save_x = get_sprite_with_this_brain(21, 0);
  
  &spritevar = sp_editor_num(&save_x);
  editor_type(&spritevar, 0);
  &spriteseq = sp_y(&current_sprite, -1);
  editor_seq(&spritevar, &spriteseq);  
  
  //unmask the secret! (play secret sound, and retrieve the fence, and the invisible hard sprite (brain 21 and 22), and delete them!
  playsound(43, 22050,0,0,0);
  &spritevar = get_sprite_with_this_brain(21, 0);
  &spriteseq = get_sprite_with_this_brain(22, 0);
  sp_active(&spritevar, 0);
  sp_active(&spriteseq, 0); 
  
  //make this sprite hard and kill off this script so this sprite is no longer moveable.
  sp_hard(&current_sprite, 0);
  draw_hard_map();
  unfreeze(1);
  kill_this_task();
 }

 goto stopex;
}


//STOPEX PROCEDURE - external bugfix. Please make sure this remains the LAST procedure in this script.
//doesn't even need to be a procedure since it's the script is sent here by goto. but whatever, this looks cleaner.
void stopex(void)
{
stopex:
 return;
}