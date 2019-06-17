# Make file 
CC	=	gcc
CFLAGS	=	-c -Wall 
MYSQLCF :=	$(shell mysql_config --cflags)
LDFLAGS	=	
MYSQLLDF:=	$(shell mysql_config --libs)
SOURCES	=	main.c log.c config.c daemon.c signals.c pkthandle.c
HEADERS =	def.h main.h log.h config.h datapkt.h daemon.h signals.h pkthndla.h
OBJECTS	=	$(SOURCES:.c=.o)
EXEC	=	meteod

.PHONY: all clean install uninstall

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(MYSQLLDF)

.c.o:
	$(CC) $(CFLAGS) $< -o $@ $(MYSQLCF)

install: $(EXEC)
	cp $(EXEC) /usr/local/bin
	chown root:root /usr/local/bin/$(EXEC)

uninstall:
	rm /usr/local/bin/$(EXEC)

clean:
	rm -f $(EXEC) *.o