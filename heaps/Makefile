CFLAGS = -std=gnu99 -m32 -g -O0 -Wall -Werror

CFILES = $(wildcard *.c)
OFILES = $(subst .c,.o,$(CFILES))

all : run

main : Makefile $(OFILES)
	gcc $(CFLAGS) -o $@ $(OFILES)

test.out : Makefile run
	./main > $@

test : Makefile test.out
	@(diff -bB test.ok test.out && echo "pass")

# keep all files
.SECONDARY :

%.o :  Makefile %.c
	gcc -c -MD $(CFLAGS) $*.c

clean ::
	rm -f *.out
	rm -f main
	rm -f *.o
	rm -f *.d

-include *.d

