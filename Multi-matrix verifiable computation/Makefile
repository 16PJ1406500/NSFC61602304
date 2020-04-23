#makefile

objects =  mf.o mfp.o utils.o   

lib = -lgmp -lrelic -lrelic_s -fopenmp
head_path = -fopenmp

all: test test2

test: test.o $(objects)
	cc -g -o test test.o $(objects) $(lib)

test2: test2.o $(objects)
	cc -g -o test2 test2.o $(objects) $(lib)

$(objects):%.o : %.c
	cc -c $< -o $@ $(head_path)
test.o: test.c
	cc -c $< -o $@ $(head_path)
test2.o: test2.c
	cc -c $< -o $@ $(head_path)


.PHONY : clean
 clean:
	rm -f test test2 c1 c2 s1 s2 *.o 
	
