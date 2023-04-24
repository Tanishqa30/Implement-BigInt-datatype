#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_dig 310

typedef struct data_type
{
	char sign;
	char Num[max_dig];
}Bigint;

Bigint init()
{
	Bigint ref;
	ref.sign = '+';
	return ref;
}

Bigint scan(Bigint val)
{
	gets(val.Num);
	int val_size = strlen(val.Num), i;

	if(val.Num[0]=='-')
	{
		val.sign = '-';
		for(i=0; i<val_size; i++)
		{
			val.Num[i] = val.Num[i+1];
		}

		val_size = val_size - 1;
	}

	if(val_size>308) 
	{
		printf("\no output exceeds size.\n");
		exit(0);
	}

	return val;
}

void display(Bigint ans)
{
	if(ans.sign=='-' && ans.Num!="0")
	{
		printf("%c", ans.sign);
	}
	
	printf("%s", ans.Num);
}

Bigint add(Bigint A, Bigint B, int A_size, int B_size)
{
	Bigint ret_sum = init();
	int i, j, k, carry;
	
	i = A_size - 1;
	j = B_size - 1;
	k = 0;
	carry = 0;

	while(j>=0)
	{
		ret_sum.Num[k] = (A.Num[i]-48) + (B.Num[j]-48) + carry; 
		carry = ret_sum.Num[k]/10;
		ret_sum.Num[k] = ret_sum.Num[k]%10 + 48; 
		i--;
		j--;
		k++;
	}
 
	while(i>=0)
	{
		ret_sum.Num[k] = (A.Num[i]-48) + carry;
		carry = ret_sum.Num[k]/10;
		ret_sum.Num[k] = ret_sum.Num[k]%10 + 48;
		i--;
		k++;
	}

	ret_sum.Num[k] = '\0';

	for(i=0; i<k/2; i++)
	{
		ret_sum.Num[i] = ret_sum.Num[i] + ret_sum.Num[k-1-i];
		ret_sum.Num[k-1-i] = ret_sum.Num[i] - ret_sum.Num[k-1-i];
		ret_sum.Num[i] = ret_sum.Num[i] - ret_sum.Num[k-1-i];
	}

	return ret_sum;
}

Bigint subtract(Bigint A, Bigint B, int A_size, int B_size)
{
	Bigint ret_diff = init();
	int i, j, k, l, borrow;
	
	i = A_size - 1;
	j = B_size - 1;
	k = A_size - 1;
	ret_diff.Num[A_size] = '\0';

	while(j>=0)
	{
		borrow = 0;
		if(A.Num[i]<B.Num[j])
		{
			l=i-1;
			while(borrow==0)
			{
				if(A.Num[l]=='0')
				{
					A.Num[l] = '9';
				}
				else
				{
					A.Num[l] = A.Num[l] - 1;
					borrow = 1;
				}

				l--;
			}
		}

		ret_diff.Num[k] = ((borrow*10) + (A.Num[i]-48) - (B.Num[j]-48)) + 48;
		i--;
		j--;
		k--;
	}

	while(i>=0)
	{
		ret_diff.Num[k] = A.Num[i];
		i--;
		k--;
	}

	return ret_diff;
}

Bigint multiply(Bigint A, Bigint B, int A_size, int B_size)
{
	Bigint prod[max_dig] = {init()}, ret_prod_sum = init();
	int i, j, k, l, carry;
	
	for(i=B_size-1, l=0; i>=0; i--, l++)
	{
		for(j=A_size-1, k=0, carry=0; j>=0; j--, k++)
		{
			prod[l].Num[l+k] = ((A.Num[j]-48) * (B.Num[i]-48)) + carry;
			carry = prod[l].Num[l+k]/10;
			prod[l].Num[l+k] = prod[l].Num[l+k]%10 + 48;
		}

		while(carry!=0)
		{
			prod[l].Num[l+k] = carry;
			carry = prod[l].Num[l+k]/10;
			prod[l].Num[l+k] = prod[l].Num[l+k]%10 + 48;
			k++;
		}
		
		for(j=0; j<l; j++)
		{
			prod[l].Num[j] = '0';
		}

		prod[l].Num[k+l] = '\0';

		for(j=0; j<(k+l)/2; j++)
		{
			prod[l].Num[j] = prod[l].Num[j] + prod[l].Num[k+l-1-j];
			prod[l].Num[k+l-1-j] = prod[l].Num[j] - prod[l].Num[k+l-1-j];
			prod[l].Num[j] = prod[l].Num[j] - prod[l].Num[k+l-1-j];
		}
	}

	for(i=1; i<l; i++)
	{
		if(strlen(prod[0].Num)>strlen(prod[i].Num))
		{
			prod[0] = add(prod[0], prod[i], strlen(prod[0].Num), strlen(prod[i].Num));
		}
		else
		{
			prod[0] = add(prod[i], prod[0], strlen(prod[i].Num), strlen(prod[0].Num));
		}
	}

	ret_prod_sum = prod[0];

	return ret_prod_sum;
}

void add_help(Bigint A, Bigint B)
{
	int A_size, B_size, temp_size; 
	Bigint temp = init(), sum = init();
	
	A_size = strlen(A.Num);
	B_size = strlen(B.Num);
	
	if(B_size>A_size)
	{
		temp = A;
		temp_size = A_size; 
		
		A = B;
		A_size = B_size;
		
		B = temp;
		B_size = temp_size;
	}
	else if(A_size==B_size)
	{
		if(strcmp(A.Num, B.Num)<0)
		{
			temp = A;
			temp_size = A_size;
	
			A = B;
			A_size = B_size;
	
			B = temp;
			B_size = temp_size;
		}
	}
	
	if(A.sign=='-' || B.sign=='-')
	{
		if(A.sign==B.sign)
		{
			sum = add(A,B,A_size,B_size);
		}
		else
		{
			sum = subtract(A,B,A_size,B_size);
		}
	}
	else
	{
		sum = add(A,B,A_size,B_size);
	}
	
	sum.sign = A.sign;
	display(sum);
}

void subtract_help(Bigint A, Bigint B)
{
	int A_size, B_size, temp_size, exchange; 
	Bigint temp = init(), diff = init();
	
	A_size = strlen(A.Num);
	B_size = strlen(B.Num);
	
	exchange = 0;
	if(B_size>A_size)
	{
		temp = A;
		temp_size = A_size;
		
		A = B;
		A_size = B_size;
		
		B = temp;
		B_size = temp_size;
		exchange = 1;
	}
	else if(A_size==B_size)
	{
		if(strcmp(A.Num, B.Num)<0)
		{
			temp = A;
			temp_size = A_size;
	
			A = B;
			A_size = B_size;
	
			B = temp;
			B_size = temp_size;

			exchange = 1;
		}
	}

	if(A.sign=='-' || B.sign=='-')
	{
		if(A.sign==B.sign)
		{
			diff = subtract(A,B,A_size,B_size);
			
			if (exchange==1)
			{
				diff.sign = '+';
			}
			else
			{
				diff.sign = '-';
			}
		}
		else
		{
			diff = add(A,B,A_size,B_size);
			
			if(exchange==1)
			{
				diff.sign = B.sign;
			}
			else
			{
				diff.sign = A.sign;
			}
		}
	}
	else
	{
		diff = subtract(A,B,A_size,B_size);
		
		if(exchange==1)
		{
			diff.sign = '-';
		}
		else
		{
			diff.sign = '+';
		}

	}

	display(diff);
}

void multiply_help(Bigint A, Bigint B)
{
	int A_size, B_size, temp_size; 
	Bigint temp = init(), product = init();
	
	A_size = strlen(A.Num);
	B_size = strlen(B.Num);

	if(B_size>A_size)
	{
		temp = A;
		temp_size = A_size;
		
		A = B;
		A_size = B_size;
		
		B = temp;
		B_size = temp_size;
	}

	product = multiply(A,B,A_size,B_size);

	if(A.sign=='-' || B.sign=='-')
	{
		if(A.sign!=B.sign)
		{
			product.sign = '-';
		}
	}

	display(product);
}

main()
{
	Bigint x = init(), y = init();
	char ch;

	printf("Enter first number: ");
	x = scan(x);

	printf("Enter operartion: ");
	scanf("%c", &ch);

	getchar();

	printf("Enter second number: ");
	y = scan(y);

	switch(ch)
	{
		case '+': add_help(x,y); break;
		case '-': subtract_help(x,y); break;
		case '*': multiply_help(x,y); break;
		default: printf("\nInvalid Operartion");
	}
}