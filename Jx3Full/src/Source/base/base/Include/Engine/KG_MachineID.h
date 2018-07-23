
#ifndef _KG_MACHINE_ID_H_
#define _KG_MACHINE_ID_H_

#ifdef WIN32
// first 4 bits in byRetMachineID[0] is version of the algorithm of machine id
ENGINE_API int KG_GetMachineID(unsigned char byRetMachineID[16]);
#endif

#endif //_KG_MACHINE_ID_H_