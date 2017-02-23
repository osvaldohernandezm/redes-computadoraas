a.out: main.o red.o arp.o ping.o
	gcc main.o red.o arp.o ping.o -Wall -Werror -lpthread
	reset

main.o: main.c
	gcc -c main.c -Wall -Werror -lpthread

red.o: red.c
	gcc -c red.c -Wall -Werror -lpthread

arp.o: arp.c
	gcc -c arp.c -Wall -Werror -lpthread

ping.o: ping.c
	gcc -c ping.c -Wall -Werror -lpthread

clean:
	rm a.out *.o
