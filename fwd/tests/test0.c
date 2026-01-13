#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t1;
    struct fwd_table * t2;
    
    assert((t1 = fwd_new()));
    fwd_delete(t1);

    assert((t2 = fwd_new()));
    fwd_delete(t2);

    assert((t1 = fwd_new()));
    assert((t2 = fwd_new()));
    fwd_delete(t2);
    fwd_delete(t1);

    assert((t1 = fwd_new()));
    assert((t2 = fwd_new()));

    fwd_clear(t2);
    fwd_clear(t1);

    fwd_delete(t2);
    fwd_delete(t1);
}
