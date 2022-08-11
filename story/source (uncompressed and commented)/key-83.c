//for bugtesting. Attached to the S key.
//scripts and variable tracker

void main(void)
{
  int &svtracker;
  
  &svtracker = sp_custom("trackscript", 1, -1);
  if (&svtracker > 0)
  {
    run_script_by_number(&svtracker, "killme");
    &svtracker = sp_custom("trackscript", 1, -1);
    if (&svtracker > 0)
    {
      //the above proc didn't run, which means the script didn't exist
      //run it instead!
      goto runtrack;
    }
  }
  else
  {
runtrack:
    &svtracker = spawn("stracker");
    sp_custom("trackscript", 1, &svtracker);
  }
  
  kill_this_task();
}
