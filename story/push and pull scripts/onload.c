//Onload script, spawned by main.c
//Runs when a game is loaded, and also runs on the title screen(changes made on title screen always carry across to "new game").

void main(void)
{
 wait(0);
 
 spawn("vcheck");   

 //Uncomment the below line to disable the old DInk push mechanic completely.
 //This will make push procedures NOT work, and Dink's push animation NOT play when walking against a non-moveable sprite.
 //push_active(0);

 //Fix for if the player loads game mid push/pull
 //Load original push and seed graphics back in.
 init("load_sequence_now graphics\dink\push\ds-p2- 312 75 45 79 -7 -21 13 -7");
 init("load_sequence_now graphics\dink\push\ds-p4- 314 75 36 69 3 -9 45 9");
 init("load_sequence_now graphics\dink\push\ds-p6- 316 75 67 71 -21 -12 21 9");
 init("load_sequence_now graphics\dink\push\ds-p8- 318 75 46 59 -9 5 12 24");
  
 init("load_sequence graphics\dink\seed\ds-s2- 522 150 49 74 -14 -9 16 10");
 init("load_sequence graphics\dink\seed\ds-s4- 524 150 47 73 -16 -10 14 10");
 init("load_sequence graphics\dink\seed\ds-s6- 526 150 53 71 -16 -10 16 10");
 init("load_sequence graphics\dink\seed\ds-s8- 528 150 50 70 -16 -9 16 9");
  
 kill_this_task();

}