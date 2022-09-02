//push/pull timer script (delay before push/pull starts)

void main(void)
{
 //retrieve the sprite stored in &save_y, before it changes.
 int &val1 = &save_y;

 //get internal engine uptime
 int &val2 = sp_attack_wait(1, -1);
 
 //create timer delay
waitloop:
 wait(1);
 //get current engine uptime
 &save_x = sp_attack_wait(1, -1);

 //subtract initial engine uptime
 &save_x -= &val2;
 //compare against pushdelay
 &save_y = sp_custom("PPtimer_delay", &val1, -1);
 if (&save_x < &save_y)
 {
  //time has not elapsed yet - loop it.
  goto waitloop;
 }
 
 sp_custom("PPtimerdone", &val1, 1);
 
 kill_this_task();
}

void killtimer(void)
{
 kill_this_task();
}