#pragma once

#include <SMS/spc/SpcInterp.hxx>
#include <Dolphin/types.h>


template <typename T> class TSpcTypedInterp : public TSpcInterp {
public:
  ~TSpcTypedInterp();

  void dispatchBuiltin(u32, u32);
};