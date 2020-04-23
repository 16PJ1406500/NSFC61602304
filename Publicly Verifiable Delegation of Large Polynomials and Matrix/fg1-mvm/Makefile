#makefile
test: 
	gcc prfm.c mvm.c mvmp.c bn_ext.c test.c -I /usr/local/include/flint  -lgmp -lflint -lrelic -lrelic_s -o test
.PHONY : clean
 clean:
	rm -f test
	
