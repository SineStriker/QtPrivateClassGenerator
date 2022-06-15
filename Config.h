#ifndef QTPRIVATECLASSGENERATOR_CONFIG_H
#define QTPRIVATECLASSGENERATOR_CONFIG_H

#include "Utils.h"

const char BaseClassHeader[] = "#ifndef %s_H\n" // HEADER_DEFINE
                               "#define %s_H\n" // HEADER_DEFINE
                               "\n"
                               "%s" // INSERT_INCLUDE_BASE
                               "#include <QtGlobal>\n"
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
                               "\n"
                               "#endif // %s_H"; // HEADER_DEFINE

const char BaseClassSource[] = "#include \"%s.h\"\n" // CLASS_NAME
                               "#include \"%s_p.h\"\n" // CLASS_NAME
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
                               "}";

const char BasePrivateHeader[] = "#ifndef %sPRIVATE_H\n" // HEADER_DEFINE
                                 "#define %sPRIVATE_H\n" // HEADER_DEFINE
                                 "\n"
                                 "#include \"%s.h\"\n" // CLASS_NAME
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
                                 "\n"
                                 "#endif // %sPRIVATE_H"; // HEADER_DEFINE

const char BasePrivateSource[] = "#include \"%s_p.h\"\n" // CLASS_NAME
                                 "\n"
                                 "%sPrivate::%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                 "}\n"
                                 "\n"
                                 "%sPrivate::~%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                 "}\n"
                                 "\n"
                                 "void %sPrivate::init() {\n" // CLASS_NAME
                                 "}";

const char DerivedClassHeader[] = "#ifndef %s_H\n" // HEADER_DEFINE
                                  "#define %s_H\n" // HEADER_DEFINE
                                  "\n"
                                  "#include \"%s.h\"\n" // BASE_NAME
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
                                  "\n"
                                  "#endif // %s_H"; // HEADER_DEFINE

const char DerivedClassSource[] = "#include \"%s.h\"\n" // CLASS_NAME
                                  "#include \"%s_p.h\"\n" // CLASS_NAME
                                  "\n"
                                  "%s::%s(%s) : %s(*new %sPrivate()%s) {\n" // CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_ARGS CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_INIT_LIST
                                  "}\n"
                                  "\n"
                                  "%s::~%s() {\n" // CLASS_NAME CLASS_NAME
                                  "}\n"
                                  "\n"
                                  "%s::%s(%sPrivate &d%s) : %s(d%s) {\n" // CLASS_NAME CLASS_NAME CLASS_NAME INSERT_CONSTRUCTOR_P_ARGS BASE_NAME INSERT_CONSTRUCTOR_P_INIT_LIST
                                  "    d.init();\n"
                                  "}";

const char DerivedPrivateHeader[] = "#ifndef %sPRIVATE_H\n" // HEADER_DEFINE
                                    "#define %sPRIVATE_H\n" // HEADER_DEFINE
                                    "\n"
                                    "#include \"%s_p.h\"\n" // BASE_NAME
                                    "\n"
                                    "#include \"%s.h\"\n" // CLASS_NAME
                                    "\n"
                                    "class %sPrivate : public %sPrivate {\n" // CLASS_NAME BASE_NAME
                                    "    Q_DECLARE_PUBLIC(%s)\n" // CLASS_NAME
                                    "public:\n"
                                    "    %sPrivate();\n" // CLASS_NAME
                                    "    ~%sPrivate();\n" // CLASS_NAME
                                    "\n"
                                    "    void init();\n"
                                    "};\n"
                                    "\n"
                                    "#endif // %sPRIVATE_H"; // HEADER_DEFINE

const char DerivedPrivateSource[] = "#include \"%s_p.h\"\n" // CLASS_NAME
                                    "\n"
                                    "%sPrivate::%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                    "}\n"
                                    "\n"
                                    "%sPrivate::~%sPrivate() {\n" // CLASS_NAME CLASS_NAME
                                    "}\n"
                                    "\n"
                                    "void %sPrivate::init() {\n" // CLASS_NAME
                                    "}";

bool GenerateBaseClassHeader(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &macros,
                             const std::string &projectName
);

bool GenerateBaseClassSource(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args
);

bool GenerateBasePrivateHeader(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::string &projectName
);

bool GenerateBasePrivateSource(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args
);

bool GenerateDerivedClassHeader(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &macros,
                                const std::string &projectName
);

bool GenerateDerivedClassSource(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args
);

bool GenerateDerivedPrivateHeader(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::string &projectName
);

bool GenerateDerivedPrivateSource(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args
);

#endif //QTPRIVATECLASSGENERATOR_CONFIG_H
