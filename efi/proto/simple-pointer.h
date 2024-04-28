#pragma once

#include "efi.h"

#define EFI_SIMPLE_POINTER_PROTOCOL_GUID \
        GUID_DEF(0x31878c87, 0xb75, 0x11d5, 0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d)

typedef struct {
        int32_t RelativeMovementX;
        int32_t RelativeMovementY;
        int32_t RelativeMovementZ;
        bool LeftButton;
        bool RightButton;
} EFI_SIMPLE_POINTER_STATE;

typedef struct {
        uint64_t ResolutionX;
        uint64_t ResolutionY;
        uint64_t ResolutionZ;
        bool LeftButton;
        bool RightButton;
} EFI_SIMPLE_POINTER_MODE;


typedef struct EFI_SIMPLE_POINTER_PROTOCOL EFI_SIMPLE_POINTER_PROTOCOL;
struct EFI_SIMPLE_POINTER_PROTOCOL {
        EFI_STATUS(EFIAPI *Reset)(EFI_SIMPLE_POINTER_PROTOCOL *This, bool ExtendedVerification);
        EFI_STATUS(EFIAPI *GetState)(EFI_SIMPLE_POINTER_PROTOCOL *This, EFI_SIMPLE_POINTER_STATE *State);
        EFI_EVENT WaitForInput;
        EFI_SIMPLE_POINTER_MODE *Mode;
};