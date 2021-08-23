void talk(void)
{
 freeze(1);
 say_stop("`%Welcome to the great unkown!", &current_sprite);
 say_stop("`%This is a little tutorial section on push and pull", &current_sprite);
 say_stop("`%Only the wisest shall find this place!", &current_sprite);
 say_stop("`%Watch the video file included in this dmod to see how to implement push and pull", &current_sprite);
 say_stop("`%This area will show you how to use it and tweak it to your liking!", &current_sprite);
 say_stop("`%Make your way to the adjacent screens following the important order N,E,W,S!", &current_sprite);
 say_stop("`%In all of the adjacent tutorial screens, the dialogue text will not time out as usual", &current_sprite);
 say_stop("`%It will not proceed unless you skip it mainually", &current_sprite);
 say_stop("`%That way you don't miss anything.", &current_sprite);
 unfreeze(1);
}