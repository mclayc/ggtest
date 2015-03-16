
#ACIS_CGM_DIR = /home/shriwise/dagmc_blds/cgm_dev
#OCC_CGM_DIR = /home/shriwise/occ_blds/cgm
MOAB_DIR = /home/shriwise/dagmc_blds/moabs/
OCC_CGM_MAKE = /home/shriwise/oce_blds/cgm/lib/cgm.make
MOAB_MAKE = /home/shriwise/oce_blds/moab/lib/moab.make

#OCC_CGM_MAKE = /home/shriwise/dagmc_blds/cgm_dev/lib/cgm.make
#MOAB_MAKE = /home/shriwise/dagmc_blds/moabs/lib/moab.make

include ${OCC_CGM_MAKE}
include ${MOAB_MAKE}

build: occ acis

acis:
	g++ ggtest_acis.cpp -o ggtest_acis -g -fpermissive  $(CGM_INCLUDES) $(CGM_LIBS_LINK) $(MOAB_INCLUDES) $(MOAB_LIBS_LINK)

occ:
	g++ ggtest_occ.cpp -o ggtest_occ -g $(CGM_INCLUDES) $(CGM_LIBS_LINK) $(MOAB_INCLUDES) $(MOAB_LIBS_LINK)

occ_cube_test:

	g++ occ_cube_test.cpp -o occ_cube_test -g $(CGM_INCLUDES) $(CGM_LIBS_LINK) $(MOAB_INCLUDES) $(MOAB_LIBS_LINK)

measure_test: 

	g++ dagmc_measure.cpp -o measure_test -g -I/$(MOAB_DIR)/include \
	-L/$(MOAB_DIR)/lib -lMOAB -ldagmc

clean:
	rm ggtest_acis ggtest_occ measure_test occ_cube_test a.out
