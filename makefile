#This makefile was generated automatically by MakeMake

#Definitions

CC=gcc
CFLAGS=-g -Wall
CCLINK=gcc
LIBS=
OBJS=point.o student.o main.o list.o cluster.o 
RM=rm -f
TARGET = ADT

$(TARGET): $(OBJS)
	  $(CCLINK) -o $(TARGET) $(OBJS) $(LIBS)

#Dependencies

cluster.o: cluster.c cluster.h defs.h point.h list.h
list.o: list.c list.h defs.h
main.o: main.c list.h defs.h point.h cluster.h student.h
student.o: student.c defs.h student.h
point.o: point.c point.h defs.h list.h

#Clean

clean:
	  $(RM) ADT *.o *.bak *~ "#"* core
