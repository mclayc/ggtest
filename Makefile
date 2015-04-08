# commandline usage to build ACIS or OCC versions
# if make is invoked without parameters the OCC version is the default
# make PRE=OCC occ
# make PRE=ACIS acis

PRE := OCC

# include and link paths for OCC
OCC_MOAB_ROOT = /userspace/m/mclayc/dagmc/moab_cgmocc14/
OCC_MOAB_MAKE = ${OCC_MOAB_ROOT}/lib/moab.make
OCC_CGM_MAKE = /userspace/m/mclayc/dagmc/cgm14.0_occ/lib/cgm.make

# include and link paths for ACIS
ACIS_MOAB_ROOT = /userspace/m/mclayc/dagmc/moab_cubit14/
ACIS_MOAB_MAKE = ${ACIS_MOAB_ROOT}/lib/moab.make
ACIS_CGM_MAKE = /userspace/m/mclayc/dagmc/cgmGGCubit/lib/cgm.make

MOAB_ROOT = ${${PRE}_MOAB_ROOT}
MOAB_MAKE = ${${PRE}_MOAB_MAKE}
CGM_MAKE = ${${PRE}_CGM_MAKE}

include ${CGM_MAKE}
include ${MOAB_MAKE}

CXX_RPATH = -Wl,-rpath=
LDFLAGS = $(subst -L,$(CXX_RPATH),$(MOAB_LDFLAGS)) -Wl,-rpath=$(MOAB_LIBDIR)
CXXFLAGS =  -g $(CGM_INCLUDES) $(CGM_LIBS_LINK) $(MOAB_INCLUDES) $(MOAB_LIBS_LINK) $(LDFLAGS)

occ:
	@echo "==========================================================="
	@echo "Building target=$@"
	@echo MOAB_ROOT=${MOAB_ROOT} LDFLAGS=${LDFLAGS}
	@echo
	g++ ggtest_occ.cpp -o ggtest_$@ ${CXXFLAGS}
	@echo "==========================================================="

acis:
	@echo "==========================================================="
	@echo "Building target=$@"
	@echo MOAB_ROOT=${MOAB_ROOT} LDFLAGS=${LDFLAGS}
	@echo
	g++ ggtest_acis.cpp -o ggtest_$@ -fpermissive ${CXXFLAGS}
	@echo "==========================================================="

occ_cube_test:

	g++ occ_cube_test.cpp -o occ_cube_test ${CXXFLAGS}

measure_test: 

	g++ dagmc_measure.cpp -o measure_test -g -I/$(MOAB_ROOT)/include \
	-L/$(MOAB_ROOT)/lib -lMOAB -ldagmc

clean:
	rm -f ggtest_acis ggtest_occ measure_test occ_cube_test a.out

.PHONY : clean