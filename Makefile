.phony: check install
		 
biblio:	./src/biblio.c ./src/main.c
		gcc -o biblio $^

install:
		cp ./biblio ~/bin/biblio

check:
		cd tests && ./run
