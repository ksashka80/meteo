# Make file 
CC	=	gcc
CFLAGS	=	-c -Wall
LDFLAGS	=	
SOURCES	=	main.c log.c config.c
HEADERS =	def.h main.h log.h config.h datapkt.h
OBJECTS	=	$(HEADERS) $(SOURCES:.cpp=.o)
EXEC	=	esp8266

.PHONY: all clean install uninstall

all: $(SOURCES) $(HEADERS) $(EXEC)

$(EXEC): $(OBJECTS)
	#echo $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

install: $(EXEC)
	cp $(EXEC) /bin
	chown root:root /bin/$(EXEC)

clean:
	rm -f $(EXEC) *.o