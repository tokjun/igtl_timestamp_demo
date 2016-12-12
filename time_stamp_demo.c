/*=========================================================================

  Program:   OpenIGTLink Library
  Language:  C

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include <stdio.h>
#include <string.h>
#include "igtl_types.h"
#include "igtl_header.h"
#include "igtl_tdata.h"
#include "igtl_util.h"

#if defined(WIN32) || defined(_WIN32)
#else
#include <sys/time.h>
#endif


#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define TEST_TDATA_NUM 3

#pragma pack(1)
struct tdata_message {
  igtl_header           header;
  igtl_tdata_element    tlist[TEST_TDATA_NUM];
};
#pragma pack()

#if defined(WIN32) || defined(_WIN32)
time_t  WinTimeOrigin;
clock_t WinClockOrigin;
#endif

void get_time_origin()
{
#if defined(WIN32) || defined(_WIN32)
  winTimeOrigin  = time( NULL );
  winClockOrigin = clock();
#endif
}


igtl_uint64 get_time_stamp()
{
#if defined(WIN32) || defined(_WIN32)
  clock_t c1 = clock();
  igtl_uint32 second     = winTimeOrigin + ( c1 - winClockOrigin ) / CLOCKS_PER_SEC;
  igtl_uint32 nanosecond = (c1 - winClockOrigin ) % CLOCKS_PER_SEC * ( 1e9 / CLOCKS_PER_SEC );
#else

  struct timeval tval;
  gettimeofday( &tval, 0 );
  igtl_uint32 second     = tval.tv_sec;
  igtl_uint32 nanosecond = tval.tv_usec * 1000; /* convert from micro to nano */

#endif // defiend(WIN32)

  // Export as 64-bit fixed-point expression used in OpenIGTLink
  igtl_uint32 sec      = second;
  igtl_uint32 fraction = igtl_nanosec_to_frac(nanosecond);

  igtl_uint64 ts  =  sec & 0xFFFFFFFF;
  ts = (ts << 32) | (fraction & 0xFFFFFFFF);

  return ts;
}


int main( int argc, char * argv [] )
{

  struct tdata_message message;
  int r;
  int s;

  get_time_origin();

  /* Tracking data 0 */
  strncpy((char*)&(message.tlist[0].name), "Tracker0", 20);
  message.tlist[0].type     = IGTL_TDATA_TYPE_6D;
  message.tlist[0].reserved = 0;
  message.tlist[0].transform[0] = -0.954892f;
  message.tlist[0].transform[1] = 0.196632f;
  message.tlist[0].transform[2] = -0.222525f;
  message.tlist[0].transform[3] = -0.196632f;
  message.tlist[0].transform[4] = 0.142857f;
  message.tlist[0].transform[5] = 0.970014f;
  message.tlist[0].transform[6] = 0.222525f;
  message.tlist[0].transform[7] = 0.970014f;
  message.tlist[0].transform[8] = -0.0977491f;
  message.tlist[0].transform[9] = 46.0531f;
  message.tlist[0].transform[10] = 19.4709f;
  message.tlist[0].transform[11] = 46.0531f;

  /* Tracking data 1 */
  strncpy((char*)&(message.tlist[1].name), "Tracker1", 20);
  message.tlist[1].type     = IGTL_TDATA_TYPE_6D;
  message.tlist[1].reserved = 0;
  message.tlist[1].transform[0] = -0.954892f;
  message.tlist[1].transform[1] = 0.196632f;
  message.tlist[1].transform[2] = -0.222525f;
  message.tlist[1].transform[3] = -0.196632f;
  message.tlist[1].transform[4] = 0.142857f;
  message.tlist[1].transform[5] = 0.970014f;
  message.tlist[1].transform[6] = 0.222525f;
  message.tlist[1].transform[7] = 0.970014f;
  message.tlist[1].transform[8] = -0.0977491f;
  message.tlist[1].transform[9] = 46.0531f;
  message.tlist[1].transform[10] = 19.4709f;
  message.tlist[1].transform[11] = 46.0531f;

  /* Tracking data 2 */
  strncpy((char*)&(message.tlist[2].name), "Tracker2", 20);
  message.tlist[2].type     = IGTL_TDATA_TYPE_6D;
  message.tlist[2].reserved = 0;
  message.tlist[2].transform[0] = -0.954892f;
  message.tlist[2].transform[1] = 0.196632f;
  message.tlist[2].transform[2] = -0.222525f;
  message.tlist[2].transform[3] = -0.196632f;
  message.tlist[2].transform[4] = 0.142857f;
  message.tlist[2].transform[5] = 0.970014f;
  message.tlist[2].transform[6] = 0.222525f;
  message.tlist[2].transform[7] = 0.970014f;
  message.tlist[2].transform[8] = -0.0977491f;
  message.tlist[2].transform[9] = 46.0531f;
  message.tlist[2].transform[10] = 19.4709f;
  message.tlist[2].transform[11] = 46.0531f;


  /* Swap byte order if necessary */
  igtl_tdata_convert_byte_order(message.tlist, TEST_TDATA_NUM);

  /* Create OpenIGTLink header */
  message.header.version = 1;
  strncpy( (char*)&(message.header.name), "TDATA", 12 );
  strncpy( (char*)&(message.header.device_name), "DeviceName", 20 );
  message.header.timestamp = get_time_stamp();
  message.header.body_size = IGTL_TDATA_ELEMENT_SIZE*TEST_TDATA_NUM;
  message.header.crc = igtl_tdata_get_crc(message.tlist, TEST_TDATA_NUM);
  igtl_header_convert_byte_order( &(message.header) );

}
