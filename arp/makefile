a.out: red.o arp.o main.o
	gcc red.o arp.o main.o -Wall -Werror -lpthread

red.o: red.c
	gcc -c red.c -Werror -Wall -lpthread

arp.o: arp.c
	gcc -c arp.c -Werror -Wall -lpthread

main.o: main.c
	gcc -c main.c -Werror -Wall -lpthread

clean:
	rm a.out *.o
