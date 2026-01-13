#include <stdio.h>
#include <assert.h>

#include "../fwd.h"

int main() {
    struct fwd_table * t;
    
    assert((t = fwd_new()));
    fwd_delete(t);

    assert((t = fwd_new()));

    for (int i = 0; i < 255; ++i) {
	char prefix[100];
	sprintf(prefix, "1.2.3.%d/32", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "1.2.3.1") == 1);
    assert(fwd_forward(t, "1.2.3.2") == 2);
    assert(fwd_forward(t, "1.2.3.3") == 3);
    assert(fwd_forward(t, "1.2.3.4") == 4);
    assert(fwd_forward(t, "1.2.3.5") == 5);
    assert(fwd_forward(t, "1.2.3.6") == 6);

    assert(fwd_forward(t, "1.2.1.1") == -1);
    assert(fwd_forward(t, "1.2.1.2") == -1);
    assert(fwd_forward(t, "1.2.1.3") == -1);
    assert(fwd_forward(t, "1.2.1.4") == -1);
    assert(fwd_forward(t, "1.2.1.5") == -1);
    assert(fwd_forward(t, "1.2.1.6") == -1);

    for (int i = 0; i < 255; ++i) {
	char address[100];
	sprintf(address, "1.2.3.%d", i);
	assert(fwd_forward(t, address) == i);
    }

    for (int i = 0; i < 255; ++i) {
	char address[100];
	sprintf(address, "255.255.255.%d", i);
	assert(fwd_forward(t, address) == -1);
    }

    fwd_delete(t);
}
