# ========================================================================================
# Makefile for G-Net Update Server			
# ========================================================================================


# ========================================================================================
# Set include directories.
INCLUDEDIR = /usr/local/include

# ========================================================================================
# Compile flags
CFLAGS = -g -m32
CC=gcc

# ========================================================================================
# TARGET/Source definitions
SRCDIR = .
TARGET = epoll_server
OBJS = $(TARGET).o
SRC = $(wildcard $(SRCDIR)/*.c)

# ========================================================================================
# Make all option.
LDLIBS = 
LIBS = -l pthread -lm -L /usr/lib/mysql -lmysqlclient -lz

all:$(TARGET)

$(TARGET):$(SRC:.c=.o)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS) $(LIBS)

# ========================================================================================
# Clean all option

clean:
	rm -f $(SRCDIR)*.o $(SRCDIR)*~ $(SRCDIR)fcs $(SRCDIR).depend
	rm -f *.o *~ $(TARGET) .depend $(TARGET)



