a.out: main.o red.o arp.o udp.o
	gcc main.o red.o arp.o udp.o -Wall -Werror -lpthread
	clear

main.o: main.c
	gcc -c main.c -Wall -Werror -lpthread

red.o: red.c
	gcc -c red.c -Wall -Werror -lpthread

arp.o: arp.c
	gcc -c arp.c -Wall -Werror -lpthread

udp.o: udp.c
	gcc -c udp.c -Wall -Werror -lpthread

clean:
	rm a.out *.o abierto.dat cerrado.dat
