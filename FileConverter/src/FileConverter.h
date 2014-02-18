/**
* @file   ${FileConverter.h}
* @author Rainer Koch
* @date   ${2014/02/12}
*
* Converts files with point clouds from one to another format.
*/

/* read from y,x file
 *
 * @param: return true, false
 *
 * */
bool load_yx_file(char* filename);
/* read from y,x, intensity file
 *
 * @param: return true, false
 *  * */
bool load_yxi_file(char* filename);

/* write to y,x file
 *
 * @param: return true, false
 *  * */
bool write_xy_file(char* filename);
/* write to y,x, intensity file
 *
 * @param: return true, false
 *  * */
bool write_xyi_file(char* filename);






