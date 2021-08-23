////////////////////////////////////////////////////////////////////
//MOVEABLE SPRITE SKELETON SCRIPT, FULLY COMMENTED FOR EASE OF USE//
///////////////////////////////////////////////////////////////////

//confirmed working as is, in all Dink versions.

//You need to make sure you have &save_x and &save_y declared as globals in main.c or this won't work at all. I used them as global juggle variables. 
//They SHOULD be declared by default, in the 'required globals' section but I mention it here because I know some authors delete them since they are technically not required.

//You can add this push and pull system to any hard sprite in your game by copying this script, renaming it to whatever you want it to be and attaching it to the sprite.
//No push procedure required anymore when using this system, it's all been rewritten and activated through touch.
//Don't worry about setting touch damage to -1 either, the external procedure called in main sorts that out and even fixes your sprite if you forgot to set it to hard and give it a speed.
//This skeleton script is set up with all the NECESSITIES to make a sprite moveable, with the additional features disabled and ready to edit yourself if you want to use them
//It is recommended you optimise it specifically for each sprite though as shown in the in-game tutorial and video tutorial, to assure you won't run into any bugs.

////////////////////////
//STRANGE EXTERNAL BUG// 
////////////////////////

//Keeps executing code, continuing into other procedures sometimes, even continuing past a return; ... wtf?
//Fixed by adding 'goto stopex;' at the end of every procedure in this script.
//If you add any of your own scripting and want to use a 'return;' please also use 'goto stopex;' as well (either straight after it, or use it instead of 'return;').


////////////////////////////////////////////////////////////////////////////////////////
//USEFUL EXTRA STUFF YOU CAN USE - SEE VIDEO TUTORIAL OR IN-GAME TUTORIAL IF CONFUSING//
////////////////////////////////////////////////////////////////////////////////////////

//external("phisbo", "terminate"); - Kills the push/pull of &current_sprite and makes it unmoveable. 
				   //Nothing else to do with move system will continue after running this, it will end it where it's at.
				   //Dink will no longer be able to push this object after this line is executed, he will walk against it like any other unmoveable sprite.
                                   //Also, you can pass a sprite to to the terminate procedure as &arg1 to terminate the passed sprite, instead of &current_sprite.

//external("phisbo", "initiate"); - After running the above terminate line on a sprite, if you want to make it moveable again, you need to run this line.
 				    //This basically resets the necessary custom keys and other stuff and sets it up to be moveable again, without causing any bugs.
                                   //Also, you can pass a sprite to the initiate procedure as &arg1 to reset the passed sprite, instead of &current_sprite.

//external("phisbo", "moveactive"); - returns 1 in pseudo variable '&return' if Dink is currently moving an object.
                                    //Pass a sprite to &arg1 to check if Dink is moving that sprite specifically.
                                    
//sp_custom("stopmove", &sprite, 1); - Stops the sprite from moving. This is not the same as the external terminate line above.
      			             //Push/pull will still activate and Dink will grab the sprite, but it will not go anywhere, as if it's hit hardness already.
      			  	     //You can use this to make it so sprites cannot be moved in certain directions.
      			  	     //Dink will also say the default line for when objects have reached there hardness (in "dsmove.c", "limit" procedure).
      			  	     //Only makes sense to use this in the "MoveDetectDuring" Procedure within this script.

//sp_custom("stopmove", &sprite, 0); - After setting the "stopmove" custom key to 1, as above, it must be set back to 0 (as shown here) to allow the sprite to move again.
				     //e.g do a check for dinks direction. If Dink Direciton is 4, stopmove is set to 1, and if it's 6, stopmove is set to 0. So dink can only move the sprite east.

void main(void)
{
 //This decides how fast the sprite will move when push/pulled. Dink will match this and keep up with the sprite, but will not exceed his current speed.
 //If this is set higher than Dinks speed, it will automatically be reduced by the push/pull system to match his current speed (handled by "Dinkspeed.c")
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 
 //ADD ANY MAIN PROCEDURE SCRIPTING FOR YOUR SPRITE HERE, Before the wait line.
 
 wait(1);

 //////////////////////////////////////////////////////
 //OPTIONAL CUSTOM KEYS FOR COLLISION AND EXTRA STUFF//
 //////////////////////////////////////////////////////
 //"setcollision" - collision based on the sprites hardbox instead of it's depth que, when moving it.
 //1 for hardbox based collision for FreeDink only(All other versions will ignore this if set). 
 //2 for hard box based collision system in FreeDink and Dink Smallwood 1.08 (DinkSmallwood HD will ignore this if set). 
 //3 for hardbox based collision system in ALL versions (not recommended - DinkHD performance is not good.
    //PLEASE NOTE: Versions checker is required for setting collision to '1' or '2', or it will simply be ignored.
    //My recommendation, install versions checker (found on Dink Network under development files), and set collision to 2.
    //It is smooth in FreeDink and quite tolerable in 1.08, but terrible in DinkHD.
 sp_custom("setcollision", &current_sprite, 0);

 //"trimleft", "trimtop", "trimright", and "trimbottom". Only for use when above collision system is active - if not, it will be ignored.
    //These are used to trim a certain amount of pixels from the designated hardbox side when calculating collision only.
    //This is useful to allow the sprites to move a bit closer to other sprites, rather than stopping precisely when the hardbox edge meets hardness.
    //e.g, if you set "trimleft" to 10,  it'll act as if 10 pixels are trimmed off the left harbox edge when calculating collision with other hardness, in all directions.
 sp_custom("trimleft", &current_sprite, 0);
 sp_custom("trimtop", &current_sprite, 0);
 sp_custom("trimright", &current_sprite, 0);
 sp_custom("trimbottom", &current_sprite, 0);
 
 //////////////////////
 //MAIN EXTERNAL LINE//
 //////////////////////
 //&arg 1 - &arg4: Hardbox values (1=left, 2=top, 3=right, 4=bottom). Just copy and paste from dink.ini. 
             //Passing hardbox values is optional for sprites, but recommended to save possible lag. You *may* experience bugs if you don't as well. Don't be lazy, pass them, it's simple.
             //Also, if you have a depth dot in your sprite located OUTSIDE the hardbox, the values MUST be passed here, or push and pull will not function properly.
 external("phisbo", "main"); 

 goto stopex;
}


void touch(void)
{
 //ADD ANY TOUCH PROCEDURE STUFF HERE.

 external("phisbo", "touch"); 

 goto stopex;
}

void MoveDetectDuring(void)
{
//Anything here will be constantly run as the sprite moves. This procedure is constantly poked by the script controlling the sprites movement, so don't put waits or you'll screw things up.
//Just use it to check stuff, like current position of this sprite. You can terminate the push/pull with this: external("phisbo", "terminate");, then you can do what you like. 
//Then if you want to make the sprite moveable again run external("phisbo", "initiate");
//Also NOTE: Using external to constantly call procedures in here will cause massive lag in DinkHD. Solution: Use the old messy goto instead, and copy your procedure into this script.
      //Obviously this doesn't apply to the above terminate and initiate external lines, because they will only run one time, not constantly.

//see staris.c for an exmaple use. 

 //do not delete "goto stopex;" line - fixes external bug 
 goto stopex;
}

void MoveDetectAfter(void)
{
//Anything here will be run AFTER the object has moved and dink releases the sprite.
//Run external("phisbo", "terminate"); if you want to make sure the sprite will no longer be moveable.
//Then if you want to make the sprite moveable again run external("Phisbo", "initiate");

//See maze-r.c for an example use.

 goto stopex;
}

void pull(void)
{
//Don't touch this procedure, and do not add anything, it's not actually run when dink starts pulling
//It's a necessity to allow pull to work when holding the 'Z' key(or whatever key you decide to change the script to) if that system is active. Regardless, leave this as is.

 external("phisbo", "pkey");

 goto stopex;
}

void talk(void)
{
 //IF you don't need a talk procedure, it's safe to delete it.

 //Check if dink is currently moving the sprite
 external("phisbo", "moveactive");
 if (&return <= 0)
 {
  //PUT YOUR NORMAL TALK STUFF HERE, BUT READ BELOW:
  
  //Anything here will be run if Dink talks to the sprite while he IS NOT currently moving it.
  //If you're going to have a wait, more than 1 say line, or a "say_stop()" please terminate push/pull and re-initiate after: external("phisbo", "terminate"); and external("phisbo", "initiate");
    //This will prevent the touch procedure trying to initiate push/pull and interrupting this procedure, causing issues.
 }
 else
 {
  //Anything here will be run when Dink talks to the sprite while he is currently moving it
  //Defaulted to "default say lines when moving sprites", see dsmove.c to edit, or delete.
  external("dsmove", "main");
 }

 goto stopex;
}

void hit(void)
{
 //Hit procedure. You can delete this procedure if not needed.
 
 goto stopex;
}


//STOPEX PROCEDURE - external bugfix. Please make sure this remains the LAST prorcedure in this script.
void stopex(void)
{
stopex:
 return;
}