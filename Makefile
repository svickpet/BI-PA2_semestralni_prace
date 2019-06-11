CODE_DIR = src

.PHONY: compile doc

all: 
	make clean
	$(MAKE) -C $(CODE_DIR) compile
	make doc

compile:
	$(MAKE) -C $(CODE_DIR) compile

run: 
	./svickpet

clean:
	rm -f ./svickpet
	rm -f $(CODE_DIR)/*.o 
	rm -rf ./doc/*

doc:
	doxygen ./doxyFile
