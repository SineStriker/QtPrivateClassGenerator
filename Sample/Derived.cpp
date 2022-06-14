#include "Derived.h"
#include "Derived_p.h"

Derived::Derived(int i) : Derived(*new DerivedPrivate(), i) {
}

Derived::~Derived() {
}

Derived::Derived(DerivedPrivate &d, int i) : Base(d, i) {
    d.init();
}