mikron_gearbox.so: \
		mikron_common.h \
		mikron_gearbox.comp \
		mikron_gears.h \
		mikron_gears.c \
		mikron_util.h \
		mikron_util.c
	@halcompile --compile mikron_gearbox.comp

gearbox: mikron_gearbox.so

all: gearbox

install: all
	@halcompile --install mikron_gearbox.comp

clean:
	@rm -f mikron_gearbox.so
