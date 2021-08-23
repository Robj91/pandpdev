void main(void)
{
 &save_x = editor_seq(9, -1);
 if (&save_x == 1)
 {
  &save_x = create_sprite(318, 233, 0, 169, 1);
  sp_seq(&save_x, 169);
  sp_brain(&save_x, 6);
  sp_script(&save_x, "stairs4");   
 }
}

void talk(void)
{
 &save_x = editor_seq(9, -1);
 if (&save_x == 1)
 {
  say("`%...", &current_sprite);
  return;
 }

 freeze(1);
 say_stop("`%Offering of the unkown.", &current_sprite);
 say_stop("`%The first element is Red.", &current_sprite);
 say_stop("`%The second element is Yellow", &current_sprite);
 say_stop("`%The third element is Purple", &current_sprite);
 say_stop("`%The fourth element is Green", &current_sprite);
 wait(200);
 say_stop("Um... what?", 1);
 unfreeze(1);
}

void puzzle(void)
{ 
 &save_x = editor_seq(7, -1);
 if (&save_x == 1)
 {
  &save_x = editor_seq(6, -1);
  if (&save_x == 3)
  {
   &save_x = editor_seq(1, -1);
   if (&save_x == 4)
   {
    &save_x = editor_seq(11, -1);
    if (&save_x == 2)
    {
     //The scrolls are placed in the correct order!

     playsound(43, 22050,0,0,0);        
    
     &save_x = create_sprite(318, 232, 7, 167, 1);
     sp_seq(&save_x, 167);
     playsound(24, 22052, 0, 0, 0); 
     
     &save_x = create_sprite(318, 233, 0, 169, 1);
     sp_seq(&save_x, 169);
     sp_brain(&save_x, 6);
     sp_script(&save_x, "stairs4");   
     
     //set the current sprites editor seq to 1
     editor_seq(9, 1);       
    }
   }
  }
 }
}