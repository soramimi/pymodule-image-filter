PYTHON=python3


.PHONY: build
build:
	$(PYTHON) setup.py build_ext -i


.PHONY: run
run:
	$(PYTHON) main.py


.PHONY: clean
clean:
	rm -f *.so
	rm -fr build

