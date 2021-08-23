void main(void)
{
 sp_speed(&current_sprite, 2);
 sp_timing(&current_sprite, 0);	
 sp_nodraw(&current_sprite, 1);
 int &fbsprite;

 //check editor seq to see if puzzle is already completed
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &fbsprite = editor_seq(&save_x, -1);
 
 if (&fbsprite == 1)
 {
  //puzzle has been solved, turn this sprite into the secret staircase
  sp_x(&current_sprite, 150);
  sp_y(&current_sprite, 140);
  sp_pseq(&current_sprite, 89);
  sp_pframe(&current_sprite, 10);
  sp_nodraw(&current_sprite, 0);
  sp_que(&current_sprite, -500); 
  sp_touch_damage(&current_sprite, -1);
  goto stopex; 
 }

 //retrieve the sign sprite, and save this sprite as a custom key inside it.
 &save_x = get_sprite_with_this_brain(20, 0);
 sp_custom("fireball", &save_x, &current_sprite);

 //the fireball hard box is no good for moveability, it's too far away from the actual sprite
 //I'm not gonna edit it in dink.ini and mess it up, so this is attached to a sprite with a hardbox about the size of the fireball
 //and the fireball is created here and locked to it. Can't use it as a shadow, it won't be in the correct place, 
 //I just relock it as it moves using the MoveDetectDuring Proc below, and also update it's depth que.
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x -= 7;
 &save_y += 19;
 &save_x = create_sprite(&save_x, &save_y, 6, 516, 1);
 sp_seq(&save_x, 516);
 sp_frame_delay(&save_x, 30);
 sp_nohit(&save_x, 1);
 &save_y = sp_y(&current_sprite, -1);
 sp_que(&save_x, &save_y);
 sp_custom("fbstore", &current_sprite, &save_x);

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 

 sp_custom("setcollision", &current_sprite, 2);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -64, -25, 9, 3); 
 
 goto stopex;
}


void touch(void)
{
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &fbsprite = editor_seq(&save_x, -1);
 
 if (&fbsprite == 1)
 {
   //warp instead of moveable.
   if (&life < 1) goto stopex;
   freeze(1);
   sp_touch_damage(&current_sprite, 0);
   playsound(39, 16000, 0, 0, 0);
   script_attach(1000);
   fade_down();
   &player_map = 14;
   sp_x(1, 266);
   sp_y(1, 100);
   sp_dir(1, 2);
   load_screen(14);
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
//relock fireball to this sprite
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("fireball", &save_x, -1);
 &fbsprite = sp_custom("fbstore", &save_x, -1);
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 sp_que(&fbsprite, &save_y);
 &save_x -= 7;
 &save_y += 19;
 sp_x(&fbsprite, &save_x);
 sp_y(&fbsprite, &save_y); 

 goto stopex;
}

void MoveDetectAfter(void)
{
 //now check each sprite against the current sprite - explosion first
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_x = sp_custom("rock", &save_x, -1);
 &save_x = sp_x(&save_x, -1);
 &save_y = sp_x(&current_sprite, -1);
 if (&save_x < &save_y) 
  goto stopex;
 
 //now the rock
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_y = sp_custom("explosion", &save_x, -1);
 &save_x = sp_custom("rock", &save_x, -1);
 &save_x = sp_x(&save_x, -1);
 &save_y = sp_x(&save_y, -1);
 if (&save_x > &save_y)
  goto stopex;

 //and the rubble
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_y = sp_custom("rubble", &save_x, -1);
 &save_x = sp_custom("rock", &save_x, -1);
 &save_x = sp_x(&save_x, -1);
 &save_y = sp_x(&save_y, -1);
 if (&save_x > &save_y)
  goto stopex;

 //if it got to this point, all sprites are in correct order.
 //assure touch damage will not reset to -1 and also the object won't be moveable again unless we do the external initiate proc.
 external("phisbo", "terminate"); 
 
 //freeze dink and do cutscene thingy.
 freeze(1);
 playsound(43, 22050,0,0,0); 
 
 wait(1000);
 &save_x = get_sprite_with_this_brain(20, 0);
 &save_y = sp_editor_num(&save_x);
 editor_type(&save_y, 0);
 editor_seq(&save_y, 1);
 int &crap = &save_x;
 
 say_stop("`%I'll be damned.", &crap);
 say_stop("`%This has been out of order for some time.", &crap);
 say_stop("`%And you fixed it!", &crap);
 wait(200);
 say_stop("Well, it's logic really.. I just put it back in order. From left to right", 1);
 say_stop("Fireball >> hits rock >> causes explosion >> and makes rubble", 1);
 wait(200);
 say_stop("`%I see..", &crap);
 
 //make the fireball vanish
 &fbsprite = sp_custom("fbstore", &current_sprite, -1);
 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);  
 sp_active(&fbsprite, 0); 
 wait(300);
 
 //make the explosion vanish
 &save_x = get_sprite_with_this_brain(20, 0);
 &fbsprite = sp_custom("explosion", &save_x, -1);
 &save_x = sp_x(&fbsprite, -1);
 &save_y = sp_y(&fbsprite, -1);
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);  
 &save_x = sp_editor_num(&fbsprite);
 if (&save_x != 0)
 editor_type(&save_x, 1); 
 sp_active(&fbsprite, 0);  
 wait(300);

 //make the rock vanish
 &save_x = get_sprite_with_this_brain(20, 0);
 &fbsprite = sp_custom("rock", &save_x, -1);
 &save_x = sp_x(&fbsprite, -1);
 &save_y = sp_y(&fbsprite, -1);
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 &save_x = sp_editor_num(&fbsprite);
 if (&save_x != 0)
 editor_type(&save_x, 1);  
 sp_active(&fbsprite, 0);
 wait(300);

 //make the rubble sprites vanish
 &save_x = get_sprite_with_this_brain(20, 0);
 &fbsprite = sp_custom("rubble", &save_x, -1);
 &save_x = sp_x(&fbsprite, -1);
 &save_y = sp_y(&fbsprite, -1);
 &save_y -= 20;
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 sp_size(&save_x, 125);
 playsound(24, 22052, 0, 0, 0);  
 
 &save_x = sp_custom("rubble1", &fbsprite, -1);
 &save_y = sp_custom("rubble2", &fbsprite, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0);
 &save_x = sp_custom("rubble3", &fbsprite, -1);
 &save_y = sp_custom("rubble4", &fbsprite, -1);
 sp_active(&save_x, 0);
 sp_active(&save_y, 0); 
 &save_x = sp_custom("rubble5", &fbsprite, -1); 
 sp_active(&save_x, 0);  
 
 &save_x = sp_editor_num(&fbsprite);
 if (&save_x != 0)
 editor_type(&save_x, 1); 
 sp_active(&fbsprite, 0);  
 wait(300);

 &save_x = create_sprite(150, 140, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);  

 //just turn the current sprite into the secret stairs, rather than creating a new sprite
 sp_x(&current_sprite, 150);
 sp_y(&current_sprite, 140);
 sp_pseq(&current_sprite, 89);
 sp_pframe(&current_sprite, 10);
 sp_nodraw(&current_sprite, 0);
 sp_que(&current_sprite, -500);
 
 //change the current sprites editor seq so we can check it later
 &fbsprite = sp_editor_num(&current_sprite);
 editor_type(&fbsprite, 0);
 editor_seq(&fbsprite, 1);
 say_stop("cool..", 1);
 sp_touch_damage(&current_sprite, -1);
 draw_hard_map();
 unfreeze(1);

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
  say("A moveable fireball... cool.", 1);
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