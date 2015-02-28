PROG = bmw
all: $(PROG)
%: %.cpp ; g++  -o $@ $< 

clean: ; rm $(PROG)
