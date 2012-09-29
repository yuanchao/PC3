DEST1 =  pc3

DEST2 =  touch

DEST3 =  align

DEST5 =  stable

OBJS1 =  pc3.o rs-232.o
 
OBJS2=  touch.o rs-232.o

OBJS3=  align.o rs-232.o
 
OBJS5=  stable.o rs-232.o
 
INCS = -I. -I/usr/include -I/usr/src/linux/include -I/usr/local/include -I/usr/local/include/sys

LIBS =  -L/usr/lib -lc -L/usr/local/lib -L/usr/local -lgpib

#CFLAGS = -O $(INCS)
CPPFLAGS = -g -O $(INCS) -Wno-deprecated

all:    $(DEST1) $(DEST2) $(DEST3) $(DEST5)

$(DEST1):        $(OBJS1)
	$(CXX) -o $(DEST1) $(OBJS1) $(LIBS) $(SYSLIB) -static

$(DEST2):        $(OBJS2)
	$(CXX) -o $(DEST2) $(OBJS2) $(LIBS) $(SYSLIB) -static

$(DEST3):        $(OBJS3)
	$(CXX) -o $(DEST3) $(OBJS3) $(LIBS) $(SYSLIB) -static

$(DEST5):        $(OBJS5)
	$(CXX) -o $(DEST5) $(OBJS5) $(LIBS) $(SYSLIB) -static

clean:
	rm -f $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS5) $(MODULE)


