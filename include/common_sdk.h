#pragma once

#if !defined(SMS_BUILD_KURIBO) && !defined(SMS_BUILD_KAMEK) && !defined(SMS_BUILD_KAMEK_INLINE)
#define SMS_BUILD_KURIBO
#endif

#if !defined(SMS_BUILD_KURIBO)
#include <Kamek/sdk/kamek_sdk.h>
#else
#include <Kuribo/sdk/kuribo_sdk.h>
#endif