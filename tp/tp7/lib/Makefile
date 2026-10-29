# Fichier     : tp/tp7/lib/Makefile
# Description : Makefile de la librairie (produit librobot.a)
# Auteurs     : Nermine Morri, Felicia Remadji Libar,
#               Kamal Chalhoub, Diaby Alpha Boubacar
# INF1900 - equipe 0110

MCU=atmega324pa

# Nom de la librairie produite : lib$(PROJECTNAME).a
PROJECTNAME=robot

# Tous les fichiers sources du repertoire font partie de la librairie
PRJSRC=$(wildcard *.cpp)

INC=

OPTLEVEL=s

####### variables de configuration #######

CC=avr-gcc

# Archiveur utilise a la place de l'editeur de liens
AR=avr-ar
ARFLAGS=-crs

REMOVE=rm -f

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

####### cible #######

TRG=lib$(PROJECTNAME).a

####### definitions #######

CFILES=$(filter %.c, $(PRJSRC))
CPPFILES=$(filter %.cpp, $(PRJSRC))

OBJDEPS=$(CFILES:.c=.o) \
	$(CPPFILES:.cpp=.o)

####### regles #######

.PHONY: all clean

all: $(TRG)

# Archivage des fichiers objets dans la librairie statique
$(TRG): $(OBJDEPS)
	$(AR) $(ARFLAGS) $(TRG) $(OBJDEPS)

-include *.d

%.o: %.c
	$(CC) $(CFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

clean:
	$(REMOVE) $(TRG) $(OBJDEPS) *.d
