[+ autogen5 template +]
# Add source files here
EXECUTABLE	:= [+Name+]
# C/C++ source files (compiled with gcc / c++)
CCFILES		:= [+Name+].cpp

################################################################################
# Rules and targets

# NOTE: Assuming P4 based install until OpenCL becomes public
# Adjust P4_Root, default is ${HOME}/perforce/
# P4_ROOT=${HOME}/myperforce/

include ../../common/common_opencl.mk

