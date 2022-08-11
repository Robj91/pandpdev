void talk(void)
{
 freeze(1);
 say_stop("`3Hi, I'm Phisbo", &current_sprite);
 wait(250);
 say_stop("ok, teach me something, damnit.", 1);
 wait(250);
 say_stop("`3Hmm... fine.", &current_sprite);
 say_Stop("`3I've been watching you and notice you push things like a fricken muppet damnit!.", &current_sprite);
 say_stop("`3It's pitiful, you walk into it, stop, and wait for it to move", &current_sprite);
 wait(250);
 say_stop("So there's a better way?", 1);
 wait(250);
 say_stop("`3YES! You already know how to do it!", &current_sprite);
 wait(250);
 say_stop("Ok.. is that it? Just walk into things like normal?", 1);
 wait(250);
 say_stop("`3Yes, when you walk into a pushable object, you will grab hold of it.", &current_sprite); 
 say_stop("`3And then you can push AND pull it!", &current_sprite); 
 wait(250);
 say_stop("Cool thanks, also your name is stupid.. Phisbo.. sounds like some sort of toy brand.", 1);
 wait(250);
 say_stop("`3Well, these scripts just started as a way to improve the push system", &current_sprite);
 say_stop("`3It was going to be called 'Push, How It's Supposed to Be Obivously', Phisbo for short", &current_sprite);
 say_stop("`3But Robj decided to make you Pull things too, so I adopted the name of the original File", &current_sprite);
 wait(250);
 say_Stop("whatever. Bye.", 1);
 unfreeze(1);

 wait(1200);

 say("So I walk into an object to grab hold of it.. ok.", 1);
}