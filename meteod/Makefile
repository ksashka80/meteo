# Make file 
CC	=	gcc
CFLAGS	=	-c -Wall
LDFLAGS	=	
SOURCES	=	main.c log.c config.c daemon.c
HEADERS =	def.h main.h log.h config.h datapkt.h daemon.h
OBJECTS	=	$(SOURCES:.c=.o)
EXEC	=	meteod

.PHONY: all clean install uninstall

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

install: $(EXEC)
	cp $(EXEC) /usr/local/bin
	chown root:root /usr/local/bin/$(EXEC)

uninstall:
	rm /usr/local/bin/$(EXEC)

clean:
	rm -f $(EXEC) *.o