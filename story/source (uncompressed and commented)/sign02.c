void main(void)
{
 sp_hard(&current_sprite, 0);
 draw_hard_map();
}

void talk(void)
{
 say("`%These stairs need to be placed in the correct spot!", &current_sprite);
}