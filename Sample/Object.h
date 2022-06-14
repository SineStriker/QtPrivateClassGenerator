#ifndef OBJECT_H
#define OBJECT_H

template<class T>
class QScopedPointer {
public:
    QScopedPointer(T *d) {
    };
};

#define Q_DECLARE_PUBLIC(X)
#define Q_DECLARE_PRIVATE(X)

class Object {
public:
    Object(int i = 0) {
    };
};


#endif //OBJECT_H
