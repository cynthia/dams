include $(top_srcdir)/am.conf
EXTRA_DIST = README phpdams.ini phpdams.xml tests/sample.php

PROJROOT	= $(shell pwd)
PROJNAME	= php@PACKAGE_NAME@
MAKEDIR		= $(PROJROOT)/$(PROJNAME)
SPEC		= $(PROJNAME).xml
TARGET		= $(PROJNAME).so

all:	$(TARGET)

install:
	(cd $(MAKEDIR); make install;)
	cp $(PROJROOT)/$(PROJNAME).ini /etc/php.d

$(TARGET):	$(SPEC)
	pecl-gen $(SPEC);
	(cd $(MAKEDIR); \
	  phpize; \
          ./configure; \
          make;)

test:
	php tests/sample.php

clean:
	rm -rf $(MAKEDIR)
