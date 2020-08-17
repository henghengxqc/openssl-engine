CFLAGS= -Wall -W  -g -fPIC -I./ -I./include -I/home/wangheng/openssl-1.1.1b/include/ -I/home/wangheng/openssl-1.1.1b/install/usr/local/ssl//include
LDFLAGS= -L /home/wangheng/openssl-1.1.1b/install/usr/local/ssl/lib -lcrypto -lssl
CC=gcc

OBJS= robin_engine.o

LIBNAME=robin_engine.so
LIB=robin_engine.so

.SUFFIXES: .c

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

all: $(LIB)

$(LIB) :$(OBJS)
	$(CC) -shared -Wl,--soname=$(LIBNAME) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(LIB)

install:
	cp $(LIB) /usr/lib/x86_64-linux-gnu/engines-1.1/
