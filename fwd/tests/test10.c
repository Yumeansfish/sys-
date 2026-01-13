#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t;
    
    assert((t = fwd_new()));
    fwd_delete(t);

    assert((t = fwd_new()));
    assert(fwd_add(t, "1.1.1.1/32", 1));
    fwd_delete(t);

    assert((t = fwd_new()));

    assert(fwd_forward(t, "1.1.1.1") == -1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == -1);

    assert(fwd_add(t, "1.1.1.1/32", 1));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == -1);

    fwd_clear(t);

    assert(fwd_forward(t, "1.1.1.1") == -1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == -1);

    assert(fwd_add(t, "1.1.1.0/24", 1));
    assert(fwd_add(t, "1.1.0.0/16", 2));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "1.1.2.2") == 2);
    assert(fwd_forward(t, "1.2.2.2") == -1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == -1);

    assert(fwd_add(t, "255.255.255.255/25", 3));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "1.1.2.2") == 2);
    assert(fwd_forward(t, "1.2.2.2") == -1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == 3);
    assert(fwd_forward(t, "255.255.255.0") == -1);
    assert(fwd_forward(t, "255.255.255.128") == 3);

    assert(fwd_add(t, "0.0.0.0/0", 4));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "1.1.2.2") == 2);
    assert(fwd_forward(t, "1.2.2.2") == 4);
    assert(fwd_forward(t, "0.0.0.0") == 4);
    assert(fwd_forward(t, "255.255.255.255") == 3);
    assert(fwd_forward(t, "255.255.255.0") == 4);
    assert(fwd_forward(t, "255.255.255.128") == 3);
    assert(fwd_forward(t, "255.255.255.127") == 4);

    assert(fwd_add(t, "0.0.0.0/2", 5));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "1.1.2.2") == 2);
    assert(fwd_forward(t, "1.2.2.2") == 5);
    assert(fwd_forward(t, "0.0.0.0") == 5);
    assert(fwd_forward(t, "255.255.255.255") == 3);
    assert(fwd_forward(t, "255.255.255.0") == 4);
    assert(fwd_forward(t, "255.255.255.128") == 3);
    assert(fwd_forward(t, "255.255.255.127") == 4);

    assert(fwd_add(t, "128.138.64.0/18", 1));
    assert(fwd_add(t, "128.138.128.0/18", 2));

    assert(fwd_forward(t, "1.1.1.1") == 1);
    assert(fwd_forward(t, "1.1.2.2") == 2);
    assert(fwd_forward(t, "1.2.2.2") == 5);
    assert(fwd_forward(t, "0.0.0.0") == 5);
    assert(fwd_forward(t, "255.255.255.255") == 3);
    assert(fwd_forward(t, "255.255.255.0") == 4);
    assert(fwd_forward(t, "255.255.255.128") == 3);
    assert(fwd_forward(t, "255.255.255.127") == 4);
    assert(fwd_forward(t, "128.138.127.23") == 1);
    assert(fwd_forward(t, "128.138.129.23") == 2);
    assert(fwd_forward(t, "128.138.240.23") == 4);

    fwd_clear(t);

    assert(fwd_forward(t, "1.1.1.1") == -1);
    assert(fwd_forward(t, "1.1.2.2") == -1);
    assert(fwd_forward(t, "1.2.2.2") == -1);
    assert(fwd_forward(t, "0.0.0.0") == -1);
    assert(fwd_forward(t, "255.255.255.255") == -1);
    assert(fwd_forward(t, "255.255.255.0") == -1);
    assert(fwd_forward(t, "255.255.255.128") == -1);
    assert(fwd_forward(t, "255.255.255.127") == -1);
    assert(fwd_forward(t, "128.138.127.23") == -1);
    assert(fwd_forward(t, "128.138.129.23") == -1);
    assert(fwd_forward(t, "128.138.240.23") == -1);

    fwd_delete(t);
}
