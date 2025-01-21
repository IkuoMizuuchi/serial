CFLAGS += -pthread

LDLIBS += -pthread
LIBS += -lpthread

all: serial

clean:
	rm serial
