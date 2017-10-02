pipeDemo: program.c program.h
	gcc -o pipeDemo program.c

.PHONY: clean run
run:
	./pipeDemo
clean:
	rm pipeDemo
usage:
	@echo make
	@echo make run
