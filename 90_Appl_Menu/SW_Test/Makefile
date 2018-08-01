# Makefile for test application

INC = -I../../library/display/ -I../
OUT = out

test: Appl_Menu_Test.cpp
	g++ $(INC) -c Appl_Menu_Test.cpp -o $(OUT)/Appl_Menu_Test.o
	g++ $(INC) -c ../Appl_Menu.cpp -o $(OUT)/Appl_Menu.o
	g++ $(INC) -c ../Appl_Menu_Cfg.cpp -o $(OUT)/Appl_Menu_Cfg.o
	g++ $(INC) -D _DEBUG_ENABLE_=ON -c ../../library/display/Max7219.cpp -o $(OUT)/Max7219.o
	g++ $(OUT)/Appl_Menu_Test.o $(OUT)/Appl_Menu.o $(OUT)/Appl_Menu_Cfg.o $(OUT)/Max7219.o -o Executable
	cp Executable $(OUT)/Executable
clean:
	rm $(OUT)/Appl_Menu_Test.o
	rm $(OUT)/Appl_Menu.o
	rm $(OUT)/Appl_Menu_Cfg.o
	rm $(OUT)/Max7219.o
	rm $(OUT)/Executable
	rm Executable

