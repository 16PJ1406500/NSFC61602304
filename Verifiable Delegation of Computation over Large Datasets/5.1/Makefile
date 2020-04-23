#makefile
test: 
	gcc sdaprfs.c dp.c dpp.c bn_ext.c test.c -I /usr/local/include/flint  -lgmp -lflint -lrelic -lrelic_s -std=c99 -o test
.PHONY : clean
 clean:
	rm -f test
	
