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
	sprintf(prefix, "1.2.3.0/%d", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "1.2.3.0") == 32);
    assert(fwd_forward(t, "1.2.3.1") == 31);
    assert(fwd_forward(t, "1.2.3.2") == 30);
    assert(fwd_forward(t, "1.2.3.4") == 29);
    assert(fwd_forward(t, "1.2.3.8") == 28);
    assert(fwd_forward(t, "1.2.3.16") == 27);
    assert(fwd_forward(t, "1.2.3.32") == 26);
    assert(fwd_forward(t, "1.2.3.64") == 25);
    assert(fwd_forward(t, "1.2.3.128") == 24);

    assert(fwd_forward(t, "1.2.0.3") == -1);

    fwd_clear(t);

    for (int i = 16; i <= 24; ++i) {
	char prefix[100];
	sprintf(prefix, "1.2.0.0/%d", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "1.2.0.3") == 24);
    assert(fwd_forward(t, "1.2.1.3") == 23);
    assert(fwd_forward(t, "1.2.2.3") == 22);
    assert(fwd_forward(t, "1.2.4.3") == 21);
    assert(fwd_forward(t, "1.2.8.3") == 20);
    assert(fwd_forward(t, "1.2.16.3") == 19);
    assert(fwd_forward(t, "1.2.32.3") == 18);
    assert(fwd_forward(t, "1.2.64.3") == 17);
    assert(fwd_forward(t, "1.2.128.3") == 16);

    assert(fwd_forward(t, "1.0.2.3") == -1);

    fwd_clear(t);

    for (int i = 8; i <= 16; ++i) {
	char prefix[100];
	sprintf(prefix, "1.0.0.0/%d", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "1.0.2.3") == 16);
    assert(fwd_forward(t, "1.1.2.3") == 15);
    assert(fwd_forward(t, "1.2.2.3") == 14);
    assert(fwd_forward(t, "1.4.2.3") == 13);
    assert(fwd_forward(t, "1.8.2.3") == 12);
    assert(fwd_forward(t, "1.16.2.3") == 11);
    assert(fwd_forward(t, "1.32.2.3") == 10);
    assert(fwd_forward(t, "1.64.2.3") == 9);
    assert(fwd_forward(t, "1.128.2.3") == 8);

    assert(fwd_forward(t, "0.1.2.3") == -1);

    fwd_clear(t);

    for (int i = 0; i <= 8; ++i) {
	char prefix[100];
	sprintf(prefix, "0.0.0.0/%d", i);
	assert(fwd_add(t, prefix, i));
    }

    assert(fwd_forward(t, "0.1.2.3") == 8);
    assert(fwd_forward(t, "1.1.2.3") == 7);
    assert(fwd_forward(t, "2.1.2.3") == 6);
    assert(fwd_forward(t, "4.1.2.3") == 5);
    assert(fwd_forward(t, "8.1.2.3") == 4);
    assert(fwd_forward(t, "16.1.2.3") == 3);
    assert(fwd_forward(t, "32.1.2.3") == 2);
    assert(fwd_forward(t, "64.1.2.3") == 1);
    assert(fwd_forward(t, "128.1.2.3") == 0);

    fwd_delete(t);
}
