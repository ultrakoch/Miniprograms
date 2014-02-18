/**
* @file   ${read_rxp.cpp}
* @author Rainer Koch
* @date   ${2013/11/15}
*
*
* All functions to read rxp file
*/

#include <fstream>
#include <stdexcept>
#define OPENMP_NUM_THREADS  2

#include "read_rxp.h"
#include "slam6d/point_type.h"
#include "slam6d/scan.h"
#include "XGetopt.h"
#include <iostream>

#include <fstream>
using std::ifstream;
#include <stdexcept>
using std::exception;

/**
 * Storing of all transformation (frames for animation) of all scans
 */
vector < vector <double*> > MetaMatrix;

/**
 * Storing of AlgoType for all frames
 */
vector < vector <Scan::AlgoType> > MetaAlgoType;

int current_frame = 0;

reader_type type  = RXP;

PointType pointtype;

unsigned int types = PointType::USE_NONE;


  static struct option longopts[] = {
     { "origin",          optional_argument,   0,  'o' },
     { "format",          required_argument,   0,  'f' },
     { "fps",             required_argument,   0,  'F' },
     { "scale",           required_argument,   0,  'S' },
     { "start",           required_argument,   0,  's' },
     { "end",             required_argument,   0,  'e' },
     { "reduce",          required_argument,   0,  'r' },
     { "max",             required_argument,   0,  'm' },
     { "min",             required_argument,   0,  'M' },
     { "octree",          optional_argument,   0,  'O' },
     { "reflectance",     no_argument,         0,  'R' },
     { "reflectivity",    no_argument,         0,  'R' },
     { "amplitude",       no_argument,         0,  'a' },
     { "deviation",       no_argument,         0,  'd' },
     { "height",          no_argument,         0,  'h' },
     { "type",            no_argument,         0,  'T' },
     { "color",           no_argument,         0,  'c' },
     { "loadObj",         required_argument,   0,  'l' },
     { "saveOct",         no_argument,         0,  '0' },
     { "loadOct",         no_argument,         0,  '1' },
     { "advanced",        no_argument,         0,  '2' },
     { 0,           0,   0,   0}                    // needed, cf. getopt.h
   };


 PointType  ptype = PointType(types);


/*
 * A function that read the .frame files created by slam6D
 *
 * @param dir the directory
 * @param start starting at scan number 'start'
 * @param end stopping at scan number 'end'
 * @param read a file containing a initial transformation matrix and apply it
 */

int read_rxp_file(string dir, int start, int end, bool readInitial)
{
  int maxDist = -1; // -1 indicates no limitation
  int minDist = -1; // -1 indicates no limitation
  types |= PointType::USE_REFLECTANCE;
  types |= PointType::USE_AMPLITUDE;
  types |= PointType::USE_DEVIATION;
  types |= PointType::USE_HEIGHT;
  types |= PointType::USE_TYPE;
  types |= PointType::USE_COLOR;

//  int r = readFrames(dir, start, end, readInitial, type);
//  cout << " Read frames" << endl;

  Scan::readScans(type, start, end, dir, maxDist, minDist, 0);

  cout << "Scans " << Scan::allScans.size() << endl;
  cout << "type " << type << endl;
  cout << "start " << start << endl;
  cout << "end " << end << endl;
  cout << "dir " << dir << endl;
  cout << "maxDist " << maxDist << endl;
  cout << "minDist " << minDist << endl;

  const vector <Point>* points = Scan::allScans[0]->get_points();

  // Save to file#


  int scannumber = Scan::allScans.size();
  for(unsigned int i = 0; i<scannumber; i++)
  {
    ofstream file;
    char filename[64];
    sprintf(filename,"scan_ext_%.3d.3d", i++);
    file.open(filename);

    // Write Header
    // Echos:
    // Intensity:
    file << "RXP converted" << endl;
//    file << "x, y, z, r ,g ,b , reflectance, amplitude, deviation" << endl;

    file << "x, y, z, reflectance, amplitude, deviation" << endl;

    for(unsigned int j=0; j<points->size(); j++)
    {
      double x = NAN;
      if((*points)[j].x) x = (*points)[j].x;
      double y = NAN;
      if((*points)[j].y) y = (*points)[j].y;
      double z = NAN;
      if((*points)[j].z) z = (*points)[j].z;
//      const char rgb[2] = "";
//      if((*points)[j].rgb[0]) rgb[0] = (*points)[j].rgb[0];
//      if((*points)[j].rgb[1]) rgb[1] = (*points)[j].rgb[1];
//      if((*points)[j].rgb[2]) rgb[2] = (*points)[j].rgb[2];
      float reflectance = 0;
      if((*points)[j].reflectance) reflectance = (*points)[j].reflectance;
      float amplitude = 0;
      if((*points)[j].amplitude) amplitude = (*points)[j].amplitude;
      float deviation = 0;
      if((*points)[j].deviation) deviation = (*points)[j].deviation;

//      file << x << " " << y << " " << z << " " << r << " " << g << " " << b << " " << reflectance << " " << amplitude << " " << deviation << endl;

      file << x << " " << y << " " << z << " " << reflectance << " " << amplitude << " " << deviation << endl;
    }
      file.close();

    cout << "File : " << filename << " written!" << endl;
  }

// if (r) generateFrames(start, start + Scan::allScans.size() - 1, false);
//   cout << " Generate frames" << endl;

  return 0;
}

/*
 * A function that read the .frame files created by slam6D
 *
 * @param dir the directory
 * @param start starting at scan number 'start'
 * @param end stopping at scan number 'end'
 * @param read a file containing a initial transformation matrix and apply it
 */
int readFrames(string dir, int start, int end, bool readInitial, reader_type &type)
{
  double initialTransform[16];
  if (readInitial) {
    cout << "Initial Transform:" << endl;
    string initialTransformFileName = dir + "initital.frame";
    ifstream initial_in(initialTransformFileName.c_str());
    if (!initial_in.good()) {
      cout << "Error opening " << initialTransformFileName << endl;
      exit(-1);
    }
    initial_in >> initialTransform;
    cout << initialTransform << endl;
  }

  ifstream frame_in;
  int  fileCounter = start;
  string frameFileName;
  for (;;) {
    if (end > -1 && fileCounter > end) break; // 'nuf read
    frameFileName = dir + "scan" + to_string(fileCounter++,3) + ".frames";

    frame_in.open(frameFileName.c_str());


    // read 3D scan
    if (!frame_in.good()) break; // no more files in the directory

    cout << "Reading Frames for 3D Scan " << frameFileName << "...";
    vector <double*> Matrices;
    vector <Scan::AlgoType> algoTypes;
    int frameCounter = 0;

    while (frame_in.good()) {
      frameCounter++;
      double *transMatOpenGL = new double[16];
      int algoTypeInt;
      Scan::AlgoType algoType;
      try {
        double transMat[16];
        frame_in >> transMat >> algoTypeInt;
        algoType = (Scan::AlgoType)algoTypeInt;

        // convert to OpenGL coordinate system
        double mirror[16];
        M4identity(mirror);
        mirror[10] = -1.0;
        if (readInitial) {
          double tempxf[16];
          MMult(mirror, initialTransform, tempxf);
          memcpy(mirror, tempxf, sizeof(tempxf));
        }
        //@@@
        //     memcpy(transMatOpenGL, transMat, 16*sizeof(double));
        MMult(mirror, transMat, transMatOpenGL);
      }
      catch (const exception &e) {
        break;
      }
      Matrices.push_back(transMatOpenGL);
      algoTypes.push_back(algoType);
    }
    MetaAlgoType.push_back(algoTypes);

    MetaMatrix.push_back(Matrices);

    if((type == UOS_MAP || type == UOS_MAP_FRAMES || type == RTS_MAP) && fileCounter == start+1) {
      MetaAlgoType.push_back(algoTypes);
      MetaMatrix.push_back(Matrices);
    }

    frame_in.close();
    frame_in.clear();
    cout << MetaMatrix.back().size() << " done." << endl;
    current_frame = MetaMatrix.back().size() - 1;
  }
  if (MetaMatrix.size() == 0) {
    cerr << "*****************************************" << endl;
    cerr << "** ERROR: No .frames could be found!   **" << endl;
    cerr << "*****************************************" << endl;
    cerr << " ERROR: Missing or empty directory: " << dir << endl << endl;
    return -1;
  }
  return 0;
}

void generateFrames(int start, int end, bool identity) {
  if (identity) {
    cout << "using Identity for frames " << endl;
  } else {
    cout << "using pose information for frames " << endl;
  }
  int  fileCounter = start;
  int index = 0;
  for (;;) {
    if (fileCounter > end) break; // 'nuf read
    fileCounter++;

    vector <double*> Matrices;
    vector <Scan::AlgoType> algoTypes;

    for (int i = 0; i < 3; i++) {
      double *transMat = new double[16];

      if (identity) {
        M4identity(transMat);
        transMat[10] = -1.0;
      } else {
        EulerToMatrix4(Scan::allScans[index]->get_rPos(), Scan::allScans[index]->get_rPosTheta(), transMat );
      }

      Matrices.push_back(transMat);
      algoTypes.push_back(Scan::ICP);

    }
    index++;
    MetaAlgoType.push_back(algoTypes);
    MetaMatrix.push_back(Matrices);
  }
}
