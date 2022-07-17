#pragma once

#include <JSystem/JSupport/JSUMemoryStream.hxx>
#include <JSystem/JDrama/JDRNameRefPtrListT.hxx>
#include <JSystem/JDrama/JDRNameRef.hxx>
#include <Dolphin/types.h>

namespace JDrama {

class TNameRefGen {
public:
  virtual void load(JSUMemoryInputStream &stream);
  virtual TNameRef *getNameRef(const char *) const;

  TNameRef *getRootNameRef();
  static TNameRefGen *getInstance();

private:
  TNameRef *mRootName;
};

} // namespace JDrama