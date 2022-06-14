#ifndef PROJECT_DERIVED_H
#define PROJECT_DERIVED_H

#include "Base.h"

class DerivedPrivate;

class Derived : public Base {
    Q_DECLARE_PRIVATE(Derived)
public:
    Derived(int i = 0);
    ~Derived();

protected:
    Derived(DerivedPrivate &d, int i = 0);
};

#endif // PROJECT_DERIVED_H