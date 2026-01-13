#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t1;
    struct fwd_table * t2;
    
    assert((t1 = fwd_new()));
    assert((t2 = fwd_new()));

    assert(fwd_add(t1, "1.1.1.1/32", 1));

    assert(fwd_forward(t2, "1.1.1.1") == -1);
    assert(fwd_forward(t1, "1.1.1.1") == 1);

    fwd_clear(t2);

    assert(fwd_forward(t2, "1.1.1.1") == -1);
    assert(fwd_forward(t1, "1.1.1.1") == 1);

    fwd_clear(t1);

    assert(fwd_forward(t2, "1.1.1.1") == -1);
    assert(fwd_forward(t1, "1.1.1.1") == -1);

    fwd_delete(t1);
    fwd_delete(t2);
}
