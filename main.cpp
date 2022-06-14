#include <cstdio>
#include <cstring>

#include "Config.h"

void showHelp() {
    printf("Usage:\n");
    printf("  %s %s\n", CMD_NAME, "[options] [class]");
    printf("\n");

    printf("Options:\n");
    printf("  %-12s%s\n", "-a", "Set more arguments, format: Class,Name,Default");
    printf("  %-12s%s\n", "-m", "Set more macros at the beginning of class");
    printf("  %-12s%s\n", "-b", "Set base class");
    printf("  %-12s%s\n", "-o", "Set output directory");
    printf("  %-12s%s\n", "-p", "Set project name");
    printf("  %-12s%s\n", "-d", "Generate derived private class, the base class must be specified");
    printf("\n");

    printf("Templates:\n");
    printf("  %-12s%s\n", "--qobject", "Use QObject template");
    printf("  %-12s%s\n", "--qwidget", "Use QWidget template");
    printf("\n");

    printf("Examples:\n");
    printf("  %s %s\n", CMD_NAME, "--qobject -b QObject MyObject");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        showHelp();
        return 0;
    }

    std::string className;

    std::vector<Argument> args;
    std::vector<std::string> macros;
    std::string base;
    std::string project;
    bool isBasic = true;

    std::string dir;

    bool qobject = false;
    bool qwidget = false;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")) {
            showHelp();
            return 0;
        } else if (!strcmp(argv[i], "-a")) {
            if (i < argc - 1) {
                Argument arg;
                if (arg.parse(argv[i + 1])) {
                    args.emplace_back(arg);
                }
                i++;
            }
        }
        if (!strcmp(argv[i], "-m")) {
            if (i < argc - 1) {
                macros.emplace_back(argv[i + 1]);
                i++;
            }
        } else if (!strcmp(argv[i], "-b")) {
            if (i < argc - 1) {
                base = argv[i + 1];
                i++;
            }
        } else if (!strcmp(argv[i], "-o")) {
            if (i < argc - 1) {
                dir = argv[i + 1];
                i++;
            }
        } else if (!strcmp(argv[i], "-p")) {
            if (i < argc - 1) {
                project = argv[i + 1];
                i++;
            }
        } else if (!strcmp(argv[i], "-d")) {
            isBasic = false;
        } else if (!strcmp(argv[i], "--qobject")) {
            qobject = true;
        } else if (!strcmp(argv[i], "--qwidget")) {
            qwidget = true;
        } else {
            className = argv[i];
        }
    }

    if (className.empty()) {
        printf("Missing class name.\n");
        return 1;
    }

    // Use QObject/QWidget template
    if (qobject) {
        args = {Argument{"QObject *", "parent", "nullptr"}};
        macros = {"Q_OBJECT"};
    } else if (qwidget) {
        args = {Argument{"QWidget *", "parent", "nullptr"}};
        macros = {"Q_OBJECT"};
    }

    // Use current working dir if not specified
    if (dir.empty()) {
        dir = ".";
    }

    if (isBasic) {
        if (!GenerateBaseClassHeader(dir, className, base, args, macros, project)) {
            goto failed;
        }
        if (!GenerateBaseClassSource(dir, className, base, args)) {
            goto failed;
        }
        if (!GenerateBasePrivateHeader(dir, className, base, args, project)) {
            goto failed;
        }
        if (!GenerateBasePrivateSource(dir, className, base, args)) {
            goto failed;
        }
    } else {
        if (base.empty()) {
            printf("Missing base class name.\n");
            return 1;
        }
        if (!GenerateDerivedClassHeader(dir, className, base, args, macros, project)) {
            goto failed;
        }
        if (!GenerateDerivedClassSource(dir, className, base, args)) {
            goto failed;
        }
        if (!GenerateDerivedPrivateHeader(dir, className, base, args, project)) {
            goto failed;
        }
        if (!GenerateDerivedPrivateSource(dir, className, base, args)) {
            goto failed;
        }
    }

    return 0;

    failed:
    printf("Generate failed.\n");
    return 1;
}
