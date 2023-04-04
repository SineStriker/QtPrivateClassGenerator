#ifndef QTPRIVATECLASSGENERATOR_UTILS_H
#define QTPRIVATECLASSGENERATOR_UTILS_H

#include <xstring>
#include <vector>

namespace StringUtils {

    extern const char *WHITESPACE;

    std::string Trim(const std::string &s, const char *t = WHITESPACE);

    std::string TrimLeft(const std::string &s, const char *t = WHITESPACE);

    std::string TrimRight(const std::string &s, const char *t = WHITESPACE);

    std::vector<std::string> Split(const std::string &s, const std::string &delimiter = " ");

    std::string Join(const std::vector<std::string> &list, const std::string &delimiter = ",");

    std::string ToUpperCase(const std::string &s);
};

struct Argument {
    std::string Class;
    std::string Name;
    std::string Default;

    bool parse(const std::string &arg) {
        auto arr = StringUtils::Split(arg, ",");
        if (arr.size() < 3) {
            return false;
        }
        Class = arr[0];
        Name = arr[1];
        if (arg.size() >= 3) {
            Default = arr[2];
        }
        return true;
    }

    std::string format() const {
        std::string c = StringUtils::Trim(Class);
        if (c.back() == '*') {
            c.pop_back();
            return StringUtils::Trim(c) + " *" + StringUtils::Trim(Name);
        }
        return StringUtils::Trim(c) + " " + StringUtils::Trim(Name);
    }

    std::string formatWithDefault() const {
        if (Default.empty()) {
            return format();
        }
        return format() + " = " + StringUtils::Trim(Default);
    }
};

#endif //QTPRIVATECLASSGENERATOR_UTILS_H
