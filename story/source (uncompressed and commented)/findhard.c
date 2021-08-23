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