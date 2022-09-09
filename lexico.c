#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 255
#define DEBUG 1

#define CODE_AUTO 100
#define CODE_VOID 129
#define CODE_BREAK 101
#define CODE_CONTINUE 105
#define CODE_DEFAULT 106
#define CODE_FOR 113
#define CODE_DO 107
#define CODE_WHILE 131
#define CODE_IF 115
#define CODE_ELSE 109
#define CODE_SWITCH 125
#define CODE_CASE 102
#define CODE_ENUM 110
#define CODE_EXTERN 111
#define CODE_GOTO 114
#define CODE_REGISTER 118
#define CODE_RETURN 119
#define CODE_SIGNED 121
#define CODE_SIZEOF 122
#define CODE_STATIC 123
#define CODE_STRUCT 124
#define CODE_TYPEDEF 126
#define CODE_UNION 127
#define CODE_VOLATILE 130
#define CODE_PACKED 132
#define CODE_CONST 104
#define CODE_UNSIGNED 128
#define CODE_CHAR 103
#define CODE_SHORT 120
#define CODE_INT 116
#define CODE_LONG 117
#define CODE_FLOAT 112
#define CODE_DOUBLE 108
#define CODE_VARIABLE_FUNCTION 136
#define CODE_NUMBER 135
#define CODE_BIN 133
#define CODE_HEX 134
#define CODE_OPEN_KEYS 5                // {
#define CODE_CLOSE_KEYS 6               // }
#define CODE_OPEN_PARENTHESES 7         // (
#define CODE_CLOSE_PARENTHESES 8        // )
#define CODE_OPEN_SQUARE_BRACKETS 9     // [
#define CODE_CLOSE_SQUARE_BRACKETS 10   // ]
#define CODE_PLUS 11                    // +
#define CODE_PLUS_PLUS 12               // ++
#define CODE_PLUS_EQUAL 13              // +=
#define CODE_LESS 14                    // -
#define CODE_LESS_LESS 15               // --
#define CODE_LESS_EQUAL 16              // -=
#define CODE_MULT 18                    // *
#define CODE_MULT_EQUAL 19              // *=
#define CODE_DIV 20                     // /
#define CODE_DIV_EQUAL 21               // /=
#define CODE_INV 25                     // !
#define CODE_DIFFERENT 26               // !=
#define CODE_RECEIVE 27                 // =
#define CODE_EQUAL 28                   // ==
#define CODE_SMALLER 29                 // <
#define CODE_LESSER_EQUAL 30            // <=
#define CODE_MORE 32                    // >
#define CODE_MORE_EQUAL 33              // >=
#define CODE_AND 38                     // &&
#define CODE_E 37                       // &
#define CODE_OR 36                      // ||
#define CODE_ESC 35                     // |
#define CODE_STRING 137
#define CODE_VALUE_CHAR 138
#define CODE_SMALLER_SMALLER 31         // <<
#define CODE_MORE_MORE 34               // >>
#define CODE_DOTE 4                     // .
#define CODE_SEMICOLON 1                // ;
#define CODE_COMMA 2                    // ,
#define CODE_TWO_POINTS 3               // :
#define CODE_RASH 17                    // #
#define CODE_PERCENTAGE 22              // %
#define CODE_PERCENTAGE_EQUAL 23        // %=
#define CODE_EXCLAMATION 24             // ?

void read_file();
void add_current_in_word();
void print_word();
int reserved_word(char word[TAM]);

void number_q0();
void number_q1();
void number_q2();
void number_q3();
void number_q4();

void words_q1();
void words_string();
void words_char();

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
int NOT_READ = 0;

int main()
{
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

    if (NOT_READ == 0)
      read_file();
    NOT_READ = 0;
    
    if (CURRENT == EOF || CURRENT == '\0')
    {
      break;
    }
    switch(CURRENT)
    {
      case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm':
      case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
      case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M':
      case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
      case '_':
        add_current_in_word();
        words_q1();
        break;
      case '\n':
        LINE++;
        break;
      case '0':
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
        break;
        case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          add_current_in_word();
          number_q1();
          break;
        case ';':
          printf("%d\n", CODE_SEMICOLON);
          break;
        case ',':
          printf("%d\n", CODE_COMMA);
          break;
        case ':':
          printf("%d\n", CODE_TWO_POINTS);
          break;
        case '.':
          if(NEXT >= 48 && NEXT <= 57) // 1 a 9
          {
            add_current_in_word();
            number_q2();
          }
          else // .
          {
            printf("%d\n", CODE_DOTE);
          }
          break;
        case '{':
          printf("%d\n", CODE_OPEN_KEYS);
          break;
        case '}':
          printf("%d\n", CODE_CLOSE_KEYS);
          break;
        case '(':
          printf("%d\n", CODE_OPEN_PARENTHESES);
          break;
        case ')':
          printf("%d\n", CODE_CLOSE_PARENTHESES);
          break;
        case '[':
          printf("%d\n", CODE_OPEN_SQUARE_BRACKETS);
          break;
        case ']':
          printf("%d\n", CODE_CLOSE_SQUARE_BRACKETS);
          break;
        case '+':
          if(NEXT == '+') // ++
          {
            read_file();
            printf("%d\n", CODE_PLUS_PLUS);
          }
          else if (NEXT == '=') // +=
          {
            read_file();
            printf("%d\n", CODE_PLUS_EQUAL);
          }
          else if (NEXT >= 48 && NEXT <= 57) // + 0 a 9
          {
            number_q1();
          }
          else // +
          {
            printf("%d\n", CODE_PLUS);
          }
          break;
        case '-':
          if(NEXT == '-') // --
          {
            read_file();
            printf("%d\n", CODE_LESS_LESS);
          }
          else if (NEXT == '=') // -=
          {
            read_file();
            printf("%d\n", CODE_LESS_EQUAL);
          }
          else if (NEXT >= 48 && NEXT <= 57) // - 0 a 9
          {
            number_q1();
          }
          else // -
          {
            printf("%d\n", CODE_LESS_LESS);
          }
          break;
        case '#':
          printf("%d\n", CODE_RASH);
          break;
        case '*':
          if (NEXT == '=') // *=
          {
            read_file();
            printf("%d\n", CODE_MULT_EQUAL);
          }
          else // *
          {
            printf("%d\n", CODE_MULT);
          }
          break;
        case '/':
          if(NEXT == '=') // /=
          {
            read_file();
            printf("%d\n", CODE_DIV_EQUAL);
          }
          else // /
          {
            printf("%d\n", CODE_DIV);
          }
          break;
        case '%':
          if(NEXT == '=') // %=
          {
            printf("%d\n", CODE_PERCENTAGE_EQUAL);
          }
          else // %
          {
            printf("%d\n", CODE_PERCENTAGE);
          }
          break;
        case '?':
          printf("%d\n", CODE_EXCLAMATION);
          break;
        case '!':
          if (NEXT == '=') // !=
          {
            read_file();
            printf("%d\n", CODE_DIFFERENT);
          }
          else // !
          {
            printf("%d\n", CODE_INV);
          }
          break;
        case '=':
          if(NEXT == '=') // ==
          {
            read_file();
            printf("%d\n", CODE_RECEIVE);
          }
          else { // =
            printf("%d\n", CODE_EQUAL);
          }
          break;
        case '<':
          if (NEXT == '=') // <=
          {
            read_file();
            printf("%d\n", CODE_LESSER_EQUAL);
          }
          else
          {
            if(NEXT == '<') // <<
            {
              printf("%d\n", CODE_SMALLER_SMALLER); 
            }
            else // <
            {
              printf("%d\n", CODE_SMALLER); 
            }
          }
          break;
        case '>':
          if (NEXT == '=') // >=
          {
            read_file();
            printf("%d\n", CODE_MORE_EQUAL);
          }
          else
          {
            if(NEXT == '>') // >>
            {
              printf("%d\n", CODE_MORE_MORE); 
            }
            else // >
            {
              printf("%d\n", CODE_MORE); 
            }
          }
          break;
        case '|':
          if(NEXT == '|') // ||
          {
            printf("%d\n", CODE_OR);
          }
          else // |
          {
            printf("%d\n", CODE_ESC);
          }
          break;
        case '&':
          if(NEXT == '&') // &&
          {
            printf("%d\n", CODE_AND);
          }
          else // &
          {
            printf("%d\n", CODE_E);
          }
          break;
        case '\'':
          words_char();
          break;
        case '\"':
          words_string();
          break;
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
  if (NEXT == '0' || NEXT == '1' || NEXT == '2' || NEXT == '3' ||
      NEXT == '4' || NEXT == '4' || NEXT == '5' || NEXT == '6' ||
      NEXT == '7' || NEXT == '8' || NEXT == '9')
  {
    read_file();
    add_current_in_word();
    number_q1();
  }
  else if (NEXT == '.')
  {
    read_file();
    add_current_in_word();
    number_q3();
  }
  else if (NEXT == 'e')
  {
    read_file();
    add_current_in_word();
    number_q4();
  }
  else if (NEXT == ' ' || NEXT == ';' || NEXT == ',' ||
           NEXT == ']' || NEXT == ')' || NEXT == '\n')
  {
    printf("%d\n", CODE_NUMBER);
    print_word();
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
  if (NEXT == '0' || NEXT == '1' || NEXT == '2' || NEXT == '3' ||
      NEXT == '4' || NEXT == '4' || NEXT == '5' || NEXT == '6' ||
      NEXT == '7' || NEXT == '8' || NEXT == '9')
  {
    read_file();
    add_current_in_word();
    number_q3();
  }
  else if (NEXT == 'e')
  {
    read_file();
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
  if (NEXT == '0' || NEXT == '1' || NEXT == '2' || NEXT == '3' ||
      NEXT == '4' || NEXT == '4' || NEXT == '5' || NEXT == '6' ||
      NEXT == '7' || NEXT == '8' || NEXT == '9')
  {
    read_file();
    add_current_in_word();
    number_q3();
  }
  else if (NEXT == 'e')
  {
    read_file();
    number_q4();
  }
  else if (NEXT == ' ' || NEXT == ';' || NEXT == ',' ||
           NEXT == ']' || NEXT == ')' )
  {
    printf("%d\n", CODE_NUMBER);
    print_word();
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
  if (NEXT == '0' || NEXT == '1' || NEXT == '2' || NEXT == '3' ||
      NEXT == '4' || NEXT == '4' || NEXT == '5' || NEXT == '6' ||
      NEXT == '7' || NEXT == '8' || NEXT == '9')
  {
    read_file();
    add_current_in_word();
    number_q4();
  }
  else if (NEXT == ' ' || NEXT == ';' || NEXT == ',')
  {
    printf("%d\n", CODE_NUMBER);
    print_word();
  }
  else
  {
    if (DEBUG)
      printf("number_q4\n");
    err();
  }
}

void words_q1()
{
  read_file();
  if(isalpha(CURRENT) || CURRENT == '_' || CURRENT == '1' || CURRENT == '2' ||
       CURRENT == '3' || CURRENT == '4' || CURRENT == '5' || CURRENT == '6' ||
       CURRENT == '7' || CURRENT == '8' || CURRENT == '9' || CURRENT == '0')
  {
    add_current_in_word();
    words_q1();
  }
  else
  {
    NOT_READ = 1;
    int aux = reserved_word(WORD);
    switch (aux)
    {
      case 1:
        printf("%d\n", CODE_AUTO);
        break;
      case 2:
        printf("%d\n", CODE_BREAK);
        break;
      case 3:
        printf("%d\n", CODE_CASE);
        break;
      case 4:
        printf("%d\n", CODE_CHAR);
        break;
      case 5:
        printf("%d\n", CODE_CONST);
        break;
      case 6:
        printf("%d\n", CODE_CONTINUE);
        break;
      case 7:
        printf("%d\n", CODE_DEFAULT);
        break;
      case 8:
        printf("%d\n", CODE_DO);
        break;
      case 9:
        printf("%d\n", CODE_DOUBLE);
        break;
      case 10:
        printf("%d\n", CODE_ELSE);
        break;
      case 11:
        printf("%d\n", CODE_ENUM);
        break;
      case 12:
        printf("%d\n", CODE_EXTERN);
        break;
      case 13:
        printf("%d\n", CODE_FLOAT);
        break;
      case 14:
        printf("%d\n", CODE_FOR);
        break;
      case 15:
        printf("%d\n", CODE_GOTO);
        break;
      case 16:
        printf("%d\n", CODE_IF);
        break;
      case 17:
        printf("%d\n", CODE_INT);
        break;
      case 18:
        printf("%d\n", CODE_LONG);
        break;
      case 19:
        printf("%d\n", CODE_REGISTER);
        break;
      case 20:
        printf("%d\n", CODE_RETURN);
        break;
      case 21:
        printf("%d\n", CODE_SHORT);
        break;
      case 22:
        printf("%d\n", CODE_SIGNED);
        break;
      case 23:
        printf("%d\n", CODE_SIZEOF);
        break;
      case 24:
        printf("%d\n", CODE_STATIC);
        break;
      case 25:
        printf("%d\n", CODE_STRUCT);
        break;
      case 26:
        printf("%d\n", CODE_SWITCH);
        break;
      case 27:
        printf("%d\n", CODE_TYPEDEF);
        break;
      case 28:
        printf("%d\n", CODE_UNION);
        break;
      case 29:
        printf("%d\n", CODE_UNSIGNED);
        break;
      case 30:
        printf("%d\n", CODE_VOID);
        break;
      case 31:
        printf("%d\n", CODE_VOLATILE);
        break;
      case 32:
        printf("%d\n", CODE_WHILE);
        break;
      case 33:
        printf("%d\n", CODE_PACKED);
        break;
      default:
        printf("%d\n", CODE_VARIABLE_FUNCTION);
    }
  }
}

void words_string()
{
  if(NEXT != '\"')
  {
    read_file();
    add_current_in_word();
    words_string();
  }
  else
  {
    read_file();
    printf("%d\n", CODE_STRING);
  }
}

void words_char()
{
  if(NEXT != '\'')
  {
    read_file();
    add_current_in_word();
    words_char();
  }
  else
  {
    read_file();
    printf("%d\n", CODE_VALUE_CHAR);
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

int reserved_word(char word[TAM])
{
  if (strcmp(word, "auto") == 0)
    return 1;
  else if (strcmp(word, "break") == 0)
    return 2;
  else if (strcmp(word, "case") == 0)
    return 3;
  else if (strcmp(word, "char") == 0)
    return 4;
  else if (strcmp(word, "const") == 0)
    return 5;
  else if (strcmp(word, "continue") == 0)
    return 6;
  else if (strcmp(word, "default") == 0)
    return 7;
  else if (strcmp(word, "do") == 0)
    return 8;
  else if (strcmp(word, "double") == 0)
    return 9;
  else if (strcmp(word, "else") == 0)
    return 10;
  else if (strcmp(word, "enum") == 0)
    return 11;
  else if (strcmp(word, "extern") == 0)
    return 12;
  else if (strcmp(word, "float") == 0)
    return 13;
  else if (strcmp(word, "for") == 0)
    return 14;
  else if (strcmp(word, "goto") == 0)
    return 15;
  else if (strcmp(word, "if") == 0)
    return 16;
  else if (strcmp(word, "int") == 0)
    return 17;
  else if (strcmp(word, "long") == 0)
    return 18;
  else if (strcmp(word, "register") == 0)
    return 19;
  else if (strcmp(word, "return") == 0)
    return 20;
  else if (strcmp(word, "short") == 0)
    return 21;
  else if (strcmp(word, "signed") == 0)
    return 22;
  else if (strcmp(word, "sizeof") == 0)
    return 23;
  else if (strcmp(word, "static") == 0)
    return 24;
  else if (strcmp(word, "struct") == 0)
    return 25;
  else if (strcmp(word, "switch") == 0)
    return 26;
  else if (strcmp(word, "typedef") == 0)
    return 27;
  else if (strcmp(word, "union") == 0)
    return 28;
  else if (strcmp(word, "unsigned") == 0)
    return 29;
  else if (strcmp(word, "void") == 0)
    return 30;
  else if (strcmp(word, "volatile") == 0)
    return 31;
  else if (strcmp(word, "while") == 0)
    return 32;
  else if (strcmp(word, "_Packed") == 0)
    return 33;
  return 0;
}