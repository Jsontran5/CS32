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


int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
	//infix check
	if (!isvalidInfix(infix))
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
	else
	{
		for (int i = 0; i < postfix.size(); i++)
		{
			char check = postfix[i];
			if (!falseValues.contains(check) && !trueValues.contains(check))
			{
				return 2;
			}
			else if (falseValues.contains(check) && trueValues.contains(check))
			{
				return 3;
			}
		}
		return 3;
	}

}


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
		if (isupper(noBlank[0]))
		{
			return false;
		}
	}


	//uppercase check
	for (int i = 0; i < noBlank.size(); i++)
	{
		if (isalpha(noBlank[i]))
		{
			if (isupper(noBlank[i]))
			{
				return false;
			}
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



int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("()z", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("n+y", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x" && answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cout << "Passed all tests" << endl;
}