#ifndef PROJECT_DERIVEDPRIVATE_H
#define PROJECT_DERIVEDPRIVATE_H

#include "Base_p.h"

#include "Derived.h"

class DerivedPrivate : public BasePrivate {
    Q_DECLARE_PUBLIC(Derived)
public:
    DerivedPrivate();
    ~DerivedPrivate();

    void init();
};

#endif // PROJECT_DERIVEDPRIVATE_H