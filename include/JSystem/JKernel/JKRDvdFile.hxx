#pragma once

#include <Dolphin/DVD.h>
#include <Dolphin/OS.h>
#include <Dolphin/types.h>
#include <JSystem/JKernel/JKRFile.hxx>
#include <JSystem/JSupport/JSUList.hxx>

class JKRDvdFile : public JKRFile {
public:
    JKRDvdFile();
    JKRDvdFile(s32);
    virtual ~JKRDvdFile();

    virtual bool open(const char *fileName) override;
    virtual void close() override;
    virtual s32 writeData(const void *addr, s32 length, s32 offset) override;
    virtual s32 readData(void *addr, s32 length, s32 offset) override;
    virtual s32 getFileSize() const override;
    virtual bool open(s32);

    void sync();

    bool mIsOpened;         // _18
    OSMutex *mMutex;        // _1C
    DVDFileInfo *mDVDInfo;  // _5C
    s32 mFileSize;          // _90
    OSMessage mMessage;     // _C0
    JSUPtrLink mDVDList;    // _E4
    OSThread *mCurThread;   // _F4
};