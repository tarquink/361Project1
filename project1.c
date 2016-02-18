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
  int key;
  
  readFreq(freq, "/home/kevin/Documents/361/361Project1/LetFreq.txt");
  calcFreq(messagefreq, "/home/kevin/Documents/361/361Project1/test.txt");
  key = findKey(freq, messagefreq);
  
  if(key != 0)
    decrypt(key, "/home/kevin/Documents/361/361Project1/test.txt");
  
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
    if(tolower(message[i]) >= 'a' && tolower((unsigned char)message[i]) <= 'z'){
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
  float dif[26], data[26];
  int i, n;
  char ch;
  float totalMin = 0, minShift =0, total = 0, smallest = 0;
  
  for(i=0; i < 26; i++){
    dif[i] = 0;
    data[i] = 0;
  }
  
  for(i=0; i < 26; i++){
    
    total = 0;
    
    for(n=0; n<26 ; n++){
      
      dif[n] = ((given[n]-found[(n+i)%26])*(given[n]-found[(n+i)%26]));
      total += dif[n];
      
      /*
      ch = rotate(n+'a',i);
      data[n] = (found[ch-'a'] - given[ch-'a']);
      data[n] = data[n] * data[n];
      total = total + data[n];
      */
    }
    
    if(dif[i] < smallest){
      smallest = total;
      minShift = i;
    }
    
    //dif[i] = total;
    //total = 0;
  }
  

  
  return minShift;
}

// Decrypt the encoded text in the input file using the key and display the decoded text
void decrypt (int key, char fname[]){
 FILE *file;
 char message[100];
 int i = 0;
 
 
 file = fopen(fname, "r");
 
 if(file == NULL){
    printf("FILE READ ERROR\n");
    exit(0);
 }
 
 while(fscanf(file, "%c", &message[i])!=EOF){
   i++;
  }
  
  for(i = 0; i < 100; i++){
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