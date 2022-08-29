//Onload script, spawned by main.c
//Runs when a game is loaded, and also runs on the title screen(changes made on title screen always carry across to "new game").

void main(void)
{
 wait(0);
 
 //Comment this line out to disable the normal hardcoded Dink push mechanics. 
 //Only need to do this if you are including a custom pushdelay longer than the normal time it takes to activate vanilla push mechanic
 //Because then they will conflict. Otherwise, it's safe to leave them both active!
 //push_active(0);
  
 kill_this_task();
}