//'C' key
//dink will say how many scripts are currently in use

void main(void)
{
 int &val1 = scripts_used();
 say("&val1", 1);
 kill_this_task();
}