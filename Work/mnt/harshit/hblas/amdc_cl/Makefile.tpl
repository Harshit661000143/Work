[+ autogen5 template +]
DEPTH = ../../../../..

include $(DEPTH)/make/openclsdkdefs.mk 

####
#
#  Targets
#
####

OPENCL			= 1
SAMPLE_EXE		= 1
EXE_TARGET 		= [+Name+]
EXE_TARGET_INSTALL   	= [+Name+]

####
#
#  C/CPP files
#
####

FILES 	= [+Name+]
CLFILES = [+Name+]_kernels.cl 

LLIBS  	+= SDKUtil

include $(DEPTH)/make/openclsdkrules.mk 

