# compile macro
CC		= g++
CFLAGS	= -std=c++11 -Wall -g
INCX11 = /opt/homebrew/include
LIBX11 = /opt/homebrew/lib
# LDFLAGS	= -lm
INCLUDES= -I ../include/HMI  -I $(INCX11) 
LIBS = -L $(LIBX11) -lX11 -lpthread

# user modify: subdir, target and objects
VPATH 	= ./bug ./environment ./behavior ./sensor ./accessory
EXENAME = main
OBJECTS	= main.o Aquarium.o Milieu.o Bug.o BugFactory.o Ear.o Eye.o SensorFactory.o BehaviorFactory.o AccessoryFacade.o Fearful.o MultiPersona.o SuicideBoomer.o Social.o Careful.o Camouflage.o Shell.o Fin.o


# make target
all:${OBJECTS}
	${CC} ${CFLAGS} -o ${EXENAME} ${OBJECTS} ${INCLUDES} ${LIBS} 

# make clean
clean:
	rm -rf ${EXENAME} ${OBJECTS} 

# dependence	
%.o : %.cpp
	${CC} ${CFLAGS} ${INCLUDES} -c $<

