void main(void)
{
 sp_que(&current_sprite, -500);
 sp_touch_damage(&current_sprite, -1);
}

void touch(void)
{
 if (&life < 1) return;
 freeze(1);
 sp_touch_damage(&current_sprite, 0);
 playsound(39, 16000, 0, 0, 0);
 script_attach(1000);
 fade_down();
 &player_map = 46;
 sp_x(1, 266);
 sp_y(1, 100);
 sp_dir(1, 2);
 load_screen(46);
 draw_screen();
 fade_up();
 kill_this_task();
}