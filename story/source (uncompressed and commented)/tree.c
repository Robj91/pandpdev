//script for tree in dragon puzzle screen

void main(void)
{
 preload_seq(167);
}

void die(void)
{
 sp_seq(&current_sprite, 20);
 playsound(6, 8000, 0, &current_sprite, 0);
 wait(500);
 wait(500);
 playsound(43, 22050, 0, 0, 0);

 &save_x = sp_x(&current_sprite, -1);
 &save_y = sp_y(&current_sprite, -1);
 &save_x = create_sprite(&save_x, &save_y, 7, 167, 1);
 sp_seq(&save_x, 167);

 sp_brain(&current_sprite, 0);
 sp_size(&current_sprite, 100);
 sp_touch_damage(&current_sprite, -1);
 sp_seq(&current_sprite, 0);
 sp_pseq(&current_sprite, 89);
 sp_pframe(&current_sprite, 10);
 &save_x = &current_sprite;
 script_attach(0);
 sp_script(&save_x, "stairs2");
 draw_hard_map();
 kill_this_task();
}
