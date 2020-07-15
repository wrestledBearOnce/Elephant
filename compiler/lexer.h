#pragma once

#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <memory>

namespace elephant
{
    /**
     * @brief This is one recognized token of elephant, e. g. eof, function definition, etc.
    */
    struct Token
    {
        enum Type
        {
            END = -1,

            // commands
            FUNC = -2,
            EXTERN = -3,

            // primary
            IDENTIFIER = -4,
            NUMBER = -5,

            // just a char
            CHAR = -6
        };

        Type m_type{};

        std::string m_identifier{};
        double m_value{};

        char m_char_val{};
    };

    // TODO: Replace with a proper state machine / pushdown automaton
    /**
        * @brief Opens a *.ele file and parses the input into tokens which can then be sorted into an AST
        * @param file
        * @return
    */
    [[nodiscard]] const std::vector<Token> parse_source_file(const std::filesystem::path& file);
}