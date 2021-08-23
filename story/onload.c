//Onload script, spawned by main.c
//Runs when a game is loaded, and also runs on the title screen(changes made on title screen always carry across to "new game").

void main(void)
{
 wait(0);
 
 spawn("vcheck");   

 //Uncomment the below line to disable the old Dink push mechanic completely.
 //This will make push procedures NOT work, and Dink's push animation NOT play when walking against a non-moveable sprite.
 //push_active(0);
  
 kill_this_task();
}