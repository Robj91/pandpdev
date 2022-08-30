void main(void)
{
 sp_brain(&current_sprite, 20);
 
 int &spritevar = sp_editor_num(&current_sprite);
 editor_type(&spritevar, 0);
 int &spriteseq = editor_seq(&spritevar, -1);
 
 if (&spriteseq == 0)
 {
  say("`%X Marks the spot!", &current_sprite);
  return;
 }
}

void talk(void)
{
 &spriteseq = editor_seq(&spritevar, -1);
 if (&spriteseq == 0)
 {
  say("`%X Marks the spot!", &current_sprite);
  return;
 }
 else
 {
  say("`%Conragrutations! You did it!", &current_sprite);
 }
}