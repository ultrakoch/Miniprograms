/**
* @file   ${read_rxp.h}
* @author Rainer Koch
* @date   ${2013/11/15}
*
*
* All functions to read rxp file
*/
#include "slam6d/point_type.h"
#include "slam6d/scan.h"
/*
 * A function that read the .frame files created by slam6D
 *
 * @param dir the directory
 * @param start starting at scan number 'start'
 * @param end stopping at scan number 'end'
 * @param read a file containing a initial transformation matrix and apply it
 */
int read_rxp_file(string dir, int start, int end, bool readInitial);

/*
 * A function that read the .frame files created by slam6D
 *
 * @param dir the directory
 * @param start starting at scan number 'start'
 * @param end stopping at scan number 'end'
 * @param read a file containing a initial transformation matrix and apply it
 */
int readFrames(string dir, int start, int end, bool readInitial, reader_type &type);

void generateFrames(int start, int end, bool identity);
