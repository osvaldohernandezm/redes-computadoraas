a.out: main.o red.o arp.o tcp.o
	gcc main.o red.o arp.o tcp.o -Wall -Werror -lpthread
	clear

main.o: main.c
	gcc -c main.c -Wall -Werror -lpthread

red.o: red.c
	gcc -c red.c -Wall -Werror -lpthread

arp.o: arp.c
	gcc -c arp.c -Wall -Werror -lpthread

tcp.o: tcp.c
	gcc -c tcp.c -Wall -Werror -lpthread

clean:
	rm a.out *.o open.dat
