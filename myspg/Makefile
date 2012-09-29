DEST =  myspg

OBJS =  myspg.o rs-232.o
 
INCS = -I. -I/usr/local/include -I/usr/src/linux/include

LIBS =  -L/usr/local/lib

#CFLAGS = -O $(INCS)
CPPFLAGS = -g -O $(INCS)

all:    $(DEST)

$(DEST):        $(OBJS)
	$(CXX) -o $(DEST) $(OBJS) $(LIBS) $(SYSLIB)

clean:
	rm -f $(OBJS) $(MODULE)


