# mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
# current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
# ROOT_DIR :=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

FILENAME := $(basename $(FILE))

# REALPREFIX = $(realpath $(PREFIX))
LDLIBS := -lm -lstdc++

$(FILENAME):
	$(CXX) $@.c -o $@.exe -lGL -lGLU -lglut

run:
	./$(FILENAME).exe
