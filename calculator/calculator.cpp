#include <iostream>
#include <stack>
#include <string>
bool isOperator(char c)
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isOperand(char c)
{
	return isdigit(c);
}

int precedence(char c)
{
	if (c == '+' || c == '-') return 1;
	if (c == '*' || c == '/') return 2;
}

void Count(std::stack<double>& operands, std::string token, char token_0)
{
	double secondOperand = operands.top();
	operands.pop();
	double firstOperand = operands.top();
	operands.pop();
	//char op = token[0];

	double result;
	switch (token_0)
	{
	case '+':
		result = firstOperand + secondOperand;
		break;
	case '-':
		result = firstOperand - secondOperand;
		break;
	case '*':
		result = firstOperand * secondOperand;
		break;
	case '/':
		result = firstOperand / secondOperand;
		break;
	}
	operands.push(result);
}

std::string infixToRPN(const std::string& expression)
{
	std::stack<char> operators;
	std::string output;
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (expression.std::string::empty())
			return "";

		if (expression[i] == ' ')
			continue;

		if (isOperand(expression[i]))
		{
			std::string operand;
			while (i < expression.size() && isOperand(expression[i]))
				operand += expression[i++];
			--i;
			output += operand + ' '; //пробелы между операндами и операциями
		}

		else if (isOperator(expression[i]))
		{
			while (!operators.empty() && precedence(expression[i]) <= precedence(operators.top()))
			{
				output += operators.top();
				operators.pop();
				output += ' ';
			}
			operators.push(expression[i]); // если оператор по приоритету больше то просто добавляем без проверки
		}
	}

	while (!operators.empty())
	{
		output += operators.top();
		operators.pop();
		output += ' ';
	}

	return output;
}

double evaluateRPN(const std::string& rpn)
{
	std::stack<double> operands;
	size_t pos = 0;

	while (pos < rpn.size())
	{
		if (rpn[pos] == ' ')
		{
			++pos;
			continue;
		}

		std::string token;
		while (pos < rpn.size() && rpn[pos] != ' ')
			token += rpn[pos++];
		char token_0 = token[0];

		if (isOperand(token_0))
			operands.push(std::stod(token));

		else if (isOperator(token_0))
		{
			Count(operands, token, token_0);
		}
		++pos;
	}

	return operands.top();
}


int Сalculate()
{
	setlocale(LC_ALL, "rus");
	std::cout << "Введите математическое выражение: ";
	std::string example;
	getline(std::cin, example);
	std::string RPN = infixToRPN(example);
	if (RPN == "")
	{
		std::cout << "Пустая строка";
		return 0;
	}
	double answer = evaluateRPN(RPN);
	std::cout << "Ответ: " << answer;
	return answer;
}

int main()
{
	Сalculate();
}