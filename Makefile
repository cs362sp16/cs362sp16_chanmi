CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
	
unittest:
	gcc -o test1 unittest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o test2 unittest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o test3 unittest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o test4 unittest4.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o card1 cardtest1.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o card2 cardtest2.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o card3 cardtest3.c -g dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o card4 cardtest4.c -g dominion.o rngs.o interface.o $(CFLAGS)
		
unittestresults.out: unittest playdom
	rm -rf unittestresults.out
	./test1 >> unittestresults.out
	echo "GCOV AFTER 1 TEST" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./test2 >> unittestresults.out
	echo "GCOV AFTER TEST 2" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./test3 >> unittestresults.out
	echo "GCOV AFTER TEST 3" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./test4 >> unittestresults.out
	echo "GCOV AFTER TEST 4" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./card1 >> unittestresults.out
	echo "GCOV AFTER CARD 1" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out	
	
	./card2 >> unittestresults.out
	echo "GCOV AFTER CARD 2" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./card3 >> unittestresults.out
	echo "GCOV AFTER CARD 3" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	echo "NEXT FILE ------" >> unittestresults.out
	
	./card4 >> unittestresults.out
	echo "GCOV AFTER CARD 4" >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	
all: playdom player

clean:
	rm -f *.o *.out playdom.exe playdom test.exe test player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.a *.dSYM *.exe
