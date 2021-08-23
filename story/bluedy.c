void main(void)
{
 external("vcheck", "runtime");
 if (&return == 0)
  kill_this_task();


 int &bluedyvar = sp_editor_num(&current_sprite);
 editor_type(&bluedyvar, 0);
 int &bluedyseq = editor_seq(&bluedyvar, -1);
 
 int &explo;
 if (&bluedyseq == 0)
 {
  freeze(1);
  freeze(&current_sprite);
  say_stop("`5Hi Dink.", &current_sprite);
  wait(200);
  say_stop("Well.. hi.", 1);
  wait(200);
  say_stop("`5Welcome to pushing and pulling, how it should be done", &current_sprite);
  say_stop("`5Let's get started with the basics..", &current_sprite);
  say_stop("`5Here's some information on what you need to know.", &current_sprite);

  show_bmp("tiles\PullTut.bmp", 0, 0);
  wait(500);
  say_stop("`5Talk to me for more information!", &current_sprite);
  
  unfreeze(1);
  unfreeze(&current_sprite);
  &bluedyseq = 1;
  editor_seq(&bluedyvar, &bluedyseq);
 }
 if (&bluedyseq == 2)
 {
  &explo = create_sprite(364, 293, 0, 27, 1);
  sp_hard(&explo, 0);
  draw_hard_map();
  sp_script(&explo, "sprite");
  return;
 }  
}

void talk(void)
{
 freeze(1);
 freeze(&current_sprite);
 say_stop("Who are you?", 1);
 wait(200);
 say_stop("`5I'm Bluedy.", &current_sprite);
 wait(200);
 say_Stop("Ok.. What's your significance in this dmod?", 1);
 wait(200);
 say_stop("`5I'm a character thrown in by Robj to credit me, Bluedy.", &current_sprite);
 say_stop("`5While I'm not the author of the dev file, I did create the mapping so Robj could showcase it", &current_sprite);
 say_stop("`5And I tested things and reported bugs every step of the way!", &current_sprite);
 say_stop("`5Basically Robj is a lazy SOB who spent a month writing scripts for this system", &current_sprite);
 say_stop("`5But couldn't create a simple map or title screen.", &current_sprite);
 say_Stop("`5So I came to the rescue and provided him a canvas to demo his blood, sweat and frustration.", &current_sprite);
 wait(200);
 
 if (&bluedyseq <= 1)
 {
  say_stop("Did you notice there is not one duck at all around this place?", 1);
  wait(200);
  say_stop("`5Hmmm.. valid point.. let me fix that, I am a wizard sprite after all.", &current_sprite);
  wait(500);
  
  &explo = create_sprite(364, 293, 7, 167, 1);
  sp_seq(&explo, 167);
  playsound(24, 22052, 0, 0, 0); 

  wait(1);

  &explo = create_sprite(364, 293, 0, 27, 1);
  sp_hard(&explo, 0);
  draw_hard_map();
  sp_script(&explo, "b-duck");

  wait(500);
  say_stop("`5There, I made you a duck.", &current_sprite);
  wait(200);
  say_stop("ALRIGHT! Beheading time..", 1);
  wait(200);
  say_Stop("`5You said nothing of beheading.. just that a duck doesn't exist anywhere here..", &current_sprite);
  say_stop("`5This duck can not be beheaded, and it is not alive as such.", &current_sprite);
  say_stop("`5You can move it around tho if you want.", &current_sprite);
  say_stop("`5To learn the different ways to move things, go North and talk to wizard Phisbo.", &current_sprite);
  wait(200);
  say_stop("Well, this is no fun.", 1);
  &bluedyseq = 2;
  editor_seq(&bluedyvar, &bluedyseq);
 }
 else
 {
  say_stop("Didn't help me much.. just made me a useless un-beheadable duck..", &current_sprite);
  wait(200);
  say_stop("`5be grateful! You can move it around!", &current_sprite);
  say_stop("`5To learn the different ways to move things, go North and talk to wizard Phisbo.", &current_sprite);
 }
 unfreeze(1);
 unfreeze(&current_sprite);
} 
 