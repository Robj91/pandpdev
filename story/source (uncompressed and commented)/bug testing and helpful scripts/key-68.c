//'D' key
//To check if dink is currently moving an object

void main(void)
{
 external("phisbo", "moveactive");
 &save_x = &return;
 say("&save_x", 1);
 kill_this_task();
}