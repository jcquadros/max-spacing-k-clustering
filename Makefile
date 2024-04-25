
#FLAGS = -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g
LIBED_DEPS = $(patsubst %.c,%.o,$(wildcard ./src/*.c)) 

all: trab1

%.o: %.c %.h
	gcc $(FLAGS) -c -o $@ $< 

libed.a: $(LIBED_DEPS)
	ar -crs libed.a $(LIBED_DEPS)

trab1: trab1.c libed.a
	gcc -o trab1 trab1.c -I src -L . -led -lm

clean:
	rm -f trab1 libed.a  $(LIBED_DEPS)
	
run:
	./trab1