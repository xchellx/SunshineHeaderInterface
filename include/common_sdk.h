#pragma once

#include <Dolphin/types.h>

#ifndef KURIBO_NO_TYPES
#define KURIBO_NO_TYPES
#endif

#if !defined(SMS_BUILD_KURIBO) && !defined(SMS_BUILD_KAMEK) && !defined(SMS_BUILD_KAMEK_INLINE)
#define SMS_BUILD_KURIBO
#endif

#ifndef __ppc__
#define __ppc__
#endif

#define SMS_DEBUG _DEBUG

#if defined(SMS_BUILD_KAMEK) || defined(SMS_BUILD_KAMEK_INLINE)
#include <Kamek/sdk/kamek_sdk.h>
#define SMS_PATCH_B(source, target)  kmBranch(source, target)
#define SMS_PATCH_BL(source, target) kmCall(source, target)
#define SMS_WRITE_8(source, value)   kmWrite8(source, value)
#define SMS_WRITE_16(source, value)  kmWrite16(source, value)
#define SMS_WRITE_32(source, value)  kmWrite32(source, value)
#elif defined(SMS_BUILD_KURIBO)
#include <Kuribo/sdk/kuribo_sdk.h>
#define SMS_PATCH_B(source, target)  pp::PatchB(source, target)
#define SMS_PATCH_BL(source, target) pp::PatchBL(source, target)
#define SMS_WRITE_8(source, value)   pp::Patch8(source, value)
#define SMS_WRITE_16(source, value)  pp::Patch16(source, value)
#define SMS_WRITE_32(source, value)  pp::Patch32(source, value)
#else
#error                                                                                             \
    "Build type unspecified. Define either SMS_BUILD_KAMEK or SMS_BUILD_KAMEK_INLINE or SMS_BUILD_KURIBO"
#endif
