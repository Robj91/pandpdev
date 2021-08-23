void talk(void)
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("What is this place?", 1);
 wait(200);
 say_stop("`5This is the cavern of the great unkown", &current_sprite);
 say_stop("`5Legend has it there is some sort of unkown knowledge to be unlocked in these caverns", &current_sprite);
 wait(200);
 say_stop("Ok.. I might just check it out", 1);
 wait(200);
 say_stop("`5remember order is everything!", &current_sprite);
 wait(200);
 say_stop("say what now?", 1);
 wait(200);
 say_stop("`5N,E,W,S! It's the order of utter importance!", &current_sprite);
 wait(200);
 say_stop("Right. Well, I'll be going now.", 1);
 unfreeze(1);
 unfreeze(&current_sprite);
}