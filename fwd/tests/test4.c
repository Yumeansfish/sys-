#include <stdio.h>
#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t;
    
    assert((t = fwd_new()));
    fwd_delete(t);

    assert((t = fwd_new()));

    for (int i = 24; i <= 32; ++i) {
	char prefix[100];
	sprintf(prefix, "1.2.3.255/%d", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "1.2.3.127") == 24);
    assert(fwd_forward(t, "1.2.3.191") == 25);
    assert(fwd_forward(t, "1.2.3.223") == 26);
    assert(fwd_forward(t, "1.2.3.239") == 27);
    assert(fwd_forward(t, "1.2.3.247") == 28);
    assert(fwd_forward(t, "1.2.3.251") == 29);
    assert(fwd_forward(t, "1.2.3.253") == 30);
    assert(fwd_forward(t, "1.2.3.254") == 31);
    assert(fwd_forward(t, "1.2.3.255") == 32);

    assert(fwd_forward(t, "1.2.0.3") == -1);

    fwd_clear(t);

    fwd_delete(t);
}
