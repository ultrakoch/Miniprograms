/**
* @file   ${FileConverter.cpp}
* @author Rainer Koch
* @date   ${2014/02/12}
*
* Converts files with point clouds from one to another format.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <memory>
#include <stdlib.h>
#include <vector>

using namespace std;

/* Default parameters for file*/
   char* file_read;
   char* file_write;
   char* filetype_read;
   char* filetype_write;

   double* data_scan;
   unsigned char* colors_scan;
   double* intensity_scan;
   unsigned int scanpoints = 0;


void init(int argc, char* argv[])
{
  if(argc==5)
  {
    file_read      = argv[1];
    file_write     = argv[2];
    filetype_read  = argv[3];
    filetype_write  = argv[4];
  }
  else
  {
    cout << "usage: " << argv[0] << " [filename in] [filename out] [type in] [type out]" << endl;
    cout << "Types:" << endl;
    cout << "xy: x,y" << endl;
    cout << "xyi: x,y,intensity" << endl;
    cout << "yx: y,x" << endl;
    cout << "yxi: y,x,intensity" << endl;
  }
}
//void save_raw_dist(std::vector<long>& distance)
//{
//    // Save as raw file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//
//    double degree = 0.0;
//    sprintf(filename, "scan_raw_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, distance" << endl;
//
//    for(int i=0; i<= raysPscan; i++)
//    {
//      degree = urg.index2rad(i);
//      file << degree << " " << distance[i] << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_xy_dist(std::vector<long>& distance)
//{
//    // Save as xy file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    double x = 0.0;
//    double y = 0.0;
//    sprintf(filename, "scan_xy_%03d.txt", cnt);
//    file.open (filename);
//   file << "x, y" << endl;
//
//    for(int i=0; i<= raysPscan; i++)
//    {
//      x = sin(urg.index2rad(i)) * dist[i];
//      y = cos(urg.index2rad(i)) * dist[i];
//      file << "" << x << " " << y << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_raw_multidist(std::vector<long>& distance)
//{
//    // Save as raw file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    unsigned int id = 0;
//    double degree = 0.0;
//    sprintf(filename, "scan_raw_m_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, distance1, distance2, distance3" << endl;
//    for(int i=0; i<= raysPscan; i++)
//    {
//      degree = urg.index2rad(i);
//      file << degree << " " << distance[3*i] << " " << distance[3*i+1] << " " << distance[3*i+2] << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_xy_multidist(std::vector<long>& distance)
//{
//    // Save as xy file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    double x = 0.0;
//    double y = 0.0;
//    double degree = 0.0;
//    sprintf(filename, "scan_xy_m_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, x, y " << endl;
//
//    for(int i=0; i<= raysPscan; i++)
//    {
//        degree = urg.index2rad(i);
//        x = sin(urg.index2rad(i)) * dist[3*i];
//        y = cos(urg.index2rad(i)) * dist[3*i];
//        file << degree << " " << x << " " << y <<  endl;
//        x = sin(urg.index2rad(i)) * dist[3*i+1];
//        y = cos(urg.index2rad(i)) * dist[3*i+1];
//        file << degree << " " << x << " " << y << endl;
//        x = sin(urg.index2rad(i)) * dist[3*i+2];
//        y = cos(urg.index2rad(i)) * dist[3*i+2];
//        file << degree << " " << x << " " << y << endl;
//    }
//
//
////    while(id <= 3*urg.max_data_size())
////    {
////      degree = urg.index2rad(id);
////      x = cos(urg.index2rad(id)) * dist[id];
////      y = sin(urg.index2rad(id)) * dist[id];
////      file << degree << " " << x << " " << y << endl;
////      x = cos(urg.index2rad(id)) * dist[id+1];
////      y = sin(urg.index2rad(id)) * dist[id+1];
////      file << degree << " " << x << " " << y << endl;
////      x = cos(urg.index2rad(id)) * dist[id+2];
////      y = sin(urg.index2rad(id)) * dist[id+2];
////      file << degree << " " << x << " " << y << endl;
////
////      id = id + 3;
////    }
//    file.close();
//    cout << "saved: " << filename << endl;
//
//    cnt++;
//}
//void save_raw_intens(std::vector<long>& distance, std::vector<unsigned short>& intensity)
//{
//    // Save as raw file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//
//    double degree = 0.0;
//    sprintf(filename, "scan_raw_i_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, distance, intensity" << endl;
//    for(int i=0; i<= raysPscan; i++)
//    {
//      degree = urg.index2rad(i);
//      file << degree << " " << distance[i] << " " << intensity[i] << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_xy_intens(std::vector<long>& distance, std::vector<unsigned short>& intensity)
//{
//    // Save as xy file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    double x = 0.0;
//    double y = 0.0;
//    sprintf(filename, "scan_xy_i_%03d.txt", cnt);
//    file.open (filename);
//    file << "x, y, intensity" << endl;
//    for(int i=0; i<= raysPscan; i++)
//    {
//      x = sin(urg.index2rad(i)) * dist[i];
//      y = cos(urg.index2rad(i)) * dist[i];
//      file << x << " " << y << " " << intensity[i] << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_raw_mulitintens(std::vector<long>& distance, std::vector<unsigned short>& intensity)
//{
//
//    // Save as raw file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    double degree = 0.0;
//    sprintf(filename, "scan_raw_mi_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, distance0, distance1, distance2, intensity0, intensity1, intensity2" << endl;
//
//    for(int i=0; i<= raysPscan; i++)
//    {
//       degree = urg.index2rad(i);
//       file << degree << " " << distance[i] << " " << distance[3*i+1] << " " << distance[3*i+2] << " " << intensity[3*i] << " " << intensity[3*i+1] << " " << intensity[3*i+2] << endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}
//void save_xy_mulitintens(std::vector<long>& distance, std::vector<unsigned short>& intensity)
//{
//
//    // Save as xy file
//    ofstream file;
//    char filename[64];
//    static int cnt = 0;
//    double x = 0.0;
//    double y = 0.0;
//    double degree = 0.0;
//    sprintf(filename, "scan_xy_mi_%03d.txt", cnt);
//    file.open (filename);
//    file << "angle, x, y, intensity " << endl;
//    for(int i=0; i<= raysPscan; i++)
//    {
//      degree = urg.index2rad(i);
//      x = sin(urg.index2rad(i)) * dist[3*i];
//      y = cos(urg.index2rad(i)) * dist[3*i];
//      file << degree << " " << x << " " << y << " " << intensity[i]<< endl;
//      x = sin(urg.index2rad(i)) * dist[3*i+1];
//      y = cos(urg.index2rad(i)) * dist[3*i+1];
//      file << degree << " " << x << " " << y << " " << intensity[i+1]<< endl;
//      x = sin(urg.index2rad(i)) * dist[3*i+2];
//      y = cos(urg.index2rad(i)) * dist[3*i+2];
//      file << degree << " " << x << " " << y << " " << intensity[i+2]<< endl;
//    }
//    file.close();
//    cout << "saved: " << filename << endl;
//    cnt++;
//}



bool load_yx_file(char* filename)
{
  // Read Y,X file
      float x, y;
      string leseString;
      ifstream file(filename);
      unsigned int linesFile = 0;

          /* read single distance */
          if(!filename)
            cerr << "Eingabe-Datei kann nicht geöffnet werden\n";
          else
          {
            for(leseString; getline(file, leseString);)
            {
              linesFile++;
            }
            scanpoints = linesFile -1;
            linesFile = 0;
            data_scan   = new double[scanpoints * 2];
            std::ifstream file(filename);
            // print file header and remove it
            getline(file, leseString);
           // cout << "Fileheader:" << leseString << endl;
            for(leseString; getline(file, leseString);)
            {
              istringstream(leseString,ios_base::in) >> y >> x;
              // Build vtkCloud
              data_scan[2*linesFile]       = x;  // x
              data_scan[2*linesFile + 1]   = y;  // y
              // cout << "data id: " << linesFile << " x: " << data_scan[2*linesFile] << " y: " << data_scan[1*linesFile+1] << endl;
              linesFile++;
             }
          }
    return true;
}
bool load_yxi_file(char* filename)
{
  // Read Y,X file
      float x, y, intensity;
      string leseString;
      ifstream file(filename);
      unsigned int linesFile = 0;

          /* read single distance and intensity */
          if(!filename)
            cerr << "Eingabe-Datei kann nicht geöffnet werden\n";
          else
          {
            for(leseString; getline(file, leseString);)
            {
              linesFile++;
            }
            scanpoints = linesFile -1;
            linesFile = 0;
            data_scan   = new double[scanpoints * 2];
            intensity_scan   = new double[scanpoints];

            std::ifstream file(filename);
            // print file header and remove it
            getline(file, leseString);
           // cout << "Fileheader:" << leseString << endl;
            for(leseString; getline(file, leseString);)
            {
              istringstream(leseString,ios_base::in) >> y >> x >> intensity;

              // Build vtkCloud
              data_scan[2*linesFile]       = x;  // x
              data_scan[2*linesFile + 1]   = y;  // y

              intensity_scan[linesFile] = intensity;

              //cout << "data_scan id: " << linesFile << " x: " << data_scan[3*linesFile] << "y: " << data_scan[3*linesFile+1] << endl;
              linesFile++;
             }
          }
    return true;
}

bool write_xy_file(char* filename)
{
    // Save as x,y file
    ofstream file;
    file.open (filename);
    file << "x, y" << endl;
    // cout << "data id: " << linesFile << " x: " << data_scan[2*linesFile] << " y: " << data_scan[1*linesFile+1] << endl;
    for(int i=0; i< scanpoints; i++)
    {
      file << data_scan[2*i] << " " << data_scan[2*i + 1] << endl;
    }
    file.close();
    return true;
}
bool write_xyi_file(char* filename)
{
  // Save as x,y, intensity file
  ofstream file;
  file.open (filename);
  file << "x, y, intensity" << endl;

  for(int i=0; i< scanpoints; i++)
  {
    file << data_scan[2*i] << " " << data_scan[2*i + 1] << " " << intensity_scan[i] << endl;
  }
  file.close();
  return true;
}

int main(int argc, char* argv[])
{
/* Init */
  // Load parameters
  init(argc, argv);
  cout << "Init finished" << endl;
  bool loadFile = 0;
  bool writeFile = 0;


/* Read file */
  if(strcmp(filetype_read,"yx")==0)
    loadFile = load_yx_file(file_read);
  else if(strcmp(filetype_read,"yxi")==0)
    loadFile = load_yxi_file(file_read);

  if(loadFile)
    cout << "file " << file_read << " loaded!" << endl;
  else
    cout << "Input filetype not specified or can not be loaded!" << endl;

/* Save file */
  if(loadFile)
  {
    if(strcmp(filetype_write,"xy")==0)
      writeFile = write_xy_file(file_write);
    else if(strcmp(filetype_write,"xyi")==0)
      writeFile = write_xyi_file(file_write);
  }

  if(writeFile)
    cout << "file " << file_write << " saved!" << endl;
  else
    cout << "Output filetype not specified or can not be written!" << endl;

  return 0;
}
