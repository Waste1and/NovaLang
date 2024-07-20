#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "lexer.h"
#include "parser.h"
#include "semantic_analyzer.h"
#include "code_generator.h"
#include "runtime.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: novalang <filename>\n";
    return 1;
  }

  std::string filename = argv[1];

  // Read source code from the file
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << "\n";
    return 1;
  }
  std::string sourceCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();

  // Tokenization
  Lexer lexer(sourceCode);
  std::vector<Token> tokens = lexer.tokenize();

  // Parsing
  Parser parser(tokens);
  std::shared_ptr<ASTNode> ast = parser.parse();

  // Semantic Analysis
  SemanticAnalyzer semanticAnalyzer;
  if (!semanticAnalyzer.check(ast)) {
    std::cerr << "Semantic errors found in the program.\n";
    return 1;
  }

  // Code Generation
  CodeGenerator codeGenerator;
  std::vector<int> bytecode = codeGenerator.generate(ast);

  // Runtime Execution
  Runtime runtime;
  runtime.execute(bytecode);

  return 0;
}
