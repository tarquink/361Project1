#include <stdio.h>
#include <stdlib.h>

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

void calcFreq(float found[], char fname[]){
 FILE *file;
 char message[200];
 int i = 0;
 file = fopen(fname, "r");
 
 if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
 }
  
  while(fscanf(file, " %c", &found[i])!=EOF){
   i++
  }
}