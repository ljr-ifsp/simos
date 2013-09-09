
all: force_look
	cd src; $(MAKE) 
	cd examples; $(MAKE)

clean: force_look
	cd src; $(MAKE) clean
	cd examples; $(MAKE) clean

force_look:
	true

