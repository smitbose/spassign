#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
int *arr;
char *lit;
bool eval(char []);
bool subeval(char []);
int findpos(char );
bool findval(int);
bool operate(bool,bool,char);
int pos;
int n;
int main()
{
	printf("Enter the number of literals: ");
	scanf("%d",&n);
	getchar();
	printf("Enter the diifferent literals: ");
	lit = new char[n];
	for(int i=0;i<n;i++)
	{
		lit[i] = getchar();
		getchar();
	}			
	printf("Enter a well formed formula: ");
	char inp[100];
	scanf("%s",inp);
	int i=0;
	arr = new int[n];
	for(int i=0;i<n;i++)
	{
		arr[i]=1;
	}
	pos=0;	
	for(int i=0;i<n;i++)
	{
		printf("%c\t",lit[i]);
	}
	printf("Output\n");
	int lim=1;
	for(int i=1;i<=n;i++)
		lim<<=1;
	printf("%d\n",lim);
	for(int i=1;i<=lim;i++)
	{
		int p=0,iter=1;
		while(p<n)
		{
			if(i%iter==0)
			{
				arr[p] = 1-arr[p];
				p++;
				iter<<=1;
			}
			else
				break;
		}
		for(int p=0;p<n;p++)
		{
			if(arr[p] == 1)
				printf("T\t");
			else
				printf("F\t");
		}
		pos=0;
		bool val = eval(inp);
		if(val == true)
			printf("T\n");
		else
			printf("F\n");
	}
	return 0;
}
bool eval(char inp[])
{
	//printf("eval...\n");	
	bool result;
	stack<bool> s;
	while(inp[pos]!='\0')
	{
		char c=inp[pos];
		//putchar(c);
		//putchar('\n');
		if(c=='(')
		{			
			pos++;			
			result=subeval(inp);
			s.push(result);
		}
		else if(c<='Z' && c>='A')
		{
			int p=findpos(c);
			result=findval(p);
			s.push(result);
		}
		else if(c=='^' || c=='v' || c=='=' || c=='>')
		{
			char temp = inp[++pos];
			if(temp == '(')
			{
				pos++;				
				result=subeval(inp);
				bool t = s.top();
				t = operate(t,result,c);
				s.pop();
				s.push(t);
			}
			else if(temp<='Z' && temp>='A')
			{
				int p = findpos(temp);
				result = findval(p);
				bool t = s.top();
				t = operate(t,result,c);
				s.pop();
				s.push(t);
			}
		}
		else if(c=='~')
		{
			char temp = inp[++pos];
			if(temp == '(')
			{
				pos++;				
				result = subeval(inp);
				if(result == true)
					s.push(false);
				else
					s.push(true);
			}
		}
		pos++;
	}
	return s.top();
}
bool subeval(char inp[])
{
	//printf("subeval...\n");	
	bool result;
	stack<bool> s;
	while(inp[pos]!=')')
	{
		char c=inp[pos];
		//putchar(c);
		//putchar('\n');
		if(c=='(')
		{			
			pos++;			
			result=subeval(inp);
			s.push(result);
		}
		else if(c<='Z' && c>='A')
		{
			int p=findpos(c);
			result=findval(p);
			s.push(result);
		}
		else if(c=='^' || c=='v' || c=='=' || c=='>')
		{
			char temp = inp[++pos];
			if(temp == '(')
			{
				pos++;				
				result=subeval(inp);
				bool t = s.top();
				t = operate(t,result,c);
				s.pop();
				s.push(t);
			}
			else if(temp<='Z' && temp>='A')
			{
				int p = findpos(temp);
				result = findval(p);
				bool t = s.top();
				t = operate(t,result,c);
				s.pop();
				s.push(t);
			}
		}
		else if(c=='~')
		{
			char temp = inp[++pos];
			if(temp == '(')
			{
				pos++;				
				result = subeval(inp);
				if(result == true)
				{
					s.push(false);
					printf("False\n");
				}
				else
				{
					s.push(true);
					printf("True\n");
				}
			}
		}
		pos++;
	}
	return s.top();
}
bool operate(bool a,bool b,char op)
{
	if(op=='^')
	{
		if(a==true && b==true)
			return true;
		else
			return false;
	}
	else if(op == 'v')
	{
		if(a==false && b==false)
			return false;
		else
			return true;
	}
	else if(op=='=')
	{
		if(a==b)
			return true;
		else 
			return false;
	}
	else if(op=='>')
	{
		if(a==false || a==b)
			return true;
		else
			return false;
	}
}
int findpos(char c)
{
	for(int i=0;i<n;i++)
	{
		if(lit[i] == c)
			return i;
	}
}
bool findval(int p)
{
	if(arr[p]==1)
		return true;
	else
		return false;
}
