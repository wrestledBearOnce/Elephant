#include "main.h"


int main()
{
    std::cout << "Hello 🐘." << std::endl;
    
    auto result = elephant::parse_source_file(std::filesystem::path("./test.ele"));

    auto lhs = std::make_unique<elephant::VariableExprAST>("x");
    auto rhs = std::make_unique<elephant::VariableExprAST>("y");
    auto expr = std::make_unique<elephant::BinaryExprAST>('+', std::move(lhs),
        std::move(rhs));

    return 0;
}
