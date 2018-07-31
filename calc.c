#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

int
main(int argc, char **argv)
{
        char *num1 = argv[2]; //number 1
        char *num2 = argv[3]; //number 2
        long int n1, n2, ans = 0; 
        char *res = malloc(sizeof(char)*8); //holds answer
        char *outputbase = argv[4]; //output base char
        char *op = argv[1]; //operator
        int isneg1 = 1, isneg2 = 1; //to keep track of sign
        int i, j, index1 = 0, index2 = 0; //loop variables
        
        //making sure there's enough args
        if(argc != 5)
        {
            fprintf(stderr, "%s\n", "Did not enter correct amount of inputs");
            return EXIT_FAILURE;
        }

        //checking if the inputs are negative
        if(*num1 == '-' || *num1 == '1')
        {
            isneg1 = 0;
            index1 = 1;
        } 
        if(*num2 == '-' || *num2 == '1')
        {
            isneg2 = 0;
            index2 = 1;

        }
    
        //making sure input has 64 or less bits (including the base prefix)
        for(i = 0; *num1 != '\0'; num1++)
        { 
            i++;
        }

        for (j = 0; *num2 != '\0'; num2++)
        {
            j++;
        }
 
        if(i > 64 || j > 64)
        {
            fprintf(stderr, "%s\n", "ERROR! Input contains more than 64 bits.\n");
            return EXIT_FAILURE;

        } else {

            //resetting pointers
            num1 = argv[2];
            num2 = argv[3];
            //if there are >=64 bits, then call
            //base conversion functions based on base indicator
            if(num1[index1] == 'o' || num1[index1] == 'O')
            {
                n1 = fromString(num1, 'o', isneg1);
            }
            else if( num1[index1] == 'x' || num1[index1] == 'X')
            {
                n1 = fromString(num1, 'x', isneg1);
            }
            else if( num1[index1] == 'b' || num1[index1] == 'B')
            {
                n1 = fromString(num1, 'b', isneg1);
            }
           else if(num1[index1] == 'd' || num1[index1] == 'D')
            {
                n1 = fromString(num1, 'd', isneg1);
      
            } else {

                fprintf(stderr, "%s\n", "ERROR! First number not formatted properly.\n");
                return EXIT_FAILURE;
            }

            if(num2[index2] == 'o' || num2[index2] == 'O')
            {
                n2 = fromString(num2, 'o', isneg2);
            }
            else if( num2[index2] == 'x' || num2[index2] == 'X')
            {
                n2 = fromString(num2, 'x', isneg2);
            }   
            else if( num2[index2] == 'b' || num2[index2] == 'B')
            {    
                n2 = fromString(num2, 'b', isneg2);
            }
            else if(num2[index2] == 'd' || num2[index2] == 'D')
            {
                n2 = fromString(num2, 'd', isneg2);

            } else {

                fprintf(stderr, "%s\n", "ERROR! Second number not formatted properly.\n");
                return EXIT_FAILURE;
            }
        }

        //adds or subtracts returned value form toString function based on op
        if(*op == '+')
        {
            ans = n1 + n2;

        } else if (*op == '-')
        {
            ans = n1 - n2;

        } else {
        
            fprintf(stderr, "ERROR! You have not entered the correct operator. It should be an addition or subtraction operator.\n");
            return EXIT_FAILURE;
        }

        //calling toString function to convert value into outputbase format
        if( toString(ans, *outputbase, res) == 0)
        {
            return EXIT_SUCCESS;  

        } else {

            return EXIT_FAILURE;
        }             
}

//reverses bit string
void reverse(char *bits)
{
    char temp;
    long i, j;

    //loop variables for reversal
    i = 0;
    j = strlen(bits)-1; 

    while((i < j) && (j > i))
    {
        temp = bits[i];

        bits[i] = bits[j];

        bits[j] = temp;

        i++;
        j--;
    }
}

/*converts string into int value if it's a valid input
takes a pointer for the input to be converted, base 
that the input is in, and if it's negative. */
long int fromString(char *input, char base, int isneg)
{
    long int i = 1, value = 0, j = 0; //value and loop variable

   //if number is negative, starting point is at 2, not 1
   if(isneg == 0)
   {
        i = 2;
   }

    if(base == 'd') //converts string into decimal
    {
        while(input[i] != '\0')
        {
            if(isdigit(input[i]))
            {
                if(isneg == 0)
                {
                    value = value * 10 + ((input[i] - '0')*-1);

                } else {

                    value = value * 10 + (input[i] - '0');
                }

            } else {

                fprintf(stderr, "%s\n","ERROR! Invalid decimal input.");
                return EXIT_FAILURE;
            }

            i++;
        }
    } 
    else if(base == 'o') //converts string into octal
    {
        while(input[i] != '\0')
        {
            if(input[i] < 8 || input[i] > 0)
            {
                if(isneg == 0) //if the number is negative
                {
                    value = value * 8 + ((input[i] - '0')*-1);

                } else {

                    value = value * 8 + (input[i] - '0');

                }

            } else {

                fprintf(stderr, "%s\n","ERROR! Invalid octal input.");
                return EXIT_FAILURE;
            }

            i++;
        } 
    }
    else if(base == 'b') //converts string into binary value
    {
        while(input[i] != '\0')
        {
            if(input[i] == '0' || input[i] == '1')
            {
                if(isneg == 0)
                {
                    value = value * 2 + ((input[i] - '0')*-1);

                } else {

                    value = value * 2 + (input[i] - '0');
                }

            } else {

                fprintf(stderr, "%s\n","ERROR! Invalid binary input.");
                return EXIT_FAILURE;
             }

            i++;          
        }
    }
    else if(base == 'x') //converts string into hex value
    {
        if(input == 0)
        {
            fprintf(stderr, "%s\n", "ERROR! Array is pointing to null.");
            return EXIT_FAILURE;

        } else {

             //have to traverse hex string backwards
            i = strlen(input)-1;

            while(input[i] != 'x')
            {
                if(input[i] == 'a' || input[i] == 'A')
                {
                    if(isneg == 0)
                    {
                        value = value + 10 * ((expcalc(16, j))*-1);

                    } else {

                        value = value + 10 * (expcalc(16, j));
                    }
                }
                else if(input[i] == 'b' || input[i] == 'B')
                {
                    if(isneg == 0)
                    {
                        value = value + 11 * ((expcalc(16, j))*-1);

                    } else {

                        value = value + 11 * (expcalc(16, j));
                    }
                }
                else if(input[i] == 'c' || input[i] == 'C')
                {
                    if(isneg == 0)
                    {
                        value = value + 12 * ((expcalc(16 ,j))*-1);

                    } else {

                        value = value + 12 * (expcalc(16 ,j));
                    }
                }
                else if(input[i] == 'd' || input[i] == 'D')
                {
                    if(isneg == 0)
                    {
                        value = value + 13 * ((expcalc(16, j))*-1);

                    } else {

                        value = value + 13 * (expcalc(16, j));
                    }
                }
                else if(input[i] == 'e' || input[i] == 'E')
                {
                    if(isneg ==0)
                    {
                        value = value + 14 * ((expcalc(16, j))*-1);

                    } else {

                        value = value + 14 * (expcalc(16, j));
                    }
                }
                else if(input[i] == 'f' || input[i] == 'F')
                {
                    if(isneg == 0)
                    {
                        value = value + 15 * ((expcalc(16, j))*-1);

                    } else {

                        value = value + 15 * (expcalc(16, j));
                    }
                }
                else if(isdigit(input[i]))
                {
                    if(isneg == 0)
                    {
                        value = value + (input[i] - '0') * ((expcalc(16, j))*-1);

                    } else {

                        value = value + (input[i] - '0') * (expcalc(16, j));

                    }

                } else {

                    fprintf(stderr, "%s\n","ERROR! Invalid hex input.");
                    return EXIT_FAILURE;
                }

                j++;
                i--;
            }
            
        }  
    }

        return value;

    }

//calculates result of base ^ pow
long int expcalc(int base, int pow)
{
    long int answer = 1;
    int i, k = 0; //loop variable

    while(k <= pow)
    {
        if(pow == 0)
        {
            return answer;

        } else {

            if(k == 0)
            {
                answer = 1;

            } else {

                 answer = base * answer;
            }
           
            k++;
        }
    }

    return answer;
}

/*converts int num into its string equivalent by taking 
the int value of the sum / difference, the base output the num
should be converted into, and a pointer to hold the answer. */
int toString(long int num, char outputbase, char *answer)
{
    int temp; //holds remainder
    int i = 0, isneg = 1; //array variable & variable for negative numbers

    if(num < 0)
    {
        isneg = 0;
    }

    if(num == 0)
    {
        *answer = outputbase;
        answer[1] = '0';
        answer[2] = '\0';

    } else {

        if(outputbase == 'd' || outputbase == 'D') //converts decimal into its string equiv
        {
            while(num != 0)
            {
                temp = num % 10;

                if(temp < 0)
                {
                    temp = temp *-1;
                
                }
                answer[i] = temp + '0';
                num = num / 10;
                i++;
            }

            answer[i] = 'd';
            i++;
            if(isneg == 0)
            {
                answer[i] = '-';
                i++;
            }
            answer[i] = '\0';

        }
        else if(outputbase == 'b' || outputbase == 'B') //converts binary into its string equiv
        {
            while(num != 0)
            {
                temp = num % 2;
                if(temp < 0)
                {
                    temp = temp *-1;
                }
                answer[i] = temp + '0';
                num = num / 2;
                i++;
            }
            //to put value into two's comp if the number is negative
            if(isneg == 0)
            {
                 reverse(answer);
                if(twosComp(answer) == 0)
                {
                    return 0;

                }

            } else {

                answer[i] = 'b';
                i++;
                answer[i] = '\0';
            }

        }
        else if(outputbase == 'o' || outputbase == 'O') //converts octal into its string equiv
        {
            while(num != 0)
            {
                temp = num % 8;
                if(temp < 0)
                {
                    temp = temp *-1;
                }
                answer[i] = temp + '0';
                num = num / 8;
                i++;
            }

            answer[i] = 'o';
            i++;
            if(isneg == 0)
            {
                answer[i] = '-';
                i++;
            }
            answer[i] = '\0';          
        }
        else if(outputbase == 'x' || outputbase == 'X') //converts hex into its string equiv
        {
            while(num != 0)
            {
                temp = num % 16;

                if(temp < 0)
                {
                    temp = temp *-1;
                }

                if(0 <= temp && temp < 10)
                {
                    answer[i] = temp + '0';
                }
                else if(temp == 10)
                {
                     answer[i] = 'A';
                }
                else if(temp == 11)
                {
                    answer[i] = 'B';
                }
                else if(temp == 12)
                {
                   answer[i] = 'C';
                }
                else if(temp == 13)
                {
                     answer[i] = 'D';
                }
                else if(temp == 14)
                {
                     answer[i] = 'E';
                }
                else if(temp == 15)
                {
                     answer[i] = 'F';
                }

                i++;
                num = num / 16;
            }
            //adding output base 
            answer[i] = 'x';
            i++;
            answer[i] = '0';
            i++;
            if(isneg == 0)
            {
                answer[i] = '-';
                i++;
            }
            answer[i] = '\0';
        }

        //reverses string
        reverse(answer);
    }
       printf("Answer is: %s\n",answer);
       return EXIT_SUCCESS;
}

/*converts binary value into two's complement 
format for negative binary values.*/
int twosComp(char *answer)
{
    int length = strlen(answer)-1;
    char temp[64];

    for(int i = 0; answer[i] != '\0'; i++)
    {
        temp[i] = answer[i];
    }
    int boundary = 64 - strlen(temp), j = 0, carry, i = 0;

    answer[0] = 'b';

    //if input does not have 64 bits already
    if(boundary != 1)
    {
        //padding binary number with 0s
        for(i = 1; i <= boundary; i++)
        {
            answer[i] = '0';
        }
        //adding actual binary value to the array
        while(j <= length)
        {
            answer[i] = temp[j];
            i++;
            j++;
        }
    }
    //switching digits
    for(j = 0; answer[j] != '\0'; j++)
    {
        if(answer[j] == '0')
        {
            answer[j] = '1';
        }
        else if(answer[j] == '1')
        {
            answer[j] = '0';
        }
    }
    //traversing input backwards to add 1 & carry remainder
        for(j = strlen(answer); j != 0; j--)
        {
            if(j == strlen(answer)-1)
            {
                if(answer[j] == '0')
                {
                    answer[j] = '1';
                    carry = 0;
                } 
                else if(answer[j] == '1')
                {
                    answer[j] = '0';
                    carry = 1;
                }

            } else {

                if(carry == 1)
                {
                    if(answer[j] == '0')
                    {
                        answer[j] = '1';
                        carry = 0;

                    } else {

                        answer[j] = '0';
                        carry = 1;
                    }

                } 
            }   
        }

        if(carry == 1 && j == 0)
        {
            answer[1] = '1';
        } 

        printf("Answer is: %s\n", answer);
        return EXIT_SUCCESS;
    
}





