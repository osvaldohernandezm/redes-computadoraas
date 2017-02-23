a.out: main.o red.o arp.o mysql.o
	gcc main.o red.o arp.o mysql.o `mysql_config --cflags` `mysql_config --libs` -Werror -Wall -lpthread

mysql.o: mysql.c
	gcc -c mysql.c `mysql_config --cflags` `mysql_config --libs` -Werror -Wall -lpthread

arp.o: arp.c
	gcc -c arp.c -Wall -Werror -lpthread	

red.o: red.c
	gcc -c red.c -Wall -Werror -lpthread

main.o: main.c
	gcc -c main.c -Wall -Werror -lpthread

clean:
	rm a.out *.o

chmod:
	chmod 777 -R *
