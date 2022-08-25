//vcheck script

void main(void)
{
 int &crap;
 int &junk;

 //uncomment the following line to crash any dink engines earlier than DinkHD or FreeDink 109.6 for a hard-lockout of old version
 //sp_custom("null", 1, -1);

//INITIAL VERSION CHECK
 &crap = get_version();
 
 if (&crap >= 111)
 {
  &junk = get_client_version();
  if (&junk >= 197)
  {
   //recent DinkHD release - feel free to change above get_client_version result to a more current one if you want
   &crap = 111;
  }
  else
  {
   //just do a negative value for old DinkHD versions
   &crap = -111;
  }
 }

proc_cont: 
  //check if new game, if so we don't want to run the "save file loaded" text
  if (&vcheck == 0)
  {
   &junk = 0;
  }
  else
  {
   &junk = &player_map;
  }
  
  //now run the appropriate procedure (after splash or after load)
  if (&crap > 0)
  {
   if (&crap < 108)
   {
    if (&junk <= 0)
    {
     olddink();
    }
    else
    {
     olddinkl();
    }
   }   
  }
  if (&crap == 108)
  {
   if (&junk <= 0)
   {
    dink108();
   }
   else
   {
    dink108l();
   }
  } 
   
  if (&crap == -111)
  {
   if (&junk <= 0)
   {
     olddinkhd();
   }
   else
   {
     olddinkhdl();
   }
  }
   
  if (&crap == 111)
  {
   if (&junk <= 0)
   {
     dinkhd();
   }
   else
   {
     dinkhdl();
   }
  }
 
 //save version in global variable &vcheck
 &vcheck = &crap;
 
 kill_this_task();
 
 goto stopex;
}

void runtime(void)
{
 //leave this here to make it compatible with previous version.
 //makes for an easier update. Just return a value greater than 0.
 return(1);
 kill_this_task();
 goto stopex;
}

/////////////////////////////////////
//VERSION CHECK AFTER SPLASH SCREEN//
/////////////////////////////////////

void olddink(void)
{
 //Dink version lower than 1.08 in use
 
 wait(1);
 stop_entire_game(1);
 choice_start();
 set_y 280
 set_title_color 15
 title_start();
 This is an outdated verison of Dink Smallwood.
 You may experience bugs or performance issues if you continue.
 title_end();
 "Continue anyway"
 "Exit"
 choice_end();
 
 if (&result == 2)
 {
  kill_game();
 }

 //bugfix
 goto stopex;
}

void dink108(void)
{
 //Dink version 1.08 in use
 
 //put stuff here

 //bugfix
 goto stopex;
}

void olddinkhd(void)
{
 //Dink HD outdated version in use
 int &crap = say_xy("Dink Smallwood HD (outdated build) - please update!", 0, 450); 
 sp_kill(&crap, 0); 
 
 wait(1);
 stop_entire_game(1);
 choice_start();
 set_y 280
 set_title_color 15
 title_start();
 You are running an outdated version of DinkHD. Please update and then try again!
 You can get the current version at The Dink Network (www.dinknetwork.com)
 You may experience bugs or performance issues if you continue.
 title_end();
 "Continue Anyway"
 "Exit"
 choice_end();
 
 if (&result == 2)
 {
  kill_game();
 }

 //bugfix
 goto stopex;
}

void dinkhd(void)
{
 //Dink Smallwood HD current version in use
 
 //put stuff here
 

 //bugfix
 goto stopex;
}

/////////////////////////////////
//VERSION CHECK AFTER LOAD GAME//
/////////////////////////////////

void olddinkl(void)
{
 //Dink version lower than 1.08 in use
 int &crap = get_version();
 &crap -= 100;
 &crap = say_xy("`%Dink Smallwood version 1.0&crap - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000);
 
 //bugfix
 goto stopex;
}

void dink108l(void)
{
 //Dink version 1.08 in use
 int &crap = say_xy("`%Dink Smallwood 1.08 - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 
 
 //put stuff here


 //bugfix
 goto stopex;
}

void olddinkhdl(void)
{
 //Dink HD outdated version in use
 int &crap = say_xy("`%Dink Smallwood HD (outdated build) - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 

 //bugfix
 goto stopex;
}

void dinkhdl(void)
{
 //Dink Smallwood HD current version in use
 int &crap = say_xy("`%Dink Smallwood HD - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 
 
 //put stuff here


 //bugfix
 goto stopex;
}

void soundbug(void)
{
 //used to check for soundbank bug
 //If this returns 1, soundbank numbers need to be subtracted by 1 before you can use them in DinkC functions
 int &crap;
 int &junk;
 
 sound_set_kill(18);
 sound_set_kill(19);
 sound_set_kill(20);
 &crap = playsound(23, 22050, 0, 0, 0);
 sound_set_kill(&crap);
 &junk = playsound(23, 22050, 0, 0, 0);
 sound_set_kill(&junk); 
 
 if (&crap != &junk)
 {
   &crap -= 1;
   &junk -= 1;
   sound_set_kill(&crap);
   sound_set_kill(&junk);
   return(1);
 }
 else
 {
  return(0);
 }
}

void argbug(void)
{
 //used to check for bug with &args.
 //If this returns 1, it means that &arg4 - &arg9 will not clear 
  //(the last known values passed to a procedure will be used again if nothing is specified in further external calls)
 
 external("vcheck", "checkarg", 1, 0, 0, 1);
 external("vcheck", "checkarg");
 return(&return);
}

void checkarg(void)
{
 if (&arg1 > 0)
 {
  //this is the first external call
  goto stopex;
 }
 else
 {
  //this is the second external call
  if (&arg4 > 0)
  {
   return(1);
  }
  else
  {
   return(0);
  }
 } 
}

///////////////////////////////////////
//Script external bug termination fix//
///////////////////////////////////////
void stopex(void)
{
 //Don't touch this - fixes a bug with external reading through return; in procs.
stopex:
 return;
}
