WARNINGS= -Wall -Woverflow -Wall -pedantic -std=iso9899:1999 -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion  -Wstrict-overflow=4
DEBUG= -DDEBUG=1 -g
HARDENING= -DFORTIFY_SOURCE=2 -fstack-protector-all

CCDYNAMIC= ${CCFLAGS} -fPIC
LDDYNAMIC= ${LDFLAGS} -shared -L. -Wl,-rpath,/usr/local/lib -Wl,-z,relro -Wl,-z,now -fPIE

libdebug.so: debug.c
	${CC} ${CCDYNAMIC} ${HARDENING} ${WARNINGS} \
	${LDDYNAMIC} -o $@ $^

install:
	cp libdebug.so /usr/local/lib
	cp debug.h /usr/local/include
	ldconfig

test: libdebug.so
	${CC} ${WARNINGS} ${HARDENING} -I. -L. -ldebug  $@.c -o $@

uninstall:
	rm -i /usr/local/lib/libdebug.so
	rm -i /usr/local/include/debug.h
	ldconfig

clean:
	rm libdebug.so
	rm test
all:
	libdebug.so
