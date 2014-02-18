/**
* @file   ${convertRXP.cpp}
* @author Rainer Koch
* @date   ${2013/11/15}
*
* Convert RXP-file (Riegel) to point cloud
*/

#include <math.h>
#include <stdlib.h>
#include <iostream>

#define OPENMP_NUM_THREADS  2

#include "slam6d/scan.h"
#include "read_rxp.h"
#include "write_ASCII.h"


using namespace std;


int main(int argc, char* argv[]) {

  int start = 0;
  int end = 0;
  bool readInitial = false;
  string dir = "/home/rainer/workspace/";

  int cols = 0;
  int x_val = 0;
  int y_val = 0;
  int z_val = 0;
  int intens_val = 0;
  int r_val = 0;
  int g_val = 0;
  int b_val = 0;

  // read and write file
  int r = read_rxp_file(dir, start, end, readInitial);
  if (r) cout << "Reading Error!" << endl;
  // Test output

  // write into *.3d file
  char filename[64];
  static int cnt = 0;
  sprintf(filename, "scan%03d.3d", cnt);

  //int w = serialize_Ascii(filename, cloud);
  //if (w) cout << "Writing Error!" << endl;

  // obviously/obcore/base/
  //serialize_Ascii(char* filename, CartesianCloud3D* cloud);

  //end

  return 0;
}
