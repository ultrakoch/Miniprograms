/**
* @file   ${write_ASCII.cpp}
* @author Rainer Koch
* @date   ${2013/11/15}
*
*
* All functions to write ASCII file
*/
#include "write_ASCII.h"

int serialize_Ascii(char* filename, Scan* cloud)
{
  ofstream file;
  file.open(filename, ios::out);

  // Number of points
//  unsigned int cnt = Scan->size();
//  unsigned char* colors = Scan->getColors();
//
//  for(unsigned int i=0; i<cnt; i++)
//  {
//    double* point = (*Scan)[i];
//    file << point[0] << " " << point[1] << " " << point[2] << " ";
//    if(colors) file << (unsigned int)colors[0] << " " << (unsigned int)colors[1] << " " << (unsigned int)colors[2] << endl;
//  }

  file.close();
  return 0;
}
