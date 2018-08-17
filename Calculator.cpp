#include <iostream>
#include <ctype.h>
#include <process.h>
#include <stdlib.h>

using namespace std;

struct postfix
{
	char ep;
	postfix *link;
};

postfix *front,*rear,*ptr,*save;
char exp[30];

postfix *newpost(char ep)
{
	ptr = new postfix;
	ptr->ep = ep;
	ptr->link = NULL;
	if(front == NULL)
		front = rear = ptr;
	else
	{
		rear->link = ptr;
		rear = ptr;
	}
}

int create_postfix(postfix *pt)
{
	bool check = 0;
	char operators[15];
	operators[0] = 'a';
	exp[0] = 'a';
	int n = 0,ob[10],k=0;
	int z = 0;
	while(pt != NULL)
	{
		check = 0;
		if(isdigit(pt->ep))
		{
			if(exp[0] != 'a')
				z++;
			exp[z] = pt->ep;
			if(isdigit(pt->link->ep))
			{
				if(exp[0] != 'a')
					z++;
				exp[z] = '%';
			}
		}
		else
		{
			if(pt->ep == '(')
			{
				if(operators[n] != 'a')
					n++;
				operators[n] = pt->ep;
				k++;
				ob[k] = n;
			}
			else
				if(pt->ep == '/')
				{
					if(operators[n] == '*' || operators[n] == '/')
					{
						if(exp[0] != 'a')
							z++;
						exp[z] = operators[n];
						operators[n] = '/';
					}
					else
					{
						if(operators[n] != 'a')
							n++;
						operators[n] = pt->ep;
					}	
				}
				else
				if(pt->ep == '*')
				{
					if(operators[n] == '*' || operators[n] == '/')
					{
						if(exp[0] != 'a')
							z++;
						exp[z] = operators[n];
						operators[n] = '*';
					}
					else
					{
						if(operators[n] != 'a')
							n++;
						operators[n] = pt->ep;
					}		
				}
				else
				if(pt->ep == '+')
				{
					if(operators[n] == '*' || operators[n] == '/' || operators[n] == '-' || operators[n] == '+')
					{
						if(exp[0] != 'a')
							z++;
						exp[z] = operators[n];
						operators[n] = '+';
					}
					else
					{
						if(operators[n] != 'a')
							n++;
						operators[n] = pt->ep;
					}
				}
				else
				if(pt->ep == '-')
				{
					if(operators[n] == '*' || operators[n] == '/' || operators[n] == '-' || operators[n] == '+')
					{
						if(exp[0] != 'a')
							z++;
						exp[z] = operators[n];
						operators[n] = '-';
					}
					else
					{
						if(operators[n] != 'a')
							n++;
						operators[n] = pt->ep;
					}
				}
				else
				if(pt->ep == ')')
				{
					for(int i = n; i>=ob[k];--i)
					{
						if(operators[i] == '(')
						{
							--n;
							break;
						}
						else
						{
							if(exp[0] != 'a')
								z++;
							exp[z] = operators[i];
							--n;
						}
					}
					--k;
				}
				for(int i = n; i>0; --i)
				{
					if((operators[i] == '+' || operators[i] == '-')&&(operators[i-1] == '+' || operators[i-1] == '-'))
					{
						if(exp[0] != 'a')
							z++;
						exp[z] = operators[i-1];
						operators[i-1] = operators[i];
						--n;
					}
				}
		}
		pt = pt->link;
	}
	for(int i =n;i>=0;--i)
	{
		if(exp[0] != 'a')
			z++;
		exp[z] = operators[i];
	}
	while(front != rear)
	{
		save = front;
		front = front->link;
		delete save;
	}
	delete front;
	front = rear = NULL;
	return z;
}

void evaluate(int count)
{
	int n = 0,n1=0,x;
	float cal[30];
	bool flow = 0;
	while(n1 <= count)
	{
		if(exp[n1] == '/')
		{
			cal[n-1] = cal[n-1]/cal[n];
			--n;
		}
		else
		if(exp[n1] == '*')
		{
			cal[n-1] = cal[n-1]*cal[n];
			--n;
		}
		else
		if(exp[n1] == '+')
		{
			cal[n-1] = cal[n-1]+cal[n];
			--n;
		}
		else
		if(exp[n1] == '-')
		{
			cal[n-1] = cal[n-1]-cal[n];
			--n;
		}
		else
		if(exp[n1] == '%')
		{
			x = exp[n1+1]-'0';
			cal[n] = cal[n]*10+x;
			n1++;
		}
		else
		{
			if(flow == 0)
			{
				flow = 1;
			}
			else
				n++;
			cal[n] = exp[n1]-'0';
		}
		n1++;
	}
	cout<<"\t\tAnswer :- "<<cal[0]<<endl;
}

int main()
{
	char ep,ch;
	int count = 0;
	cout<<"\t\t\t\t\t\t--Calculator--"<<endl;
	cout<<"\n\t Use ';' to end the calculation Part.."<<endl;
	do
	{
		cout<<"\t\t--> ";
		while(ep != ';')
		{
			cin>>ep;
			newpost(ep);
		}
		if(ep == ';')
		{
			count = create_postfix(front);
			evaluate(count);
		}
		ep = '0';
		cout<<"Want to calculate More? (Y/N):- ";
		cin>>ch;
		ch = toupper(ch);
		if(ch != 'Y')
			exit(0);
	}while(ch == 'Y');
	system("PAUSE");
}