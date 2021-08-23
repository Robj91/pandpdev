void talk(void)
{
 freeze(1);
 say_stop("`%North, House of Great Wizard Phisbo", &current_sprite);
 wait(200);
 say_stop("`%West, Great Maze of Wonders and Mystery.", &current_sprite);
 wait(200);
 say_stop("`%East, Playground(?)", &current_sprite);
 wait(200);
 say_stop("`%South, Stairs to the great unkown", &current_sprite);
 unfreeze(1);
}