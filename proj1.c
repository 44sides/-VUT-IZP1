#include <stdio.h>
#include <string.h>
/*
The program processes the data line-by-line. In each line it processes symbol-by-symbol.
One loop is the processing of a string pair (name; number).
The program goes through the data once,
and writes it using getc() function.
GETC() gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream.
*/

/*
Structure is user defined data type, that allows to combine data items of different kinds.
Structure of 4 letters is defined here.
*/
struct Letters
{
  char l1, l2, l3, l4;
};

/*
Declare symbols that belong to each digit. (Mobile keyboard)
*/
void fillnumbers (struct Letters *number)
{
  number[0].l1 = '+';

  number[2].l1 = 'a'; number[3].l1 = 'd'; number[4].l1 = 'g'; number[5].l1 = 'j'; number[6].l1 = 'm';
  number[2].l2 = 'b'; number[3].l2 = 'e'; number[4].l2 = 'h'; number[5].l2 = 'k'; number[6].l2 = 'n';
  number[2].l3 = 'c'; number[3].l3 = 'f'; number[4].l3 = 'i'; number[5].l3 = 'l'; number[6].l3 = 'o';

  number[7].l1 = 'p'; number[8].l1 = 't'; number[9].l1 = 'w';
  number[7].l2 = 'q'; number[8].l2 = 'u'; number[9].l2 = 'x';
  number[7].l3 = 'r'; number[8].l3 = 'v'; number[9].l3 = 'y';
  number[7].l4 = 's';                     number[9].l4 = 'z';
}

/*
Function OUTPUTS in the correct format in case NO ARGUMENT is specified:
The function writes lines (while != '\n')
And, according to the even or odd row, sets separation characters.
The function works, "while != EOF".
*/
_Bool argumentnullOutput(int argc)
{
  if(argc == 1)
{
  char letter;
  int row = 1;
  letter = getc(stdin);

   while(letter != EOF)
   {
    while(letter != '\n' && letter != EOF)
    {
      printf("%c", letter);
      letter = getc(stdin);
    }

    row = row * -1; // if "-1" - above was printed odd line. if "1" - above was printed even line.

    if(row == 1) // even line in a file
    {
    printf("\n");
    }
    else // odd line in a file
    {
     printf(", ");
    }

    letter = getc(stdin);
   }

  printf("\n");
  return 1;
}
  else
  {
  return 0;
  }
}

/*
RESET of arrays to AVOID saving and using previous values:
Filling arrays "-1".
*/
void resetTempArrays (int *arr1, int *arr2)
{
  for (int t = 0; t < 100; t++)
  {
    arr1[t] = -1;
    arr2[t] = -1;
  }
}


/*
Writing LETTERS from "jmeno", that match one of the argument DIGITS,
in digit format to the same position to the ARRAY OF MATCHES "jmenoTemp":
The function considers each letter of the string "jmeno". "\n" signals end of string.

The letter from "jmeno" is taken and compared with the letters that correspond to a certain digit of the argument.
If there are matches, a digit is written to the array, which is potentially part of the search sequence.
The comparison is case-independent, so we also consider the upper case of the letter (according to the ASCII table we add 32 positions to the small case letter).
The letter from "jmeno" must match each digit of the argument.

"i" acts as the size of the array "jmeno" as well.
The modified ARRAY OF MATCHES and its size are returned to the "int main()".
*/
void Letter_to_Number (char *jmeno, int *jmenoTemp, int arg[], int argNum, int *i, struct Letters *number)
{
  while (jmeno[*i] != '\n')
  {
      for (int argI = 0; argI < argNum; argI++) // checking each digit of the argument
      {
        if(arg[argI] == 7 || arg[argI] == 9) // for 7 and 9 must be checking 4 letter
        {
          if ((number[arg[argI]].l1 == jmeno[*i] || number[arg[argI]].l1 == jmeno[*i] + 32) || (number[arg[argI]].l2 == jmeno[*i] || number[arg[argI]].l2 == jmeno[*i] + 32) || (number[arg[argI]].l3 == jmeno[*i] || number[arg[argI]].l3 == jmeno[*i] + 32) || (number[arg[argI]].l4 == jmeno[*i] || number[arg[argI]].l4 == jmeno[*i] + 32))
          { jmenoTemp[*i] = arg[argI]; }
        }
        else if(arg[argI] == 0) // for 0 is checking 1 letter
        {
          if (number[arg[argI]].l1 == jmeno[*i])
          { jmenoTemp[*i] = arg[argI]; }
        }
        else // for others is checking 1 letter
        {
          if ((number[arg[argI]].l1 == jmeno[*i] || number[arg[argI]].l1 == jmeno[*i] + 32) || (number[arg[argI]].l2 == jmeno[*i] || number[arg[argI]].l2 == jmeno[*i] + 32) || (number[arg[argI]].l3 == jmeno[*i] || number[arg[argI]].l3 == jmeno[*i] + 32))
          { jmenoTemp[*i] = arg[argI]; }
        }
      }

    *i = *i + 1;
    jmeno[*i] = getc(stdin);
  }
  jmeno[*i] = '\0'; // Expression of word border, setting end of string
}

/*
Checking integer array "jmenoTemp" for sequence:
The function lists the elements of the ARRAY OF MATCHES and compares to the first element of the argument.
If the comparison is successful, the found element becomes a POTENTIAL FIRST ELEMENT of the sequence and goes to the "while" for verification.

The "while" loop moves the cursor in the ARRAY OF MATCHES and in the ARGUMENT ARRAY to the next positions,
The loop will stop, if the elements in the arrays are NOT equal (1st case) OR the maximum position of the ARGUMENT ARRAY is reached (2nd case).

If the loop stopped due to the 1st case, the sequence came down and we are forced to start again.
If the loop stopped due to the 2nd case,
all matches the ARGUMENT elements with the elements of ARRAY OF MATCHES (starting from POTENTIAL FIRST ELEMENT of the sequence) were detected
and the function returns "true".
*/
_Bool Sequence_Checking_jmeno(int jmenoTemp[], int jmeno_size, int arg[], int argNum)
{
  int argI = 0;

	for (int p = 0; p < jmeno_size; p++) // p - index of the ARRAY OF MATCHES
  {
    while (jmenoTemp[p] == arg[argI] && argI != argNum)
    {
      argI++;
      p++;
    }

    if(argI == argNum) // successful exit from the cycle
    {
      return 1;
    }

    if (argI != 0) // unsuccessful exit from the cycle. If "argI! = 0", the "while" loop was involved.
    {
/*
We have increased "p" and should test it for a POTENTIAL FIRST ELEMENT,
but when we go to the beginning, the "for" loop won't allow us to check, because it will increase “p” again.
Therefore, we decrease the value of "p", so that "for" increases it again. ( + - + )
*/
      argI = 0; p--;
    }
  }

	return 0;
}

/*
Writing SYMBOLS(digits and "+" !) from "telefon", that match one of the ARGUMENT DIGITS,
in digit format to the same position to the ARRAY OF MATCHES "telefonTemp":
The function considers each symbol of the string "telefon". "\n" signals end of string or "EOF" signals the end of the stream, because the number string may be the last.

The symbol from "telefon" is taken and compared with the symbols that correspond to a certain digit of the argument.
If there are matches, a digit is written to the array, which is potentially part of the search sequence.
The symbol from "telefon" must match each digit of the argument.

"i" acts as the size of the array "telefon" as well.
The modified ARRAY OF MATCHES and its size are returned to the "int main()".
*/
void Telefon_to_Number (char *telefon, int *telefonTemp, int arg[], int argNum, int *i, struct Letters *number)
{
  while (telefon[*i] != '\n' && telefon[*i] != EOF)
  {
    for (int argI = 0; argI < argNum; argI++) // checking each digit of the argument
    {
      if (arg[argI] == 0)
      {
        if(number[0].l1 == telefon[*i]) // check if the symbol is "+"
        { telefonTemp[*i] = arg[argI]; }
      }
      if (arg[argI] == (int)(telefon[*i] - '0'))
      { telefonTemp[*i] = arg[argI]; }
    }

    *i = *i + 1;
    telefon[*i] = getc(stdin);
  }
  telefon[*i] = '\0'; // Expression of word border, setting end of string
}

/*
Checking integer array "telefonTemp" for sequence:
The function lists the elements of the ARRAY OF MATCHES and compares to the first element of the argument.
If the comparison is successful, the found element becomes a POTENTIAL FIRST ELEMENT of the sequence and goes to the "while" for verification.

The "while" loop moves the cursor in the ARRAY OF MATCHES and in the ARGUMENT ARRAY to the next positions,
The loop will stop, if the elements in the arrays are NOT equal (1st case) OR the maximum position of the ARGUMENT ARRAY is reached (2nd case).

If the loop stopped due to the 1st case, the sequence came down and we are forced to start again.
If the loop stopped due to the 2nd case,
all matches the ARGUMENT elements with the elements of ARRAY OF MATCHES (starting from POTENTIAL FIRST ELEMENT of the sequence) were detected
and the function returns "true".
*/
_Bool Sequence_Checking_telefon(int telefonTemp[], int telefon_size, int arg[], int argNum)
{
  int argI = 0;

  for (int p = 0; p < telefon_size; p++) // p - index of the ARRAY OF MATCHES
  {
    while (telefonTemp[p] == arg[argI] && argI != argNum)
    {
      argI++;
      p++;
    }

    if(argI == argNum) // successful exit from the cycle
    {
      return 1;
    }

    if (argI != 0) // unsuccessful exit from the cycle. If "argI! = 0", the "while" loop was involved.
    {
/*
We have increased "p" and should test it for a POTENTIAL FIRST ELEMENT,
but when we go to the beginning, the "for" loop won't allow us to check, because it will increase “p” again.
Therefore, we decrease the value of "p", so that "for" increases it again. ( + - + ).
*/
      argI = 0; p--;
    }
  }

  return 0;
}


int main(int argc, char *argv[])
{
  printf("\n");

  if(argumentnullOutput(argc) == 1)
  {
    return 0;
  }

  struct Letters number[10];
  fillnumbers(number);

  char jmeno[100]; // Array for the strings of contact's name
  char telefon[100]; // Array for the strings of contact's phone
  int jmenoTemp[100]; int telefonTemp[100]; // ARRAYS OF MATCHES. Arrays to record found matches, in digit format.

  resetTempArrays(jmenoTemp, telefonTemp);

  int i = 0; // size of arrays in some cases.
  _Bool VERIFICATION = 0; // output indicator of the string "telefon". "True" if the sequence is found in "jmeno" and it's necessary to output "telefon" without checking.
  _Bool NOTFOUND = 1; // If the value won't be changed to "false", no results found (will outputs "Not Found").

  int argNum = 0;
  while(argv[1][argNum] != '\0') {argNum++;} // sum of argument digits

  if(argNum > 100) // if argument contains > 100 symbols
  {
    printf("BIG ARGUMENT\n\n");
    return 0;
  }

  int arg[argNum];
  while(i < argNum) // checking for the correct argument format
  {
    if ((int)(argv[1][i]) >= 48 && (int)(argv[1][i]) <= 57)
    {
      arg[i] = argv[1][i] - '0'; i++; // simplification: changing the type of argument
    }
    else
    {
      printf("The argument must be 0 to 9\n\n");
      return 0;
    }
  }

  i = 0;

  jmeno[i] = getc(stdin);

  while(jmeno[i] != EOF) // while != End Of File. (If isn't end of input stream)
  {
    Letter_to_Number(jmeno, jmenoTemp, arg, argNum, &i, number);

    if(Sequence_Checking_jmeno(jmenoTemp, i, arg, argNum) == 1) // Sequence exists in the name
    {
      printf("%s, ", jmeno);
      VERIFICATION = 1;
    }

    i = 0;

    telefon[i] = getc(stdin);

    Telefon_to_Number (telefon, telefonTemp, arg, argNum, &i, number);

    if(VERIFICATION == 1) // No need to check the number for sequence
    {
      NOTFOUND = 0;
      printf("%s", telefon);
      printf("\n");
    }
    else
    {
      if(Sequence_Checking_telefon(telefonTemp, i, arg, argNum) == 1) // Sequence exists in the number
      {
        NOTFOUND = 0;
        printf("%s, %s",jmeno, telefon);
        printf("\n");
      }
    }

    i = 0;

    jmeno[i] = getc(stdin);

    VERIFICATION = 0;

    resetTempArrays(jmenoTemp, telefonTemp);
/*
At the end, the arrays reset.
Then begins the study of the another pair (name;number),
if the end of the stream is not reached.
*/
 } // end of the general cycle "while"


  if(NOTFOUND == 1)
  {
    /*
    Value left in "true" status
    */
    printf("Not Found\n");
  }

  printf("\n");
  return 0;
}
