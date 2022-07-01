default: cs rs

r: # read gpio pins
	./test/read_pins.sh

cs: # compiles src
	gcc src/main.c -o out/main -I . -pthread
rs: # run srcs
	./out/main || True

ct: # compiles test
	gcc test/test_setup.c -o out/test_setup -I .
rt: # compiles test
	./out/test_setup

clean: # clean all stuff
	rm out/* || True