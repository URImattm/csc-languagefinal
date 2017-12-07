//Author: Matthew Mayers/Julio Molina

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

int toBase27(std::string trigram);
std::vector<std::string> pullTrigramsFromSequence(std::string sequence);
std::vector<int> toFreqVector(std::string fileDir);
double findCosineSimilarity(std::vector <int> originalSequence, std::vector <int> possibleSequence);

int main(int argc, char *argv[]){
  std::string testFileDir = argv[argc-1];
  std::string testSequence;
  std::ifstream infile;
  std::string closestMatchName = "None.";
  double closestMatchValue = 0.0;
  infile.open(testFileDir.c_str());
  std::getline(infile,testSequence);
  infile.close();
  for(int i = 1;i<(argc-1);i++){
    if(findCosineSimilarity(toFreqVector(testFileDir),toFreqVector(argv[i]))>closestMatchValue){
      closestMatchValue = findCosineSimilarity(toFreqVector(testFileDir),toFreqVector(argv[i]));
      closestMatchName = argv[i];
    }
  }
  std::cout << closestMatchName << std::endl;
  return 0;
  }

  double findCosineSimilarity(std::vector <int> originalSequence, std::vector <int> possibleSequence){
      double upper = 0.0;
      double lower_a = 0.0;
      double lower_b = 0.0;
      for(int i = 0; i < (int)originalSequence.size(); i++) {
        upper += originalSequence[i] * possibleSequence[i];
        lower_a += originalSequence[i] * originalSequence[i];
        lower_b += possibleSequence[i] * possibleSequence[i];
      }
      return (upper / (sqrt(lower_a) * sqrt(lower_b)));
  }

std::vector<int> toFreqVector(std::string fileDir) {
  std::string fileSequence;
  std::ifstream infile;
  infile.open(fileDir.c_str());
  std::getline(infile,fileSequence);
  infile.close();
  std::vector<std::string>vectorOfTrigrams = pullTrigramsFromSequence(fileSequence);
  std::vector<int>frequencyVector;
  for(int i=0;i<19683;i++){
    frequencyVector.push_back(0);
  }
  for(int i=0;i<(int)vectorOfTrigrams.size();i++)
    frequencyVector[toBase27(vectorOfTrigrams[i])] += 1;
  return frequencyVector;
}

//Takes a trigram string and outputs its corresponding base27 value
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

//Loops through the raw sequence and gets the trigram frequencies from a string
std::vector<std::string> pullTrigramsFromSequence(std::string sequence){
  std::vector<std::string> trigramVector;
  int seqlen = sequence.length();
  for(int i=2;i<seqlen;i++){
    std::string currentTrigram = "";
    currentTrigram += sequence[i-2];
    currentTrigram += sequence[i-1];
    currentTrigram += sequence[i];
    trigramVector.push_back(currentTrigram);
  }
	return trigramVector;
}
