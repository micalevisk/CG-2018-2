# mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
# current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
# ROOT_DIR :=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

FILENAME := $(basename $(FILE))
ext := $(suffix $(FILE))

# REALPREFIX = $(realpath $(PREFIX))
LDLIBS := -lglut -lGLU -lGL -lm

$(FILENAME):
	$(CXX) $@$(ext) -o $@.exe $(LDLIBS) -D DEBUG=true
	$(MAKE) run

run:
	./$(FILENAME).exe
