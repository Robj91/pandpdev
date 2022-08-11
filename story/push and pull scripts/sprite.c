//================//
//*Important Info*//
//================//

//confirmed working as is, in all FREEDINK versions. Not compatible with Dink 1.08 or DinkHD.

//You need to make sure you have &save_x and &save_y declared as globals in main.c or this won't work at all. I used them as global juggle variables. 
//They SHOULD be declared by default, in the 'required globals' section but I mention it here because I know some authors delete them since they are technically not required.

//where you would usually use "return;" to stop execution of a procedure at any point, please use "goto stopex;" instead. If you don't do this, there will be bugs with this script.

void main(void)
{
 //This decides how fast the sprite will move when push/pulled. Dink will match this and keep up with the sprite, but will not exceed his current speed.
 //If this is set higher than Dinks speed, it will automatically be reduced by the push/pull system to match his current speed.
 sp_speed(&current_sprite, 1);
 sp_timing(&current_sprite, 0);	
 
 //Add any Main procedure stuff you want here, before the wait line.
 
 //required wait line
 wait(1);

 //////////////////////
 //MAIN EXTERNAL LINE//
 //////////////////////
 //&arg 1 - &arg4: Hardbox values (1=left, 2=top, 3=right, 4=bottom). Just copy and paste the last 4 values from the "load_sequence" or "set_sprite_info line" in your dink.ini. 
     //It is highly recommended to pass the sprites hardbox values to this external procedure for better performance.
     //Also, if the depth dot of the sprite is located OUTSIDE the hardbox, the values MUST be passed here, or push and pull will not function properly.
 external("phisbo", "main"); 

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}


void touch(void)
{
 //ADD ANY TOUCH PROCEDURE STUFF HERE.

 external("phisbo", "touch"); 

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}

void MoveDetectDuring(void)
{
//This procedure is constantly called(several times a second) while Dink is pushing or pulling a sprite. It will only be called if the sprite has changed positions since the last call.
//Because it is called this way, don't use any waits, it'll screw things up. Just use it to check stuff, like current position of the sprite. 
//You can terminate the push/pull with this: external("phisbo", "terminate"); then you can do what you like because Dink will release the sprite the push and pull system won't be running anymore. 
//Then if you want to make the sprite moveable again run this: external("phisbo", "initiate");

//see staris.c for an exmaple use. 

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}

void MoveDetectAfter(void)
{
//Anything here will be run AFTER the object has moved and dink releases the sprite.
//Run: external("phisbo", "terminate"); - if you want to make Dink release the sprite, and make sure the sprite will no longer be moveable.
//Then if you want to make the sprite moveable again run: external("phisbo", "initiate");

//See maze-r.c for an example use.

 //do not delete "goto stopex;" line. It is there to prevent bugs.
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
  
  //Anything here will be run if Dink talks to the sprite while he IS NOT currently holding onto/moving it.
  //If you're going to have a wait or say line please terminate push/pull and re-initiate after: external("phisbo", "terminate"); and external("phisbo", "initiate");
    //This will prevent the touch procedure trying to initiate push/pull and interrupting this procedure, causing issues.
 }
 else
 {
  //Anything here will be run when Dink talks to the sprite while he IS currently holding onto/moving it
  //Defaulted to "default say lines when moving sprites", see dsmove.c to edit, or delete.
  external("dsmove", "main");
 }

 //do not delete "goto stopex;" line. It is there to prevent bugs.
 goto stopex;
}

void hit(void)
{
 //Hit procedure. You can delete this procedure if not needed.

 //do not delete "goto stopex;" line. It is there to prevent bugs. 
 goto stopex;
}


//STOPEX PROCEDURE - external bugfix. Please make sure this remains the LAST procedure in this script.
void stopex(void)
{
stopex:
 return;
}