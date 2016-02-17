#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void readFreq (float[], char[]);
void calcFreq (float[], char[]);
char rotate (char, int);
int findKet (float[], float[]);
void decrypt (int, char[]);


int main(){
  float freq[26];
  readFreq(freq, "/home/kevin/Documents/361/361Project1/LetFreq.txt");
  
  return 0;
}

// Load array given with the letter frequencies for English from file LetFreq.txt
void readFreq(float given[], char fname[]){
  FILE *file;
  
  char ch;
  int i = 0;
  
  file = fopen(fname, "r");
  
  if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
  }
  
  for(i=0; i<26; i++){
    fscanf(file," %c%f", &ch, &given[i]);
  }
  
  fclose(file);
}

// Read the encoded text from an input file and accumulate the letter frequency                  
// data for the encoded text. Store the frequency data in array found.
void calcFreq(float found[], char fname[]){
 FILE *file;
 char message[100];
 int i = 0;
 float messageFreq[26];
 float total = 0.0;
 
 file = fopen(fname, "r");
 
 if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
 }
  
  while(fscanf(file, " %c", &message[i])!=EOF){
   i++;
  }
  
  i = 0;
  while(message[i] != '\0'){
    if(tolower(message[i]) >= 'a' && tolower(message[i]) <= 'z'){
      messageFreq[message[i] - 'a']++;
    }
    i++;
  }
  
  for(i=0; i < 26; i++){
    total = total + messageFreq[i];
  }
  
  for(i=0; i < 26; i++){
    messageFreq[i] = messageFreq[i]/total;
  }
  
  fclose(file);
}