#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM 255
#define DEBUG 1
#define TAM_ARRAY 200

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
#define CODE_DOT 4                      // .
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
int add_name(char word[TAM]);
int add_value(char word[TAM]);

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

void show_debug(int code);
void show_numbers();
void show_names();

char CURRENT, NEXT;
char WORD[TAM];
int POSITION;
FILE *PONT_ARQ;
int CONTINUE = 1;
int LINE = 0;
int NOT_READ = 0;
char **LIST_VAL;
char **LIST_NAMES;

int main()
{
  PONT_ARQ = fopen("numeros.txt", "r");
  if (PONT_ARQ == NULL)
  {
    printf("Erro ao tentar abrir o arquivo!");
    return EXIT_FAILURE;
  }

  LIST_VAL = calloc(TAM_ARRAY, sizeof(char[TAM]));
  LIST_NAMES = calloc(TAM_ARRAY, sizeof(char[TAM]));

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
          if(DEBUG)
            show_debug(CODE_SEMICOLON);
          else
            printf("%d\t%d\n", CODE_SEMICOLON, LINE);
          break;
        case ',':
          if(DEBUG)
            show_debug(CODE_COMMA);
          else
            printf("%d\t%d\n", CODE_COMMA, LINE);
          break;
        case ':':
          if(DEBUG)
            show_debug(CODE_TWO_POINTS);
          else
            printf("%d\t%d\n", CODE_TWO_POINTS, LINE);
          break;
        case '.':
          if(NEXT >= 48 && NEXT <= 57) // 1 a 9
          {
            add_current_in_word();
            number_q2();
          }
          else // .
          {
            if(DEBUG)
              show_debug(CODE_DOT);
            else
              printf("%d\t%d\n", CODE_DOT, LINE);
          }
          break;
        case '{':
          if(DEBUG)
            show_debug(CODE_OPEN_KEYS);
          else
            printf("%d\t%d\n", CODE_OPEN_KEYS, LINE);
          break;
        case '}':
          if(DEBUG)
            show_debug(CODE_CLOSE_KEYS);
          else
            printf("%d\t%d\n", CODE_CLOSE_KEYS, LINE);
          break;
        case '(':
          if(DEBUG)
            show_debug(CODE_OPEN_PARENTHESES);
          else
            printf("%d\t%d\n", CODE_OPEN_PARENTHESES, LINE);
          break;
        case ')':
          if(DEBUG)
            show_debug(CODE_CLOSE_PARENTHESES);
          else
            printf("%d\t%d\n", CODE_CLOSE_PARENTHESES, LINE);
          break;
        case '[':
          if(DEBUG)
            show_debug(CODE_OPEN_SQUARE_BRACKETS);
          else
            printf("%d\t%d\n", CODE_OPEN_SQUARE_BRACKETS, LINE);
          break;
        case ']':
          if(DEBUG)
            show_debug(CODE_CLOSE_SQUARE_BRACKETS);
          else
            printf("%d\t%d\n", CODE_CLOSE_SQUARE_BRACKETS, LINE);
          break;
        case '+':
          if(NEXT == '+') // ++
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_PLUS_PLUS);
            else
              printf("%d\t%d\n", CODE_PLUS_PLUS, LINE);
          }
          else if (NEXT == '=') // +=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_PLUS_EQUAL);
            else
              printf("%d\t%d\n", CODE_PLUS_EQUAL, LINE);
          }
          else if (NEXT >= 48 && NEXT <= 57) // + 0 a 9
          {
            number_q1();
          }
          else // +
          {
            if(DEBUG)
              show_debug(CODE_PLUS);
            else
              printf("%d\t%d\n", CODE_PLUS, LINE);
          }
          break;
        case '-':
          if(NEXT == '-') // --
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_LESS_LESS);
            else
              printf("%d\t%d\n", CODE_LESS_LESS, LINE);
          }
          else if (NEXT == '=') // -=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_LESS_EQUAL);
            else
              printf("%d\t%d\n", CODE_LESS_EQUAL, LINE);
          }
          else if (NEXT >= 48 && NEXT <= 57) // - 0 a 9
          {
            number_q1();
          }
          else // -
          {
            if(DEBUG)
              show_debug(CODE_LESS);
            else
              printf("%d\t%d\n", CODE_LESS, LINE);
          }
          break;
        case '#':
          if(DEBUG)
            show_debug(CODE_RASH);
          else
            printf("%d\t%d\n", CODE_RASH, LINE);
          break;
        case '*':
          if (NEXT == '=') // *=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_MULT_EQUAL);
            else
              printf("%d\t%d\n", CODE_MULT_EQUAL, LINE);
          }
          else // *
          {
            if(DEBUG)
              show_debug(CODE_MULT);
            else
              printf("%d\t%d\n", CODE_MULT, LINE);
          }
          break;
        case '/':
          if(NEXT == '=') // /=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_DIV_EQUAL);
            else
              printf("%d\t%d\n", CODE_DIV_EQUAL, LINE);
          }
          else // /
          {
            if(DEBUG)
              show_debug(CODE_DIV);
            else
              printf("%d\t%d\n", CODE_DIV, LINE);
          }
          break;
        case '%':
          if(NEXT == '=') // %=
          {
            if(DEBUG)
              show_debug(CODE_PERCENTAGE_EQUAL);
            else
              printf("%d\t%d\n", CODE_PERCENTAGE_EQUAL, LINE);
          }
          else // %
          {
            if(DEBUG)
              show_debug(CODE_PERCENTAGE);
            else
              printf("%d\t%d\n", CODE_PERCENTAGE, LINE);
          }
          break;
        case '?':
          if(DEBUG)
            show_debug(CODE_EXCLAMATION);
          else
            printf("%d\t%d\n", CODE_EXCLAMATION, LINE);
          break;
        case '!':
          if (NEXT == '=') // !=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_DIFFERENT);
            else
              printf("%d\t%d\n", CODE_DIFFERENT, LINE);
          }
          else // !
          {
            if(DEBUG)
              show_debug(CODE_INV);
            else
              printf("%d\t%d\n", CODE_INV, LINE);
          }
          break;
        case '=':
          if(NEXT == '=') // ==
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_EQUAL);
            else
              printf("%d\t%d\n", CODE_EQUAL, LINE);
          }
          else { // =
            if(DEBUG)
              show_debug(CODE_RECEIVE);
            else
              printf("%d\t%d\n", CODE_RECEIVE, LINE);
          }
          break;
        case '<':
          if (NEXT == '=') // <=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_LESSER_EQUAL);
            else
              printf("%d\t%d\n", CODE_LESSER_EQUAL, LINE);
          }
          else
          {
            if(NEXT == '<') // <<
            {
              if(DEBUG)
                show_debug(CODE_SMALLER_SMALLER);
              else
                printf("%d\t%d\n", CODE_SMALLER_SMALLER, LINE); 
            }
            else // <
            {
              if(DEBUG)
                show_debug(CODE_SMALLER);
              else
                printf("%d\t%d\n", CODE_SMALLER, LINE); 
            }
          }
          break;
        case '>':
          if (NEXT == '=') // >=
          {
            read_file();
            if(DEBUG)
              show_debug(CODE_MORE_EQUAL);
            else
              printf("%d\t%d\n", CODE_MORE_EQUAL, LINE);
          }
          else
          {
            if(NEXT == '>') // >>
            {
              if(DEBUG)
                show_debug(CODE_MORE_MORE);
              else
                printf("%d\t%d\n", CODE_MORE_MORE, LINE); 
            }
            else // >
            {
              if(DEBUG)
                show_debug(CODE_MORE);
              else
                printf("%d\t%d\n", CODE_MORE, LINE); 
            }
          }
          break;
        case '|':
          if(NEXT == '|') // ||
          {
            if(DEBUG)
              show_debug(CODE_OR);
            else
              printf("%d\t%d\n", CODE_OR, LINE);
          }
          else // |
          {
            printf("%d\n", CODE_ESC);
          }
          break;
        case '&':
          if(NEXT == '&') // &&
          {
            if(DEBUG)
              show_debug(CODE_AND);
            else
              printf("%d\t%d\n", CODE_AND, LINE);
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

  show_numbers();
  show_names();

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

int add_name(char word[TAM])
{
  for(int i = 0; i < TAM_ARRAY; i++)
  {
    if(LIST_NAMES[i] != NULL)
    {
      if(strncmp(word, LIST_NAMES[i], sizeof(char[TAM])) == 0)
      {
        return i;
      }
    }
    else
    {
      LIST_NAMES[i] = malloc(sizeof(char[TAM]));
      strcpy(LIST_NAMES[i], word);
      return i;
    }
  }
}

int add_value(char word[TAM])
{
  for(int i = 0; i < TAM_ARRAY; i++)
  {
    if(LIST_VAL[i] != NULL)
    {
      if(strncmp(word, LIST_VAL[i], sizeof(char[TAM])) == 0)
      {
        return i;
      }
    }
    else
    {
      LIST_VAL[i] = malloc(sizeof(char[TAM]));
      strcpy(LIST_VAL[i], word);
      return i;
    }
  }
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
    int aux = add_value(WORD);
    if(DEBUG)
    {
      show_debug(CODE_NUMBER);
      printf("<id, %d>\n", aux);
    }
    else
    {
      printf("%d\t%d\n", CODE_NUMBER, LINE);
      printf("%d\n", aux);
    }
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
    int aux = add_value(WORD);
    if(DEBUG)
    {
      show_debug(CODE_NUMBER);
      printf("<id, %d>\n", aux);
    }
    else
    {
      printf("%d\t%d\n", CODE_NUMBER, LINE);
      printf("%d\n", aux);
    }
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
    int aux = add_value(WORD);
    if(DEBUG)
    {
      show_debug(CODE_NUMBER);
      printf("<id, %d>\n", aux);
    }
    else
    {
      printf("%d\t%d\n", CODE_NUMBER, LINE);
      printf("%d\n", aux);
    }
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
        if(DEBUG)
          show_debug(CODE_AUTO);
        else
          printf("%d\t%d\n", CODE_AUTO, LINE);
        break;
      case 2:
        if(DEBUG)
          show_debug(CODE_BREAK);
        else
          printf("%d\t%d\n", CODE_BREAK, LINE);
        break;
      case 3:
        if(DEBUG)
          show_debug(CODE_CASE);
        else
          printf("%d\t%d\n", CODE_CASE, LINE);
        break;
      case 4:
        if(DEBUG)
          show_debug(CODE_CHAR);
        else
          printf("%d\t%d\n", CODE_CHAR, LINE);
        break;
      case 5:
        if(DEBUG)
          show_debug(CODE_CONST);
        else
          printf("%d\t%d\n", CODE_CONST);
        break;
      case 6:
        if(DEBUG)
          show_debug(CODE_CONTINUE);
        else
          printf("%d\t%d\n", CODE_CONTINUE, LINE);
        break;
      case 7:
        if(DEBUG)
          show_debug(CODE_DEFAULT);
        else
          printf("%d\t%d\n", CODE_DEFAULT, LINE);
        break;
      case 8:
        if(DEBUG)
          show_debug(CODE_DO);
        else
          printf("%d\t%d\n", CODE_DO, LINE);
        break;
      case 9:
        if(DEBUG)
          show_debug(CODE_DOUBLE);
        else
          printf("%d\t%d\n", CODE_DOUBLE, LINE);
        break;
      case 10:
        if(DEBUG)
          show_debug(CODE_ELSE);
        else
          printf("%d\t%d\n", CODE_ELSE, LINE);
        break;
      case 11:
        if(DEBUG)
          show_debug(CODE_ENUM);
        else
          printf("%d\t%d\n", CODE_ENUM, LINE);
        break;
      case 12:
        if(DEBUG)
          show_debug(CODE_EXTERN);
        else
          printf("%d\t%d\n", CODE_EXTERN, LINE);
        break;
      case 13:
        if(DEBUG)
          show_debug(CODE_FLOAT);
        else
          printf("%d\t%d\n", CODE_FLOAT, LINE);
        break;
      case 14:
        if(DEBUG)
          show_debug(CODE_FOR);
        else
          printf("%d\t%d\n", CODE_FOR, LINE);
        break;
      case 15:
        if(DEBUG)
          show_debug(CODE_GOTO);
        else
          printf("%d\t%d\n", CODE_GOTO, LINE);
        break;
      case 16:
        if(DEBUG)
          show_debug(CODE_IF);
        else
          printf("%d\t%d\n", CODE_IF, LINE);
        break;
      case 17:
        if(DEBUG)
          show_debug(CODE_INT);
        else
        printf("%d\t%d\n", CODE_INT, LINE);
        break;
      case 18:
        if(DEBUG)
          show_debug(CODE_LONG);
        else
          printf("%d\t%d\n", CODE_LONG, LINE);
        break;
      case 19:
        if(DEBUG)
          show_debug(CODE_REGISTER);
        else
          printf("%d\t%d\n", CODE_REGISTER, LINE);
        break;
      case 20:
        if(DEBUG)
          show_debug(CODE_RETURN);
        else
          printf("%d\t%d\n", CODE_RETURN, LINE);
        break;
      case 21:
        if(DEBUG)
          show_debug(CODE_SHORT);
        else
          printf("%d\t%d\n", CODE_SHORT, LINE);
        break;
      case 22:
        if(DEBUG)
          show_debug(CODE_SIGNED);
        else
          printf("%d\t%d\n", CODE_SIGNED, LINE);
        break;
      case 23:
        if(DEBUG)
          show_debug(CODE_SIZEOF);
        else
          printf("%d\t%d\n", CODE_SIZEOF, LINE);
        break;
      case 24:
        if(DEBUG)
          show_debug(CODE_STATIC);
        else
          printf("%d\t%d\n", CODE_STATIC, LINE);
        break;
      case 25:
        if(DEBUG)
          show_debug(CODE_STRUCT);
        else
          printf("%d\t%d\n", CODE_STRUCT, LINE);
        break;
      case 26:
        if(DEBUG)
          show_debug(CODE_SWITCH);
        else
          printf("%d\t%d\n", CODE_SWITCH, LINE);
        break;
      case 27:
        if(DEBUG)
          show_debug(CODE_TYPEDEF);
        else
          printf("%d\t%d\n", CODE_TYPEDEF, LINE);
        break;
      case 28:
        if(DEBUG)
          show_debug(CODE_UNION);
        else
          printf("%d\t%d\n", CODE_UNION, LINE);
        break;
      case 29:
        if(DEBUG)
          show_debug(CODE_UNSIGNED);
        else
          printf("%d\t%d\n", CODE_UNSIGNED, LINE);
        break;
      case 30:
        if(DEBUG)
          show_debug(CODE_VOID);
        else
          printf("%d\t%d\n", CODE_VOID, LINE);
        break;
      case 31:
        if(DEBUG)
          show_debug(CODE_VOLATILE);
        else
          printf("%d\t%d\n", CODE_VOLATILE, LINE);
        break;
      case 32:
        if(DEBUG)
          show_debug(CODE_WHILE);
        else
          printf("%d\t%d\n", CODE_WHILE, LINE);
        break;
      case 33:
        if(DEBUG)
          show_debug(CODE_PACKED);
        else
          printf("%d\t%d\n", CODE_PACKED, LINE);
        break;
      default:
        int aux = add_name(WORD);
        if(DEBUG)
        {
          show_debug(CODE_VARIABLE_FUNCTION);
          printf("<id, %d>\n", aux);
        }
        else
        {
          printf("%d\t%d\n", CODE_VARIABLE_FUNCTION, LINE);
          printf("%d\n", aux);
        }
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
    int id = add_value(WORD);
    if(DEBUG)
    {
      show_debug(CODE_STRING);
      printf("<id, %d>\n", id);
    }
    else
      printf("%d\t%d\n%d\n", CODE_STRING, LINE, id);
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
    int id = add_value(WORD);
    if(DEBUG)
    {
      show_debug(CODE_VALUE_CHAR);
      printf("<id, %d>\n", id);
    }
    else
      printf("%d\t%d\n%d\n", CODE_VALUE_CHAR, LINE, id);
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

void show_numbers()
{
  printf("99999\n");
  for(int i = 0; i < TAM_ARRAY; i++)
  {
    if(LIST_VAL[i] == NULL)
      break;

    for(int j = 0; j < TAM; j++)
    {
      printf("%c", LIST_VAL[i][j]);
    }
    printf("\n");
  }
}

void show_names()
{
  printf("names\n");
  for(int i = 0; i < TAM_ARRAY; i++)
  {
    if(LIST_NAMES[i] == NULL)
      break;

    for(int j = 0; j < TAM; j++)
    {
      printf("%c", LIST_NAMES[i][j]);
    }
    printf("\n");
  }
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

void show_debug(int code)
{
  char token[30];
  memset(token, 0, sizeof token);
  switch(code)
  {
    case CODE_SEMICOLON:
      strcpy(token, "PontoVirgula");
      break;
    case CODE_COMMA:
      strcpy(token, "Virgula");
      break;
    case CODE_TWO_POINTS:
      strcpy(token, "DoisPontos");
      break;
    case CODE_DOT:
      strcpy(token, "Ponto");
      break;
    case CODE_OPEN_KEYS:
      strcpy(token, "AbreChaves");
      break;
    case CODE_CLOSE_KEYS:
      strcpy(token, "FechaChaves");
      break;
    case CODE_OPEN_PARENTHESES:
      strcpy(token, "AbreParenteses");
      break;
    case CODE_CLOSE_PARENTHESES:
      strcpy(token, "FechaParenteses");
      break;
    case CODE_OPEN_SQUARE_BRACKETS:
      strcpy(token, "AbreColchetes");
      break;
    case CODE_CLOSE_SQUARE_BRACKETS:
      strcpy(token, "FechaColchetes");
      break;
    case CODE_PLUS_PLUS:
      strcpy(token, "SomaUm");
      break;
    case CODE_PLUS_EQUAL:
      strcpy(token, "MaisAtribuição");
      break;
    case CODE_PLUS:
      strcpy(token, "Soma");
      break;
    case CODE_LESS_LESS:
      strcpy(token, "SubtraiUm");
      break;
    case CODE_LESS_EQUAL:
      strcpy(token, "SubAtribuicao");
      break;
    case CODE_LESS:
      strcpy(token, "Subtracao");
      break;
    case CODE_RASH:
      strcpy(token, "RashTag");
      break;
    case CODE_MULT_EQUAL:
      strcpy(token, "MultAtribuicao");
      break;
    case CODE_MULT:
      strcpy(token, "Mult");
      break;
    case CODE_DIV_EQUAL:
      strcpy(token, "DivAtrib");
      break;
    case CODE_DIV:
      strcpy(token, "Divisao");
      break;
    case CODE_PERCENTAGE_EQUAL:
      strcpy(token, "%=");
      break;
    case CODE_PERCENTAGE:
      strcpy(token, "Porcent");
      break;
    case CODE_EXCLAMATION:
      strcpy(token, "Exclamacao");
      break;
    case CODE_DIFFERENT:
      strcpy(token, "Diferente");
      break;
    case CODE_INV:
      strcpy(token, "Inv");
      break;
    case CODE_RECEIVE:
      strcpy(token, "Recebe");
      break;
    case CODE_EQUAL:
      strcpy(token, "Igual");
      break;
    case CODE_LESSER_EQUAL:
      strcpy(token, "MenorIgual");
      break;
    case CODE_SMALLER_SMALLER:
      strcpy(token, "Bits <<");
      break;
    case CODE_SMALLER:
      strcpy(token, "Menor");
      break;
    case CODE_MORE_EQUAL:
      strcpy(token, "MaiorIgual");
      break;
    case CODE_MORE_MORE:
      strcpy(token, "Bits >>");
      break;
    case CODE_MORE:
      strcpy(token, "Maior");
      break;
    case CODE_OR:
      strcpy(token, "Ou");
      break;
    case CODE_AND:
      strcpy(token, "E");
      break;
    case CODE_NUMBER:
      strcpy(token, "Numero");
      break;
    case CODE_VARIABLE_FUNCTION:
      strcpy(token, "Nome");
      break;
    case CODE_IF:
      strcpy(token, "IF");
      break;
    case CODE_INT:
      strcpy(token, "INT");
      break;
    case CODE_AUTO:
      strcpy(token, "Auto");
      break;
    case CODE_BREAK:
      strcpy(token, "Break");
      break;
    case CODE_CASE:
      strcpy(token, "Case");
      break;
    case CODE_CHAR:
      strcpy(token, "Char");
      break;
    case CODE_CONST:
      strcpy(token, "Const");
      break;
    case CODE_CONTINUE:
      strcpy(token, "Contunue");
      break;
    case CODE_DEFAULT:
      strcpy(token, "Default");
      break;
    case CODE_DO:
      strcpy(token, "Do");
      break;
    case CODE_DOUBLE:
      strcpy(token, "Double");
      break;
    case CODE_ELSE:
      strcpy(token, "Else");
      break;
    case CODE_ENUM:
      strcpy(token, "Enum");
      break;
    case CODE_EXTERN:
      strcpy(token, "Extern");
      break;
    case CODE_FLOAT:
      strcpy(token, "Float");
      break;
    case CODE_FOR:
      strcpy(token, "For");
      break;
    case CODE_GOTO:
      strcpy(token, "Goto");
      break;
    case CODE_LONG:
      strcpy(token, "Long");
      break;
    case CODE_REGISTER:
      strcpy(token, "Register");
      break;
    case CODE_RETURN:
      strcpy(token, "Return");
      break;
    case CODE_SHORT:
      strcpy(token, "Short");
      break;
    case CODE_SIGNED:
      strcpy(token, "Signed");
      break;
    case CODE_SIZEOF:
      strcpy(token, "Size_of");
      break;
    case CODE_STATIC:
      strcpy(token, "Static");
      break;
    case CODE_STRUCT:
      strcpy(token, "Struct");
      break;
    case CODE_SWITCH:
      strcpy(token, "Switch");
      break;
    case CODE_TYPEDEF:
      strcpy(token, "Typedef");
      break;
    case CODE_UNION:
      strcpy(token, "Union");
      break;
    case CODE_UNSIGNED:
      strcpy(token, "Unsigned");
      break;
    case CODE_VOID:
      strcpy(token, "Void");
      break;
    case CODE_VOLATILE:
      strcpy(token, "Volatile");
      break;
    case CODE_WHILE:
      strcpy(token, "While");
      break;
    case CODE_PACKED:
      strcpy(token, "Packed");
      break;
    case CODE_STRING:
      strcpy(token, "String");
      break;
    case CODE_VALUE_CHAR:
      strcpy(token, "Value char");
      break;
    
  }
  printf("Linha[%d]\tToken[%d]\t <", LINE, code);
  for(int i = 0; i < 30; i++) {
    printf("%c",token[i]);
  }
  printf(">\n");
}