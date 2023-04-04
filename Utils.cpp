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

std::vector<std::string> StringUtils::Split(const std::string &s, const std::string &delimiter) {
    std::string::size_type lastPos = s.find_first_not_of(delimiter, 0);
    std::string::size_type pos = s.find_first_of(delimiter, lastPos);
    std::vector<std::string> tokens;
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiter, pos);
        pos = s.find_first_of(delimiter, lastPos);
    }
    return tokens;
}

std::string StringUtils::Join(const std::vector<std::string> &list, const std::string &delimiter) {
    if (list.empty()) {
        return {};
    }

    std::string res = list.front();
    for (auto it = list.begin() + 1; it != list.end(); ++it) {
        res += delimiter + *it;
    }
    return res;
}

std::string StringUtils::ToUpperCase(const std::string &s) {
    std::string res = s;
    for (char &ch: res) {
        if (ch >= 'a' && ch <= 'z') {
            ch = char(ch + 'A' - 'a');
        }
    }
    return res;
}