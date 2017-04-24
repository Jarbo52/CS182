make: minprio.c testminprio.c
	gcc -g -std=c99 -o testMin testminprio.c minprio.c
test: testMin
	./testMin
prim: minprio.c testprim.c graph.c graphio.c primMST.c 
	gcc -g -std=c99 -o testPrim testprim.c primMST.c minprio.c graphio.c graph.c
primTest: testPrim
	./testPrim
