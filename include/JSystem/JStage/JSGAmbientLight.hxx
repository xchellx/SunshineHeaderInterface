#pragma once

#include <JSystem/JStage/JSGObject.hxx>
#include <Dolphin/types.h>

namespace JStage {

class TAmbientLight : public TObject {
public:
  virtual ~TAmbientLight();

  virtual u32 JSGFGetType() const;
};

} // namespace JStage