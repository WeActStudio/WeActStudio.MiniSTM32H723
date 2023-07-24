// By zhuyix
// 2021.01.10

#include "w25qxx_ospi.h"

#define NOTICK
#define OSPI_Infer (&hospi1)

W25Qxx_Interface_t OSPI_NOR_Mode = W25Qxx_SPI_MODE;

static int32_t W25Qxx_ResetEnable(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId       = HAL_OSPI_FLASH_ID_1;
    
    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_EnableReset;
    
    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DataMode           = HAL_OSPI_DATA_NONE;
    
    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_ResetDevice(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId       = HAL_OSPI_FLASH_ID_1;
    
    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_ResetDevice;
    
    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DataMode           = HAL_OSPI_DATA_NONE;
    
    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_ReadJEDECID(OSPI_HandleTypeDef *Ctx, W25Qxx_Interface_t Mode, uint8_t *ID)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    /* Initialize the read ID command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_JedecDeviceID;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;

    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

    s_command.DataMode           = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_DATA_1_LINE : HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = 3U;

    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Reception of the data */
    if (HAL_OSPI_Receive(Ctx, ID, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_ReadSR(OSPI_HandleTypeDef *Ctx, 
                                W25Qxx_Interface_t Mode, 
                                uint8_t Registerx, uint8_t *data)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    /* Initialize the read ID command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = Registerx;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = 0x0;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DataMode           = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_DATA_1_LINE : HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = 1U;
    
    s_command.DummyCycles        = 0U;
    
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Reception of the data */
    if (HAL_OSPI_Receive(Ctx, data, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_WriteSR(OSPI_HandleTypeDef *Ctx, 
                                W25Qxx_Interface_t Mode, 
                                uint8_t Registerx, uint8_t data)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    /* Initialize the read ID command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = Registerx;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = 0x0;

    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;

    s_command.DataMode           = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_DATA_1_LINE : HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = 1U;

    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Transmit of the data */
    if (HAL_OSPI_Transmit(Ctx, &data, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_WriteCMD(OSPI_HandleTypeDef *Ctx, W25Qxx_Interface_t Mode,uint8_t CMD)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    s_command.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId       = HAL_OSPI_FLASH_ID_1;
    
    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = CMD;
    
    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DataMode           = HAL_OSPI_DATA_NONE;
    
    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

//等待空闲
static void W25QXX_Wait_Busy(OSPI_HandleTypeDef *Ctx, W25Qxx_Interface_t Mode)
{
    uint8_t data;
    while(1)
    {
        W25Qxx_ReadSR(Ctx,Mode,W25X_ReadStatusReg1,&data);
        if((data & W25X_SR_WIP) != 0x01)
            break;
    }
}

static int32_t W25Qxx_AutoPolling(OSPI_HandleTypeDef *Ctx, W25Qxx_Interface_t Mode,uint8_t Registerx, uint32_t Match, uint32_t Mask, uint32_t IntervalTime)
{
    OSPI_RegularCmdTypeDef s_command = {0};
    OSPI_AutoPollingTypeDef s_config = {0};
    
    s_command.OperationType = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId       = HAL_OSPI_FLASH_ID_1;
    
    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = Registerx;
    
    s_command.Address            = 0x00;
    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DataMode           = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_DATA_1_LINE : HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = 1U;
    
    s_command.DummyCycles        = 0U;
    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    s_config.Match           = Match;
    s_config.Mask            = Mask;
    s_config.MatchMode       = HAL_OSPI_MATCH_MODE_AND;
    s_config.Interval        = IntervalTime;
    s_config.AutomaticStop   = HAL_OSPI_AUTOMATIC_STOP_ENABLE;
    
    if (HAL_OSPI_AutoPolling(Ctx, &s_config, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }

    return W25Qxx_OK;
}

static int32_t W25Qxx_WriteEnable(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    int32_t ret = W25Qxx_OK;
    if (W25Qxx_WriteCMD(Ctx,Mode,W25X_WriteEnable) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    #ifdef NOTICK
    else
    {
        uint8_t data;
        while(1)
        {
            W25Qxx_ReadSR(Ctx,Mode,W25X_ReadStatusReg1,&data);
            if((data & W25X_SR_WREN) == W25X_SR_WREN)
                break;
        }
    }
    #else
    else if(W25Qxx_AutoPolling(Ctx,Mode,W25X_ReadStatusReg1,W25X_SR_WREN, W25X_SR_WREN,10) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    #endif
    return ret;
}

static int32_t W25Qxx_QuadEnable(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    
    uint8_t stareg2;
    int32_t ret = W25Qxx_OK;
    
    if(Mode == W25Qxx_QPI_MODE)
    {
        return W25Qxx_ERROR;
    }
	else if(W25Qxx_ReadSR(Ctx,Mode,W25X_ReadStatusReg2,&stareg2) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    else 
    {
        if((stareg2 & 0X02) == 0)
        {
            if(W25Qxx_WriteEnable(Ctx,Mode) != W25Qxx_OK)
            {
                ret = W25Qxx_ERROR;
            }
            else
            {
                stareg2 |= 1<<1;
                if(W25Qxx_WriteSR(Ctx,Mode,W25X_WriteStatusReg2,stareg2) != W25Qxx_OK)
                {
                    ret = W25Qxx_ERROR;
                }
            }
        }
    }
    
    return ret;
}

static int32_t W25Qxx_ReadSTR(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode,uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    /* Initialize the read ID command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = (Mode == W25Qxx_SPI_MODE) ? W25X_QUAD_INOUT_FAST_READ_CMD : W25X_FastReadData;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = ReadAddr;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_4_LINES;
    s_command.AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE;
    s_command.AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS;
    s_command.AlternateBytes     = 0xFF;
    
    s_command.DummyCycles        = (Mode == W25Qxx_SPI_MODE) ? W25X_DUMMY_CYCLES_QUAD_INOUT_FAST_READ : W25X_DUMMY_CYCLES_FAST_READ_QPI_MDOE;

    s_command.DataMode           = HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = Size;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Reception of the data */
    if (HAL_OSPI_Receive(Ctx, pData, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

static int32_t W25Qxx_SectorErase(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode, uint32_t SectorAddress)
{
    int32_t ret = W25Qxx_OK;
    OSPI_RegularCmdTypeDef s_command = {0};
    
    W25Qxx_WriteEnable(Ctx,Mode);
    
    /* Initialize the read ID command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_SectorErase;

    s_command.AddressMode        = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_ADDRESS_1_LINE : HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = SectorAddress;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DummyCycles        = 0;

    s_command.DataMode           = HAL_OSPI_DATA_NONE;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        ret =  W25Qxx_ERROR;
    }
    #ifdef NOTICK
    else
    {
        W25QXX_Wait_Busy(Ctx,Mode);
    }
    #else
    else if(W25Qxx_AutoPolling(Ctx,Mode,W25X_ReadStatusReg1,0,W25X_SR_WIP,10) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    #endif
    return ret;
}

static int32_t W25Qxx_BlockErase(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode, uint32_t BlockAddress)
{
    int32_t ret = W25Qxx_OK;
    OSPI_RegularCmdTypeDef s_command = {0};

    W25Qxx_WriteEnable(Ctx,Mode);
    
    /* Initialize the command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_BlockErase;

    s_command.AddressMode        = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_ADDRESS_1_LINE : HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = BlockAddress;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DummyCycles        = 0;

    s_command.DataMode           = HAL_OSPI_DATA_NONE;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        ret =  W25Qxx_ERROR;
    }
    #ifdef NOTICK
    else
    {
        W25QXX_Wait_Busy(Ctx,Mode);
    }
    #else
    else if(W25Qxx_AutoPolling(Ctx,Mode,W25X_ReadStatusReg1,0,W25X_SR_WIP,10) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    #endif
    return ret;
}

static int32_t W25Qxx_ChipErase(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    int32_t ret = W25Qxx_OK;
    OSPI_RegularCmdTypeDef s_command = {0};

    W25Qxx_WriteEnable(Ctx,Mode);
    
    /* Initialize the command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = W25X_ChipErase;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_NONE;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DummyCycles        = 0;

    s_command.DataMode           = HAL_OSPI_DATA_NONE;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        ret =  W25Qxx_ERROR;
    }
    #ifdef NOTICK
    else
    {
        W25QXX_Wait_Busy(Ctx,Mode);
    }
    #else
    else if(W25Qxx_AutoPolling(Ctx,Mode,W25X_ReadStatusReg1,0,W25X_SR_WIP,10) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    #endif
    return ret;
}

static int32_t W25Qxx_PageProgram(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode, uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    OSPI_RegularCmdTypeDef s_command = {0};

    W25Qxx_WriteEnable(Ctx,Mode);
    
    /* Initialize command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_COMMON_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = (Mode == W25Qxx_SPI_MODE) ? W25X_QUAD_INPUT_PAGE_PROG_CMD : W25X_PageProgram;

    s_command.AddressMode        = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_ADDRESS_1_LINE : HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    s_command.Address            = WriteAddr;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    
    s_command.DummyCycles        = 0;

    s_command.DataMode           = HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;
    s_command.NbData             = Size;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Reception of the data */
    if (HAL_OSPI_Transmit(Ctx, pData, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    #ifdef NOTICK
    W25QXX_Wait_Busy(Ctx,Mode);
    #else
    if(W25Qxx_AutoPolling(Ctx,Mode,W25X_ReadStatusReg1,0,W25X_SR_WIP,10) != W25Qxx_OK)
    {
        return W25Qxx_ERROR;
    }
    #endif
    return W25Qxx_OK;
}

static int32_t W25Qxx_EnableSTRMemoryMappedMode(OSPI_HandleTypeDef *Ctx,W25Qxx_Interface_t Mode)
{
    OSPI_RegularCmdTypeDef s_command = {0};
    OSPI_MemoryMappedTypeDef s_mem_mapped_cfg = {0};
    
    /* Initialize the read command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_READ_CFG;
    s_command.FlashId            = HAL_OSPI_FLASH_ID_1;

    s_command.InstructionMode    = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_INSTRUCTION_1_LINE : HAL_OSPI_INSTRUCTION_4_LINES;
    s_command.InstructionDtrMode = HAL_OSPI_INSTRUCTION_DTR_DISABLE;
    s_command.InstructionSize    = HAL_OSPI_INSTRUCTION_8_BITS;
    s_command.Instruction        = (Mode == W25Qxx_SPI_MODE) ? W25X_QUAD_INOUT_FAST_READ_CMD : W25X_FastReadData;

    s_command.AddressMode        = HAL_OSPI_ADDRESS_4_LINES;
    s_command.AddressDtrMode     = HAL_OSPI_ADDRESS_DTR_DISABLE;
    s_command.AddressSize        = HAL_OSPI_ADDRESS_24_BITS;
    
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_4_LINES;
    s_command.AlternateBytesDtrMode = HAL_OSPI_ALTERNATE_BYTES_DTR_DISABLE;
    s_command.AlternateBytesSize = HAL_OSPI_ALTERNATE_BYTES_8_BITS;
    s_command.AlternateBytes     = 0xFF;
    
    s_command.DummyCycles        = (Mode == W25Qxx_SPI_MODE) ? W25X_DUMMY_CYCLES_QUAD_INOUT_FAST_READ : W25X_DUMMY_CYCLES_FAST_READ_QPI_MDOE;

    s_command.DataMode           = HAL_OSPI_DATA_4_LINES;
    s_command.DataDtrMode        = HAL_OSPI_DATA_DTR_DISABLE;

    s_command.DQSMode            = HAL_OSPI_DQS_DISABLE;
    s_command.SIOOMode           = HAL_OSPI_SIOO_INST_EVERY_CMD;

    /* Send the command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    /* Initialize the program command */
    s_command.OperationType      = HAL_OSPI_OPTYPE_WRITE_CFG;
    s_command.Instruction        = (Mode == W25Qxx_SPI_MODE) ? W25X_QUAD_INPUT_PAGE_PROG_CMD : W25X_PageProgram;
    s_command.AddressMode        = (Mode == W25Qxx_SPI_MODE) ? HAL_OSPI_ADDRESS_1_LINE : HAL_OSPI_ADDRESS_4_LINES;
    s_command.AlternateBytesMode = HAL_OSPI_ALTERNATE_BYTES_NONE;
    s_command.DummyCycles        = 0;
    
      /* Send the write command */
    if (HAL_OSPI_Command(Ctx, &s_command, HAL_OSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
      /* Configure the memory mapped mode */
    s_mem_mapped_cfg.TimeOutActivation = HAL_OSPI_TIMEOUT_COUNTER_DISABLE;

    if (HAL_OSPI_MemoryMapped(Ctx, &s_mem_mapped_cfg) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    
    return W25Qxx_OK;
}

/**
  * @brief  This function reset the OSPI memory.
  * @param  Instance  OSPI instance
  * @retval BSP status
  */
int32_t OSPI_NOR_ResetMemory (void)
{
    W25Qxx_ResetEnable(OSPI_Infer,W25Qxx_QPI_MODE);

    W25Qxx_ResetDevice(OSPI_Infer,W25Qxx_QPI_MODE);

    W25Qxx_ResetEnable(OSPI_Infer,W25Qxx_SPI_MODE);

    W25Qxx_ResetDevice(OSPI_Infer,W25Qxx_SPI_MODE);

    return W25Qxx_OK;
}

int32_t OSPI_NOR_ReadID(uint32_t *ID)
{
    uint8_t id[3];
    if(W25Qxx_ReadJEDECID(OSPI_Infer,OSPI_NOR_Mode,id) != W25Qxx_OK)
    {
        return W25Qxx_ERROR;
    }
    else
    {
        *ID = (id[0] << 16) + (id[1] << 8) + id[2];
        return W25Qxx_OK;
    }
}

int32_t OSPI_NOR_ReadAllRegister(uint8_t *data)
{
    int32_t ret = W25Qxx_OK;
    if(W25Qxx_ReadSR(OSPI_Infer,OSPI_NOR_Mode,W25X_ReadStatusReg1,&data[0]) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    else if(W25Qxx_ReadSR(OSPI_Infer,OSPI_NOR_Mode,W25X_ReadStatusReg2,&data[1]) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    else if(W25Qxx_ReadSR(OSPI_Infer,OSPI_NOR_Mode,W25X_ReadStatusReg3,&data[2]) != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    return ret;
}

int32_t OSPI_NOR_WriteEnable(void)
{
    return W25Qxx_WriteEnable(OSPI_Infer,OSPI_NOR_Mode);
}

int32_t OSPI_NOR_QuadEnable(void)
{
    return W25Qxx_QuadEnable(OSPI_Infer,OSPI_NOR_Mode);
}

int32_t OSPI_EnterQPIMode(void)
{
    
    return W25Qxx_OK;
}

int32_t OSPI_NOR_ReadSTR(uint8_t *pData, uint32_t ReadAddr, uint32_t Size)
{
    return W25Qxx_ReadSTR(OSPI_Infer,OSPI_NOR_Mode,pData,ReadAddr,Size);
}

int32_t OSPI_NOR_SectorErase(uint32_t SectorAddress)
{
    return W25Qxx_SectorErase(OSPI_Infer,OSPI_NOR_Mode,SectorAddress);
}

int32_t OSPI_NOR_BlockErase(uint32_t BlockAddress)
{
    return W25Qxx_BlockErase(OSPI_Infer, OSPI_NOR_Mode, BlockAddress);
}

int32_t OSPI_NOR_ChipErase(void)
{
    return W25Qxx_ChipErase(OSPI_Infer, OSPI_NOR_Mode);
}

int32_t OSPI_NOR_PageProgram(uint8_t *pData, uint32_t WriteAddr, uint32_t Size)
{
    return W25Qxx_PageProgram(OSPI_Infer, OSPI_NOR_Mode, pData, WriteAddr, Size);
}

//无检验写SPI FLASH
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(最大32bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
int32_t OSPI_NOR_WriteNoCheck(uint8_t *pBuffer,uint32_t WriteAddr,uint32_t NumByteToWrite)
{
	uint16_t pageremain;	   
	pageremain = 256 - WriteAddr % 256; //单页剩余的字节数
	if (NumByteToWrite <= pageremain)
	{
		pageremain = NumByteToWrite; //不大于256个字节
	}
	while(1)
	{
        if(OSPI_NOR_PageProgram(pBuffer, WriteAddr, pageremain) != W25Qxx_OK)
        {
            return W25Qxx_ERROR;
        }
        if (NumByteToWrite == pageremain)
		{
			break; //写入结束了
		}
	 	else //NumByteToWrite>pageremain
		{
			pBuffer += pageremain;
			WriteAddr += pageremain;

			NumByteToWrite -= pageremain; //减去已经写入了的字节数
			if (NumByteToWrite > 256)
				pageremain = 256; //一次可以写入256个字节
			else
				pageremain = NumByteToWrite; //不够256个字节了
		}
	}
    return W25Qxx_OK;
}

int32_t OSPI_NOR_EnableSTRMemoryMappedMode(void)
{
    return W25Qxx_EnableSTRMemoryMappedMode(OSPI_Infer,OSPI_NOR_Mode);
}

int32_t OSPI_NOR_DisableSTRMemoryMappedMode(void)
{
    if(HAL_OSPI_Abort(OSPI_Infer) != HAL_OK)
    {
        return W25Qxx_ERROR;
    }
    else
    {
        return W25Qxx_OK;
    }
}


uint32_t OSPI_NOR_ID;
uint8_t OSPI_NOR_Register[3];

int32_t OSPI_NOR_Init(void)
{
    int32_t ret = W25Qxx_OK;
    
    #ifdef NOTICK
    for(uint32_t count = 0;count<2000;count++) // 1ms 等待flash稳定
        __nop();
    #else
    HAL_Delay(5);
    #endif
    
    if(OSPI_NOR_ResetMemory() != W25Qxx_OK)
    {
        ret = W25Qxx_ERROR;
    }
    else
    {
        #ifdef NOTICK
        for(uint32_t count = 0;count<2000;count++) // 1ms 等待flash稳定
            __nop();
        #else
        HAL_Delay(5);
        #endif
        
        if(OSPI_NOR_ReadID(&OSPI_NOR_ID) != W25Qxx_OK)
        {
            ret = W25Qxx_ERROR;
        }
        else if(OSPI_NOR_ReadAllRegister(OSPI_NOR_Register) != W25Qxx_OK)
        {
            ret = W25Qxx_ERROR;
        }
        else if(OSPI_NOR_QuadEnable() != W25Qxx_OK)
        {
            ret = W25Qxx_ERROR;
        }
        //OSPI_NOR_EnableSTRMemoryMappedMode();
    }
    
    return ret;
}

#if 1
uint8_t OSPI_NOR_ReadData[4096];
uint8_t OSPI_NOR_WriteData[4096];
uint32_t errorcount=0;
int32_t tt;
void OSPI_NOR_Test(void)
{
//    tt += OSPI_NOR_ResetMemory();
//    
//    HAL_Delay(5);
//    
//    tt += OSPI_NOR_ReadID(&OSPI_NOR_ID);
//    
//    tt += OSPI_NOR_WriteEnable();
//    
//    tt += OSPI_NOR_QuadEnable();
    
    tt += OSPI_NOR_Init();

    tt += OSPI_NOR_SectorErase(0);
    
    tt += OSPI_NOR_ReadAllRegister(OSPI_NOR_Register);
    tt += OSPI_NOR_ReadSTR(OSPI_NOR_ReadData,0,sizeof(OSPI_NOR_ReadData));
    //HAL_Delay(2000);
    
    for(uint32_t i=0;i<sizeof(OSPI_NOR_WriteData);i++)
        OSPI_NOR_WriteData[i] = i;
    
    tt += OSPI_NOR_WriteNoCheck(OSPI_NOR_WriteData,0,sizeof(OSPI_NOR_WriteData));
    tt += OSPI_NOR_ReadAllRegister(OSPI_NOR_Register);
//     //HAL_Delay(2000);
//    
    tt += OSPI_NOR_ReadSTR(OSPI_NOR_ReadData,0,sizeof(OSPI_NOR_ReadData));
    for(uint32_t i=0;i<sizeof(OSPI_NOR_WriteData);i++)
    {
        if(OSPI_NOR_WriteData[i] != OSPI_NOR_ReadData[i])
            errorcount++;
    }
//    tt += OSPI_NOR_EnableSTRMemoryMappedMode();
}

#endif

