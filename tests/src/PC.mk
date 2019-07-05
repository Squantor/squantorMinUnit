# update per change V0002
# board specific settings
C_SOURCES += src/main_$(PLATFORM).c
CXX_SOURCES += 
S_SOURCES += 
DEFINES += -D$(PLATFORM)
INCLUDES += -I../inc
ALIBS +=
RLIBS +=
DLIBS +=
ALIBDIR +=
RLIBDIR +=
DLIBDIR +=

#custom build rules
pre-clean:
	

pre-release:
	

pre-debug:
	

.PHONY: pre-clean pre-release pre-debug
