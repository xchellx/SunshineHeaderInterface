#pragma once

#include <Dolphin/types.h>
#include <JSystem/JKernel/JKRArchivePri.hxx>

class JKRCompArchive : public JKRArchive {
public:
    JKRCompArchive(s32, u32);  // EMountDirection
    virtual ~JKRCompArchive();

    virtual void removeResourceAll();
    virtual bool removeResource(void *);

    virtual void *fetchResource(SDIFileEntry *, u32 *);
    virtual void *fetchResource(void *src, u32 len, SDIFileEntry *, u32 *);

    void open(s32);
};