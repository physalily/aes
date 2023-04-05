build:
	gcc aes.c -o aes.out
run:
	./aes.out
clean:
	rm *.out
do:
	make build
	make run

