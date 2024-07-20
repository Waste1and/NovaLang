#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <string>
#include <sstream>

#include "runtime.h"

// Global variable to store the symbol table
std::map<std::string, int> symbolTable;

// Function to evaluate an expression
int Runtime::evaluateExpression(const ASTNode& node) {
  if (node.type == "Integer") {
    return std::stoi(node.value);
  } else if (node.type == "Identifier") {
    return symbolTable[node.value];
  } else if (node.type == "BinaryOperator") {
    int left = evaluateExpression(*node.children[0]);
    int right = evaluateExpression(*node.children[1]);
    if (node.value == "+") {
      return left + right;
    } else if (node.value == "-") {
      return left - right;
    } else if (node.value == "*") {
      return left * right;
    } else if (node.value == "/") {
      if (right == 0) {
        throw std::runtime_error("Division by zero error");
      }
      return left / right;
    }
  }
  throw std::runtime_error("Invalid expression");
}

// Function to execute a statement
void Runtime::executeStatement(const ASTNode& node) {
  if (node.type == "Assignment") {
    symbolTable[node.children[0]->value] = evaluateExpression(*node.children[1]);
  } else if (node.type == "Print") {
    std::cout << evaluateExpression(*node.children[0]) << std::endl;
  } else if (node.type == "IfStatement") {
    if (evaluateExpression(*node.children[0])) {
      executeBlock(*node.children[1]);
    } else if (node.children.size() > 2) {
      executeBlock(*node.children[2]);
    }
  } else if (node.type == "WhileStatement") {
    while (evaluateExpression(*node.children[0])) {
      executeBlock(*node.children[1]);
    }
  }
}

// Function to execute a block of statements
void Runtime::executeBlock(const ASTNode& node) {
  for (const auto& child : node.children) {
    executeStatement(*child);
  }
}

// Function to execute bytecode
void Runtime::execute(const std::vector<int>& bytecode) {
  std::stack<int> operandStack;

  for (int instruction : bytecode) {
    // Interpret bytecode instructions (example)
    switch (instruction) {
      case PUSH_INTEGER:
        operandStack.push(operandStack.top());
        break;
      case ADD:
        operandStack.push(operandStack.top() + operandStack.top());
        break;
      // ... other instructions
    }
  }
}
