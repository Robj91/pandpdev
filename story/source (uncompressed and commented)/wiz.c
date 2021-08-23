void talk(void)
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("Hi, who are you", 1);
 wait(200);
 say_Stop("`3The wizard of making rocks lighter...", &current_sprite);
 wait(200);
 say_stop("ok.. ?", 1);
 wait(200);
 say_stop("`3The top rock is the same speed as all the other sprites you've pushed previously.. quite slow", &current_sprite);
 say_stop("`3The middle sprite, is not as heavy, and moves at your normal walk speed", &current_sprite);
 say_stop("`3The bottom sprite is even lighter, and moves the same speed as herb boots!", &current_sprite);
 say_stop("`3So if you push it with herb boots on, you can move it super fast!", &current_sprite);

 &save_x = count_item("item-bt");
 if (&save_x <= 0)
 {
  Playsound(10,22050,0,0,0);
  add_item("item-bt", 438, 22);
  say_stop("`3Here's a pair of herb boots! Try pushing the bottom sprite with and without them equipped", &current_sprite);
 }
 else
 {
  say_stop("`3Try pushing the bottom sprite with and without herb boots equipped", &current_sprite);
 }
 wait(200);
 say_stop("ok...", 1);
 unfreeze(1);
 unfreeze(&current_sprite);
}

 