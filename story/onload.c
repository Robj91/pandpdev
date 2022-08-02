//Onload script, spawned by main.c
//Runs when a game is loaded, and also runs on the title screen(changes made on title screen always carry across to "new game").

void main(void)
{
 wait(0);
 
 spawn("vcheck");

 push_active(0);
  
 kill_this_task();
}