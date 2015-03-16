#undef NDEBUG
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <map>
#include <string>

#include "GeometryModifyTool.hpp"
#include "GeometryQueryTool.hpp"
#include "GMem.hpp"
#include "RefVertex.hpp"
#include "RefEdge.hpp"
#include "RefFace.hpp"
#include "RefVolume.hpp"
#include "Surface.hpp"
#include "InitCGMA.hpp"
#include "CubitCompat.hpp"

#include  "MBCartVect.hpp"

#define STRINGIFY(S) XSTRINGIFY(S)
#define XSTRINGIFY(S) #S
#ifndef SRCDIR
#  define SRCDIR "."
#endif

using std::list;
using std::pair;
using std::set;
using std::map;
using std::vector;

int main( int argc, char** argv ) {

  CubitStatus status = InitCGMA::initialize_cgma();
  if (CUBIT_SUCCESS != status) return 1;
  GeometryQueryTool *gti = GeometryQueryTool::instance();
   
  // Read in the geometry from files specified on the command line
  const char* filename = "cube.sat";
  status = CubitCompat_import_solid_model(filename, "ACIS_SAT");
  if (status != CUBIT_SUCCESS) {
    PRINT_ERROR("Problems reading geometry file %s.\n", filename);
    return 1;
  }
 
  DLIList<RefFace*> my_surfs;
  gti->ref_faces(my_surfs);

  std::vector<CubitVector> points;  
  std::vector<int> ids;
  for(unsigned int i = 0 ; i < my_surfs.size(); i++)
    {

      GMem data;
      //get the facet points
      my_surfs[i]->get_graphics(data, 1e-03, 1e-03);

      RefEntity *ent = dynamic_cast<RefEntity*>(my_surfs[i]);

      std::cout << "-------------------------" << std::endl;

      std::cout << "Surface id: " << ent->id() << std::endl; 

      std::cout << "-------------------------" << std::endl;



      

      for( unsigned int j = 0; j < data.pointListCount; j++)
	{

	  

	CubitVector point(data.point_list()[j].x,
			  data.point_list()[j].y,
			  data.point_list()[j].z );  

	std::cout << "Point " << j << std::endl; 
	std::cout << "x: " << point.x() << std::endl; 
	std::cout << "y: " << point.y() << std::endl; 
	std::cout << "z: " << point.z() << std::endl; 

        }


      std::cout << "Triangle facet indices:" << std::endl;
      int tri_num = 1;
      for( unsigned int j = 0; j < data.fListCount; j += data.facet_list()[j] + 1){

      int* facet = data.facet_list() + j;

      std::cout << "Triangle " << tri_num << std::endl; 
      tri_num++;

      std::vector<MBCartVect> verts;

      for( unsigned int k=1; k <= *facet ; k++)
	{
	std::cout << facet[k] << "\t";

	CubitVector point(data.point_list()[facet[k]].x,
			  data.point_list()[facet[k]].y,
			  data.point_list()[facet[k]].z ); 

	MBCartVect vert( point.x(), point.y(), point.z() );

	verts.push_back(vert);

	}

      verts[1] -= verts[0];
      verts[2] -= verts[0];
      MBCartVect norm = verts[1] * verts[2];
      norm.normalize();
      std::cout << "Normal: " <<  norm  << std::endl;


      std::cout << std::endl;
      }//end facet index loop

      std::cout << "-------------------------" << std::endl;
      
    }//end surface loop




}
