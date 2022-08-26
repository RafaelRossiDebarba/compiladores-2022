#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 255
#define DEBUG 0

void number_start(char word[TAM]);
void number_q0(int counter, char word[TAM]);
void number_q1(int counter, char word[TAM]);
void number_q2(int counter, char word[TAM]);
void number_q3(int counter, char word[TAM]);
void number_q4(int counter, char word[TAM]);

void err();
void finish(char word[TAM]);

void bin_start(char word[TAM]);
void bin_q0(int counter, char word[TAM]);
void bin_q1(int counter, char word[TAM]);
void bin_q2(int counter, char word[TAM]);

void hex_start(char word[TAM]);
void hex_q0(int counter, char word[TAM]);
void hex_q1(int counter, char word[TAM]);
void hex_q2(int counter, char word[TAM]);

int NEXT = 1;

int main() {
  FILE *pont_arq;
  char c, word[TAM], *aux;
  int position;

  pont_arq = fopen("numeros.txt","r");
  if (pont_arq == NULL)
  {
    printf("Erro ao tentar abrir o arquivo!");
    return EXIT_FAILURE;
  }

  do {
    memset(word, 0, sizeof word);
    position = 0;
    int check = 0;
    do {
      c = fgetc(pont_arq);
      if(c == EOF) {
        break;
      }
      aux = &c;
      if(c != '\n' && c != ' ' && c != ';') {
        word[position] = c;
        position++;
      }

      if(c == '\n') {
        check = 1;
      }

    } while(check == 0);

    if(DEBUG)
      printf("---------\n");
    
    hex_start(word);
    if(NEXT)
      bin_start(word);
    if(NEXT)
      number_start(word);
    
    if(NEXT) {
      printf("não reconhecido ");
      for(int i = 0; i < TAM; i++) {
        printf("%c", word[i]);
      }
      printf("\n");
    }
    
    NEXT = 1;

  } while (c != EOF);

  return(0);
}

void number_start(char word[TAM]) {
  int counter = 0;
  number_q0(counter, word);
}

void number_q0(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '1') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '2') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '3') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '4') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '5') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '6') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '7') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '8') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '9') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '.') {
      number_q2( ++counter, word);
    }
    else if(word[counter] == '+') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '-') {
      number_q1( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("number_q0 %c\n", word[counter]);
      err();
    }
  }
}

void number_q1(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '1') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '2') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '3') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '4') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '5') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '6') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '7') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '8') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '9') {
      number_q1( ++counter, word);
    }
    else if(word[counter] == '.') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == 'e') {
      number_q4( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("number_q1 %c\n", word[counter]);
      err();
    }
  }
}

void number_q2(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '1') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '2') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '3') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '4') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '5') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '6') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '7') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '8') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '9') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == 'e') {
      number_q4( ++counter, word);
    }
    else {
      if(DEBUG)
        printf("number_q2 %c\n", word[counter]);
      err();
    }
  }
}

void number_q3(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '1') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '2') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '3') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '4') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '5') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '6') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '7') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '8') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == '9') {
      number_q3( ++counter, word);
    }
    else if(word[counter] == 'e') {
      number_q4( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("number_q3 %c\n", word[counter]);
      err();
    }
  }
}

void number_q4(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '1') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '2') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '3') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '4') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '5') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '6') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '7') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '8') {
      number_q4( ++counter, word);
    }
    else if(word[counter] == '9') {
      number_q4( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("number_q4 %c\n", word[counter]);
      err();
    }
  }
}

void bin_start(char word[TAM]) {
  int counter = 0;
  bin_q0(counter, word);
}

void bin_q0(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      bin_q1( ++counter, word);
    }
    else {
      if(DEBUG)
        printf("bin_q0 %c\n", word[counter]);
      err();
    }
  }
}

void bin_q1(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == 'b') {
      bin_q2( ++counter, word);
    }
    else {
      if(DEBUG)
        printf("bin_q1 %c\n", word[counter]);
      err();
    }
  }
}

void bin_q2(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      bin_q2( ++counter, word);
    }
    else if(word[counter] == '1') {
      bin_q2( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("bin_q2 %c\n", word[counter]);
      err();
    }
  }
}

void hex_start(char word[TAM]) {
  int counter = 0;
  hex_q0(counter, word);
}

void hex_q0(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      hex_q1( ++counter, word);
    }
    else {
      if(DEBUG)
        printf("hex_q0 %c\n", word[counter]);
      err();
    }
  }
}

void hex_q1(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == 'x') {
      hex_q2( ++counter, word);
    }
    else {
      if(DEBUG)
        printf("hex_q1 %c\n", word[counter]);
      err();
    }
  }
}

void hex_q2(int counter, char word[TAM]) {
  if(counter < TAM) {
    if(word[counter] == '0') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '1') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '2') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '3') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '4') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '5') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '6') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '7') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '8') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == '9') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'a') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'b') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'c') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'd') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'e') {
      hex_q2( ++counter, word);
    }
    else if(word[counter] == 'f') {
      hex_q2( ++counter, word);
    }
    else if(!word[counter]) {
      finish(word);
    }
    else {
      if(DEBUG)
        printf("hex_q2 %c\n", word[counter]);
      err();
    }
  }
}

void err() {
  NEXT = 1;
}

void finish(char word[TAM]) {
  for(int i = 0; i < TAM; i++) {
    printf("%c", word[i]);
  }
  printf("\n");
  NEXT = 0;
}