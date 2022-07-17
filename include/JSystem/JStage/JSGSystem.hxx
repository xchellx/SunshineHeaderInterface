#pragma once

#include <JSystem/JStage/JSGObject.hxx>
#include <Dolphin/types.h>

namespace JStage {

class TSystem : public TObject {
public:
  virtual ~TSystem();

  virtual unsigned long JSGFGetType() const;
  virtual unsigned long JSGGetSystemData(unsigned long);
  virtual void JSGSetSystemData(unsigned long, unsigned long);
  virtual TObject *JSGFindObject(const char *, TEObject) const;
  virtual unsigned long JSGCreateObject(const char *, TEObject);
  virtual void JSGDestroyObject(TObject *);
};

} // namespace JStage