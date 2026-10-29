# Fichier     : tp/tp7/exec/Makefile
# Description : Makefile de l'executable de test (utilise librobot.a)
# Auteurs     : Nermine Morri, Felicia Remadji Libar,
#               Kamal Chalhoub, Diaby Alpha Boubacar
# INF1900 - equipe 0110

MCU=atmega324pa

PROJECTNAME=testLibrairie

PRJSRC=main.cpp

# Repertoire de la librairie et nom de celle-ci (librobot.a)
REPERTOIRE_LIB=../lib
NOM_LIB=robot

# Ou trouver les fichiers .h de la librairie (compilation)
INC=-I$(REPERTOIRE_LIB)

# Ou trouver la librairie et laquelle lier (edition de liens)
LIBS=-L$(REPERTOIRE_LIB) -l$(NOM_LIB)

OPTLEVEL=s

AVRDUDE_PROGRAMMERID=usbasp

####### variables de configuration #######

CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
REMOVE=rm -f
HEXFORMAT=ihex

####### options de compilation #######

CFLAGS=-I. -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-DF_CPU=8000000UL \
	-std=c++14 -fpack-struct -fshort-enums \
	-funsigned-bitfields -funsigned-char \
	-Wall

# avr-gcc 12 et plus : evite de faux avertissements sur l'acces aux registres
GCCVERSION := $(shell expr `$(CC) -dumpversion | cut -f1 -d.` \>= 12)
ifeq "$(GCCVERSION)" "1"
	CFLAGS += --param=min-pagesize=0
endif

CXXFLAGS=-fno-exceptions

LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

####### cibles #######

TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex

####### definitions #######

CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))

OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)

####### regles #######

.PHONY: all install clean debug

all: $(TRG) $(HEXROMTRG)

# Mode debogage : DEBUG est defini a la compilation seulement
debug: CFLAGS += -DDEBUG
debug: clean all

# Edition de liens avec la librairie
$(TRG): $(OBJDEPS) $(REPERTOIRE_LIB)/lib$(NOM_LIB).a
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)

-include *.d

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P usb -e -U flash:w:$(HEXROMTRG)

clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
