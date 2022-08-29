void talk(void)
{
 freeze(1);
 say_stop("`%Congratulations on solving all the puzzles!", &current_sprite);
 say_stop("`%If you are a Dmod author and you want to use Push and Pull in your Dmod", &current_sprite);
 say_stop("`%Read the readme file in the 'pushandpull' dmod folder for a link to the google doc", &current_sprite);
 say_stop("`5That contains all the documentation that you will need to get started.", &current_sprite);
 unfreeze(1);
}