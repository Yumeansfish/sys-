#include <stdio.h>
#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t1;
    struct fwd_table * t2;
    
    assert((t1 = fwd_new()));
    assert((t2 = fwd_new()));

    for (int i = 0; i < 255; ++i) {
	char prefix[100];
	sprintf(prefix, "1.1.%d.0/24", i);
	assert(fwd_add(t1, prefix, i));
    }

    for (int i = 0; i < 255; ++i) {
	char prefix[100];
	sprintf(prefix, "1.2.%d.0/24", i);
	assert(fwd_add(t2, prefix, i));
    }

    assert(fwd_forward(t1, "1.1.0.0") == 0);
    assert(fwd_forward(t2, "1.1.0.0") == -1);

    assert(fwd_forward(t1, "1.1.1.0") == 1);
    assert(fwd_forward(t2, "1.1.1.0") == -1);

    assert(fwd_forward(t1, "1.1.2.0") == 2);
    assert(fwd_forward(t2, "1.1.2.0") == -1);

    assert(fwd_forward(t1, "1.1.3.0") == 3);
    assert(fwd_forward(t2, "1.1.3.0") == -1);

    assert(fwd_forward(t1, "1.1.4.0") == 4);
    assert(fwd_forward(t2, "1.1.4.0") == -1);

    assert(fwd_forward(t1, "1.2.0.0") == -1);
    assert(fwd_forward(t2, "1.2.0.0") == 0);

    assert(fwd_forward(t1, "1.2.1.0") == -1);
    assert(fwd_forward(t2, "1.2.1.0") == 1);

    assert(fwd_forward(t1, "1.2.2.0") == -1);
    assert(fwd_forward(t2, "1.2.2.0") == 2);

    assert(fwd_forward(t1, "1.2.3.0") == -1);
    assert(fwd_forward(t2, "1.2.3.0") == 3);

    assert(fwd_forward(t1, "1.2.4.0") == -1);
    assert(fwd_forward(t2, "1.2.4.0") == 4);

    fwd_clear(t2);

    assert(fwd_forward(t1, "1.1.0.0") == 0);
    assert(fwd_forward(t2, "1.1.0.0") == -1);

    assert(fwd_forward(t1, "1.1.1.0") == 1);
    assert(fwd_forward(t2, "1.1.1.0") == -1);

    assert(fwd_forward(t1, "1.1.2.0") == 2);
    assert(fwd_forward(t2, "1.1.2.0") == -1);

    assert(fwd_forward(t1, "1.1.3.0") == 3);
    assert(fwd_forward(t2, "1.1.3.0") == -1);

    assert(fwd_forward(t1, "1.1.4.0") == 4);
    assert(fwd_forward(t2, "1.1.4.0") == -1);

    assert(fwd_forward(t1, "1.2.0.0") == -1);
    assert(fwd_forward(t2, "1.2.0.0") == -1);

    assert(fwd_forward(t1, "1.2.1.0") == -1);
    assert(fwd_forward(t2, "1.2.1.0") == -1);

    assert(fwd_forward(t1, "1.2.2.0") == -1);
    assert(fwd_forward(t2, "1.2.2.0") == -1);

    assert(fwd_forward(t1, "1.2.3.0") == -1);
    assert(fwd_forward(t2, "1.2.3.0") == -1);

    assert(fwd_forward(t1, "1.2.4.0") == -1);
    assert(fwd_forward(t2, "1.2.4.0") == -1);

    fwd_delete(t1);
    fwd_delete(t2);
}
