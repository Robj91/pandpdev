//Moveable heart sprite that looks like a collectible but isn't

void main(void)
{
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	

 wait(1);

 //needed for talk procedure. Can't use global juggle var, causes a bug. If no talk procedure, can delete.
 int &val1; 
 
 sp_custom("setcollision", &current_sprite, 1);

 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 external("phisbo", "main", -25, -11, 24, 11); 
 
 goto stopex;
}


void touch(void)
{
 //make this heart talk and let dink know it's not collectible the first time he touches it.
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &save_y = editor_seq(&save_x, -1);
 if (&save_y <= 0)
 {
  sp_touch_damage(&current_sprite, 0);
  freeze(1);
  say_stop("`1HA! FOOLED YA!", &current_sprite);
  wait(200);
  say_stop("What the..", 1);
  wait(200);
  say_Stop("`1I'm not collectable.. just moveable.", &current_sprite);
  wait(200);
  say_stop("Right..", 1);
  &save_x = sp_editor_num(&current_sprite);
  editor_seq(&save_x, 1); 
  unfreeze(1);
  sp_touch_damage(&current_sprite, -1);
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
 }

 external("phisbo", "touchreset");
 goto stopex;
}

void hit(void)
{
 external("phisbo", "hit");

 say("I'm a heartbreaker!", 1);

 external("phisbo", "touchreset");
 goto stopex;
}

void stopex(void)
{
stopex:
 return;
}