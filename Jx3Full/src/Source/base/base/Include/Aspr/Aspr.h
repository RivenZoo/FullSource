// v3.01

#ifdef __BORLANDC__

 #define CRC_CHECK_BEGIN     __emit__ (0xEB,0x04,0xEB,0x05,0x19,0x01);
 #define CRC_CHECK_END       __emit__ (0xEB,0x04,0xEB,0x05,0x29,0x01);

 #define CRC_BUFFER_BEGIN    __emit__ (0xE9,0x25,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0);
 #define CRC_BUFFER_END      __emit__ (0xE9,0x85,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0);

 #define ENVELOPE_CHECK             __emit__ (0xEB,0x04,0xEB,0x05,0x97,0x01);
 #define ENVELOPE_CHECK_FUNC        __emit__ (0xEB,0x04,0xEB,0x05,0x97,0x02);

 #define USER_POLYBUFFER            __emit__ (0xEB,0x04,0xEB,0x05,0x39,0x19);

 #define ENVELOPE_CHECK_BUFFER      __emit__ (0xE9,0x05,0x01,0,0,0,0,0,0,0);
 #define ENVELOPE_CHECK_FUNC_BUFFER __emit__ (0x33,0xC0,0xE9,0x03,0x01,0,0,0,0,0);

 #define DEFAULT_BUFFER             __emit__ (0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0);

#else

 #define CRC_CHECK_BEGIN \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x19 \
 __asm _emit 0x01

 #define CRC_CHECK_END \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x29 \
 __asm _emit 0x01

 #define CRC_BUFFER_BEGIN \
 __asm _emit 0xE9 \
 __asm _emit 0x25 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00

 #define CRC_BUFFER_END \
 __asm _emit 0xE9 \
 __asm _emit 0x85 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00

 #define ENVELOPE_CHECK \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x97 \
 __asm _emit 0x01

 #define ENVELOPE_CHECK_FUNC \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x97 \
 __asm _emit 0x02

 #define USER_POLYBUFFER \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x39 \
 __asm _emit 0x19

 #define ENVELOPE_CHECK_BUFFER \
 __asm _emit 0xE9 \
 __asm _emit 0x05 \
 __asm _emit 0x01 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00

 #define ENVELOPE_CHECK_FUNC_BUFFER \
 __asm _emit 0x33 \
 __asm _emit 0xC0 \
 __asm _emit 0xE9 \
 __asm _emit 0x03 \
 __asm _emit 0x01 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00 \
 __asm _emit 0x00

 #define DEFAULT_BUFFER \
 __asm _emit 0x0 __asm _emit 0x0 __asm _emit 0x0 __asm _emit 0x0 \
 __asm _emit 0x0 __asm _emit 0x0 __asm _emit 0x0 __asm _emit 0x0 \


// ASProtect 1.23 function
#ifdef __BORLANDC__

 #define REG_CRYPT_BEGIN __emit__ (0xEB,0x04,0xEB,0x05,0x89,0x01);
 #define REG_CRYPT_END   __emit__ (0xEB,0x04,0xEB,0x05,0x99,0x01);

#else

 #define REG_CRYPT_BEGIN \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x89 \
 __asm _emit 0x01		

 #define REG_CRYPT_END \
 __asm _emit 0xEB \
 __asm _emit 0x04 \
 __asm _emit 0xEB \
 __asm _emit 0x05 \
 __asm _emit 0x99 \
 __asm _emit 0x01 

#endif


#define APIConst		0xFFFFFFFF
#define capiDecrypt			 4
#define capiGetRegInfo			 5
#define capiGetTrialDays  		 8
#define capiGetTrialExecs 		 9

typedef DWORD (__stdcall  *TapiDecrypt) (IN char   *Key, IN DWORD  KeySize);
typedef char* (__stdcall  *TapiGetRegInfo) ();
typedef DWORD (__stdcall  *TapiGetTrialDays) ();
typedef DWORD (__stdcall  *TapiGetTrialExecs) ();

// ASProtect Check function by Freeway get from internet

//void __stdcall TestUSER32orKERNEL32API( void* Addr )
//{
//	__asm 
//	{
//		mov  eax,  Addr
//		push dword ptr [eax]
//		pop  dword ptr [eax]	
//    } 
//		   
//}

#define CHECK_ASPROTECT(nResult, APIFunction) \
{   \
	static unsigned char Proc[8] = { 0x5b,0x58,0xff,0x30,0x8f,0x00,0xff,0xe3 }; \
\
    __try { \
        __asm { push APIFunction }        \
        __asm { mov  eax, offset Proc }     \
		__asm { call eax }                 \
\
        nResult = true;     \
\
    } __except (EXCEPTION_EXECUTE_HANDLER) {    \
        nResult = false; \
    }  \
}

#endif