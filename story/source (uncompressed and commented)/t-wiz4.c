void main(void)
{
 int &val1;
 int &val2;
 
 if (&story >= 4)
  return;
 
 if (&story < 3)
 {
  freeze(1);
  say_stop("`%N,E,W,S. ORDER IS IMPORTANT!!!", &current_sprite);
  move_stop(1, 8, -200, 1);
 }

tutorial:
 screenlock(1);
 sp_brain(&current_sprite, 20);
 
  freeze(1); 

  sp_custom("inprogress", &current_sprite, 1);

  wait(500);
  
  &val1 = say_xy("`%Dialogue text timeout disabled - all text must be skipped manually in tutorial screens.", 10, 30);
  &val2 = say_xy("`%(press space bar to continue)", 10, 70);
  external("tutorial", "tuttext", &val1, &val2);  

  &val1 = say_stop("`%Welcome to section 4 of the tutorial.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%We have already covered the main essentials of push and pull", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%as well as the extra procedures.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%In section 1 we talked about the skeleton 'moveable sprite' script [sprite.c],", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%And that is the only script we have been dealing with.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Although it IS probably the only one you really need to touch,", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%There are 2 other scripts that you might need to edit", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%Depending on your Dmod.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%I will start with the simple one..", &current_sprite);
  external("tutorial", "txtskip", &val1);   

  &save_x = create_sprite(192, 150, 0, 38, 1); 
  sp_que(&save_x, 500);
  sp_custom("txt1", &current_sprite, &save_x);

  &val1 = say_stop("`%'dsmove.c' is the script that contains some of the default say lines in push and pull", &current_sprite);
  external("tutorial", "txtskip", &val1);   

  &val1 = say_stop("`%This includes the random say lines when talking to a sprite while Dink is moving it.", &current_sprite);
  external("tutorial", "txtskip", &val1); 
 
  &val1 = say_stop("`%And also the default line when an object reaches hardness or cannnot move any further.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%This script is very self explanatory. You can open the script and edit the say lines yourself.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_active(&save_x, 0);

  &save_x = create_sprite(457, 150, 0, 38, 2); 
  sp_que(&save_x, 500);
  sp_custom("txt1", &current_sprite, &save_x);

  &val1 = say_stop("`%The second script is 'DinkSpeed.c", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`%You will only need to edit this if your dmod includes unique items, magic, buffs or debuffs", &current_sprite);
  external("tutorial", "txtskip", &val1); 
 
  &val1 = say_stop("`%Anything that affects Dink's Speed.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%This is because when push/pull initiaites, Dink's speed is actually set to -1", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`%Which means he cannot move.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%And Dink is locked in position, relative to the sprite, with his x and y constantly updated.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Afterwards, when he stops moving the sprite, Dink's speed needs to be reset to what it was before", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%But unfortunately, it cannot be retrieved and stored in a variable.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%So push and pull will look into the DinkSpeed.c script to determine the correct speed to reset", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%It checks if Dink has any items equipped that alter his speed, and resets the speed accordingly", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%There are two procedures in DinkSpeed.c.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%They are 'speedlock' and 'speedreset'", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%They are both important, and you will need to add any speed altering buffs to both of these", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%So push and pull can function correctly.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%Herb boots has already been added.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%So you can use that as an example when adding your own checks for speed buffs/debuffs", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%I will go through the herb boots example, though.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%First let's look at the 'speedlock' example of herb boots.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_active(&save_x, 0);
  
  &save_x = create_sprite(113, 85, 0, 38, 3); 
  sp_que(&save_x, 500);
  sp_custom("txt1", &current_sprite, &save_x); 
  
  &save_x = create_sprite(243, 73, 0, 35, 28); 
  &save_y = create_sprite(243, 73, 15, 36, 28);
  sp_noclip(&save_y, 1);
  sp_noclip(&save_x, 1);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt2", &current_sprite, &save_y); 

  &save_x = create_sprite(527, 268, 0, 38, 5); 
  sp_que(&save_x, 502);
  sp_custom("txt3", &current_sprite, &save_x);  
  sp_y(&current_sprite, 300);
  sp_x(&current_sprite, 517);

  &val1 = say_stop("`%Speedlock is where the push and pull system looks to, to assure the moveable sprite is not too fast", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%As mentioned before, when push/pull is initiated, Dink's speed is set to -1, and he cannot move.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%And his x and y is constantly updated so he is 'locked' to the sprite as it moves.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Because of this, we need to make sure the sprite's speed is not faster than Dink's speed", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`%It would look wierd if Dink can suddenly move faster when he pushes a really fast sprite", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%So if the moveable sprite's speed IS faster than Dink's, we reduce it to match.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%We don't use the 'current_sprite' variable to refer to the sprite here.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%The sprite being moved is stored in the 'arg1' psuedo variable, so we use that.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 29);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 29);

  &val1 = say_stop("`%Here we are checking if Dink has herb boots equipped", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 30);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 30);

  &val1 = say_stop("`%And here we are storing the moveable sprites speed in the 'save_y' global variable", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 31);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 31);

  &val1 = say_stop("`%If herb boots IS equipped, these DinkC lines will run.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%We know that when herb boots is equipped, it raises Dink's speed to 6.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%So we don't want the sprite to be any faster than 6", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 32);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 32);

  &val1 = say_stop("`%Hence why we check that here", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 33);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 33);

  &val1 = say_stop("`%And if it is greater than 6, these line will assure it is reduced to 6.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 34);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 34);

  &val1 = say_stop("`%If it is LOWER than 6, these lines will run instead.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%This external line just assures that if Dink opens his inventory in the middle of push and pull,", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%That his speed will be updated accordingly, if it is a speed altering item that he has equipped.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%So you need not worry about this too much.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Just make sure you include this section when adding checks for your own items.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%There is only ONE thing you need to change in this external line though..", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 35);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 35);

  &val1 = say_stop("`%You need to pass the speed of your item/buff to the 'arg2' pseudo variable, like so..", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Here I have passed 6, because that is the speed of herb boots.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 36);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 36);

  &val1 = say_stop("`%And make sure you finish with a kill_this_task.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Otherwise this external script will stay in the games memory forever, until you exit..", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Since it was called from within a script that is attached to 1000.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%That's all there is to it.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%It's very simple. Just copy the herb boots check, and edit it to suit your item.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Use it as a template.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_active(&save_x, 0);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_active(&save_x, 0);

  &save_x = sp_custom("txt3", &current_sprite, -1);
  sp_active(&save_x, 0);
  
  sp_y(&current_sprite, 376);
  sp_x(&current_sprite, 577);

  &val1 = say_stop("`%Now let's take a look at the herb boots section in 'resetspeed'..", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%This part is very simple.", &current_sprite);
  external("tutorial", "txtskip", &val1); 
 
  &save_x = create_sprite(113, 85, 0, 38, 4); 
  sp_que(&save_x, 500);
  sp_custom("txt1", &current_sprite, &save_x); 

  &save_x = create_sprite(241, 73, 0, 35, 37); 
  &save_y = create_sprite(241, 73, 15, 36, 37);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt2", &current_sprite, &save_y);  
 
  &val1 = say_stop("`%After Dink stops moving the sprite, push/pull needs to reset Dink's speed", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%To what it was originally. So we check what Dink currently has equipped.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 38);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 38);

  &val1 = say_stop("`%Again, here we are checking if Dink currently has herb boots equipped.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt2", &current_sprite, -1);
  sp_pframe(&save_x, 39);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 39);

  &val1 = say_stop("`%And if so, these lines will run, setting Dink's speed and frame_delay correctly.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%This is copied straight from the herb boots arm procedure.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%With 'kill_this_task' added.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%That's it!", &current_sprite);
  external("tutorial", "txtskip", &val1); 
  
  &val1 = say_stop("`% If you don't have anything extra in your dmod that affects speed, you need not edit DinkSpeed.c", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%That concludes this section, and the push and pull tutorial.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Keep in mind sprite.c is heavily commented to help you out, so it's very simple to follow.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Same as DinkSpeed.c and dsmove.c", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%All other scripts will be compressed to .d format since you don't need to touch them", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Plus, in testing, compressing them boosted performance a litte in 1.08 and DinkHD", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%There is also a youtube video tutorial as well, if you want to watch that.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%The link is in the 'Readme Readme Readme' file in this Dmods directory.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%If you want to view this section again, talk to me at any time.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%That is all.", &current_sprite);
  external("tutorial", "txtskip", &val1);
 
  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_active(&save_x, 0);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);
  
 sp_custom("inprogress", &current_sprite, 0); 
 
 if (&story < 4)
  &story = 4;
 
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

    if (&save_x == 3)
     goto phase3;

    if (&save_x == 4)
     goto phase4;

    if (&save_x == 5)
     goto phase5;
   }
  return;
 }

 if (&story >= 4)
 {
  freeze(1);
  choice_start();
  "View Tutorial Section 4 again"
  "leave"
  choice_end();  
  
   if (&result == 1)
   {
    goto tutorial;
   }
  
  unfreeze(1);
 } 
}