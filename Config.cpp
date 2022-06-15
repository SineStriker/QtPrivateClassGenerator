#include "Config.h"

#include <cstdio>

#define INDENT "    "

bool GenerateBaseClassHeader(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &macros,
                             const std::string &projectName) {

    std::string filename = dir + "/" + className + ".h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;
    std::string HEADER_DEFINE;
    std::string INSERT_INCLUDE_BASE;
    std::string INSERT_EXTENDED;

    std::string INSERT_MACROS;
    std::string INSERT_VIRTUAL;

    std::string INSERT_CONSTRUCTOR_ARGS;
    std::string INSERT_CONSTRUCTOR_P_ARGS;

    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    if (!baseName.empty()) {
        INSERT_INCLUDE_BASE = "#include \"" + baseName + ".h\"\n\n";
        INSERT_EXTENDED = " : public " + baseName;
    } else {
        INSERT_VIRTUAL = "virtual "; // Make destructor virtual for basic class
    }

    for (const std::string &macro :macros) {
        INSERT_MACROS += INDENT + macro + "\n";
    }

    if (!args.empty()) {
        auto it = args.begin();
        INSERT_CONSTRUCTOR_ARGS += it->formatWithDefault();
        INSERT_CONSTRUCTOR_P_ARGS += ", " + it->formatWithDefault();
        for (it++; it != args.end(); it++) {
            INSERT_CONSTRUCTOR_ARGS += ", " + it->formatWithDefault();
            INSERT_CONSTRUCTOR_P_ARGS += ", " + it->formatWithDefault();
        }
    }

    fprintf(f, BaseClassHeader,
            HEADER_DEFINE.c_str(),
            HEADER_DEFINE.c_str(),
            INSERT_INCLUDE_BASE.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_EXTENDED.c_str(),
            INSERT_MACROS.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_ARGS.c_str(),
            INSERT_VIRTUAL.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_P_ARGS.c_str(),
            CLASS_NAME.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBaseClassSource(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args) {

    std::string filename = dir + "/" + className + ".cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;
    std::string INSERT_EXTENDED;

    std::string INSERT_CONSTRUCTOR_ARGS;
    std::string INSERT_CONSTRUCTOR_P_ARGS;

    std::string INSERT_CONSTRUCTOR_INIT_LIST;
    std::string INSERT_CONSTRUCTOR_P_INIT_LIST;

    CLASS_NAME = className;

    if (!args.empty()) {
        auto it = args.begin();
        INSERT_CONSTRUCTOR_ARGS += it->format();
        INSERT_CONSTRUCTOR_P_ARGS += ", " + it->format();

        INSERT_CONSTRUCTOR_INIT_LIST += ", " + it->Name;
        INSERT_CONSTRUCTOR_P_INIT_LIST += it->Name;

        for (it++; it != args.end(); it++) {
            INSERT_CONSTRUCTOR_ARGS += ", " + it->format();
            INSERT_CONSTRUCTOR_P_ARGS += ", " + it->format();

            INSERT_CONSTRUCTOR_INIT_LIST += ", " + it->Name;
            INSERT_CONSTRUCTOR_P_INIT_LIST += ", " + it->Name;
        }
    }

    if (baseName.empty()) {
        INSERT_CONSTRUCTOR_P_INIT_LIST.clear();
    } else {
        INSERT_CONSTRUCTOR_P_INIT_LIST = baseName + "(" + INSERT_CONSTRUCTOR_P_INIT_LIST + "), ";
    }

    fprintf(f, BaseClassSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_ARGS.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_INIT_LIST.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_P_ARGS.c_str(),
            INSERT_CONSTRUCTOR_P_INIT_LIST.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBasePrivateHeader(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::string &projectName) {

    std::string filename = dir + "/" + className + "_p.h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;
    std::string HEADER_DEFINE;

    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    fprintf(f, BasePrivateHeader,
            HEADER_DEFINE.c_str(),
            HEADER_DEFINE.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBasePrivateSource(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args) {

    std::string filename = dir + "/" + className + "_p.cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;

    CLASS_NAME = className;

    fprintf(f, BasePrivateSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedClassHeader(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &macros,
                                const std::string &projectName) {

    std::string filename = dir + "/" + className + ".h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string BASE_NAME;
    std::string CLASS_NAME;
    std::string HEADER_DEFINE;

    std::string INSERT_MACROS;

    std::string INSERT_CONSTRUCTOR_ARGS;
    std::string INSERT_CONSTRUCTOR_P_ARGS;

    BASE_NAME = baseName;
    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    for (const std::string &macro :macros) {
        INSERT_MACROS += INDENT + macro + "\n";
    }

    if (!args.empty()) {
        auto it = args.begin();
        INSERT_CONSTRUCTOR_ARGS += it->formatWithDefault();
        INSERT_CONSTRUCTOR_P_ARGS += ", " + it->formatWithDefault();
        for (it++; it != args.end(); it++) {
            INSERT_CONSTRUCTOR_ARGS += ", " + it->formatWithDefault();
            INSERT_CONSTRUCTOR_P_ARGS += ", " + it->formatWithDefault();
        }
    }

    fprintf(f, DerivedClassHeader,
            HEADER_DEFINE.c_str(),
            HEADER_DEFINE.c_str(),
            BASE_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            BASE_NAME.c_str(),
            INSERT_MACROS.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_ARGS.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_P_ARGS.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedClassSource(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args) {

    std::string filename = dir + "/" + className + ".cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string BASE_NAME;
    std::string CLASS_NAME;
    std::string INSERT_EXTENDED;

    std::string INSERT_CONSTRUCTOR_ARGS;
    std::string INSERT_CONSTRUCTOR_P_ARGS;

    std::string INSERT_CONSTRUCTOR_INIT_LIST;
    std::string INSERT_CONSTRUCTOR_P_INIT_LIST;

    BASE_NAME = baseName;
    CLASS_NAME = className;

    if (!args.empty()) {
        auto it = args.begin();
        INSERT_CONSTRUCTOR_ARGS += it->format();
        INSERT_CONSTRUCTOR_P_ARGS += ", " + it->format();

        INSERT_CONSTRUCTOR_INIT_LIST += ", " + it->Name;
        INSERT_CONSTRUCTOR_P_INIT_LIST += ", " + it->Name;

        for (it++; it != args.end(); it++) {
            INSERT_CONSTRUCTOR_ARGS += ", " + it->format();
            INSERT_CONSTRUCTOR_P_ARGS += ", " + it->format();

            INSERT_CONSTRUCTOR_INIT_LIST += ", " + it->Name;
            INSERT_CONSTRUCTOR_P_INIT_LIST += ", " + it->Name;
        }
    }

    fprintf(f, DerivedClassSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_ARGS.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_INIT_LIST.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_CONSTRUCTOR_P_ARGS.c_str(),
            BASE_NAME.c_str(),
            INSERT_CONSTRUCTOR_P_INIT_LIST.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedPrivateHeader(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::string &projectName) {

    std::string filename = dir + "/" + className + "_p.h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string BASE_NAME;
    std::string CLASS_NAME;
    std::string HEADER_DEFINE;

    BASE_NAME = baseName;
    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    fprintf(f, DerivedPrivateHeader,
            HEADER_DEFINE.c_str(),
            HEADER_DEFINE.c_str(),
            BASE_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            BASE_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedPrivateSource(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args) {

    std::string filename = dir + "/" + className + "_p.cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;

    CLASS_NAME = className;

    fprintf(f, DerivedPrivateSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str()
    );

    fclose(f);

    return true;
}