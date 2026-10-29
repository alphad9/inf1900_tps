# Fichier     : tp/tp7/Makefile
# Description : Makefile racine : construit lib, puis exec
# Auteurs     : Nermine Morri, Felicia Remadji Libar,
#               Kamal Chalhoub, Diaby Alpha Boubacar
# INF1900 - equipe 0110

.PHONY: all lib exec debug install clean

all: exec

lib:
	$(MAKE) -C lib

exec: lib
	$(MAKE) -C exec

debug: lib
	$(MAKE) -C exec debug

install: exec
	$(MAKE) -C exec install

clean:
	$(MAKE) -C lib clean
	$(MAKE) -C exec clean
