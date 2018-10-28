#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


/* Author: Brian Phair
   Description: This function will generate a random number that will return a random array element.
   References:
   - https://linux.die.net/man/3/srand
*/
char inputChar()
{
    // TODO: rewrite this function
    srand(time(NULL));                  //set seed
    int randomNumber = rand() % 9;      //generate random number between 0 and 9

    char array[10] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};

    return array[randomNumber];
}


/* Author: Brian Phair
   Description: This function will shuffle an word "reset" randomly and return that word. The function to shuffle the array was inspired from the website listed in References.
   References: 
   - https://en.wikipedia.org/wiki/Fisher–Yates_shuffle
*/
char *inputString()
{
    // TODO: rewrite this function
    srand(time(NULL));      //set seed
    char *array;
    array = malloc(sizeof(char)*5);
    strcat(array, "reset");
    // char array[] = "reset";
    // char *array = malloc(sizeof(char) * 5);
    // array = "reset";
    int i, randomNumber;

    for(i = 0; i < 3; i++){
      randomNumber = rand() % 4;
      char temp = array[i];
      array[i] = array[randomNumber];
      array[randomNumber] = temp;
    }
    return array;
}




void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;

  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
