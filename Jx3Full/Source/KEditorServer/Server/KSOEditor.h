#ifndef _KSO_EDITOR_H_
#define _KSO_EDITOR_H_

class KNetworkMgr;
class KSOEditor
{
public:
    KSOEditor();
    virtual ~KSOEditor();

    BOOL Init();
    void UnInit();

    void Run();

    void Quit();

private:
    BOOL                m_bRunFlag;
    KNetworkMgr*        m_pNetworkMgr;
};

extern KSOEditor* g_pSOEditor;

#endif // _KSO_EDITOR_H_