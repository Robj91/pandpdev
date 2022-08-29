//Script with default push/pull say lines for, edit to your hearts content.

void main(void)
{
 //Will run whenever dink talks to a sprite while he is pushing it.
 &save_x = random(10, 1);
 if (&save_x == 1)
 {
  say("It's heavier than it looks!", 1);
 }
 if (&save_x == 2)
 {
  say("Nothing shall remain in my way!", 1); 
 } 
 if (&save_x == 3)
 {
  say("I think I prefer beheading ducks", 1);
 }
 if (&save_x == 4)
 {
  say("Nothing like a bit of hard work, this better be worth it..", 1);
 } 
 if (&save_x == 5)
 {
  say("I'd rather go set fire to some trees", 1);
 } 
 if (&save_x == 6)
 {
  say("One of these days I'll get myself a sidekick, or a slave, to do all this hard work.", 1);
 } 
 if (&save_x == 7)
 {
  say("Look at me, the mighty Dink Smallwood, able to move things! ", 1);
 } 
 if (&save_x == 8)
 {
  say("I'm Dink Smallwood. Things should just move for me without me having to touch them!", 1);
 } 
 if (&save_x == 9)
 {
  say("Hello object, thank you for moving, it really helps. Ok, thanks, bye. Good conversation.", 1);
 }
 if (&save_x == 10)
 {
  say("Little bit tedius this is..", 1);
 }
 kill_this_task();
}

void limit(void)
{
 //This is what dink will say if the rock can not be pushed any further (has reached hardness) or the "stopmove" custom key is set to 1 to prevent it from moving.
 //Feel Free to change it, or delete it. Or if you want custom lines for different sprites, do &player_map checks I guess.
 //&arg1 = sprite being moved. Just in case you want to use that and run some checks to trigger different say lines or some other wierd reason.
 
 say("I can't move it any further in this direction..", 1);
}

void space(void)
{
 //This is what Dink will say if there is not enough room behind if to grab hold of the sprite
 //Will only take effect if the "enforce_pullspace" custom key is set
 say("This space is too tight for me to get a decent hold of it!", 1);
}