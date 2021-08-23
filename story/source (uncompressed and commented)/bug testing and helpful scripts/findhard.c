//There are some sprites that use the 'default' hardbox given to it (so you can't copy the values out of dink.ini becasue they don't exist).
//This script gives you the hardbox values of a sprite.
//Just copy this script into your story folder and put the following line in the sprite's hit procedure: external("findhard", "findhard");,
//and then stand completely against a hardbox edge (no gap or you'll get incorrect value), and make sure you're facing it, and hit the sprite.
//Dink will say the value that would be in the dink.ini line for that hardbox edge if it existed.

void findhard(void)
{
 &save_x = sp_dir(1, -1);
 if (&save_x == 6)
 {
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_x(1, -1);
  &save_x -= &save_y;
  &save_x *= -1;
  &save_x += 1;
  say("Based on your position and direction, the left hardbox value of this sprite is &save_x", 1);
  return;
 }
 if (&save_x == 2)
 {
  &save_x = sp_y(&current_sprite, -1);
  &save_y = sp_y(1, -1);
  &save_x -= &save_y;
  &save_x *= -1;
  &save_x += 1;
  say("Based on your position and direction, the top hardbox value of this sprite is &save_x", 1);
  return;
 }
 if (&save_x == 4)
 {
  &save_x = sp_x(&current_sprite, -1);
  &save_y = sp_x(1, -1);
  &save_y -= &save_x;
  say("Based on your position and direction, the right hardbox value of this sprite is &save_y", 1);
  return;
 }
 if (&save_x == 8)
 {
  &save_x = sp_y(&current_sprite, -1);
  &save_y = sp_y(1, -1);
  &save_y -= &save_x;
  say("Based on your position and direction, the bottom hardbox value of this sprite is &save_y", 1);
  return;
 } 
}