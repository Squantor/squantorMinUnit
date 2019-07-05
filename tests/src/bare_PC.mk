# update per change V0002
# board specific settings
C_SOURCES += src/00_start.c src/_exit.c src/main_$(PLATFORM).c
CXX_SOURCES +=
S_SOURCES += src/startup.s
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
