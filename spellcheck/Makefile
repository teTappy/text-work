
wordcheck: wordcheck.o dictionary.o
		gcc wordcheck.o dictionary.o -o wordcheck

spellcheck: spellcheck.o dictionary.o
		gcc spellcheck.o dictionary.o -o spellcheck

spellcheck.o: spellcheck.c
		gcc -Wall -Werror -Wextra -g -c spellcheck.c

dictionary.o: dictionary.c dictionary.h
		gcc -Wall -Werror -Wextra -g -c dictionary.c

wordcheck.o: wordcheck.c
		gcc -Wall -Werror -Wextra -g -c wordcheck.c

clean:
		rm -f *.o
