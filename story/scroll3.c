//green scroll of the unknown

void main(void)
{
 sp_touch_damage(&current_sprite, -1);
 return;
}

void touch(void)
{
 sp_touch_damage(&current_sprite, 0);
 add_item("item-gsu", 438, 17);
 Playsound(10,22050,0,0,0);
 say_xy("`%Green Scroll of the unknown acquired.", 0, 380);  
 sp_brain_parm(&current_sprite, 3);
 sp_brain(&current_sprite, 12);
 sp_touch_damage(&current_sprite, 0);
 sp_timing(&current_sprite, 0);
 int &hold = sp_editor_num(&current_sprite);
 if (&hold != 0)
 editor_type(&hold, 1);
 sp_notouch(&current_sprite, 1);
 sp_nohit(&current_sprite, 1);
 sp_hard(&current_sprite, 1);
 draw_hard_sprite(&current_sprite);
 wait(200);
 sp_active(&current_sprite, 0);
}
