#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int toBase27(std::string trigram);

int main(int argc, char *argv[]) {
  //Value should be 6094 (it is)
  std::cout << toBase27("his") << std::endl;
  return 0;
}

//Subtract by 96 (would be 97 but reduced by 1 to account for spaces) in order to change ascii decimal value to specified format
int toBase27(std::string trigram){
  /*Loop checks all chars of the trigram and assigns all spaces to "'" (grave accent) because "'" equals 96, and since our text files
  have all the "'" chars removed, we can safely replace spaces with "'" so that when subtraced by 96, it will represent 0.
  This method seems crude, as if punctuation needs to be later rewritten in to this problem this would not work, but thankfully
  that is not the case and this simple method can be used.
  */
  for (int i=0;i<3; i++ ) {
    if(trigram[i] == ' ')
      trigram[i] = '`';
}
  return (((int)trigram[0]-96)*729)+(((int)trigram[1]-96)*27)+(int)trigram[2]-96;
}
