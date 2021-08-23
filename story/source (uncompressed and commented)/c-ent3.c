void main(void)
{
 preload_seq(452);

 sp_touch_damage(&current_sprite, -1);
}


void touch(void)
{
if (&life < 1) return;

freeze(1);
&save_x = sp_x(&current_sprite, -1);
&save_y = sp_y(&current_sprite, -1);
&save_x -= 1;
&save_y += 38;
sp_x(1, &save_x);
sp_y(1, &save_y);
sp_seq(1, 452);
sp_frame(1, 1);
sp_nocontrol(1, 1); //dink can't move until anim is done!
sp_touch_damage(&current_sprite, 0);
sp_brain(1, 0);
wait(2000);
sp_brain(1, 1);
&player_map = 48;
sp_x(1, 284);
sp_y(1, 159);
sp_dir(1,4);
load_screen(48);
draw_screen();
}