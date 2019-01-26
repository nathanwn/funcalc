#pragma once

#include <climits>
#include <string>
#include <cmath>

struct Token {
    enum TokenType {
        NIL,
        NUMBER,
        OPERATOR,
        VARIABLE
    };

    Token() = default;
    virtual ~Token() = default;

    virtual TokenType GetType() const {
        return NIL;
    };
};

struct OperatorToken : Token {
    TokenType type = OPERATOR;
    std::string symbol;
    bool is_unary;

    OperatorToken() = default;
    OperatorToken(std::string symbol) : symbol(symbol), is_unary(false) {}

    virtual TokenType GetType() const {
        return type;
    }

    std::string GetSymbol() const {
        return symbol;
    };

    void SetUnary(bool flag) {
        is_unary = flag;
    }

    bool IsUnary() const {
        return is_unary;
    }

    int Precedence() {
        if (!is_unary) {
            if (symbol == "+" || symbol == "-") {
                return 1;
            }
            if (symbol == "*" || symbol == "/") {
                return 2;
            }
            if (symbol == "^") {
                return 3;
            }
        }
        return INT_MAX;
    }

    bool IsRightAssociative() const {
        if (symbol == "^") {
            return true;
        }
        return false;
    }
};

struct NumberToken : Token {
    TokenType type = NUMBER;
    double value;

    NumberToken() = default;
    NumberToken(double value) : value(value) {}

    virtual TokenType GetType() const {
        return type;
    }

    double GetValue() const {
        return value;
    }

    void HandleUnaryOperator(OperatorToken* op_token) {
        if (op_token->GetSymbol() == "+") {
            value *= 1;
        }
        else if (op_token->GetSymbol() == "-") {
            value *= -1;
        }
        else if (op_token->GetSymbol() == "sin") {
            value = sin(value);
        }
        else if (op_token->GetSymbol() == "cos") {
            value = cos(value);
        }
        else if (op_token->GetSymbol() == "tan") {
            value = tan(value);
        }
        else if (op_token->GetSymbol() == "cot") {
            value = 1 / tan(value);
        }
        else if (op_token->GetSymbol() == "exp") {
            value = exp(value);
        }
    }

    bool IsInteger(double d) {
        const double EPS = 1e-6;
        double int_part;
        double frac_part = std::modf(d, &int_part);
        return frac_part < EPS;
    }

    void HandleBinaryOperator(OperatorToken* op_token, NumberToken* other) {
        std::string op_str = op_token->GetSymbol();
        if (op_str == "+") {
            value += other->value;
        }
        else if (op_str == "-") {
            value -= other->value;
        }
        else if (op_str == "*") {
            value *= other->value;
        }
        else if (op_str == "/") {
            value /= other->value;
        }
        else if (op_str == "^") {
            value = pow(value, other->value);
        }
        else if (op_str == "div") {
            if (!IsInteger(value) || !IsInteger(other->value)) {
                std::cout << "Error: cannot apply integer operation on floating point numbers\n";
                exit(0);
            }

            int a = (int) std::round(value);
            int b = (int) std::round(other->value);
            value = a / b;
        }
        else if (op_str == "mod") {
            if (!IsInteger(value) || !IsInteger(other->value)) {
                std::cout << "Error: cannot apply integer operation on floating point numbers\n";
                exit(0);
            }

            int a = (int) std::round(value);
            int b = (int) std::round(other->value);
            value = a % b;
        }
    }
};

struct VariableToken : Token {
    TokenType type = VARIABLE;
    std::string name;

    VariableToken()  = default;
    VariableToken(std::string name) : name(name) {}

    virtual TokenType GetType() const {
        return type;
    }

    std::string GetName() const {
        return name;
    }
};


