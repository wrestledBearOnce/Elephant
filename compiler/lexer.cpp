#include "lexer.h"

const std::vector<elephant::Token> elephant::parse_source_file(const std::filesystem::path& file)
{
    std::vector<Token> result{};

    std::ifstream stream;
    stream.open(file.string(), std::ios::in);

    if (stream.good())
    {
        auto current_char = std::make_unique<char>();
        *current_char = ' ';

        Token current_token{};

        while (stream.read(current_char.get(), 1))
        {
            // ignore whitespace
            if (std::isspace(*current_char))
                continue;
            
            if (std::isalpha(*current_char)) //  [a-zA-Z][a-zA-Z0-9]* 
            {
                while (std::isalnum(*current_char))
                {
                    current_token.m_identifier += *current_char;
                    stream.read(current_char.get(), 1);
                }

                if (current_token.m_identifier == "func")
                {
                    current_token.m_type = elephant::Token::FUNC;
                    result.push_back(current_token);
                    current_token.m_identifier.clear();
                }

                else if (current_token.m_identifier == "extern")
                {
                    current_token.m_type = elephant::Token::EXTERN;
                    result.push_back(current_token);
                    current_token.m_identifier.clear();
                }
                else
                {
                    current_token.m_type = elephant::Token::IDENTIFIER;
                    result.push_back(current_token);
                    current_token.m_identifier.clear();
                }
            }
            else if (std::isdigit(*current_char) || *current_char == '.') // Number: [0-9.]+
            {   

                std::string nbr_as_string{};

                do {
                    nbr_as_string += *current_char;
                    stream.read(current_char.get(), 1);
                } while (std::isdigit(*current_char) || *current_char == '.');

                current_token.m_value = std::strtod(nbr_as_string.c_str(), 0);
                current_token.m_type = elephant::Token::NUMBER;
                result.push_back(current_token);
                current_token.m_value = 0;
            }
            else if (*current_char == '#') {
                // Comment until end of line.
                do
                {
                    stream.read(current_char.get(), 1);
                }
                while (*current_char != EOF && *current_char != '\n' && *current_char != '\r');
            }
            else
            {
                current_token.m_type = elephant::Token::CHAR;
                current_token.m_char_val = *current_char;
                result.push_back(current_token);
                current_token.m_char_val = ' ';
            }
        };
    }
    else
    {
        throw std::runtime_error("Couldn't open stream " + file.string());
    }

    stream.close();
    return result;
}



