void main(void)
{
 int &val1;
 int &val2;
 
 if (&story >= 3)
  return;
 
 if (&story < 2)
 {
  freeze(1);
  say_stop("`%N,E,W,S. ORDER IS IMPORTANT!!!", &current_sprite);
  move_stop(1, 6, 700, 1);
 }

tutorial:
 screenlock(1);
 sp_brain(&current_sprite, 20);
 
  freeze(1); 

  &save_x = sp_custom("trock", &current_sprite, -1);
  if (&save_x > 0)
  {
   sp_active(&save_x, 0);
  }   
  &save_x = sp_custom("trock2", &current_sprite, -1);
  if (&save_x > 0)
  {
   sp_active(&save_x, 0);
  }  

  sp_custom("inprogress", &current_sprite, 1); 
  
  wait(500);
  
  &val1 = say_xy("`%Dialogue text timeout disabled - all text must be skipped manually in tutorial screens.", 10, 30);
  &val2 = say_xy("`%(press space bar to continue)", 10, 70);
  external("tutorial", "tuttext", &val1, &val2);   

  &val1 = say_stop("`%Welcome to section 3 of the tutorial.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%We will cover the extra procedures of the 'moveable sprite' script.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Before I continue I should point out, I will not cover each of the common procedures in detail.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Such as touch, talk, and hit. These are self explanatory", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%But I will touch on the most important aspect of them in general.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Each of the common procedures have one or more external lines.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%DO NOT delete these, they are required as part of the push and pull system.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%In each procedure, you will see comments that tell you where you can insert your scripting.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%So if you have anything to add, just follow what the comments say for the common procedures.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Also at the end of each procedure you will see the line 'goto stopex'", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Do not remove this either, it fixes a nasty bug with 'external'", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Also on that note..", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%If you want to use 'return' within your moveable sprite script, please use 'goto stopex' instead", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%This is to prevent a rare bug caused by external, where the script continues past a 'return' line", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%There is also comments in the script to remind you of this as well, so don't worry.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Now that's out of the way, let's get into our additional procedures added by push and pull.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%There are 2 new procedures you might find yourself using a lot, when making a dmod.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%They are already added into sprite.c, so you don't need to remember them", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%As long as  you use it as a skeleton script like I said earlier, it's all very simple.", &current_sprite);
  external("tutorial", "txtskip", &val1);
  
  &val1 = say_stop("`%The 2 new procedures are MoveDetectDuring, and MoveDetectAfter.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Both of these are used to run stuff at different times within the pushing / pulling of a sprite.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%Let's take a look at the MoveDetectAfter procedure first.", &current_sprite);
  external("tutorial", "txtskip", &val1);
 
  &save_x = create_sprite(276, 171, 0, 35, 13); 
  &save_y = create_sprite(276, 171, 15, 36, 13);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

  &val1 = say_stop("`%Here is the MoveDetectAfter procedure, with comments removed, and no scripting added yet.", &current_sprite);
  external("tutorial", "txtskip", &val1);  

  &val1 = say_stop("`%Anything in this procedure will run AFTER Dink has moved the sprite and released it.", &current_sprite);
  external("tutorial", "txtskip", &val1);

  &val1 = say_stop("`%To test this out so you can make sense of it, let me give you an example.", &current_sprite);
  external("tutorial", "txtskip", &val1);      

  &save_x = create_sprite(277, 106, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(277, 106, 0, 95, 1);
  sp_script(&save_x, "t-rock8"); 
  sp_custom("trock", &current_sprite, &save_x); 

  &val1 = say_stop("`%Let's add some scripting to MoveDetectAfter, in this moveable rock's script...", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%How about this..", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 14);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 14);

  &val1 = say_stop("`%So now everytime Dink moves this rock and let's go of it, his strength will be increased by 1", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &val1 = say_stop("`%Give it a go and talk to me when you're ready to continue.", &current_sprite);
  external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);
 
 unfreeze(1);
}

void phase 1(void)
{
phase1:
 freeze(1);

 &val1 = say_stop("`%As you can see, this could be quite useful for certain circumstances.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%For instance, you could check if the player moved the sprite to a certain part of the screen.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%In some circumstances, you may want to turn the sprite into a normal unmoveable sprite.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%To make a sprite a normal, unmoveable sprite, there is an external line you need to run.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(270, 177, 0, 35, 15); 
  &save_y = create_sprite(270, 177, 15, 36, 15);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

 &val1 = say_stop("`%The external line is displayed below.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%This line can be run ANYWHERE in the moveable sprties script, to make it unmoveable.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%If, after making the sprite unmoveable, you want to make it moveable again, use the following line.", &current_sprite);
 external("tutorial", "txtskip", &val1);
 
  &save_x = create_sprite(270, 230, 0, 35, 16); 
  &save_y = create_sprite(270, 230, 15, 36, 16);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt2", &current_sprite, &save_y); 

 &val1 = say_stop("`%This will run the necessary functions to make the sprite moveable again without causing any bugs.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Now let's add both of these lines to the example rock over here.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);

  &save_x = sp_custom("txt2", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);

 &val1 = say_stop("`%Let's take another look at our MoveDetectAfter Procedure...", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(436, 42, 0, 35, 14); 
  &save_y = create_sprite(436, 42, 15, 36, 14);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

 &val1 = say_stop("`%First we'll add the external line to make it an unmoveable sprite..", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 17);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 17); 

 &val1 = say_stop("`%So now when Dink moves the sprite and releases it, it will become unmovable", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%And his strength will increase by 1.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%To demonstrate changing it back into a moveable sprite, I'll use the sprites hit procedure", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0);

  &save_x = create_sprite(270, 175, 0, 35, 18); 
  &save_y = create_sprite(270, 175, 15, 36, 18);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

 &val1 = say_stop("`%This is the default hit procedure from the skeleton script without anything added.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Let's add the external line to make the sprite movable again..", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 19);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 19); 

 &val1 = say_stop("`%So now here's what we have..", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%When Dink pushes the sprite and releases, it will become an unmovable sprite", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%And then Dinks Strength will be increased by 1.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%If Dink hits the sprite, it will become moveable again.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Test it out, and talk to me when you want to continue.", &current_sprite);
 external("tutorial", "txtskip", &val1);
 
  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 
 
 &save_x = sp_custom("trock", &current_sprite, -1);
 sp_script(&save_x, "t-rock9");

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
 playsound(24, 22052, 0, 0, 0); 
 sp_active(&val1, 0); 

 &val1 = say_stop("`%This is just an example, there are many scenarios where this would be quite useful.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%That's it for the MoveDetectAfter Procedure. Let's look at the second extra Procedure.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%The other extra procedure is MoveDetectDuring.", &current_sprite);
 external("tutorial", "txtskip", &val1);  
 
 &val1 = say_stop("`%I'll now give you an example the same way I did for MoveDetectAfter.", &current_sprite);
 external("tutorial", "txtskip", &val1);   
 
  &save_x = create_sprite(277, 106, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(277, 106, 0, 95, 1);
  sp_script(&save_x, "t-rock10"); 
  sp_custom("trock", &current_sprite, &save_x); 

 &val1 = say_stop("`%Let's take a look at the MoveDetectDuring procedure..", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(276, 171, 0, 35, 20); 
  &save_y = create_sprite(276, 171, 15, 36, 20);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);  
 
 &val1 = say_stop("`%Here is the MoveDetectDuring Procedure with comments removed and no scripting added.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Any scripting in this procedure will CONSTANTLY be run when Dink is moving the object.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Even when the player is idle while holding the sprite it will still run constantly", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%This is very useful to check the location of the object as the player is moving it.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Rather than waiting until after it has been moved and released.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%To allow you to make sense of it I will use the same example as before.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 21);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 21); 

 &val1 = say_stop("`%So now Dink's strength will constantly increase by 1 as the sprite is being moved.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Give it a go, and talk to me when you're ready to continue.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 
 
  sp_custom("inprogress", &current_sprite, 3);
 
 unfreeze(1);  
}

void phase3(void)
{
phase3:
 
 freeze(1);

 &val1 = say_stop("`%Just as before you can terminate push/pull and make the object unmoveable", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Using the external line mentioned previously.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%When terminating push/pull in MoveDetectDuring, MoveDetectAfter WILL NOT execute", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Because move has been terminated, and anything relating to it from then on won't run.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%So you're MoveDetectDuring procedure will continue, and that's it.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Let's look at the same example as before but in MoveDetectDuring..", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = create_sprite(276, 171, 0, 35, 21); 
  &save_y = create_sprite(276, 171, 15, 36, 21);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y); 

 &val1 = say_stop("`%This is the MoveDetectDuring procedure of the rock.", &current_sprite);
 external("tutorial", "txtskip", &val1);   

 &val1 = say_stop("`%Let's add the external line to make it unmoveable..", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 27);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 27); 

 &val1 = say_stop("`%And we'll also update the hit procedure as well, same as the previous example..", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  &save_x = create_sprite(270, 175, 0, 35, 18); 
  &save_y = create_sprite(270, 175, 15, 36, 18);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);
 
 &val1 = say_stop("`%Let's add the line here to make it moveable again..", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 19);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 19); 

 &val1 = say_stop("`%OK, so we have the same example as used previously in MoveDetectAfter", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%When Dink pushes the the rock it will become unmoveable", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%And Dink's strength will increase by 1", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Then hitting the rock will make it moveable again.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%This will behave a lot differently than MoveDetectAfter", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%In fact, the sprite won't move at all.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%As soon as push/pull initiates and MoveDetecturing executes, push/pull will terminate.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%Give it a go for yourself and see how it behaves.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &save_x = sp_custom("trock", &current_sprite, -1);
 sp_script(&save_x, "t-rock11");

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  sp_custom("inprogress", &current_sprite, 4);

 unfreeze(1);
}

void phase4(void)
{
phase4:
 
 freeze(1);
 
 &val1 = sp_custom("trock", &current_sprite, -1);
 &save_x = sp_x(&val1, -1);
 &save_y = sp_y(&val1, -1);
 
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 sp_active(&val1, 0);  
 
 &val1 = say_stop("`%So as you can see, MoveDetectDuring can be very useful for certain situations", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%For instance, when the rock reaches a certain position on the screen you could detect it", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%And then terminate push/pull, and make the sprite unmoveable.", &current_sprite);
 external("tutorial", "txtskip", &val1);     

 &val1 = say_stop("`%This is a good time to mention one more useful thing that you can use.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Let's say you want to make it so a sprite can't move in a certain direction.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%The external line to terminate the push/pull of a sprite is no good in this circumstance", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Because that will make the sprite entirely unmoveable", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%So there is something else which STOPS the sprite moving, but doesn't terminate push/pull", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%Sounds confusing, but it will make sense.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = create_sprite(264, 186, 0, 35, 22); 
  &save_y = create_sprite(264, 186, 15, 36, 22);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

 &val1 = say_stop("`%Here it is. It is a custom key. When set to 1, it is active.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%This is really only useful in the MoveDetectDuring procedure", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%If this line is executed, Dink will continue pushing, but the sprite will not move", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%It will behave EXACTLY as if it's already collided with hardness and won't go anywhere", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%And to allow the sprite to move again, we need to reset the custom key to 0, like so..", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(264, 216, 0, 35, 23); 
  &save_y = create_sprite(264, 216, 15, 36, 23);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt2", &current_sprite, &save_y);
 
 &val1 = say_stop("`%This will make more sense with an example use..", &current_sprite);
 external("tutorial", "txtskip", &val1); 

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  &save_x = sp_custom("txt2", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  &save_x = create_sprite(277, 106, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);   
  
  &save_x = create_sprite(277, 106, 0, 95, 1);
  sp_script(&save_x, "t-rock12"); 
  sp_custom("trock", &current_sprite, &save_x); 

 &val1 = say_stop("`%Let's make it so this rock cannot be pushed west, but can be pushed any other direction.", &current_sprite);
 external("tutorial", "txtskip", &val1);  

  &save_x = create_sprite(101, 141, 7, 167, 1);
  sp_seq(&save_x, 167);

  &save_x = create_sprite(512, 143, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0); 
  
  sp_x(&current_sprite, 512);
  sp_y(&current_sprite, 143);
  
  wait(1000);

  &save_x = create_sprite(250, 73, 0, 35, 20); 
  &save_y = create_sprite(250, 73, 15, 36, 20);
  brain(&save_y, 15);
  sp_brain_parm(&save_y, &save_x);
  sp_que(&save_x, 501);
  sp_que(&save_y, 500);
  sp_custom("txt1", &current_sprite, &save_y);

  &save_x = create_sprite(520, 85, 0, 38, 5); 
  sp_que(&save_x, 502);
  sp_custom("txt2", &current_sprite, &save_x); 

 &val1 = say_stop("`%Here is it's MoveDetectDuring procedure. Let's add a check for Dink facing west.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 24);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 24);   

 &val1 = say_stop("`%And if he IS facing west, we'll set the 'stopmove' custom key to 1.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 25);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 25); 

 &val1 = say_stop("`%And as mentioned before, to make the rock move again we need to reset the custom key to 0.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%So if Dink is moving in ANY other direction, we'll set custom key 'stopmove' to 0.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  sp_pframe(&save_x, 26);
  &save_x = sp_brain_parm(&save_x, -1);
  sp_pframe(&save_x, 26); 

 &val1 = say_stop("`%Now the sprite will not move west.", &current_sprite);
 external("tutorial", "txtskip", &val1);

 &val1 = say_stop("`%Feel free to test it, and talk to me when you want to continue.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = sp_custom("txt1", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  &save_x = sp_custom("txt2", &current_sprite, -1);
  &save_y = sp_brain_parm(&save_x, -1);
  sp_active(&save_y, 0);
  sp_active(&save_x, 0); 

  wait(200);

  &save_x = create_sprite(101, 141, 7, 167, 1);
  sp_seq(&save_x, 167);

  &save_x = create_sprite(512, 143, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);

  sp_x(&current_sprite, 101);
  sp_y(&current_sprite, 141);

 sp_custom("inprogress", &current_sprite, 5);

 unfreeze(1);
}

void phase5(void)
{
phase5:

 freeze(1);

 &val1 = sp_custom("trock", &current_sprite, -1);
 &save_x = sp_x(&val1, -1);
 &save_y = sp_y(&val1, -1);
 
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);
 playsound(24, 22052, 0, 0, 0); 
 sp_active(&val1, 0);  
 
 &val1 = say_stop("`%That concludes this section.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%I'll leave you a couple of sprites to mess around with.", &current_sprite);
 external("tutorial", "txtskip", &val1);

  &save_x = create_sprite(277, 106, 0, 95, 1);
  sp_script(&save_x, "t-rock13"); 
  sp_custom("trock", &current_sprite, &save_x); 

  &save_x = create_sprite(394, 110, 0, 95, 1);
  sp_script(&save_x, "t-rock14"); 
  sp_custom("trock2", &current_sprite, &save_x);

  &save_x = create_sprite(277, 106, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);
 
  &save_x = create_sprite(394, 110, 7, 167, 1);
  sp_seq(&save_x, 167);
  playsound(24, 22052, 0, 0, 0);
 
 &val1 = say_stop("`%Both of these rocks will tell you their x co-ordinate when moved.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%The left one uses MoveDetectAfter, and will tell you AFTER it's moved.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%The right uses MoveDetectDuring, and will constantly update as you move it.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%You can toggle between them saying their x and y position by hitting the sprites.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%If you are interested in seeing how this works...", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%The script for the left rock is t-rock13.c.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%And the script for the right rock is t-rock14.c.", &current_sprite);
 external("tutorial", "txtskip", &val1); 

 &val1 = say_stop("`%When you're ready, head back to the entrance screen and head south", &current_sprite);
 external("tutorial", "txtskip", &val1);  

 &val1 = say_stop("`%If you want to view this section again, talk to me at anytime.", &current_sprite);
 external("tutorial", "txtskip", &val1);
 
 sp_custom("inprogress", &current_sprite, 0); 
 
 if (&story < 3)
 &story = 3;
 
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

 if (&story >= 3)
 {
  freeze(1);
  choice_start();
  "View Tutorial Section 3 again"
  "leave"
  choice_end();  
  
   if (&result == 1)
   {
    goto tutorial;
   }
  
  unfreeze(1);
 } 
}