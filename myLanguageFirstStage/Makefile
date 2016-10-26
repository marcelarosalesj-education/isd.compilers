CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: myLanguage

myLanguage: mylanguage.l mylanguage.y
	flex mylanguage.l
	bison -d mylanguage.y
	gcc lex.yy.c mylanguage.tab.c mylanguage.tab.h -o myLang

clean:
	\rm myLang lex.yy.c mylanguage.tab.c mylanguage.tab.h
