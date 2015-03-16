 
#include "DagMC.hpp"
#include <iostream>

using namespace moab; 

int main( int argc, char** argv) 
{

  ErrorCode rval; 



  DagMC *dag = DagMC::instance();
 
  rval =  dag->load_file("cube.h5m", 1e-03);
  assert( MB_SUCCESS == rval);
  if( MB_SUCCESS != rval) return rval; 
  
  //get the volume handle  
   //get the GEOM_DIM tag
  Tag geom_dim;
  rval = dag->moab_instance()->tag_get_handle( GEOM_DIMENSION_TAG_NAME, 1,
  					       MB_TYPE_INTEGER, geom_dim);
  assert( MB_SUCCESS == rval);
  if( MB_SUCCESS != rval) return rval; 
  
  // geom dimension of 3 should indicate a volume
  int dim = 3;
  void* ptr = &dim;
  
  Range volumes;
  
  //get all volume meshsets (should only be one)

  rval = dag->moab_instance()->get_entities_by_type_and_tag( 0, MBENTITYSET, &geom_dim, &ptr, 1, volumes);
   assert( MB_SUCCESS == rval);
   if( MB_SUCCESS != rval) return rval; 
   
   std::cout << "Number of volumes: " << volumes.size() << std::endl;

   //assume its the one and only volume 
   EntityHandle cube = volumes[0];

   
   double cube_volume; 
   dag->measure_volume( cube, cube_volume );


   std::cout << "Volume of the occ cube is: " << cube_volume << std::endl;
}



