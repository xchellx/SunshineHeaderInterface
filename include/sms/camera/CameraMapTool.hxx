#pragma once

#include <JSystem/JGeometry.hxx>
#include <JSystem/JSupport/JSUMemoryStream.hxx>

class TCameraMapTool {
public:
    TCameraMapTool(const TCameraMapTool &);
    virtual ~TCameraMapTool();

    void calcPosAndAt(TVec3f *, TVec3f *) const;
    void load(JSUMemoryInputStream &);
};