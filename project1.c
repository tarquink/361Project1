// CIS 361 PROJECT 1 KEVIN TARQUINIO


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void readFreq (float[], char[]);
void calcFreq (float[], char[]);
char rotate (char, int);
int findKey (float[], float[]);
void decrypt (int, char[]);


int main(){
  float freq[26];
  float messagefreq[26];
  float messagefreq2[26];
  int key;
  
  readFreq(freq, "/home/tarquink/361/361Project1/LetFreq.txt");
  calcFreq(messagefreq, "/home/tarquink/361/361Project1/test2.txt");
  
  key = findKey(freq, messagefreq);
  
  decrypt(key, "/home/tarquink/361/361Project1/test2.txt");
  
  calcFreq(messagefreq, "/home/tarquink/361/361Project1/test.txt");
  
  key = findKey(freq, messagefreq);
  
  decrypt(key, "/home/tarquink/361/361Project1/test.txt");
  
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
 char message[200];
 int i = 0;
 float messageFreq[26];
 float total = 0.0;
 
 file = fopen(fname, "r");
 
 if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
 }
  
  while(fscanf(file, "%c", &message[i])!=EOF){
   i++;
  }
  
  i = 0;
  while(i != 26){
   messageFreq[i] = 0.0;
   i++;
  }
  
  i = 0;
  while(message[i] != '\0'){
    if(tolower(message[i]) >= 'a' && tolower(message[i]) <= 'z'){
      messageFreq[tolower(message[i]) - 'a']++;
    }
    i++;
  }
    
  for(i=0; i < 26; i++){
    total = total + messageFreq[i];
  }
  
  for(i=0; i < 26; i++){
    found[i] = messageFreq[i]/total;
  }

  fclose(file);
}

// Rotate the character in parameter ch down the alphabet for the number of   
// positions as given in parameter num and return the resulting character.
char rotate ( char ch, int num ){
  if(isupper(ch)){
    ch = (((ch - 'A') + num) % 26) + 'A';
  }
  
  if(islower(ch)){
    ch = (((ch - 'a') + num) % 26) + 'a';
  }
  
  return ch;
}

// Compare the data in array found with the frequency data in array given, looking
// for a key that will give you the best match. To do this, try each of the 26 rotations,
// and remember which gives the smallest difference between the frequencies you
// observed and the frequencies given. Return the key.
int findKey ( float given[], float found[] ){

  int i, shift, minShift;
  float total, diff, minTotal, prevTotal;
  
  prevTotal = 5;
  minTotal = 0;

  for(shift = 0; shift < 26; shift++){
    
    total = 0;
    
    for( i=0 ; i<26 ; i++){
      diff = given[i]-(found[(i+shift)%26]);
      diff = diff * diff;
      total = total + diff;
      }
    
    if(total < prevTotal){
      prevTotal = total;  
      minTotal = total;
      minShift = shift;
    }


    }
    
    printf("The key is: %d\n", minShift);
    
    return 26 - minShift;

  }


// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt (int key, char fname[]){
 FILE *file;
 char message[200];
 int i = 0;
 
 file = fopen(fname, "r");
 
 if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
 }
 
 while(fscanf(file, "%c", &message[i])!= EOF){
   i++;
  }
  
  for(i = 0; i < 200; i++){
    if(islower(message[i]) || isupper(message[i])){    
      message[i] = rotate(message[i], key);
    }
  }
  
  i = 0;
  while(message[i] != '\0'){
    printf("%c",message[i]);
    i++;
  }
  
  printf("\n");
  
}
