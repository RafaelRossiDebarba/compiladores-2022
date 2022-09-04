#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 255
#define DEBUG 1

#define CODE_NUMBER 1
#define CODE_BIN 2
#define CODE_HEX 3
#define CODE_OPEN_KEYS 4  // {
#define CODE_CLOSE_KEYS 5 // }

void read_file();
void add_current_in_word();
void print_word();

void number_q0();
void number_q1();
void number_q2();
void number_q3();
void number_q4();

void err();
void finish(char word[TAM]);

void bin_q1();

void hex_q1();

char CURRENT, NEXT;
char WORD[TAM];
int POSITION;
FILE *PONT_ARQ;
int CONTINUE = 1;
int LINE = 0;

int main()
{
  char *aux;

  PONT_ARQ = fopen("numeros.txt", "r");
  if (PONT_ARQ == NULL)
  {
    printf("Erro ao tentar abrir o arquivo!");
    return EXIT_FAILURE;
  }

  NEXT = ' ';

  do
  {
    if (CONTINUE == 0)
    {
      break;
    }
    // memset(WORD, 0, sizeof WORD);
    for (int i = 0; i < TAM; i++)
    {
      WORD[i] = '\0';
    }
    POSITION = 0;

    read_file();
    if (CURRENT == EOF || CURRENT == '\0')
    {
      break;
    }
    if (isalpha(CURRENT))
    {
      printf("alf\n");
    }
    else if (CURRENT == '\n')
    {
      LINE++;
    }
    else if (CURRENT == '{')
    {
      printf("%d\n", CODE_OPEN_KEYS);
    }
    else if (CURRENT == '}')
    {
      printf("%d\n", CODE_CLOSE_KEYS);
    }
    else if (CURRENT == '0')
    {
      if (NEXT == 'b')
      {
        WORD[POSITION] = '0';
        WORD[POSITION + 1] = 'b';
        POSITION += 2;
        read_file();
        bin_q1();
      }
      else if (NEXT == 'x')
      {
        WORD[POSITION] = '0';
        WORD[POSITION + 1] = 'x';
        POSITION += 2;
        read_file();
        hex_q1();
      }
      else
      {
        add_current_in_word();
        number_q1();
      }
    }
    else if (CURRENT == '1' || CURRENT == '2' || CURRENT == '3' || CURRENT == '4' || CURRENT == '5' ||
             CURRENT == '6' || CURRENT == '7' || CURRENT == '8' || CURRENT == '9' || CURRENT == '+' ||
             CURRENT == '-' )
    {
      add_current_in_word();
      number_q1();
    }
    else if (CURRENT == '.')
    {
      add_current_in_word();
      number_q2();
    }
  } while (NEXT != EOF && CONTINUE);

  return (0);
}

void read_file()
{
  CURRENT = NEXT;
  NEXT = fgetc(PONT_ARQ);
  if (NEXT == EOF)
    CONTINUE = 0;
}

void add_current_in_word()
{
  WORD[POSITION] = CURRENT;
  POSITION++;
}

void number_q1()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1' || CURRENT == '2' || CURRENT == '3' ||
      CURRENT == '4' || CURRENT == '4' || CURRENT == '5' || CURRENT == '6' ||
      CURRENT == '7' || CURRENT == '8' || CURRENT == '9')
  {
    add_current_in_word();
    number_q1();
  }
  else if (CURRENT == '.')
  {
    add_current_in_word();
    number_q3();
  }
  else if (CURRENT == 'e')
  {
    add_current_in_word();
    number_q4();
  }
  else if (CURRENT == ' ' || CURRENT == ';' || CURRENT == ',')
  {
    printf("%d\n", CODE_NUMBER);
  }
  else
  {
    if (DEBUG)
      printf("number_q1\n");
    err();
  }
}

void number_q2()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1' || CURRENT == '2' || CURRENT == '3' ||
      CURRENT == '4' || CURRENT == '4' || CURRENT == '5' || CURRENT == '6' ||
      CURRENT == '7' || CURRENT == '8' || CURRENT == '9')
  {
    add_current_in_word();
    number_q3();
  }
  else if (CURRENT == 'e')
  {
    add_current_in_word();
    number_q4();
  }
  else
  {
    if (DEBUG)
      printf("number_q2\n");
    err();
  }
}

void number_q3()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1' || CURRENT == '2' || CURRENT == '3' ||
      CURRENT == '4' || CURRENT == '4' || CURRENT == '5' || CURRENT == '6' ||
      CURRENT == '7' || CURRENT == '8' || CURRENT == '9')
  {
    add_current_in_word();
    number_q3();
  }
  else if (CURRENT == 'e')
  {
    number_q4();
  }
  else if (CURRENT == ' ' || CURRENT == ';' || CURRENT == ',')
  {
    printf("%d\n", CODE_NUMBER);
  }
  else
  {
    if (DEBUG)
      printf("number_q3\n");
    err();
  }
}

void number_q4()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1' || CURRENT == '2' || CURRENT == '3' ||
      CURRENT == '4' || CURRENT == '4' || CURRENT == '5' || CURRENT == '6' ||
      CURRENT == '7' || CURRENT == '8' || CURRENT == '9')
  {
    add_current_in_word();
    number_q4();
  }
  else if (CURRENT == ' ' || CURRENT == ';' || CURRENT == ',')
  {
    printf("%d\n", CODE_NUMBER);
  }
  else
  {
    if (DEBUG)
      printf("number_q4\n");
    err();
  }
}

void bin_q1()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1')
  {
    add_current_in_word();
    bin_q1();
  }
  else if (CURRENT == ' ' || CURRENT == ';' || CURRENT == ',')
  {
    printf("%d\n", CODE_BIN);
  }
  else
  {
    if (DEBUG)
      printf("bin_q1 CURRENT %s NEXT %s\n", CURRENT, NEXT);
    err();
  }
}

void hex_q1()
{
  read_file();
  if (CURRENT == '0' || CURRENT == '1' || CURRENT == '2' || CURRENT == '3' || CURRENT == '4' || CURRENT == '5' ||
      CURRENT == '6' || CURRENT == '7' || CURRENT == '8' || CURRENT == '9' || CURRENT == 'a' || CURRENT == 'b' ||
      CURRENT == 'c' || CURRENT == 'd' || CURRENT == 'e' || CURRENT == 'f')
  {
    add_current_in_word();
    hex_q1();
  }
  else if (CURRENT == ' ' || CURRENT == ';' || CURRENT == ',')
  {
    printf("%d\n", CODE_HEX);
  }
  else
  {
    if (DEBUG)
      printf("hex_q1\n");
    err();
  }
}

void err()
{
  printf("ERR\n");
  CONTINUE = 0;
  if (DEBUG)
  {
    print_word();
    printf("Current %c NEXT %c\n", CURRENT, NEXT);
  }
}

void print_word()
{
  for (int i = 0; i < TAM; i++)
  {
    printf("%c", WORD[i]);
  }
  printf("\n");
}
