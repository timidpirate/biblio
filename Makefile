.phony: all tests install clean
		 
biblio:	./src/biblio.c ./src/main.c
		gcc -o biblio $^

install:
		cp ./biblio ~/bin/biblio

test:
		cd tests && ./run
		
clean:
		
