void main(void)
{
 int &val1;
 int &val2;
 
 if (&story >= 1)
  return;

tutorial:
 screenlock(1);
 sp_brain(&current_sprite, 20);
 
  freeze(1);
  
  &save_x = sp_custom("trock", &current_sprite, -1);
  if (&save_x > 0)
   sp_active(&save_x, 0);
  
  &save_x = sp_custom("bones", &current_sprite, -1);
  if (&save_x > 0)
   sp_active(&save_x, 0);  

  &save_x = sp_custom("heart", &current_sprite, -1);
  if (&save_x > 0)
   sp_active(&save_x, 0);  

  sp_custom("inprogress", &current_sprite, 1); 

  wait(500);

  &val1 = say_xy("`%Dialogue text timeout disabled - all text must be skipped manually in tutorial screens.", 10, 30);
  &val2 = say_xy("`%(press space bar to continue)", 10, 70);
  external("tutorial", "tuttext", &val1, &val2);  
 
  &val1 = say_stop("`%It's me, PHISBO the wizard!", &current_sprite);
  external("tutorial", "txtskip", &val1);
 
  &val1 = say_stop("`%Let me show you a few things on how to use this thing once you've implemented it.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%Implementation is easy, you can read the readme file, and watch the video link included", &current_sprite);
  external("tutorial", "txtskip", &val1);  
  
  &val1 = say_stop("`%Let's get started - This system uses A LOT of scripts.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%However, you need not worry about most of them", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%The only script you will probably need to touch is 'sprite.c'", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%'sprite.c' will be your skeleton script for moveable objects.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%You can make copies of this, rename it to suit your sprite and attach it.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  wait(500);
  
  &save_x = create_sprite(318, 232, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(318, 220, 0, 95, 1);
  sp_script(&save_x, "t-rock"); 
  sp_custom("trock", &current_sprite, &save_x);  
  
  wait(200);
  
  &val1 = say_stop("`%Here is a rock with a copy of the skeleton script attached.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%As it is, this sprite will move around just fine with no changes", &current_sprite);
  external("tutorial", "txtskip", &val1);  
  
  &save_x = create_sprite(492, 221, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(492, 221, 0, 90, 3);
  sp_que(&save_x, -500);
  sp_custom("bones", &current_sprite, &save_x);
    
  &val1 = say_stop("`%Try pushing the sprite as it is now. Move it to this X", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  unfreeze(1);
}

void phase1(void)
{
 freeze(1);
 &val1 = say_stop("`%It moves ok just with the skeleton script, as you just saw", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &val1 = say_stop("`%But we can make it run a bit smoother in 1.08 and DinkHD with a simple addition.", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &val1 = say_stop("`%And it will also make push activate slightly quicker, when walking against the sprite.", &current_sprite);
 external("tutorial", "txtskip", &val1);   
 
 &val1 = say_stop("`%In the Main procedure of the skeleton script - 'sprite.c', you will see this line.", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &save_x = create_sprite(250, 150, 0, 35, 1); 
 &save_y = create_sprite(250, 150, 15, 36, 1);
 brain(&save_y, 15);
 sp_brain_parm(&save_y, &save_x);
 sp_que(&save_x, 501);
 sp_que(&save_y, 500);
 sp_custom("txt1", &current_sprite, &save_y);
 
 &val1 = say_stop("`%To make it run smoother, we just need to pass the values of the sprite's hardbox", &current_sprite); 
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%To the main procedure in phisbo.", &current_sprite); 
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%We can just copy these values from dink.ini, and paste them into the external line.", &current_sprite); 
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Let's do an example with this rock.", &current_sprite); 
 external("tutorial", "txtskip", &val1); 
 
 &val1 = say_stop("`%First let's have a look at the hardbox values in dink.ini", &current_sprite); 
 external("tutorial", "txtskip", &val1); 
 
 &val1 = say_stop("`%The sequence of this rock is 95, and the frame is 1.", &current_sprite);
 external("tutorial", "txtskip", &val1); 
 
 &val1 = say_stop("`%So if we open up dink.ini and search for '95 1', and find the set_sprtie_info line..", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = create_sprite(250, 180, 0, 35, 2); 
 &save_y = create_sprite(250, 180, 15, 36, 2);
 brain(&save_y, 15);
 sp_brain_parm(&save_y, &save_x);
 sp_que(&save_x, 501);
 sp_que(&save_y, 500);
 sp_custom("txt2", &current_sprite, &save_y);

 &val1 = say_stop("`%We'll see this.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%This is the set_sprite_info line which defines this rocks depth dot and hardbox", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &val1 = say_stop("`%We are only interested in the last 4 numbers", &current_sprite);
 external("tutorial", "txtskip", &val1); 
 
 &save_x = sp_custom("txt2", &current_sprite, -1);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 3);
 
 &val1 = say_stop("`%These are the numbers we need to copy into the external line", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Just paste them on the end, separated by commmas, like this...", &current_sprite);
 external("tutorial", "txtskip", &val1); 
 
 &save_x = sp_custom("txt1", &current_sprite, -1);
 sp_pframe(&save_x, 4);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 4); 

 &val1 = say_stop("`%And that's it.", &current_sprite);
 external("tutorial", "txtskip", &val1); 
 
 &save_x = sp_custom("txt1", &current_sprite, -1);
 &save_y = sp_brain_parm(&save_x, -1);
 sp_active(&save_y, 0);
 sp_active(&save_x, 0);

 &save_x = sp_custom("txt2", &current_sprite, -1);
 &save_y = sp_brain_parm(&save_x, -1);
 sp_active(&save_y, 0);
 sp_active(&save_x, 0);

 &save_x = sp_custom("trock", &current_sprite, -1);
 sp_script(&save_x, "t-rock2");
 
 &val1 = say_stop("`%It's a good idea to add the hardbox values in when making any sprite moveable", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Since it's an easy copy and paste, and makes things run a bit smoother", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Also, there might not be a set_sprite_info line for your sprite in dink.ini", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%In this case you will look for the 'load_sequence' line instead", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Then still just copy the last 4 numbers like we did previously", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = create_sprite(318, 232, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0);   
  
 &save_x = create_sprite(318, 220, 6, 52, 1);
 sp_seq(&save_x, 52);
 sp_script(&save_x, "t-heart");
 sp_custom("heart", &current_sprite, &save_x);

 &val1 = say_stop("`%For example, this heart sprite is sequence 52 and does not have a set_sprite_info line.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%But if we open up dink.ini and search for sequence 52..", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &save_x = create_sprite(241, 180, 0, 35, 5); 
 &save_y = create_sprite(241, 180, 15, 36, 5);
 brain(&save_y, 15);
 sp_brain_parm(&save_y, &save_x);
 sp_que(&save_x, 501);
 sp_que(&save_y, 500);
 sp_custom("txt1", &current_sprite, &save_y);

 &val1 = say_stop("`%we'll eventually find the load_sequence line of the sprite, as displayed here.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = sp_custom("txt1", &current_sprite, -1);
 &save_x = sp_brain_parm(&save_x, -1);
 sp_pframe(&save_x, 6);

 &val1 = say_stop("`%You will copy and paste the last 4 numbers into the external line, as we did earlier.", &current_sprite);
 external("tutorial", "txtskip", &val1); 
 
 &val1 = say_stop("`%Simple stuff. That's it for this section.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &save_x = sp_custom("txt1", &current_sprite, -1);
 &save_y = sp_brain_parm(&save_x, -1);
 sp_active(&save_y, 0);
 sp_active(&save_x, 0);

 &val1 = say_stop("`%As stated earlier,  although push and pull will work without the hardbox values added in", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%it's a good idea to ALWAYS add them in anyway.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%And not just for better performance..", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%A lot of the optional stuff in the following sections won't work if hardbox values aren't passed.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Please go back and head East of the entrance screen when you're ready to proceed.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%If you want to view this section again, just talk to me at anytime.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 sp_custom("inprogress", &current_sprite, 0); 

 if (&story < 1)
  &story = 1;
  
 playsound(43, 22050,0,0,0);   
 screenlock(0);
 unfreeze(1); 
}

void talk(void)
{
 &save_x = sp_custom("inprogress", &current_sprite, -1); 
 if (&save_x > 0)
  return;

 if (&story >= 1)
 {
  freeze(1);
  choice_start();
  "View Tutorial Section 1 again"
  "leave"
  choice_end();  
  
   if (&result == 1)
   {
    goto tutorial;
   }
  
  unfreeze(1);
 }
}