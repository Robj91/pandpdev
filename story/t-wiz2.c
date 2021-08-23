void main(void)
{
 int &val1;
 int &val2;
 
 if (&story >= 2)
  return;

 if (&story < 1)
 {
  freeze(1);
  say_stop("`%N,E,W,S. ORDER IS IMPORTANT!!!", &current_sprite);
  move_stop(1, 4, -50, 1);
 }

tutorial:
 screenlock(1);
 sp_brain(&current_sprite, 20);

  freeze(1);
  draw_hard_map();
  
  &save_x = sp_custom("trock", &current_sprite, -1);
  if (&save_x > 0)
  {
   external("tutorial", "boxkill", &save_x);
   &save_x = sp_custom("trock", &current_sprite, -1);
   sp_active(&save_x, 0);
  }
  
  &save_x = sp_custom("trock2", &current_sprite, -1);
  if (&save_x > 0)
  {
   external("tutorial", "boxkill", &save_x);
   &save_x = sp_custom("trock2", &current_sprite, -1);
   sp_active(&save_x, 0);  
  }

  &save_x = sp_custom("trock3", &current_sprite, -1);
  if (&save_x > 0)
  {
   sp_active(&save_x, 0);
  }   
  
  &save_x = sp_custom("trock4", &current_sprite, -1);
  if (&save_x > 0)
  {
   sp_active(&save_x, 0);
  }     

  &save_x = sp_custom("sparkle", &current_sprite, -1);
  if (&save_x > 0)
  {
   sp_active(&save_x, 0); 
  }

  &save_x = sp_custom("pillar", &current_sprite, -1);
  if (&save_x > 0)
  {
   external("tutorial", "boxkill", &save_x);
   &save_x = sp_custom("pillar", &current_sprite, -1);
   sp_active(&save_x, 0); 
  }
  
  sp_custom("inprogress", &current_sprite, 1);

  wait(500);
  
  &val1 = say_xy("`%Dialogue text timeout disabled - all text must be skipped manually in tutorial screens.", 10, 30);
  &val2 = say_xy("`%(press space bar to continue)", 10, 70);
  external("tutorial", "tuttext", &val1, &val2);   

  &val1 = say_stop("`%Welcome to section 2", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%We will be covering the rest of the skeleton script's main procedure here.", &current_sprite);
  external("tutorial", "txtskip", &val1);
 
  &val1 = say_stop("`%And some of the optional stuff you can do with it", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Everything in this section requires the hardbox values to be passed.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%To the 'main' procedure in 'phisbo', as shown in the previous section.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(156, 230, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(156, 230, 0, 95, 1);
  sp_script(&save_x, "t-rock3"); 
  sp_custom("trock", &current_sprite, &save_x); 

  &val1 = say_stop("`%First, let's look at exactly how hardness works normally", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%When pushing or pulling an object.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Here is a moveable rock, with hardbox values passed to 'main' in 'phisbo'", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%When interacting with other hardness, this rock will act like any other sprite.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%It will stop at hardness based on it's depth dot.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_y = sp_custom("trock", &current_sprite, -1);
  &save_x = create_sprite(156, 230, 6, 37, 1);
  sp_seq(&save_x, 37);
  sp_brain(&save_x, 15);
  sp_brain_parm(&save_x, &save_y);
  sp_que(&save_x, 231);
  sp_custom("sparkle", &current_sprite, &save_x); 

  &val1 = say_stop("`%The depth dot of this rock sprite is located on this blue sparkle I created on the rock.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Whenever this exact point contacts any other hardness, the sprite will stop", &current_sprite);
  external("tutorial", "txtskip", &val1);   

  &save_x = create_sprite(339, 227, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   

  &save_x = create_sprite(339, 227, 0, 80, 27);
  sp_hard(&save_x, 0);
  sp_custom("pillar", &current_sprite, &save_x); 
  draw_hard_map(); 
  
  &val1 = say_stop("`%Here's a hard sprite.", &current_sprite);
  external("tutorial", "txtskip", &val1);   
  
  &save_x = sp_custom("pillar", &current_sprite, -1);
  external("tutorial", "hardbox", -22, -9, 22, 29, &save_x);

  &val1 = say_stop("`%And these sparkles show the boundaries of it's hard box.", &current_sprite);
  external("tutorial", "txtskip", &val1);       
 
  &val1 = say_stop("`%If you move the rock against the pillar, you'll see what I mean", &current_sprite);
  external("tutorial", "txtskip", &val1);  
 
  &val1 = say_stop("`%The sparkle on the rock will stop at the sparkle on the hardbox edges", &current_sprite);
  external("tutorial", "txtskip", &val1);   

  &val1 = say_stop("`%In fact, they will appear almost exactly in line with each other.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Try it if you want. Talk to me when you want to continue.", &current_sprite);
  external("tutorial", "txtskip", &val1); 
    
  unfreeze(1);
}

void phase1(void)
{
phase1:
 freeze(1);
 
  &val1 = say_stop("`%That being demonstrarted, let's get into the first optional tweak", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%The first one is Collision", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Collision changes the way your moveable sprite interacts with hardness", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Instead of stopping based on it's depth dot, it stops based on it's own hardbox", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`%I'll show you what I mean.", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`%Let's have another look at this rock.", &current_sprite);
  external("tutorial", "txtskip", &val1); 
 
  &val1 = sp_custom("trock", &current_sprite, -1);
  &save_x = sp_x(&val1, -1);
  &save_y = sp_y(&val1, -1);
 
  &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
  sp_seq(&save_x, 167);
  &save_x = create_sprite(133, 270, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);  
  
  sp_x(&val1, 133);
  sp_y(&val1, 270);

  &val1 = sp_custom("sparkle", &current_sprite, -1);
  sp_que(&val1, 271);
  
  &val1 = say_stop("`%I will now mark the hardbox of this rock with sparkles as well.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &save_x = sp_custom("trock", &current_sprite, -1);
  external("tutorial", "hardbox", -21, -35, 23, 9, &save_x);

  &save_x = sp_custom("trock", &current_sprite, -1);  
  sp_script(&save_x, "t-rock4");
 
  &val1 = say_stop("`%It now also has Collision enabled.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%If you're using Dink Smallwood HD, this will lag a lot when you move it.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%This will be explained shortly.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Try moving it into the other sprite's hardbox again and see how it behaves", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Talk to me when you want to continue", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  sp_custom("inprogress", &current_sprite, 2);

 unfreeze(1);
}

void phase2(void)
{
phase2:
 freeze(1);
 
 &val1 = sp_custom("trock", &current_sprite, -1);
 &save_x = sp_x(&val1, -1);
 &save_y = sp_y(&val1, -1);

 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 &save_x = create_sprite(143, 270, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 
 sp_x(&val1, 143);
 sp_y(&val1, 270);
 &save_x = is_script_attached(&val1);
 if (&save_x > 0)
 {
  run_script_by_number(&save_x, "MoveDetectDuring");
 }

 &val1 = say_stop("`%As you can see, collision is now based on the sprite's hardbox", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Rather than it's depth dot.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%To enable this is quite simple.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%In the main procedure of your sprite's script, you'll find this line.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = create_sprite(250, 165, 0, 35, 7); 
 &save_y = create_sprite(250, 165, 15, 36, 7);
 brain(&save_y, 15);
 sp_brain_parm(&save_y, &save_x);
 sp_que(&save_x, 501);
 sp_que(&save_y, 500);
 sp_custom("txt1", &current_sprite, &save_y);
 
 &val1 = say_stop("`%By default, it is set to 0. This means Collision is disabled.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%There are 2 other settings, and there are a few things to note about each one.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 8);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 8);

 &val1 = say_stop("`%Setting Collision to 1 will enable Collision for FreeDink versions ONLY.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%All other versions will act as if it is disabled.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%The addon'Version Checker' is REQUIRED when setting Collision to 1.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Otherwise it will be ignored in ALL versions - basically, it will be as if it's set to 0", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 9);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 9);
 
 &val1 = say_stop("`%Setting Collision to 2, will enable Collision in FreeDink and 1.08", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 40);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 40);
 
 &val1 = say_stop("`%Setting Collision to 3, will enable Collision in ALL Dink Smallwood versions", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%This is not recommended, because Dink Smallwood HD lags with collision turned on.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%The collision system performs best in FreeDink, is tolerable in 1.08, and is terrible in Dink HD.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%My recommendation is to set collision to 2. And install Version Checker in your dmod.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Now let's move on.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = sp_custom("txt1", &current_sprite, -1);
 &save_y = sp_brain_parm(&save_x, -1);
 sp_active(&save_y, 0);
 sp_active(&save_x, 0);
 
 &val1 = say_stop("`%There is one final tweak in the main procedure of the script that we need to cover.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%And it allows you to adjust your collision even more, and customise it for each sprite", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Sometimes you might want to tweak the collision a little bit", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%So that the sprite can move a little further than it's hardbox boundary", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%When it touches other hardness.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = create_sprite(339, 209, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);   
 
 &save_x = create_sprite(339, 209, 0, 95, 1);
 sp_custom("trock2", &current_sprite, &save_x); 
 draw_hard_map(); 
 external("tutorial", "hardbox", -21, -35, 23, 9, &save_x);
 &save_x = sp_custom("trock2", &current_sprite, -1); 
 sp_script(&save_x, "t-rock5");

 &val1 = say_stop("`%Here's another rock sprite, stopped at a hard sprite, where it's hardbox has collided.", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &val1 = say_stop("`%Let's say you wanted to tweak the collison so it can move a little bit further", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%So instead, it could be moved to the following position before it stops", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = sp_custom("trock2", &current_sprite, -1);
 sp_y(&save_x, 219);
 &save_x = is_script_attached(&save_x);
 if (&save_x > 0)
 {
  run_script_by_number(&save_x, "MoveDetectDuring");
 }


 &val1 = say_stop("`%Well, you can 'trim' the hardbox of a sprite for Collision calculation only", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%So the actual hardbox remains the same, but push and pull acknowledges the trim", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%And calculates collision accordingly.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Inside your scripts Main procedure you will find the following lines.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = create_sprite(261, 321, 0, 35, 10); 
 &save_y = create_sprite(261, 321, 15, 36, 10);
 brain(&save_y, 15);
 sp_brain_parm(&save_y, &save_x);
 sp_que(&save_x, 501);
 sp_que(&save_y, 500);
 sp_custom("txt1", &current_sprite, &save_y); 
 
 &val1 = say_stop("`%Each line refers to a hardbox edge.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%So to allow the rock to move closer to the pillar, where it currently is.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%We would adjust 'trimbottom'", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%In it's current position, it has moved 10 pixels past it's bottom hardbox edge.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%So in other words, we want to trim the bottom hardbox edge by 10", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Like so..", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 11);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 11);

 &val1 = say_stop("`%Remember, it only affects it for collision calculation only", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%So it will ONLY come into play when Dink is moving the sprite with the trim applied", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Other sprites will still stop at it's normal hardbox as normal.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%So you don't have to worry about this interefering with or messing anything else up.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%But to allow you to test it, and really see the difference", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 12);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 12);

 &val1 = say_stop("`%I will trim all hardbox edges of this rock by 10, as displayed.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &save_x = sp_custom("txt1", &current_sprite, -1);
 &save_y = sp_brain_parm(&save_x, -1);
 sp_active(&save_y, 0);
 sp_active(&save_x, 0);

 &save_x = create_sprite(142, 220, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 
 &save_x = sp_custom("trock2", &current_sprite, -1);
 sp_x(&save_x, 142);
 sp_y(&save_x, 220);
 &save_x = is_script_attached(&save_x);
 if (&save_x > 0)
 {
  run_script_by_number(&save_x, "MoveDetectDuring");
 }

 &val1 = say_stop("`%So now both rocks have Collision enabled in ALL Dink versions.", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%And the top one has all hardbox edges trimmed by 10 pixels for collision calculation.", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%If you move it into the hard sprite you will see", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%The sparkles that define it's physical hardbox will overlap those of the hard sprite by 10 pixels.", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%And here's another rock with Collision activated for FreeDink only. [collison set to 1].", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = create_sprite(259, 105, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);   
 
 &save_x = create_sprite(259, 105, 0, 95, 1);
 sp_script(&save_x, "t-rock6");
 sp_custom("trock3", &current_sprite, &save_x); 
 draw_hard_map(); 

 &val1 = say_stop("`%And another one with collision enabled for Dink 1.08 AND FreeDink. [collison set to 2].", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = create_sprite(325, 105, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);   
 
 &save_x = create_sprite(325, 105, 0, 95, 1);
 sp_script(&save_x, "t-rock15");
 sp_custom("trock4", &current_sprite, &save_x); 
 draw_hard_map(); 

 &val1 = say_stop("`%And one more with collision DISABLED...", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = create_sprite(398, 105, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);   
 
 &save_x = create_sprite(398, 105, 0, 95, 1);
 sp_script(&save_x, "t-rock7");
 sp_custom("trock5", &current_sprite, &save_x); 
 draw_hard_map(); 

 &val1 = say_stop("`%In case you want to test these in other versions later and compare the difference.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%That concludes this section. Feel free to mess around with the sprites.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%To see how they behave when moved into the hard sprite", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%When you're ready, head back to the entrance screen and head west", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%If you want to view this section again, talk to me at anytime.", &current_sprite);
 external("tutorial", "txtskip", &val1);
  
 sp_custom("inprogress", &current_sprite, 0); 
 if (&story < 2)
  &story = 2;
  
 playsound(43, 22050,0,0,0);   
 screenlock(0);
 unfreeze(1); 
}

void talk(void)
{
 &save_x = sp_custom("inprogress", &current_sprite, -1);
 if (&save_x > 0)
 {
  choice_start();
  "Ready to continue"
  "nevermind"
  choice_end();
  
   if (&result == 1)
   {
    &save_x = sp_custom("inprogress", &current_sprite, -1);
    if (&save_x == 1)
     goto phase1;
    
    if (&save_x == 2)
     goto phase2;
   }
  return;
 }

 if (&story >= 2)
 {
  freeze(1);
  choice_start();
  "View Tutorial Section 2 again"
  "leave"
  choice_end();  
  
   if (&result == 1)
   {
    goto tutorial;
   }
  
  unfreeze(1);
 } 
}