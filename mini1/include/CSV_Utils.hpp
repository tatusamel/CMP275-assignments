#ifndef CSV_UTILS_HPP
#define CSV_UTILS_HPP

#include <string>
#include <vector>
#include <cstddef>

// Free function to split a CSV line.
inline std::vector<std::string> splitCSVLine(const std::string &line) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;
    
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        
        if (c == '"') {
            // Check if it's an escaped quote.
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                token.push_back('"');
                ++i;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(c);
        }
    }
    tokens.push_back(token);
    return tokens;
}

#endif // CSV_UTILS_HPP
