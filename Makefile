GCCPARAMS = -Iinclude -g

OBJECTS=obj/main.o \
	obj/mars.o \

obj/%.o: src/%.c
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

all: mars

mars: $(OBJECTS)
	gcc $(OBJECTS) -o mars $(GCCPARAMS)

clean:
	rm -rf mars obj
