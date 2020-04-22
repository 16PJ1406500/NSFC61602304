#makefile
test: 
	gcc -g error_hdl.c param.c mm42.c bn_ext.c test.c -I /usr/local/include/flint  -lgmp -lflint -lrelic -lrelic_s -o test
.PHONY : clean
 clean:
	rm -f test
	
