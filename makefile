CC = g++ -std=c++17
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lgtest
BD=build

OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LFLAGS += -pthread -lsubunit
endif

PROFILE = 3DViewer.pro

all : uninstall clean build

build : mk replication
	cd $(BD); qmake $(PROFILE)
	make -C  $(BD)/
	cd $(BD); rm -rf *.c *.h *.cpp *.ui *.o *.icns *.pro *.user *.qrc *.fsh *.vsh makefile view ui model textures controller 3rdparty icons_ui

mk:
	mkdir $(BD)/
	mkdir $(BD)/model/
	mkdir $(BD)/controller/
	mkdir $(BD)/view/
	mkdir $(BD)/icons_ui/
	mkdir $(BD)/textures/
	mkdir $(BD)/3rdparty/

replication:
	cp $(PROFILE) $(BD)/
	cp -r 3rdparty/ $(BD)/3rdparty/
	cp main.cpp $(BD)/
	cp 3DViwer_tests.cpp $(BD)/
	cp *.qrc $(BD)/
	cp *.fsh $(BD)/
	cp *.vsh $(BD)/
	cp icons_ui/*.png $(BD)/icons_ui/
	cp textures/*.png $(BD)/textures/
	cp -r controller $(BD)/
	cp -r view $(BD)/
	cp -r model $(BD)/
	cp makefile $(BD)/

install: uninstall build

uninstall: 
	rm -rf $(BD)

dist: clean 
	rm -rf backup_3DViewer
	mkdir backup_3DViewer
	mkdir backup_3DViewer/icons_ui
	mkdir backup_3DViewer/textures
	mkdir backup_3DViewer/3rdparty
	cp -r controller backup_3DViewer/
	cp -r view backup_3DViewer/
	cp -r model backup_3DViewer/
	cp -r ui backup_3DViewer/
	cp -r 3rdparty/ backup_3DViewer/3rdparty/
	cp icons_ui/*.png backup_3DViewer/icons_ui/
	cp textures/*.png backup_3DViewer/textures/
	cp makefile *.pro *.cpp *.cpp *.qrc *.fsh *.vsh backup_3DViewer/
	tar -cvzf $(HOME)/Desktop/backup_3DViewer.tgz backup_3DViewer/
	rm -rf backup_3DViewer/

tests : clean
	$(CC) $(FLAGS) 3DViwer_tests.cpp model/s21_matrix_oop.cpp -o test $(LFLAGS)
	./test

leaks: clean tests
	leaks --atExit -- ./test

cpplint :
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp model/*.cpp
	python3 ../materials/linters/cpplint.py --extensions=cpp view/*.cpp
	python3 ../materials/linters/cpplint.py --extensions=h model/*.h
	python3 ../materials/linters/cpplint.py --extensions=h view/*.h
	python3 ../materials/linters/cpplint.py --extensions=h controller/*.h
	$(RM) CPPLINT.cfg

cppcheck :
	cppcheck --std=c++17 --enable=all --check-config --suppress=missingIncludeSystem --suppress=missingInclude --suppress=unmatchedSuppression model/* view/* controller/*

gcov_report : clean
	$(MAKE) LFLAGS="$(LFLAGS) --coverage" tests
	lcov -t test -o test.info -c -d . --no-external
	genhtml -o report test.info
ifeq ($(OS), Linux)
	-xdg-open report/index.html
else
	-open report/index.html
endif

report_clean :
	$(RM) -rf ./*.gcda ./*.gcno ./*.info ./*.gch ./report

dvi :
	cp man.dvi $(BD)/
	cp man.pdf $(BD)/
ifeq ($(OS), Linux)
	xdg-open $(BD)/man.pdf
else
	open $(BD)/man.pdf
endif

clean : report_clean
	rm -rf test *.a *.so *.o *.cfg *.gcda *.gcno *.html *.info *.dSYM report
