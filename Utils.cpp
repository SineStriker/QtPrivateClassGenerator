#include "Utils.h"

const char *StringUtils::WHITESPACE = " \n\r\t";

std::string StringUtils::Trim(const std::string &s, const char *t) {
    return TrimRight(TrimLeft(s, t), t);
}

std::string StringUtils::TrimLeft(const std::string &s, const char *t) {
    size_t startPos = s.find_first_not_of(t);
    return (startPos == std::string::npos) ? "" : s.substr(startPos);
}

std::string StringUtils::TrimRight(const std::string &s, const char *t) {
    size_t endPos = s.find_last_not_of(t);
    return (endPos == std::string::npos) ? "" : s.substr(0, endPos + 1);
}

std::vector<std::string> StringUtils::Split(const std::string &s, const std::string &delimiters) {
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);
    std::vector<std::string> tokens;
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
    return tokens;
}

std::string StringUtils::ToUpperCase(const std::string &s) {
    std::string res = s;
    for (char &ch:res) {
        if (ch >= 'a' && ch <= 'z') {
            ch = char(ch + 'A' - 'a');
        }
    }
    return res;
}