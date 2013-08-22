SHELL=/bin/sh

dirs := \
	lib \
	App \
	Add-Ons

default install clean:
	@for dir in $(dirs); do \
		if [ -d "$$dir" ]; then \
			$(MAKE) -C $$dir $@; \
		fi \
	done
