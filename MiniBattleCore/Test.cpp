#include <iostream>
#include "Test.h"

test testInit(Mode mode) {
	test t;
	if (mode == Mode::pve) {
		t.x = 12, t.y = 10;
	}
	else if (mode == Mode::pvp) {
		t.x = 10, t.y = 50;
	}
	return t;
}