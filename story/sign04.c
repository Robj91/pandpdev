void main(void)
{
 sp_hard(&current_sprite, 0);
 draw_hard_sprite(&current_sprite);

 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 int &val1 = editor_seq(&save_x, -1);

 if (&val1 == 1)
 {
  return;
 }

 say("`%Out of order?", &current_sprite);
}

void talk(void)
{
 &save_x = sp_editor_num(&current_sprite);
 editor_type(&save_x, 0);
 &val1 = editor_seq(&save_x, -1);

 if (&val1 == 1)
 {
  say("`%...", &current_sprite);
  return;
 }

 freeze(1);
 say_stop("`%Out of order?", &current_sprite);
 wait(200);
 say_stop("Well.. what can I do about that?", 1);
 unfreeze(1);
}