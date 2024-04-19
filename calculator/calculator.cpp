#include <iostream>
#include <stack>
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

int main()
{
    std::string s = "3 * 10 + 5 - 100 / 2";
    std::string result = infixToRPN(s);
    std::cout << result;
}