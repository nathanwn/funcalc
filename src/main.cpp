#include <iostream>
#include <string>
#include <iomanip>

#include "../lib/dsalib-cpp/structures/array-list.h"
#include "../lib/dsalib-cpp/structures/queue.h"
#include "../lib/dsalib-cpp/structures/stack.h"
#include "../lib/dsalib-cpp/structures/tree-map.h"
#include "../lib/dsalib-cpp/structures/tree-set.h"
#include "../lib/dsalib-cpp/util/util.h"

#include "io.h"
#include "token.h"

class Calculator {
    TreeSet<std::string> operator_set;
    ArrayList<std::string> variables;
    TreeMap<std::string, double> const_map;
    TreeMap<std::string, double> var_map;

    void Initialize() {
        std::string operators[] = {"+", "-", "*", "/", "^", "div", "mod", "(", ")", "sin", "cos", "tan", "cot", "exp"};
        int num_operators = sizeof(operators) / sizeof(*operators);
        for (int i = 0; i < num_operators; i++) {
            operator_set.Push(operators[i]);
        }
        KeyValuePair<std::string, double> consts[] = {{"pi", acos(-1)}};
        int num_consts = sizeof(consts) / sizeof(*consts);
        for (int i = 0; i < num_consts; i++) {
            const_map.Push(consts[i].key, consts[i].value);
        }
    }

    bool ValidateEqualSign(std::string line) {
        bool has_equal_sign = false;

        for (char c : line) {
            if (c == '=') {
                if (has_equal_sign) return false;
                has_equal_sign = true;
            }
        }

        return has_equal_sign;
    }

    std::string SplitVarName(std::string &line, int line_num) {
        int length = line.length();
        std::string var_name;
        int i;

        for (i = 0; i < length; i++) {
            if (!util::IsLetter(line[i])) break;
            var_name += line[i];
        }

        if (var_name.length() == 0) {
            std::cout << "Error: no variable to assign on line " << line_num << '\n';
            exit(0);
        }

        int equal_sign_pos = -1;

        for (; i < length; i++) {
            if (line[i] == '=') {
                equal_sign_pos = i;
                break;
            }
        }

        if (equal_sign_pos == -1) {
            std::cout << "Error: no equal sign on line " << line_num << '\n';
        }

        line = line.substr((uint32_t) (equal_sign_pos + 1), std::string::npos);
        return var_name;
    }

    ArrayList<Token*> Tokenize(std::string& line, int line_num) {
        ArrayList<Token*> tokens;
        int length = line.length();

        for (int i = 0; i < length; i++) {
            if (line[i] == ' ') continue;

            if (line[i] == '.' || util::IsDigit(line[i])) {
                bool has_decimal_point = line[i] == '.';
                std::string num_string;

                while (i < length) {
                    if (util::IsDigit(line[i])) {
                        num_string += line[i];
                    }
                    else if (line[i] == '.') {
                        if (has_decimal_point) {
                            std::cout << "Error: invalid number on line " << line_num << ", column " << i << '\n';
                            exit(0);
                        }
                        num_string += '.';
                    }
                    else {
                        break;
                    }
                    ++i;
                }
                --i;

                double num = std::stod(num_string);
                tokens.PushBack(new NumberToken(num));
            }
            else if (util::IsLetter(line[i])) {
                std::string word;

                while (i < length) {
                    if (util::IsLetter(line[i])) {
                        word += line[i];
                        ++i;
                    }
                    else break;
                }
                --i;

                if (operator_set.Has(word)) {
                    tokens.PushBack(new OperatorToken(word));
                }
                else {
                    tokens.PushBack(new VariableToken(word));
                }
            }
            else {
                std::string symbol;
                symbol += line[i];

                if (!operator_set.Has(symbol)) {
                    std::cout << "Error: invalid symbol on line " << line_num << ": " << symbol << '\n';
                    std::cout << "[" << symbol << "]\n";
                    exit(0);
                }

                tokens.PushBack(new OperatorToken(symbol));
            }
        }

        return tokens;
    }

    void CheckUnaryOperators(ArrayList<Token*>& tokens) {
        /**
         * Unary Operator Cases:
         * 1. first token in the expression
         * 2. after opening parenthesis
         * 3. after an operator
         */
        for (int i = 0; i < tokens.Size(); i++) {
            if (tokens[i]->GetType() == Token::OPERATOR) {
                auto cur_token = dynamic_cast<OperatorToken*>(tokens[i]);

                if (i == 0) {
                    cur_token->SetUnary(true);
                }
                else if (tokens[i - 1]->GetType() == Token::OPERATOR) {
                    auto prev_token = dynamic_cast<OperatorToken*>(tokens[i - 1]);

                    if (prev_token->symbol != ")") {
                        cur_token->SetUnary(true);
                    }
                }
            }
        }
    }

    void ProcessVariables(ArrayList<Token*>& tokens, int line_num) {
        for (int i = 0; i < tokens.Size(); i++) {
            if (tokens[i]->GetType() == Token::VARIABLE) {
                auto token = dynamic_cast<VariableToken *>(tokens[i]);
                std::string name = token->GetName();

                double number;

                if (const_map.Has(name)) {
                    number = const_map.Get(name);
                }
                else {
                    if (!var_map.Has(name)) {
                        std::cout << "Error: unassigned variable " + name + " on line " << line_num << '\n';
                        exit(0);
                    }
                    number = var_map.Get(name);
                }

                delete tokens[i];
                tokens[i] = new NumberToken(number);
            }
        }
    }

    Queue<Token*> ShuntingYard(ArrayList<Token*>& tokens, int line_num) {
        Stack<OperatorToken*> op_stack;
        Queue<Token*> postfix_queue;
        for (int i = 0; i < tokens.Size(); i++) {
            if (tokens[i]->GetType() == Token::NUMBER) {
                postfix_queue.Enqueue(tokens[i]);
            }
            else {
                auto op_token = dynamic_cast<OperatorToken*>(tokens[i]);

                if (op_token->IsUnary()) {
                    op_stack.Push(op_token);
                }
                else if (op_token->GetSymbol() == "(") {
                    op_stack.Push(op_token);
                }
                else if (op_token->GetSymbol() == ")") {
                    while (op_stack.Top()->GetSymbol() != "(") {
                        postfix_queue.Enqueue(dynamic_cast<Token*>(op_stack.Pop()));
                    }
                    op_stack.Pop(); // Pop "("
                }
                else {
                    if (!op_stack.Empty() && !op_stack.Top()->IsRightAssociative()) {
                        while (!op_stack.Empty() && op_stack.Top()->GetSymbol() != "(" && op_stack.Top()->Precedence() >= op_token->Precedence()) {
                            postfix_queue.Enqueue(dynamic_cast<Token*>(op_stack.Pop()));
                        }
                    }
                    else {
                        while (!op_stack.Empty() && op_stack.Top()->GetSymbol() != "(" && op_stack.Top()->Precedence() > op_token->Precedence()) {
                            postfix_queue.Enqueue(dynamic_cast<Token*>(op_stack.Pop()));
                        }
                    }
                    op_stack.Push(op_token);
                }
            }
        }

        while (!op_stack.Empty()) {
            postfix_queue.Enqueue(op_stack.Pop());
        }

        return postfix_queue;
    }

    double Evaluate(Queue<Token*>& postfix_queue, int line_num) {
        Stack<Token*> num_stack;

        while (!postfix_queue.Empty()) {
            if (postfix_queue.Front()->GetType() != Token::OPERATOR) {
                num_stack.Push(postfix_queue.Dequeue());
            }
            else {
                auto op_token = dynamic_cast<OperatorToken*>(postfix_queue.Dequeue());
                if (op_token->IsUnary()) {
                    auto num_token = dynamic_cast<NumberToken*>(num_stack.Pop());
                    num_token->HandleUnaryOperator(op_token);
                    num_stack.Push(dynamic_cast<Token*>(num_token));
                }
                else {
                    auto num_token_b = dynamic_cast<NumberToken*>(num_stack.Pop());
                    auto num_token_a = dynamic_cast<NumberToken*>(num_stack.Pop());
                    num_token_a->HandleBinaryOperator(op_token, num_token_b);
                    num_stack.Push(dynamic_cast<Token*>(num_token_a));
                }
            }
        }

        if (num_stack.Size() != 1) {
            std::cout << "Error: cannot evaluate expression on line " << line_num << '\n';
            exit(0);
        }

        double result = dynamic_cast<NumberToken*>(num_stack.Pop())->GetValue();
        return result;
    }

    void PrintTokens(ArrayList<Token*>& tokens, int line_num) {
        std::cout << "Line " << line_num << ": ";
        for (int i = 0; i < tokens.Size(); i++) {
            if (tokens[i]->GetType() == Token::NUMBER) {
                std::cout << "Number[";
                auto token = dynamic_cast<NumberToken*>(tokens[i]);
                std::cout << token->GetValue() << "], ";
            }
            else if (tokens[i]->GetType() == Token::OPERATOR) {
                std::cout << "Operator[";
                auto token = dynamic_cast<OperatorToken*>(tokens[i]);
                std::cout << token->GetSymbol() << "], ";
            }
            else if (tokens[i]->GetType() == Token::VARIABLE) {
                std::cout << "Variable[";
                auto token = dynamic_cast<VariableToken*>(tokens[i]);
                std::cout << token->GetName() << "], ";
            }
        }
        std::cout << '\n';
    }

    void ProcessLine(std::string& line, int line_num) {
        ArrayList<Token*> tokens = Tokenize(line, line_num);
#ifdef DEBUG
        PrintTokens(tokens, line_num);
#endif // DEBUG
        CheckUnaryOperators(tokens);
        ProcessVariables(tokens, line_num);
        Queue<Token*> postfix_queue = ShuntingYard(tokens, line_num);

        double result = Evaluate(postfix_queue, line_num);
        std::string variable = variables[line_num];

        if (var_map.Has(variable)) {
            var_map.Pop(variable);
        }

        var_map.Push(variable, result);
    }

public:
    void Run() {
        Initialize();

        ArrayList<std::string> lines = io::ReadLines();

        int num_lines = lines.Size();
        for (int i = 0; i < num_lines; i++) {
            std::cout << lines[i] << '\n';
        }

        for (int i = 0; i < num_lines; i++) {
            if (!ValidateEqualSign(lines[i])) {
                std::cout << "Error: Invalid number of equal signs (=) - line " << i << '\n';
                std::cout << "Expression: " << lines[i] << '\n';
                exit(0);
            }
        }

        for (int i = 0; i < num_lines; i++) {
            std::string var_name = SplitVarName(lines[i], i);
            variables.PushBack(var_name);
        }

        for (int i = 0; i < num_lines; i++) {
            ProcessLine(lines[i], i);
        }

        ArrayList<KeyValuePair<std::string, double>> table = var_map.Entries();

        console::DrawLine();
        std::cout << "Evaluation Result:\n";

        for (int i = 0; i < table.Size(); i++) {
            KeyValuePair<std::string, double> pair = table[i];
            std::string variable = pair.key;
            double value = pair.value;
            std::cout << std::fixed << std::setprecision(6);
            std::cout << '[' << variable << ']' << " = " << value << '\n';
        }
    }
};

int main() {
    Calculator calculator;
    calculator.Run();
    return 0;
}
