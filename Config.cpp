#include "Config.h"

#include <cstdio>

#define INDENT "    "

const char BaseClassHeader[] = "#ifndef %s_H\n" // HEADER_DEFINE
                               "#define %s_H\n" // HEADER_DEFINE
                               "\n"
                               "%s" // INSERT_INCLUDE_BASE
                               "#include <QtGlobal>\n"
                               "%s" // INSERT_NAMESPACE_BEGIN
                               "\n"
                               "class %sPrivate;\n" // CLASS_NAME
                               "\n"
                               "class %s%s {\n" // INSERT_EXTENDED
                               "%s" // INSERT_MACROS
                               "    Q_DECLARE_PRIVATE(%s)\n" // CLASS_NAME
                               "public:\n"
                               "    %s(%s);\n" // CLASS_NAME INSERT_CONSTRUCTOR_ARGS
                               "    %s~%s();\n" // INSERT_VIRTUAL CLASS_NAME
                               "\n"
                               "protected:\n"
                               "    %s(%sPrivate &d%s);\n" // CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_P_ARGS
                               "\n"
                               "    QScopedPointer<%sPrivate> d_ptr;\n" // CLASS_NAME
                               "};\n"
                               "%s" // INSERT_NAMESPACE_END
                               "\n"
                               "#endif // %s_H"; // HEADER_DEFINE

const char BaseClassSource[] = "#include \"%s.h\"\n" // CLASS_NAME
                               "#include \"%s_p.h\"\n" // CLASS_NAME
                               "%s" // INSERT_NAMESPACE_BEGIN
                               "%s" // INSERT_PRIVATE_SOURCES
                               "\n"
                               "%s::%s(%s) : %s(*new %sPrivate()%s) {\n" // CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_ARGS CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_INIT_LIST
                               "}\n"
                               "\n"
                               "%s::~%s() {\n" // CLASS_NAME CLASS_NAME
                               "}\n"
                               "\n"
                               "%s::%s(%sPrivate &d%s) : %sd_ptr(&d) {\n" // CLASS_NAME CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_P_ARGS INSERT_CONSTRUCTOR_P_INIT_LIST
                               "    d.q_ptr = this;\n"
                               "\n"
                               "    d.init();\n"
                               "}\n"
                               "%s"; // INSERT_NAMESPACE_END

const char BasePrivateHeader[] = "#ifndef %sPRIVATE_H\n" // HEADER_DEFINE
                                 "#define %sPRIVATE_H\n" // HEADER_DEFINE
                                 "\n"
                                 "#include \"%s.h\"\n" // CLASS_NAME
                                 "%s" // INSERT_NAMESPACE_BEGIN
                                 "\n"
                                 "class %sPrivate {\n" // CLASS_NAME
                                 "    Q_DECLARE_PUBLIC(%s)\n" // CLASS_NAME
                                 "public:\n"
                                 "    %sPrivate();\n"  // CLASS_NAME
                                 "    virtual ~%sPrivate();\n" // CLASS_NAME
                                 "\n"
                                 "    void init();\n"
                                 "\n"
                                 "    %s *q_ptr;\n" // CLASS_NAME
                                 "};\n"
                                 "%s" // INSERT_NAMESPACE_END
                                 "\n"
                                 "#endif // %sPRIVATE_H"; // HEADER_DEFINE

const char BasePrivateSource[] = "#include \"%s_p.h\"\n" // CLASS_NAME
                                 "%s" // INSERT_NAMESPACE_BEGIN
                                 "\n"
                                 "%sPrivate::%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                 "}\n"
                                 "\n"
                                 "%sPrivate::~%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                 "}\n"
                                 "\n"
                                 "void %sPrivate::init() {\n" // CLASS_NAME
                                 "}\n"
                                 "%s"; // INSERT_NAMESPACE_END

const char DerivedClassHeader[] = "#ifndef %s_H\n" // HEADER_DEFINE
                                  "#define %s_H\n" // HEADER_DEFINE
                                  "\n"
                                  "#include \"%s.h\"\n" // BASE_NAME
                                  "%s" // INSERT_NAMESPACE_BEGIN
                                  "\n"
                                  "class %sPrivate;\n" // CLASS_NAME
                                  "\n"
                                  "class %s : public %s {\n" // CLASS_NAME BASE_NAME
                                  "%s" // INSERT_MACROS
                                  "    Q_DECLARE_PRIVATE(%s)\n" // CLASS_NAME
                                  "public:\n"
                                  "    %s(%s);\n" // CLASS_NAME INSERT_CONSTRUCTOR_ARGS
                                  "    ~%s();\n" // CLASS_NAME
                                  "\n"
                                  "protected:\n"
                                  "    %s(%sPrivate &d%s);\n" // CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_P_ARGS
                                  "};\n"
                                  "%s" // INSERT_NAMESPACE_END
                                  "\n"
                                  "#endif // %s_H"; // HEADER_DEFINE

const char DerivedClassSource[] = "#include \"%s.h\"\n" // CLASS_NAME
                                  "#include \"%s_p.h\"\n" // CLASS_NAME
                                  "%s" // INSERT_NAMESPACE_BEGIN
                                  "%s" // INSERT_PRIVATE_SOURCES
                                  "\n"
                                  "%s::%s(%s) : %s(*new %sPrivate()%s) {\n" // CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_ARGS CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_INIT_LIST
                                  "}\n"
                                  "\n"
                                  "%s::~%s() {\n" // CLASS_NAME CLASS_NAME
                                  "}\n"
                                  "\n"
                                  "%s::%s(%sPrivate &d%s) : %s(d%s) {\n" // CLASS_NAME CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_P_ARGS BASE_NAME INSERT_CONSTRUCTOR_P_INIT_LIST
                                  "    d.init();\n"
                                  "}"
                                  "%s"; // INSERT_NAMESPACE_END

const char DerivedPrivateHeader[] = "#ifndef %sPRIVATE_H\n" // HEADER_DEFINE
                                    "#define %sPRIVATE_H\n" // HEADER_DEFINE
                                    "\n"
                                    "#include \"%s_p.h\"\n" // BASE_NAME
                                    "\n"
                                    "#include \"%s.h\"\n" // CLASS_NAME
                                    "%s" // INSERT_NAMESPACE_BEGIN
                                    "\n"
                                    "class %sPrivate : public %sPrivate {\n" // CLASS_NAME BASE_NAME
                                    "    Q_DECLARE_PUBLIC(%s)\n" // CLASS_NAME
                                    "public:\n"
                                    "    %sPrivate();\n" // CLASS_NAME
                                    "    ~%sPrivate();\n" // CLASS_NAME
                                    "\n"
                                    "    void init();\n"
                                    "};\n"
                                    "%s" // INSERT_NAMESPACE_END
                                    "\n"
                                    "#endif // %sPRIVATE_H"; // HEADER_DEFINE

const char DerivedPrivateSource[] = "#include \"%s_p.h\"\n" // CLASS_NAME
                                    "%s" // INSERT_NAMESPACE_BEGIN
                                    "\n"
                                    "%sPrivate::%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                    "}\n"
                                    "\n"
                                    "%sPrivate::~%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                    "}\n"
                                    "\n"
                                    "void %sPrivate::init() {\n" // CLASS_NAME
                                    "}"
                                    "%s"; // INSERT_NAMESPACE_END

const char PrivateSource2[] = "\n"
                              "%sPrivate::%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                              "}\n"
                              "\n"
                              "%sPrivate::~%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                              "}\n"
                              "\n"
                              "void %sPrivate::init() {\n" // CLASS_NAME
                              "}\n";

static std::vector<std::string> _to_namespace_begin(const std::vector<std::string> &namespaces) {
    std::vector<std::string> res;
    for (const auto &ns: namespaces) {
        res.push_back("namespace " + ns + " {");
    }
    return res;
}

static std::vector<std::string> _to_namespace_end(const std::vector<std::string> &namespaces) {
    std::vector<std::string> res;
    for (const auto &ns: namespaces) {
        res.push_back("}");
    }
    return res;
}

bool GenerateBaseClassHeader(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &namespaces,
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

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

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

    for (const std::string &macro: macros) {
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
            INSERT_NAMESPACE_BEGIN.c_str(),
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
            INSERT_NAMESPACE_END.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBaseClassSource(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &namespaces,
                             bool privateSource) {

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

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

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

    char buf[sizeof(PrivateSource2) + 200] = {0};
    if (privateSource) {
        sprintf(buf, PrivateSource2,
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str()
        );
    }

    fprintf(f, BaseClassSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_BEGIN.c_str(),
            buf,
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
            INSERT_CONSTRUCTOR_P_INIT_LIST.c_str(),
            INSERT_NAMESPACE_END.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBasePrivateHeader(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::vector<std::string> &namespaces,
                               const std::string &projectName) {

    std::string filename = dir + "/" + className + "_p.h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;
    std::string HEADER_DEFINE;

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    fprintf(f, BasePrivateHeader,
            HEADER_DEFINE.c_str(),
            HEADER_DEFINE.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_BEGIN.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_END.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateBasePrivateSource(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::vector<std::string> &namespaces) {

    std::string filename = dir + "/" + className + "_p.cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

    CLASS_NAME = className;

    fprintf(f, BasePrivateSource,
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_BEGIN.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_END.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedClassHeader(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &namespaces,
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

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

    BASE_NAME = baseName;
    CLASS_NAME = className;

    HEADER_DEFINE = StringUtils::ToUpperCase(className);
    if (!projectName.empty()) {
        HEADER_DEFINE = StringUtils::ToUpperCase(projectName) + "_" + HEADER_DEFINE;
    }

    for (const std::string &macro: macros) {
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
            INSERT_NAMESPACE_BEGIN.c_str(),
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
            INSERT_NAMESPACE_END.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedClassSource(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &namespaces,
                                bool privateSource) {

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

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

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

    char buf[sizeof(PrivateSource2) + 200] = {0};
    if (privateSource) {
        sprintf(buf, PrivateSource2,
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str(),
                CLASS_NAME.c_str()
        );
    }

    fprintf(f, DerivedClassSource,
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_BEGIN.c_str(),
            buf,
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
            INSERT_CONSTRUCTOR_P_INIT_LIST.c_str(),
            INSERT_NAMESPACE_END.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedPrivateHeader(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::vector<std::string> &namespaces,
                                  const std::string &projectName) {

    std::string filename = dir + "/" + className + "_p.h";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string BASE_NAME;
    std::string CLASS_NAME;
    std::string HEADER_DEFINE;

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

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
            INSERT_NAMESPACE_BEGIN.c_str(),
            CLASS_NAME.c_str(),
            BASE_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_END.c_str(),
            HEADER_DEFINE.c_str()
    );

    fclose(f);

    return true;
}

bool GenerateDerivedPrivateSource(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::vector<std::string> &namespaces) {

    std::string filename = dir + "/" + className + "_p.cpp";

    FILE *f = fopen(filename.c_str(), "w");
    if (!f) {
        return false;
    }

    std::string CLASS_NAME;

    std::string INSERT_NAMESPACE_BEGIN;
    std::string INSERT_NAMESPACE_END;

    if (!namespaces.empty()) {
        INSERT_NAMESPACE_BEGIN = "\n" + StringUtils::Join(_to_namespace_begin(namespaces), "\n\n") + "\n";
        INSERT_NAMESPACE_END = "\n" + StringUtils::Join(_to_namespace_end(namespaces), "\n\n") + "\n";
    }

    CLASS_NAME = className;

    fprintf(f, DerivedPrivateSource,
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_BEGIN.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            CLASS_NAME.c_str(),
            INSERT_NAMESPACE_END.c_str()
    );

    fclose(f);

    return true;
}