/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "FlashOS.h" // FlashOS Structures

struct FlashDevice const FlashDevice = {
    FLASH_DRV_VERS,         // Driver Version, do not modify!
    "STM32H723VxT6_W25Q64", // Device Name
    EXTSPI,                 // Device Type
    0x90000000,             // Device Start Address
    0x00800000,             // Device Size (8MB)
    4096,                   // Programming Page Size
    0,                      // Reserved, must be 0
    0xFF,                   // Initial Content of Erased Memory
    1000,                   // Program Page Timeout 300 mSec
    3000,                   // Erase Sector Timeout 3000 mSec

    // Specify Size and Address of Sectors
    0x000800, 0x000000, // Sector Size 4kB (2048 Sectors)
    SECTOR_END};
