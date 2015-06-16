#include <cstdio>
#include <cstring>
#include <stack>
#include <algorithm>
#include "checker.h"
using namespace std;
int *arr;
char *lit;
bool eval(char []);
bool subeval(char [],int);
int findpos(char );
bool findval(int);
bool operate(bool,bool,char);
int prece(char);
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
	if(check(inp)==0)
		return 0;
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
	//printf("%d\n",lim);
	bool tf = true, ff =true;
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
		{
			printf("T\n");
			ff = false;
		}
		else
		{
			printf("F\n");
			tf = false;
		}
	}
	if(tf == true)
	{
		printf("This is a valid formula!\n");
	}
	else if(ff == true)
		printf("This is an inconsistent formula!\n");
	else
		printf("The formula is consistent but invalid!\n");
	return 0;
}
bool eval(char exp[])
{
    stack<bool> s;
    bool result;
    while(exp[pos]!='\0')
    {
        char c = exp[pos];
        if(c<='Z' && c>='A')
        {
            int p = findpos(c);
            result = findval(p);
            s.push(result);
        }
        else if(c == '(')
        {
            int p = prece(')');
            pos++;
            bool result = subeval(exp,p);
            s.push(result);
        }
        else if(c == '~')
        {
            char temp = exp[++pos];
            if(temp<='Z' && temp>='A')
            {
                int p = findpos(temp);
                result = findval(p);
            }
            else if(temp == '(')
            {
                pos++;
                int p = prece(')');
                result = subeval(exp,p);
            }
            if(result == true)
                s.push(false);
            else if(result == false)
                s.push(true);
        }
        else if(c == 'v' || c=='>' || c=='=')
        {
            pos++;
            int p = prece(c);
            result = subeval(exp,p);
            bool temp = s.top();
            s.pop();
            temp = operate(temp,result,c);
            s.push(temp);
        }
        else if(c == '^')
        {
            char temp = exp[++pos];
            if(temp == '(')
            {
                int p = prece(')');
                pos++;
                result = subeval(exp,p);
                bool t = s.top();
                s.pop();
                t = operate(t,result,c);
                s.push(t);
            }
            else
            {
                int p = findpos(temp);
                result = findval(p);
                bool t = s.top();
                s.pop();
                t = operate(t, result, c);
                s.push(t);
            }
        }
        pos++;
    }
    return s.top();
}
bool subeval(char exp[],int prec)
{
    stack<bool> s;
    bool result;
    while(prece(exp[pos])<=prec || (exp[pos]<='Z' && exp[pos]>='A') || (exp[pos] == '~'))
    {
        char c= exp[pos];
        if(c<='Z' && c>='A')
        {
            int p = findpos(c);
            result = findval(p);
            s.push(result);
        }
        else if(c == '(')
        {
            int p = prece(')');
            pos++;
            bool result = subeval(exp,p);
            s.push(result);
        }
        else if(c == '~')
        {
            char temp = exp[++pos];
            if(temp<='Z' && temp>='A')
            {
                int p = findpos(temp);
                result = findval(p);
            }
            else if(temp == '(')
            {
                pos++;
                int p = prece(')');
                result = subeval(exp,p);
            }
            if(result == true)
                s.push(false);
            else if(result == false)
                s.push(true);
        }
        else if(c == 'v' || c=='>' || c=='=')
        {
            pos++;
            int p = prece(c);
            result = subeval(exp,p);
            bool temp = s.top();
            s.pop();
            temp = operate(temp,result,c);
            s.push(temp);
        }
        else if(c == '^')
        {
            char temp = exp[++pos];
            if(temp == '(')
            {
                int p = prece(')');
                pos++;
                result = subeval(exp,p);
                bool t = s.top();
                s.pop();
                t = operate(t,result,c);
                s.push(t);
            }
            else
            {
                int p = findpos(temp);
                result = findval(p);
                bool t = s.top();
                s.pop();
                t = operate(t, result, c);
                s.push(t);
            }
        }
        pos++;
        if(exp[pos] == '\0')
        {
            pos--;
            return s.top();
        }
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
int prece(char c)
{
    if(c == ')')
        return 6;

    else if(c == 'v')
        return 3;
    else if(c == '>' || c=='=')
        return 4;
    else if(c == '^')
        return 2;
    else if(c == '(')
        return 1;
}
