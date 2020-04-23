#makefile

objects = sum.o sum2.o

lib = -L. -lpbc -lgmp -lm
#head_path = -I /usr/local/include/flint

all: test test2 test3 test4

test: test.o $(objects)
	cc -g -o test test.o $(objects) $(lib)

test2: test2.o $(objects)
	cc -g -o test2 test2.o $(objects) $(lib)

test3: test3.o $(objects)
	cc -g -o test3 test3.o $(objects) $(lib)
test4: test4.o $(objects)
	cc -g -o test4 test4.o $(objects) $(lib)



$(objects):%.o : %.c
	cc -c $< -o $@ 
test.o: test.c
	cc -c $< -o $@ 
test2.o: test2.c
	cc -c $< -o $@
test3.o: test3.c
	cc -c $< -o $@
test4.o: test4.c
	cc -c $< -o $@


.PHONY : clean
 clean:
	rm -f test test2 test3 test4 *.o
	
