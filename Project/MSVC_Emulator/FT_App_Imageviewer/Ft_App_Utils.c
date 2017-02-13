#include "FT_Platform.h"
#ifdef FT900_PLATFORM
#include "ff.h"
#endif
#include "FT_App_Utils.h"

ft_uint32_t Ft_CmdBuffer_Index;
ft_uint32_t Ft_DlBuffer_Index;

#ifdef FT900_PLATFORM
FATFS FatFs;
FIL 			 CurFile;
FRESULT          fResult;
SDHOST_STATUS    SDHostStatus;
#endif

#ifdef BUFFER_OPTIMIZATION
ft_uint8_t  Ft_DlBuffer[FT_DL_SIZE];
ft_uint8_t  Ft_CmdBuffer[FT_CMD_FIFO_SIZE];
#endif

ft_void_t Ft_App_WrCoCmd_Buffer(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t cmd)
{
#ifdef  BUFFER_OPTIMIZATION
	/* Copy the command instruction into buffer */
	ft_uint32_t *pBuffcmd;
	pBuffcmd = (ft_uint32_t*)&Ft_CmdBuffer[Ft_CmdBuffer_Index];
	*pBuffcmd = cmd;
#endif
#ifdef ARDUINO_PLATFORM
	Ft_Gpu_Hal_WrCmd32(phost, cmd);
#endif
#ifdef FT900_PLATFORM
	Ft_Gpu_Hal_WrCmd32(phost, cmd);
#endif
	/* Increment the command index */
	Ft_CmdBuffer_Index += FT_CMD_SIZE;
}

ft_void_t Ft_App_WrDlCmd_Buffer(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t cmd)
{
#ifdef BUFFER_OPTIMIZATION  
	/* Copy the command instruction into buffer */
	ft_uint32_t *pBuffcmd;
	pBuffcmd = (ft_uint32_t*)&Ft_DlBuffer[Ft_DlBuffer_Index];
	*pBuffcmd = cmd;
#endif

#ifdef ARDUINO_PLATFORM
	Ft_Gpu_Hal_Wr32(phost, (RAM_DL + Ft_DlBuffer_Index), cmd);
#endif
#ifdef FT900_PLATFORM
	Ft_Gpu_Hal_Wr32(phost, (RAM_DL + Ft_DlBuffer_Index), cmd);
#endif
	/* Increment the command index */
	Ft_DlBuffer_Index += FT_CMD_SIZE;
}

ft_void_t Ft_App_WrCoStr_Buffer(Ft_Gpu_Hal_Context_t *phost, const ft_char8_t *s)
{
#ifdef  BUFFER_OPTIMIZATION  
	ft_uint16_t length = strlen(s) + 1;//last for the null termination;

    strcpy(&Ft_CmdBuffer[Ft_CmdBuffer_Index], s);
	/* increment the length and align it by 4 bytes */
	Ft_CmdBuffer_Index += ((length + 3) & ~3);
#endif  
}

ft_void_t Ft_App_Flush_DL_Buffer(Ft_Gpu_Hal_Context_t *phost)
{
#ifdef  BUFFER_OPTIMIZATION    
	if (Ft_DlBuffer_Index> 0)
		Ft_Gpu_Hal_WrMem(phost, RAM_DL, Ft_DlBuffer, Ft_DlBuffer_Index);
#endif     
	Ft_DlBuffer_Index = 0;

}

ft_void_t Ft_App_Flush_Co_Buffer(Ft_Gpu_Hal_Context_t *phost)
{
#ifdef  BUFFER_OPTIMIZATION    
	if (Ft_CmdBuffer_Index > 0)
		Ft_Gpu_Hal_WrCmdBuf(phost, Ft_CmdBuffer, Ft_CmdBuffer_Index);
#endif     
	Ft_CmdBuffer_Index = 0;
}

ft_void_t Ft_DisplayCalibrate(Ft_Gpu_Hal_Context_t *phost)
{
	Ft_Gpu_CoCmd_Dlstart(phost);
	Ft_App_WrCoCmd_Buffer(phost, CLEAR(1, 1, 1));
	Ft_App_WrCoCmd_Buffer(phost, COLOR_RGB(255, 255, 255));
#if defined(DISPLAY_RESOLUTION_WQVGA) || defined(DISPLAY_RESOLUTION_QVGA) || DISPLAY_RESOLUTION_HVGA_PORTRAIT
	Ft_Gpu_CoCmd_Text(phost, FT_DispWidth / 2, FT_DispHeight / 2, 26, OPT_CENTERX | OPT_CENTERY, "Please tap on a dot");
#elif defined(DISPLAY_RESOLUTION_WVGA)
	Ft_Gpu_CoCmd_Text(phost, FT_DispWidth / 2, FT_DispHeight / 2, 30, OPT_CENTERX | OPT_CENTERY, "Please tap on a dot");
#endif
	Ft_Gpu_CoCmd_Calibrate(phost, 0);
	Ft_App_Flush_Co_Buffer(phost);
	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
}

ft_void_t Ft_App_Init(ft_void_t)
{
    Ft_CmdBuffer_Index = 0;
}

ft_void_t Ft_DisplayLogo(Ft_Gpu_Hal_Context_t *phost)
{
    Ft_Gpu_CoCmd_Logo(phost);
    Ft_App_Flush_Co_Buffer(phost);
    Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
}
