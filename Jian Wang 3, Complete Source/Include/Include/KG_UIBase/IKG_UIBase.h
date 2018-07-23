////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : IKG_UIBase.h
//  Version     : 1.0
//  Creator     : tongxuehu, zoukewei
//  Create Date : 02/18/2008
//  Comment     : The following ifdef block is the standard way of creating macros which make exporting 
//                from a DLL simpler. All files within this DLL are compiled with the KG_UIBASE_EXPORTS
//                symbol defined on the command line. this symbol should not be defined on any project
//                that uses this DLL. This way any other project whose source files include this file see 
//                KG_UIBASE_API functions as being imported from a DLL, whereas this DLL sees symbols
//                defined with this macro as being exported.
//                #ifdef KG_UIBASE_EXPORTS
//  Copyright (C) 2008 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////

#ifndef IKG_UIBASE_H
#define IKG_UIBASE_H

class IKG_UIGraphics;

struct KG_UIBaseParam
{
    lua_State      *pLuaState;
    IKG_UIGraphics *piUIGraphics;   // if NULL, then call default graphics interface
    HWND            hDrawWnd;
};

class IKG_UIBase
{
public:
    virtual int Init(const KG_UIBaseParam &crUIBaseParam, void *pvContext) = 0;
    virtual int UnInit(void *pvContext) = 0;

    virtual int Breathe() = 0;
    virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
};

#define KG_GET_UIBASE_FUNC_KEY "GetUIBase"
typedef IKG_UIBase* (*KG_GET_UIBASE_FUNC)();

#endif // IKG_UIBASE_H