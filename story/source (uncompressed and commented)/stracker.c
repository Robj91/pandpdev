//constantly monitor variables and scripts used
//'S' key to toggle

void main(void)
{
  //locals
  int &svtext;
  int &svtracker;
  
  //loop to constantly update scripts and variables used
loop:
  //check if a scripts used text is alrady showing
  &svtext = sp_custom("stext", 1, -1);
  if (&svtext > 0)
  {
    //An extra check to confirm we are killing off the correct sprite
    &svtracker = sp_custom("confirm", &svtext, -1);
    if (&svtracker == 2)
    {
      //it is already showing, kill old one off before updating with new one
      sp_active(&svtext, 0);
    }
  }
  
  //get scripts used
  &svtracker = scripts_used();
  
  //show scripts used text
  &svtext = say_xy("`%There are currently &svtracker scripts active", -20, 344);
  //make sure it will live inifinitely
  sp_kill(&svtext, 0);
  
  //save scripts used text in custom key "stext", attached to Dink
  //and save a custom key value in the text sprite as well
  sp_custom("stext", 1, &svtext);
  sp_custom("confirm", &svtext, 2);
  
  //Now do all the above again, but with the variables used
  &svtext = sp_custom("vtext", 1, -1);
  if (&svtext > 0)
  {
    &svtracker = sp_custom("confirm", &svtext, -1);
    if (&svtracker == 1)
    {
      //it is already showing, kill old one off before updating with new one
      sp_active(&svtext, 0);
    }
  }
  
  &svtracker = var_used();
  
  &svtext = say_xy("`%There are currently &svtracker variables active", -20, 375);
  
  sp_custom("vtext", 1, &svtext);
  sp_custom("confirm", &svtext, 1);
  
  sp_kill(&svtext, 0);
  
  wait(200);
  
  goto loop;
}

void killme(void)
{
  //kill it all off
  
  //kill script text
  &svtext = sp_custom("stext", 1, -1);
  sp_active(&svtext, 0);
  
  //kill var text
  &svtext = sp_custom("vtext", 1, -1);
  sp_active(&svtext, 0);
  
  //reset custom key
  sp_custom("trackscript", 1, 0);
  
  //kill script
  kill_this_task();
}
