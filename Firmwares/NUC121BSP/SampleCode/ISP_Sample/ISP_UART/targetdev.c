
#include "targetdev.h"
#include "ISP_USER.h"

// Supports 32K (APROM)
uint32_t GetApromSize()
{
    return 0x8000;
}

#define CONFIG0_DFEN                0x01
void GetDataFlashInfo(uint32_t *addr, uint32_t *size)
{
    uint32_t uData;
    *size = 0;
    FMC_Read_User(Config0, &uData);

    if ((uData & CONFIG0_DFEN) == 0) { //DFEN enable
        FMC_Read_User(Config1, &uData);

        if (uData > g_apromSize || (uData & 0x1FF)) { //avoid config1 value from error
            uData = g_apromSize;
        }

        *addr = uData;
        *size = g_apromSize - uData;
    } else {
        *addr = g_apromSize;
        *size = 0;
    }
}
