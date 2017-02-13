#ifndef _FT_APP_UTILS_H_
#define _FT_APP_UTILS_H_

#include "FT_Platform.h"

#if !defined(DISPLAY_RESOLUTION_QVGA) && !defined(DISPLAY_RESOLUTION_WVGA) && !defined(DISPLAY_RESOLUTION_HVGA_PORTRAIT)
/* Global variables for display resolution to support various display panels */
/* Default is WQVGA - 480x272 */
#define FT_DispWidth	480
#define FT_DispHeight	272
#define FT_DispHCycle	548
#define FT_DispHOffset	43
#define FT_DispHSync0	0
#define FT_DispHSync1	41
#define FT_DispVCycle	292
#define FT_DispVOffset	12
#define FT_DispVSync0	0
#define FT_DispVSync1	10
#define FT_DispPCLK     5
#define FT_DispSwizzle	0
#define FT_DispPCLKPol	1
#define FT_DispCSpread	1
#define FT_DispDither   1
/* Configuration of LCD display */
#elif defined(DISPLAY_RESOLUTION_QVGA)
/* Values specific to QVGA LCD display */
#define FT_DispWidth    320
#define FT_DispHeight   240
#define FT_DispHCycle   408
#define FT_DispHOffset  70
#define FT_DispHSync0   0
#define FT_DispHSync1   10
#define FT_DispVCycle   263
#define FT_DispVOffset  13
#define FT_DispVSync0   0
#define FT_DispVSync1   2
#define FT_DispPCLK     8
#define FT_DispSwizzle  2
#define FT_DispPCLKPol  0
#define FT_DispCSpread  1
#define FT_DispDither   1
#elif defined(DISPLAY_RESOLUTION_WVGA)
/* Values specific to QVGA LCD display */
#define FT_DispWidth    800
#define FT_DispHeight   480
#define FT_DispHCycle   928
#define FT_DispHOffset  88
#define FT_DispHSync0   0
#define FT_DispHSync1   48
#define FT_DispVCycle   525
#define FT_DispVOffset  32
#define FT_DispVSync0   0
#define FT_DispVSync1   3
#define FT_DispPCLK     2
#define FT_DispSwizzle  0
#define FT_DispPCLKPol  1
#define FT_DispCSpread  0
#define FT_DispDither   1
#elif defined(DISPLAY_RESOLUTION_HVGA_PORTRAIT)
/* Values specific to HVGA LCD display */

#define FT_DispWidth    320
#define FT_DispHeight   480
#define FT_DispHCycle   400
#define FT_DispHOffset  40
#define FT_DispHSync0   0
#define FT_DispHSync1   10
#define FT_DispVCycle   500
#define FT_DispVOffset  10
#define FT_DispVSync0   0
#define FT_DispVSync1   5
#define FT_DispPCLK     4
#define FT_DispSwizzle  2
#define FT_DispPCLKPol  1
#define FT_DispCSpread  1
#define FT_DispDither   1
#else
#error "Unknown display"
#endif

#ifdef ME810A_HV35R
#define FT_DispPCLK     5
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Application initialization
ft_void_t Ft_App_Init(ft_void_t);
// Application write to FT8XX command buffer with context saving in @phost
ft_void_t Ft_App_WrCoCmd_Buffer(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t cmd);
// Application write to FT8XX display list buffer with context saving in @phost
ft_void_t Ft_App_WrDlCmd_Buffer(Ft_Gpu_Hal_Context_t *phost, ft_uint32_t cmd);
// Application write to FT8XX display list buffer with context saving in @phost
ft_void_t Ft_App_WrCoStr_Buffer(Ft_Gpu_Hal_Context_t *phost, const ft_char8_t *s);
// Flush FT8XX command buffer
ft_void_t Ft_App_Flush_Co_Buffer(Ft_Gpu_Hal_Context_t *phost);
// Flush FT8XX display list buffer
ft_void_t Ft_App_Flush_DL_Buffer(Ft_Gpu_Hal_Context_t *phost);
// Invoke calibration functionality on FT8XX
ft_void_t Ft_DisplayCalibrate(Ft_Gpu_Hal_Context_t *phost);
// Show FTDI logo on the screen
ft_void_t Ft_DisplayLogo(Ft_Gpu_Hal_Context_t *phost);

void setup(void);
void loop(void);
#ifdef __cplusplus
}
#endif

#endif // _FT_APP_UTILS_H_
