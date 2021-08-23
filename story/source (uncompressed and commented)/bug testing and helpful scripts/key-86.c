//'V' key
//dink will say how many variables are currently in use.

void main(void)
{
 int &val1 = var_used();
 say("&val1", 1);
 kill_this_task();
}