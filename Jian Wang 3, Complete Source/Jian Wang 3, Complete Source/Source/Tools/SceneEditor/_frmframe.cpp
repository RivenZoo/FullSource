// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "_frmframe.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// C_frmFrame
namespace MFCFramework
{

IMPLEMENT_DYNCREATE(C_frmFrame, CWnd)

/////////////////////////////////////////////////////////////////////////////
// C_frmFrame properties

/////////////////////////////////////////////////////////////////////////////
// C_frmFrame operations

CString C_frmFrame::GetEnabled()
{
	CString result;
	InvokeHelper(0x68030006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetEnabled(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString C_frmFrame::GetPHeightMapName()
{
	CString result;
	InvokeHelper(0x68030005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPHeightMapName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL C_frmFrame::MeLoadPictures()
{
	BOOL result;
	InvokeHelper(0x60030029, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short C_frmFrame::GetPMaterialUp()
{
	short result;
	InvokeHelper(0x68030004, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPMaterialUp(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x68030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short C_frmFrame::GetPMaterialDown()
{
	short result;
	InvokeHelper(0x68030003, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPMaterialDown(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x68030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void C_frmFrame::LoadPictures()
{
	InvokeHelper(0x6003002a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString C_frmFrame::GetPTextureDir()
{
	CString result;
	InvokeHelper(0x68030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPTextureDir(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString C_frmFrame::GetPTextureDefFile()
{
	CString result;
	InvokeHelper(0x68030001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPTextureDefFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x68030001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

short C_frmFrame::GetPNumMaterial()
{
	short result;
	InvokeHelper(0x68030000, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void C_frmFrame::SetPNumMaterial(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x68030000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}
};