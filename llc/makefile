a.out: main.o red.o llc.o analisa.o
	gcc main.o red.o llc.o analisa.o -Werror -Wall -lpthread

llc.o: llc.c
	gcc -c llc.c -Wall -Werror -lpthread    

red.o: red.c
	gcc -c red.c -Wall -Werror -lpthread

main.o: main.c
	gcc -c main.c -Wall -Werror -lpthread

analisa.o: analisa.c
	gcc -c analisa.c -Wall -Werror -lpthread

clean:
	rm a.out *.o *.dat

chmod:
	chmod 777 -R *

dependencias:
	apt-get install libmysqlclient-dev
	
