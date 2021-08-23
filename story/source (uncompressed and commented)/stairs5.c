void main(void)
{
 sp_touch_damage(&current_sprite, -1);
}

void touch(void)
{
 if (&life < 1) return;
 freeze(1);
 sp_touch_damage(&current_sprite, 0);
 playsound(24, 32000, 0, 0, 0); 
 script_attach(1000);
 fade_down();
 &player_map = 17;
 sp_x(1, 319);
 sp_y(1, 211);
 sp_dir(1, 8);
 load_screen(17);
 draw_screen();
 fade_up();
 kill_this_task();
}