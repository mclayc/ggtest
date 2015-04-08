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
#include "Surface.hpp"
#include "RefVertex.hpp"
#include "RefEdge.hpp"
#include "RefFace.hpp"
#include "RefVolume.hpp"
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
  const char* filename = "cube.stp";
  status = CubitCompat_import_solid_model(filename, "STEP");
  if (status != CUBIT_SUCCESS) {
    PRINT_ERROR("Problems reading geometry file %s.\n", filename);
    return 1;
  }

  DLIList<RefEntity*> my_surfs;
  const char name[] = "Surface";

  gti->ref_entity_list( &(name[0]), my_surfs, true);
  my_surfs.reset();

  std::vector<CubitVector> points;
  for(unsigned int i = 0 ; i < my_surfs.size(); i++)
    {

      GMem data;
      //get the facet points
      RefFace *this_surf = dynamic_cast<RefFace*> (my_surfs[i]);
      this_surf->get_graphics(data, 5, 1e-02);




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

      MBCartVect tri_center = (1.0/3.0)*(verts[0] + verts[1] + verts[2] );
      tri_center.normalize();

      verts[1] -= verts[0];
      verts[2] -= verts[0];
      MBCartVect norm = verts[1] * verts[2];
      norm.normalize();
      std::cout << "Normal: " <<  norm  << std::endl;
      std::cout << "TriCtr: " <<  tri_center  << std::endl;
      std::cout << "Dot w/ Surf Normal: " << tri_center % norm << std::endl;


      std::cout << std::endl;
      }//end facet index loop

      std::cout << "-------------------------" << std::endl;

    }//end surface loop

  exit(0);
}
