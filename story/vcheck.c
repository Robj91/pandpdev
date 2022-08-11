//vcheck script

void main(void)
{
 int &crap;
 int &junk;
 int &val1;

 if (&player_map <= 0)
 {
  HCtextkill();
 }
 
//INITIAL VERSION CHECK
 &crap = get_version();
 
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
   //check if vanilla 1.08 or FreeDink 109.6, with a  keystroke
   //adjust position of version checker text below
   &junk = say_xy("`%Please press F2, so  this dmod can determine your Dink version", 20, 200);
   sp_kill(&junk, 0);
   sp_brain(1, 1);
   set_dink_speed(1, -1);
   sp_nodraw(1, 1);
   &crap = create_sprite(1, 1, 0, 1, 1);
   sp_nodraw(&crap, 1);
   sp_gold(&crap, 999);
  detect-key:
   wait(50);
   &val1 = sp_gold(&crap, -1);
   if (&val1 != 999)
   {
    &crap = &val1;
   }
   else
   {
    goto detect-key;
   }
    
   //change dink back to mouse
   sp_active(&junk, 0);
   set_dink_speed(1, 3);
   sp_nodraw(1, 0);   
   sp_seq(1, 0);
   sp_brain(1, 13);
   sp_pseq(1,10);
   sp_pframe(1,8);
   sp_que(1,20000);
   sp_noclip(1, 1);
   sp_base_idle(1, -1);
   sp_base_walk(1, -1);


   if (&crap == 1096)
   {
    //Freedink 109.6 - check for linux version (broken &arg4 - &arg8)
    //this will store 1096 for windows and -1096 for linux
    external("vcheck", "l-w", 1, 0, 0, 99);
    external("vcheck", "l-w");
    &crap = &return;
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
  if (&crap >= 109)
  {
   if (&crap <= 110)
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
  }
  if (&crap >= 111)
  {
   if (&crap < 1000)
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
  if (&crap == -1096)
  {
   if (&junk <= 0)
   {
    freedink-1096();
   }
   else
   {
    freedink-1096l();
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
 int &crap = say_xy("Free Dink 109.6 (Windows)", 0, 450); 
 sp_kill(&crap, 0); 
 
 //put stuff here
 
 
 //bugfix
 goto stopex;
}

void freedink-1096(void)
{
 //Free Dink version 109.6 or later is in use
 int &crap = say_xy("Free Dink 109.6 (Linux)", 0, 450); 
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
 int &crap = say_xy("`%Free Dink 109.6 (Windows) - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 
 
 //put stuff here


 //bugfix
 goto stopex;
}

void freedink-1096l(void)
{
 //Free Dink version 109.6 or later is in use on Linux
 int &crap = say_xy("`%Free Dink 109.6 (Linux) - Save File Loaded", 10, 380); 
 sp_kill(&crap, 3000); 
 
 //put stuff here


 //bugfix
 goto stopex;
}

void l-w(void)
{
 //used to differentiate between windows and linux version of FreeDink 109.6
 if (&arg1 > 0)
 {
  //this is the first external call
  goto stopex;
 }
 else
 {
  //this is the secon external call
  if (&arg4 > 0)
  {
   return(-1096);
  }
  else
  {
   return(1096);
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
