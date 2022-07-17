#pragma once

#include "sms/spc/SpcInterp.hxx"
#include <dolphin/types.h>


template <typename T> class TSpcTypedInterp : public TSpcInterp {
public:
  ~TSpcTypedInterp();

  void dispatchBuiltin(u32, u32);
};