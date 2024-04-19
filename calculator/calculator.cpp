#include <iostream>
#include <stack>
#include<string>
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

std::string infixToRPN(const std::string& expression)
{
    std::stack<char> operators;
    std::string output;
    for (size_t i = 0; i < expression.size(); i++)
    {
        if (expression[i] == ' ')
            continue;

        if (isOperand(expression[i]))
        {
            std::string operand;
            while (i < expression.size() && isOperand(expression[i]))
            {
                operand += expression[i++];
            }
            output += operand + ' '; //пробелы между операндами и операциями
            //--i; //WHY???
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
        { ++pos; continue; }

        std::string token;
        while (pos < rpn.size() && rpn[pos] != ' ')
            token += rpn[pos++];

        if (isOperand(token[0]))
            operands.push(std::stod(token));

        else if (isOperator(token[0]))
        {
            double secondOperand = operands.top();
            operands.pop();
            double firstOperand = operands.top();
            operands.pop();
            char op = token[0];

            double result;
            switch (op)
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
        ++pos;
    }
    return operands.top();
}

int main()
{ 
    setlocale(LC_ALL, "rus");
    std::string example;
    std::cout << "Введите математический пример (между операндами и операторами пробел): ";
    getline(std::cin, example);
    std::string RPN = infixToRPN(example);
    double answer = evaluateRPN(RPN);
    std::cout << "Ответ: " << answer;
    
}