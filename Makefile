.PHONY: i386 i386-clean help

i386:
	@make -f makefiles/Makefile.i386

i386-clean:
	@make -f makefiles/Makefile.i386 clean

help:
	@echo Opciones
	@echo - i386
	@echo - i386-clean
