void main(void)
{
 sp_hard(&current_sprite, 0);
 draw_hard_sprite(&current_sprite);

 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 int &val1 = editor_seq(&save_x, -1);

 if (&val1 == 1)
 {
  &save_x = create_sprite(202, 293, 0, 89, 10);
  sp_script(&save_x, "stairs");
  return;
 }

 say("`%Bomb rocks.", &current_sprite);
}

void talk(void)
{
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 int &val1 = editor_seq(&save_x, -1);

 if (&val1 == 1)
 {
  say("`%...", &current_sprite);
  return;
 }

 say("`%Bomb rocks.", &current_sprite);
}