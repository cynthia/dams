include $(top_srcdir)/am.conf
ACLOCAL_AMFLAGS	= -I m4
dicdir	= $(libdir)/geonlp
MAKEDIC	= dams_makedic/dams_makedic
DAMS	= src/dams

SUBDIRS	= include lib dams_makedic src
DIST_SUBDIRS	= $(SUBDIRS) include php-extension
EXTRA_DIST	= m4 autotools.sh configure.ac data/dams.txt.gz
DIC	= data/dams.try data/dams.dat
CLEANFILES	= $(DIC)

$(DIC):	data/dams.txt.gz
	@gzip -dc data/dams.txt.gz > data/dams.txt
	@if [ -f data/alias.txt ]; then \
		echo "バイナリ形式の住所辞書を作成します（住所変更履歴付き）。"; \
		$(MAKEDIC) -r data/dams.txt -a data/alias.txt -w data/dams; \
	else \
		echo "バイナリ形式の住所辞書を作成します。"; \
		$(MAKEDIC) -r data/dams.txt -w data/dams; \
	fi
	@echo "バイナリ住所辞書を作成しました。"
	@-rm data/dams.txt

test:	$(DIC) $(DAMS)
	$(DAMS) '千葉県柏市柏の葉5-1-5' data/dams

dic:	$(DIC)

install-dic:
	@if ! [ -d $(libdir)/dams ]; \
		then mkdir -p $(libdir)/dams; \
	fi
	$(install_sh_DATA) $(DIC) $(libdir)/dams
