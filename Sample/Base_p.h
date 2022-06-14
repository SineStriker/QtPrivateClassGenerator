#ifndef PROJECT_BASEPRIVATE_H
#define PROJECT_BASEPRIVATE_H

#include "Base.h"

class BasePrivate {
    Q_DECLARE_PUBLIC(Base)
public:
    BasePrivate();
    virtual ~BasePrivate();

    void init();

    Base *q_ptr;
};

#endif // PROJECT_BASEPRIVATE_H