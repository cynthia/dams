include $(top_srcdir)/am.conf
AM_CPPFLAGS	= -DDEFAULT_DIC_PATH=\"$(libdir)/dams/\"
GENERATOR	= generate_itaijicpp
EXTRA_DIST	= itaiji.euc itaiji.cpp.in $(GENERATOR).cpp
ITAIJI_CPP	= itaiji.cpp
lib_LTLIBRARIES	= libdams.la
libdams_la_SOURCES	= libdams.h dam.h strlib.h try.h iconv_converter.h tmplvect.h MatchNodeResult.h \
	DamsWrapper.cpp openfile.cpp try.cpp dam.cpp iconv_converter.cpp lmatch.cpp strlib.cpp $(ITAIJI_CPP)
libdams_la_LDFLAGS	= -release $(LIB_VERSION_INFO)

$(GENERATOR):	$(GENERATOR).cpp
	$(CXXCOMPILE) -o $@ $<

$(ITAIJI_CPP):	$(GENERATOR) $(ITAIJI_CPP).in itaiji.euc
	-rm $(ITAIJI_CPP); ./$(GENERATOR)

clean-local:
	-rm $(GENERATOR) $(ITAIJI_CPP)
