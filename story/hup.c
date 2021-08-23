//push/pull timer script (delay before push/pull starts)

void main(void)
{
 //retrieve the sprite stored in &save_y, before it changes.
 int &val1 = &save_y;
 
 //retrieve the designated pushdelay amount
 &save_x = sp_custom("pushdelay", &save_y, -1);
 
 //create delay
 wait(&save_x);
 
 sp_custom("timerdone", &val1, 1);
 
 kill_this_task();
}

void killtimer(void)
{
 kill_this_task();
}