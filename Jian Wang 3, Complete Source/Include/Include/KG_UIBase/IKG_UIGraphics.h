////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : IKG_UIGraphics.h
//  Version     : 1.0
//  Creator     : tongxuehu, zoukewei
//  Create Date : 07/01/2008
//  Comment     : 
//  
//  Copyright (C) 2008 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////

#ifndef IKG_UIGRAPHICS_H
#define IKG_UIGRAPHICS_H

#define KG_TRIANGLE_VERTEX_COUNT 3

#define KG_TEXTURE_COORDINATES_MAX 1.0f
#define KG_TEXTURE_COORDINATES_MIN 0.0f

enum KG_QUADRANGLE_VERTEX
{
    KG_VERTEX_TOPLEFT,
    KG_VERTEX_TOPRIGHT,
    KG_VERTEX_BOTTOMRIGHT,
    KG_VERTEX_BOTTOMLEFT,

    KG_VERTEX_COUNT,
};

struct KG_D3DVertex
{
    enum  {FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1};
    float fX, fY, fZ, fW;
    unsigned long ulColor;
    float fU, fV;
};

inline void  KG_FILL_VERTEX(
    KG_D3DVertex &rVertex, 
    float fX, 
    float fY, 
    unsigned long ulColor, 
    float fU, 
    float fV
)
{
    rVertex.fX = fX;
    rVertex.fY = fY;
    rVertex.fZ = 0.0f;
    rVertex.fW = 0.0f;
    rVertex.ulColor = ulColor;
    rVertex.fU = fU;
    rVertex.fV = fV;
};

enum KG_UIFontStyle
{
    KG_UIFONT_STYLE_NORMAL          = 0x00,
    KG_UIFONT_STYLE_BOLD            = 0x01,
    KG_UIFONT_STYLE_ITALIC          = 0x02,

    KG_UIFONT_STYLE_BORDER          = 0x100,
    KG_UIFONT_STYLE_SHADOW          = 0x200, 
    KG_UIFONT_STYLE_UNDERLINE       = 0x400,
    KG_UIFONT_STYLE_LINE_THROUGH    = 0x800,
};

struct KG_UIFont
{
    const char   *pcszFile;
    unsigned int  uHDPI;
    unsigned int  uVDPI;
};

struct KG_UIText
{
    unsigned int  uFontSize;
    const wchar_t *pwcszText;
    int           nTextLength;
    unsigned long ulStyle;
    unsigned long ulColor;
    unsigned long ulBoldColor;
    unsigned long ulBkColor;
    float fX;
    float fY;
    float fSpacing;
};

struct KG_UITexture
{
    unsigned int  uTextureID;
    unsigned long ulStyle;
    KG_D3DVertex  aD3DVertex[KG_VERTEX_COUNT];
};

typedef int (*KG_FUNC_RENDER_CALLBACK)(float fElapsedTime);

class IKG_UIGraphics
{
public:
    virtual int RegisterRenderCallback(KG_FUNC_RENDER_CALLBACK funcCallback) = 0;

    virtual int OnRender() = 0;
    virtual int SetFullScreen(int nEnable) = 0;
    virtual int UpdateSize() = 0;

public:
    virtual int BeginStencil(float fX, float fY, float fWidth, float fHeight) = 0;
    virtual int EndStencil() = 0;

public:
    virtual int CreateFont(const KG_UIFont &crUIFont, int *pnRetFontID) = 0;
    virtual int ReleaseFont(int nFontID) = 0;
    virtual int DrawText(int nFontID, const KG_UIText &crUIText) = 0;
    virtual int GetTextExtent(int nFontID, const KG_UIText &crUIText,  float *pfRetWidth, float *pfRetHeight) = 0;
    virtual int GetLineTextCount(int nFontID, const KG_UIText &crUIText, float fLineWidth, int *pnRetCount, float *pfRetTextWidth = NULL) = 0;
    virtual int GetLineHeight(int nFontID, unsigned int uFontSize, float *pfRetHeight) = 0;

    virtual int LoadTextureFromFile(const char cszFile[], unsigned int *puRetTextureID) = 0;
    virtual int UnloadTexture(unsigned int uTextureID) = 0;
    virtual int DrawTexture(const KG_UITexture &crUITexture) = 0;
    virtual int GetTextureSize(unsigned int uTextureID, float *pfRetWidth, float *pfRetHeight) = 0;
};

#endif // IKG_UIGRAPHICS_H
