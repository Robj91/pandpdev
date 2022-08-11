//vcheck script

void main(void)
{
 int &crap;
 int &junk;

 if (&player_map <= 0)
 {
  HCtextkill();
 }
 
//INITIAL VERSION CHECK
 &crap = get_version();
 
  if (&crap > 108)
  {
    &crap = get_client_version();
    if (&crap < 197)
    {
      &crap = 109;
    }
    else
    {
      &crap = 110;
    }
  }
 if (&crap == 108)
 { 
  //check if this is FreeDink version 108.4 or lower
  //those version would return a unset sp_custom value of -1 instead of 0.
  &junk = create_sprite(20, 20, 0, 21, 1);
  sp_nodraw(&junk, 1);
  &crap = sp_custom("null", &junk, -1);
  if (&crap < 0)
  {
   &crap = 1084;
  }
  else
  {
   //Dink 1.08 or FreeDink 109.6(or higher) in use. Let's differentiate
   //Using the sound bug in the latest FreeDink to check version. :-)
   //we should make sure we at least have a few of soundbank numbers free
   sound_set_kill(18);
   sound_set_kill(19);
   sound_set_kill(20);
   &crap = playsound(23, 22050, 0, 0, 0);
   sound_set_kill(&crap);
   &junk = playsound(23, 22050, 0, 0, 0);
   sound_set_kill(&junk);
   
   if (&junk == 0)
   {
    //sound is disabled, which means the soundbank differentiation won't work.
    //ask the player to select their version
    
    wait(1);
    stop_entire_game(1);
    choice_start();
    set_y 280
    set_title_color 15
    title_start();
    Version can not be determined between 1.08 and FreeDink 109.6 while sound is disabled!
    Please select the Dink version you are currently using.
    title_end();
    "Dink Smallwood 1.08"
    "FreeDink 109.6"
    choice_end();    
    
    if (&result == 1)
    {
     &crap = 108;
     goto proc_cont;
    }
    if (&result == 2)
    {
     &crap = 1096;
     goto proc_cont;
    }
   }
   if (&crap != &junk)
   {
    &crap -= 1;
    &junk -= 1;
    sound_set_kill(&crap);
    sound_set_kill(&junk);
    &crap = 1096;
   }
   else
   {
    &crap = 108;
   }
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
  if (&crap == 109)
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
  if (&crap == 110) 
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
  if (&crap == 1084)
  {
   if (&junk <= 0)
   {
    freedink1084();
   }
   else
   {
    freedink1084l();
   }
  }
  if (&crap == 1096)
  {
   if (&junk <= 0)
   {
    freedink1096();
   }
   else
   {
    freedink1096l();
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

void HCtextkill(void)
{
 //Delete the hard coded version text on the title screen if it exists so we can replace it!
 int &crap;
 if (&player_map <= 0)
 {
  &crap = get_sprite_with_this_brain(8, 0);
  if (&crap > 0)
  {
   sp_kill(&crap, 1);
  }
 }
 goto stopex;
}

/////////////////////////////////////
//VERSION CHECK AFTER SPLASH SCREEN//
/////////////////////////////////////

void olddink(void)
{
 //Dink version lower than 1.08 in use
 //This version text doesn't seem to function as intended in older versions
 //So I've commented it out!
 int &crap = get_version();
 &crap -= 100;
 &crap = say_xy("Dink Smallwood version 1.0&crap", 0, 450); 
 sp_kill(&crap, 0);
 
 wait(1);
 stop_entire_game(1);
 choice_start();
 set_y 280
 set_title_color 15
 title_start();
 Dink Smallwood v1.08, FreeDink or DinkHD is required to run this! Current version does not match!
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
 int &crap = say_xy("Dink Smallwood 1.08", 0, 450); 
 sp_kill(&crap, 0); 
 
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
 int &crap = say_xy("Dink Smallwood HD", 0, 450); 
 sp_kill(&crap, 0); 
 
 //put stuff here
 

 //bugfix
 goto stopex;
}

void freedink1084(void)
{
 //Free Dink version 108.4 or older is in use
 int &crap = say_xy("v1.08 FreeDink", 0, 450); 
 sp_kill(&crap, 0); 

 //bugfix
 goto stopex;
}

void freedink1096(void)
{
 //Free Dink version 109.6 or later is in use
 int &crap = say_xy("Free Dink 109.6", 0, 450); 
 sp_kill(&crap, 0); 
 
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

void freedink1084l(void)
{
 //Free Dink version 108.4 or older is in use
 int &crap = say_xy("`%v1.08 FreeDink - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 

 //bugfix
 goto stopex;
}

void freedink1096l(void)
{
 //Free Dink version 109.6 or later is in use
 int &crap = say_xy("`%Free Dink 109.6 - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 
 
 //put stuff here


 //bugfix
 goto stopex;
}

void flawtest(void)
{
 return;
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