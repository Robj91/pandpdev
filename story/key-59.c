void main(void)
{
 //F2 button - FreeDink
 int &check = 0;
 int &val1;
loop:
 &check = get_next_sprite_with_this_brain(0, 0, &check);
 if (&check > 0)
 {
  &val1 = sp_gold(&check, -1);
  if (&val1 == 999)
  {
   sp_gold(&check, 1096);
  }
  
  &check += 1;
  goto loop;
 }
 
 kill_this_task();
}