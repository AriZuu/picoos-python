#
# Step 2 of MicroPython build:  Use MicroPython make framework
#                               to build it into .o files.
#
include ../micropython/py/mkenv.mk

QSTR_DEFS = qstrdefsport.h

include ../micropython/py/py.mk

OBJ = $(PY_O)

all: $(OBJ)

include ../micropython/py/mkrules.mk
