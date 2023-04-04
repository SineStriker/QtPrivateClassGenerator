#ifndef QTPRIVATECLASSGENERATOR_CONFIG_H
#define QTPRIVATECLASSGENERATOR_CONFIG_H

#include "Utils.h"

bool GenerateBaseClassHeader(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &namespaces,
                             const std::vector<std::string> &macros,
                             const std::string &projectName
);

bool GenerateBaseClassSource(const std::string &dir,
                             const std::string &className,
                             const std::string &baseName,
                             const std::vector<Argument> &args,
                             const std::vector<std::string> &namespaces,
                             bool privateSource = false
);

bool GenerateBasePrivateHeader(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::vector<std::string> &namespaces,
                               const std::string &projectName
);

bool GenerateBasePrivateSource(const std::string &dir,
                               const std::string &className,
                               const std::string &baseName,
                               const std::vector<Argument> &args,
                               const std::vector<std::string> &namespaces
);

bool GenerateDerivedClassHeader(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &namespaces,
                                const std::vector<std::string> &macros,
                                const std::string &projectName
);

bool GenerateDerivedClassSource(const std::string &dir,
                                const std::string &className,
                                const std::string &baseName,
                                const std::vector<Argument> &args,
                                const std::vector<std::string> &namespaces,
                                bool privateSource = false
);

bool GenerateDerivedPrivateHeader(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::vector<std::string> &namespaces,
                                  const std::string &projectName
);

bool GenerateDerivedPrivateSource(const std::string &dir,
                                  const std::string &className,
                                  const std::string &baseName,
                                  const std::vector<Argument> &args,
                                  const std::vector<std::string> &namespaces
);

#endif //QTPRIVATECLASSGENERATOR_CONFIG_H
