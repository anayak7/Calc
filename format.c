#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

int
main(int argc, char **argv)
{
	int i, comp;
	float result = 0;
	char *ptr;


	//checking if there's enough arguments
	if(argc < 3)
	{
		fprintf(stderr, "ERROR! You have not entered enough arguments!\n");
		return EXIT_FAILURE;
	}

	i = 1; //counter for number of bits in arg 1
	
	//checking if arg 1 is binary
	for(ptr = argv[1]; *ptr != '\0'; ptr++)
	{
		if(*ptr != '0' && *ptr != '1')
		{
			fprintf(stderr, "ERROR! Argument is not binary!\n");
			return EXIT_FAILURE;
		}

		//increments every time a successful iteration occurs for bit count
		i++;
	}

	//checks value of i to make sure there are 32 bits
	if(i != 33)
	{
		fprintf(stderr, "ERROR! Argument does not contain 32 bits.\n");
		return EXIT_FAILURE;
	}

	//case in-sensitive check for second argument and calls appropriate function
	if(strcasecmp(argv[2], "int") == 0)
	{
		//calls int function
		if(toInt(argv[1], 'i') == 0)
		{
			return EXIT_SUCCESS;

		} else {

			return EXIT_FAILURE;
		}

	}
	else if(strcasecmp(argv[2], "float") == 0)
	{
		/*use the int value returned and pass 
		the float value into the float function*/
		if(toInt(argv[1], 'f') == 0)
		{
	 		return EXIT_SUCCESS;
 
		} else {

			return EXIT_FAILURE;
		}

	} else {

		//arg 2 does not contain correct type
		fprintf(stderr, "ERROR, incorrect type entered for argument 2.\n");
		return EXIT_FAILURE;
	}

return 0;

}

union Number 
{
	int	i;
	float f;
};

//formats twos complement bit input into decimal form
int toInt(char *num, char type)
{
	int i = 0, carry, neg = 1;
	char *bits = num, *answer;
	union Number ans;
	ans.i = 0;

	//checks sign: if it's 1, then we flip, add, and carry
	if(*bits == '1')
	{	
		//flipping digits
		while(*bits != '\0')
		{
			if(*bits == '0')
			{
				*bits = '1';

			} else {

				*bits = '0';
			}

			bits++;
		}

		//traversing input backwards to add 1 & carry remainder
		for(i = strlen(num)-1; i != '\0'; i--)
		{
			if(i == 31)
			{
				if(num[i] == '0')
				{
					num[i] = '1';
					carry = 0;
				} 
				else if(num[i] == '1')
				{

					num[i] = '0';
					carry = 1;
				}

			} else {

				if(carry == 1)
				{
					if(num[i] == '0')
					{
						num[i] = '1';
						carry = 0;

					} else {

						num[i] = '0';
						carry = 1;
					}
				} 
			}	
		}

		if(carry == 1 && i == 0)
		{
			num[0] = '1';
		} 

		//for negative sign
		neg = 0;
	} 
		//reversing string for conversion
		reverse(num);		

	//converts into decimal form
	for(i = 0; i != strlen(num); i++)
	{
		if(num[i] == '1')
		{
			ans.i += expcalc(2, i);
		}
	}

	//adding negative sign to final answer
	if(neg == 0)
	{
		ans.i *= -1;
	}

	//calls the float method depending on the type char
	if(type == 'f')
	{	
		//allocating enough for float value
		answer = malloc(sizeof(float)*8);
		floatToASCII(ans.f, answer);
		free(answer);
		return 0;

	} else {

		//allocating enough for int value
		answer = malloc(sizeof(int)*8);
		//to convert function into decimal ascii
		intToDecASCII(ans.i, answer);
		//reversing order of numbers
		reverse(answer);
	}
	
	if(answer == '\0')
	{
		return EXIT_FAILURE;
	}

	printf("Answer is: %s\n", answer);	
	free(answer);
	return 0;
}

/*converts int input into decimal ascii by 
taking in an int input and char pointer to hold 
the result*/
void intToDecASCII(int input, char *answer)
{
	int i = 0, remainder, isneg = 1;

	if(input < 0)
	{
		isneg = 0;
	}

	while(input != 0)
	{
		remainder = input % 10;
		if(remainder < 0)
        {
            remainder = remainder *-1;
        
        }
        answer[i] = remainder + '0';
        input = input / 10;
        i++;
	}
	if(isneg == 0)
    {
        answer[i] = '-';
        i++;
    }
    answer[i] = '\0';
}

//reverses bit string
void reverse(char *bits)
{
	char temp;
	int i, j;

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

//calculates result of base ^ pow
int expcalc(int base, int pow)
{
    int answer = 1, k = 0;

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

static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
	// +/- inf, +/- Nan stuff here
	
	//SPECIAL CASES
    if(biasedExp == 0 && mantissa == 0.0)
    {   
        if(sign == 1 || sign == -1)
        {
            //negative 0
            printf("Answer is: -0.0e0\n");
            return;

        } else {

            //positive 0
            printf("Answer is: 0.0e0\n");
            return;
        }
    } 
    else if(biasedExp == 255 && mantissa == 0.0)
    {
        if(sign == 1 || sign == -1)
        {   
            //negative infinity
            printf("Answer is: ninf\n");
            return;

        } else {
            
            //positive infinity
            printf("Answer is: pinf\n");
            return;
        }
    } 
    else if(biasedExp == 255 && mantissa != 0)
    {   
    	if(sign == 1 || sign == -1)
        { 
        	printf("Answer is: -NaN\n");
        	return;

    	} else {

    		//not a number
	        printf("Answer is: NaN\n");
	        return;
    	}
        
    } else {

    	output[0] ='\0';
		if ( x < 0.0 )
		{
			append( output, '-' );
			x = -x;					// make x positive
		}
		get_float_digit( x, &c, &pow10, &remainder );
		append( output, c );
		append( output, '.' );
		x = remainder;
		plast = p10 = pow10;			// pow10 set by get_float_digit()
		for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
		{
			get_float_digit( x, &c, &p10, &remainder );
			if ( (plast - p10) > 1 )
			{
				append( output, '0' );	// fill in zero to next nonzero digit
				plast -= 1;
			}
			else
			{
				append( output, c );
				x = remainder;
				plast = p10;
			}
		}
		if ( pow10 < 0 )		// negative exponent
		{
			exponent[0] = 'e';
			intToDecASCII( pow10, exponent+1 );
			reverse(exponent+1);
		}
		else if ( pow10 < 10 )		// positive single-digit exponent
		{
			exponent[0] = 'e';
			exponent[1] = '+';
			exponent[2] = '0';

			intToDecASCII( pow10, exponent+3);
			reverse(exponent+3);
		}
		else				// positive multi-digit exponent
		{
			exponent[0] = 'e';
			exponent[1] = '+';

			intToDecASCII( pow10, exponent+2 );
			reverse(exponent+2);
		}
			strcat(output, exponent);
	}	

	printf("Answer is: %s\n", output);
}


