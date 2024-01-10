#pragma once

UENUM(BlueprintType)
enum class NBG_E_Hero : uint8
{
    Idle UMETA(DisplayName = "Idle"),
    Walk UMETA(DisplayName = "Walk"),
    Shoot UMETA(DisplayName = "Shoot"),
    Jump UMETA(DisplayName = "Jump")
};
