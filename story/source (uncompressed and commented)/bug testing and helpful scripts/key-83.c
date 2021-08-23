//for bugtesting. Attached to the S key.
//scripts and variable tracker
//**ONLY WORKS IN FREEDINK**//

void main(void)
{
  int &svtracker;
  
  &svtracker = sp_custom("trackscript", 1, -1);
  if (&svtracker > 0)
  {
    run_script_by_number(&svtracker, "killme");
  }
  else
  {
    &svtracker = spawn("stracker");
    sp_custom("trackscript", 1, &svtracker);
  }
  
  kill_this_task();
}
