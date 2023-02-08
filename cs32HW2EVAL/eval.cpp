#include <cassert>
#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include "Set.h"  //  type alias: char
using namespace std;


int precedence(char input);
bool isvalidInfix(string infix);
void inToPost(string infix, string& postfix);


void inToPost(string infix, string& postfix)
{
	postfix = "";
	stack<char> signs;

	for (int i = 0; i < infix.size(); i++)
	{
		char temp = infix[i];
		

		switch (temp)
		{
			case ' ':
				break;
			case '(':
				signs.push(temp);
				break;
			case ')':
				while (signs.top() != '(')
				{
					postfix += signs.top();
					signs.pop();
				}
				signs.pop();
				break;
			case '&':
			case '!':
			case '|':
				while (!signs.empty() && signs.top() != '(' && precedence(temp) <= precedence(signs.top()))
				{
					postfix += signs.top();
					signs.pop();
				}
				signs.push(temp);
				break;
			default:
				postfix += temp;
		}
	}
	while (!signs.empty())
	{
		postfix += signs.top();
		signs.pop();
	}
}

int precedence(char input)
{
	if (input == '!') 
	{
		return 3;
	}
	else if (input == '&')
	{
		return 2;
	}
	else if (input == '|')
	{
		return 1;
	}
	else
		return 0;
}


bool isvalidInfix(string infix)
{
	if (infix.size() == 0)
	{
		return false;
	}

	string noBlank = "";

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] != ' ')
		{
			noBlank += infix[i];
		}
	}
	
	if (noBlank.size() == 0)
	{
		return false;
	}


	if (noBlank[0] != '!' && noBlank[0] != '(' && !isalpha(noBlank[0]))
	{
		return false;
	}

	if (isalpha(noBlank[0]))
	{
		if(isupper(noBlank[0]))
		{
			return false;
		}
	}

	//parenthesis checker
	stack<char> parenthesis;
	for (int i = 0; i < noBlank.size(); i++)
	{
		if (noBlank[i] == '(' || noBlank[i] == ')')
		{
			if (noBlank[i] == '(')
			{
				parenthesis.push(noBlank[i]);
			}
			if (noBlank[i] == ')' && parenthesis.empty())
			{
				return false;
			}
			if (noBlank[i] == ')' && !parenthesis.empty())
			{
				parenthesis.pop();
			}
		}
	}
	if (!parenthesis.empty())
	{
		return false;
	}


	stack<char> check;
	check.push(noBlank[0]);

	for (int i = 1; i < noBlank.size(); i++)
	{
		char temp = noBlank[i];
		char top = check.top();

		switch (temp)
		{
			case '!':
				if (top == ')' || isalpha(top))
					return false;
				check.push(temp);
				break;
			case '&':
				if (!isalpha(top) && top != ')')
					return false;
				check.push(temp);
				break;
			case '|':
				if (!isalpha(top) && top != ')')
					return false;
				check.push(temp);
				break;
			case '(':
				if (isalpha(top) || top == ')')
				{
					return false;
				}
				check.push(temp);
				break;
			case ')':
				if (!isalpha(top) && top != ')')
					return false;
				check.push(temp);
				break;
			default:
				if (!isalpha(temp) && !islower(temp))
				{
					return false;
				}
				if (top == ')' || isalpha(top))
				{
					return false;
				}
				return true;
		}

	}

	if (!isalpha(check.top()) && check.top() != ')')
	{
		return false;
	}
	else
	{
		return true;
	}
}


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
	//infix check
	if (!isvalidInfix)
	{
		return 1;
	}

	inToPost(infix, postfix);

	bool contain = true;
	for (int i = 0; i < postfix.size(); i++)
	{
		char check = postfix[i];

		if (isalpha(check))
		{
			if ((trueValues.contains(check) && !falseValues.contains(check)) || (falseValues.contains(check) && !trueValues.contains(check)))
			{
				continue;
			}
			else
			{
				contain = false;
			}
		}
	}

	if (contain == true)
	{
		stack<bool> operand;
		
		for (int i = 0; i < postfix.size(); i++)
		{
			if (isalpha(postfix[i]))
			{
				if (trueValues.contains(postfix[i]))
				{
					operand.push(true);
				}
				else
				{
					operand.push(false);
				}
			}
			else if (postfix[i] == '|' || postfix[i] == '&')
			{
				bool operand2 = operand.top();
				operand.pop();
				bool operand1 = operand.top();
				operand.pop();
				//prone to bug cuz !
				switch (postfix[i])
				{
					case '&':
						operand.push(operand1 && operand2);
						break;
					case '|':
						operand.push(operand1 || operand2);
						break;

				}
			}
			else if (postfix[i] == '!')
			{
				bool front = operand.top();
				operand.pop();
				operand.push(!front);
			}
		}

		result = operand.top();


		return 0;
	}

}
