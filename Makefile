OBJS = changeInfo.o deleteInfo.o gui.o guiClass.o guiGrade.o guiHelper.o guiStudent.o informationIn.o main.o testInfo.o
CC = gcc
PKGCONFIG = $(shell which pkg-config)
CFLAGs = $(shell $(PKGCONFIG) --cflags gtk+-2.0)
StuddentSystem : $(OBJS)
	$(CC) $(OBJS) -o StuddentSystem

changeInfo.o : changeInfo.c head.h
	$(CC) -c changeInfo.c $(CFLAGs) -o changeInfo.o 

deleteInfo.o : deleteInfo.c head.h
	$(CC) -c deleteInfo.c -o deleteInfo.o $(CFLAGs)

gui.o : gui.c head.h
	$(CC) -c gui.c -o gui.o $(CFLAGs)

guiClass.o : guiClass.c head.h
	$(CC) -c guiClass.c -o guiClass.o $(CFLAGs)

guiGrade.o : guiGrade.c head.h
	$(CC) -c guiGrade.c -o guiGrade.o $(CFLAGs)

guiHelper.o : guiHelper.c head.h
	$(CC) -c guiHelper.c -o guiHelper.o $(CFLAGs)

guiStudent.o : guiStudent.c head.h
	$(CC) -c guiStudent.c -o guiStudent.o $(CFLAGs)

informationIn.o : informationIn.c head.h
	$(CC) -c informationIn.c -o informationIn.o $(CFLAGs)

main.o : main.c head.h
	$(CC) -c main.c -o main.o $(CFLAGs)

testInfo.o : testInfo.c head.h
	$(CC) -c testInfo.c -o testInfo.o $(CFLAGs)

clean:
	rm -rf *.o StuddentSystem
