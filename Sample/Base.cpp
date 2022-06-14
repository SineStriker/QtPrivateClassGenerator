#include "Base.h"
#include "Base_p.h"

Base::Base(int i) : Base(*new BasePrivate(), i) {
}

Base::~Base() {
}

Base::Base(BasePrivate &d, int i) : Object(i), d_ptr(&d) {
    d.q_ptr = this;

    d.init();
}