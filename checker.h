#include <cstdio>
#include <stack>
#include <algorithm>
using namespace std;
int check(char inp[])
{
	//char inp[100];
	//scanf("%s",inp);
	stack<char> s;
	int i=0;
	char c=inp[i];
	while(inp[i]!='\0')
	{
		c=inp[i];
		if(c=='(' || (c>='A' && c<='Z') )
		{
			s.push(c);
		}
		else if(c=='^' || c=='v' || c=='>' || c=='<')
		{
			i++;
			char temp=inp[i];
			if(temp=='(' )
			{
				s.push(temp);
				//i++;
				//continue;
			}
			else if(temp<='Z' && temp>='A')
			{
				if(s.empty())
				{
					printf("Not a well formed formula!\n");
					return 0;
				}				
				s.pop();
				s.push('a');
			}
			else
			{
				printf("Not a well formed formula!\n");
				return 0;
			}
		}
		else if(c<='Z' && c>='A')
		{
			char temp = s.top();
			if(temp<='Z' && temp>='A')
			{
				printf("Not a well formed formula!\n");
				return 0;
			}
			else
			{
				s.push(c);
			}		
		}
		else if(c=='~')
		{
			if(i!=0 && inp[i-1]<='Z' && inp[i-1]>='A')
			{
				printf("Not a well formed formula!\n");
				return 0;
			}
			else
			{
				i++;
				char temp = inp[i];
				if(temp == '(' || (temp<='Z' && temp>='A'))
				{
					s.push(temp);
				}
				else
				{
					printf("Not a well formed formula!\n");
				}
			}
		}
		else if(c==')')
		{
			if(s.empty())
			{
				printf("Not a well formed formula!\n");
			}			
			while(1)
			{
				if(s.empty())
				{
					printf("Not a well formed formula!\n");
					return 0;
				}
				else if(s.top()!='(')
				{
					s.pop();
				}
				else if(s.top()=='(')
				{	
					s.pop();
					s.push('a');
					break;
				}
			}
			
		}	
		else
		{
			printf("Not a well formed formula!\n");
			return 0;
		}				
		i++;
	}
	printf("The formula is a well formed formula!\n");
	return 1;
}
