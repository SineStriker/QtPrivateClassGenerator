#ifndef PROJECT_BASE_H
#define PROJECT_BASE_H

#include "Object.h"

#include <QtGlobal>

class BasePrivate;

class Base : public Object {
    Q_DECLARE_PRIVATE(Base)
public:
    Base(int i = 0);
    ~Base();

protected:
    Base(BasePrivate &d, int i = 0);

    QScopedPointer<BasePrivate> d_ptr;
};

#endif // PROJECT_BASE_H