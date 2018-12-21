#define __MAIN_C__
#include "main.h"

int main(int argc, char **argv)
{
    RUN(sl_Start(0, 0, 0));

    printf("Device information: \n");
    _u8 pConfigOpt;
    _u8 pConfigLen;
    SlVersionFull ver;
    pConfigLen = sizeof(ver);
    pConfigOpt = SL_DEVICE_GENERAL_VERSION;
    sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION,&pConfigOpt,&pConfigLen,(_u8 *)(&ver));
    printf("CHIP %d\nMAC 31.%d.%d.%d.%d\nPHY %d.%d.%d.%d\nNWP %d.%d.%d.%d\nROM %d\nHOST %d.%d.%d.%d\n",
            ver.ChipFwAndPhyVersion.ChipId,
            ver.ChipFwAndPhyVersion.FwVersion[0],ver.ChipFwAndPhyVersion.FwVersion[1],
            ver.ChipFwAndPhyVersion.FwVersion[2],ver.ChipFwAndPhyVersion.FwVersion[3],
            ver.ChipFwAndPhyVersion.PhyVersion[0],ver.ChipFwAndPhyVersion.PhyVersion[1],
            ver.ChipFwAndPhyVersion.PhyVersion[2],ver.ChipFwAndPhyVersion.PhyVersion[3],
            ver.NwpVersion[0],ver.NwpVersion[1],ver.NwpVersion[2],ver.NwpVersion[3],
            ver.RomVersion,
            SL_MAJOR_VERSION_NUM,SL_MINOR_VERSION_NUM,SL_VERSION_NUM,SL_SUB_VERSION_NUM);


    {
		slWlanScanParamCommand_t ScanParamConfig;
		_u16 Option = WLAN_GENERAL_PARAM_OPT_SCAN_PARAMS;
		_u16 OptionLen = sizeof(slWlanScanParamCommand_t);
		sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID ,&Option,&OptionLen,(_u8 *)&ScanParamConfig);
		printf("\nSCAN_APRAMS:\nG_Channels_mask: %u\nrssiThershold: %d \n",
				ScanParamConfig.G_Channels_mask, ScanParamConfig.rssiThershold);
    }
    {
    	_i8 TXPower = 0;
		_u16 Option = WLAN_GENERAL_PARAM_OPT_AP_TX_POWER;
		_u16 OptionLen = sizeof(_i8);
		sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID ,&Option,&OptionLen,(_u8 *)&TXPower);
		printf("Access Point TX power: %d (0-15, as dB offset from max power (0 will set MAX power) )\n", TXPower);
    }
    {
		_i8 TXPower = 0;
		_u16 Option = WLAN_GENERAL_PARAM_OPT_STA_TX_POWER;
		_u16 OptionLen = sizeof(_i8);
		sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID ,&Option,&OptionLen,(_u8 *)&TXPower);
		printf("Station TX power: %d (0-15, as dB offset from max power (0 will set MAX power))\n", TXPower);
    }
    {
		_i8 country[3];
		_u16 len = 3;
		_u16  config_opt = WLAN_GENERAL_PARAM_OPT_COUNTRY_CODE;
		sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID, &config_opt, &len, (_u8* )country);
		printf("Country code: %c%c%c%c\n", country[0], country[1], country[2], country[3]);
    }

    {
    	printf("\nPrint PHY socket options:\n");
    	_i16 channel = 7;
    	_i16 soc = sl_Socket(SL_AF_RF, SL_SOCK_DGRAM, channel);

    	_u32 rate = 5; // see wlan.h RateIndex_e for values]
    	sl_SetSockOpt(soc, SL_SOL_PHY_OPT, SL_SO_PHY_RATE, &rate, sizeof(rate));

    	rate = 0;
    	SlSocklen_t optlen = sizeof(rate);
    	sl_GetSockOpt(soc, SL_SOL_PHY_OPT, SL_SO_PHY_RATE, &rate, &optlen);
    	printf("Rate %u\n", rate);

    	_u32 txpower = 7; // valid range is 1-15
    	sl_SetSockOpt(soc, SL_SOL_PHY_OPT, SL_SO_PHY_TX_POWER, &txpower, sizeof(txpower));

    	txpower = 1; // valid range is 1-15
        optlen = sizeof(txpower);
    	sl_GetSockOpt(soc, SL_SOL_PHY_OPT, SL_SO_PHY_TX_POWER, &txpower,  &optlen);
    	printf("TX power %u (0-15), 0 - MAX, 15 - MIN\n", txpower);

    	_u32 numframes;
    	optlen = sizeof(numframes);
    	sl_GetSockOpt(soc, SL_SOL_PHY_OPT, SL_SO_PHY_NUM_FRAMES_TO_TX, &numframes, &optlen);
    	printf("Number of frames: %u\n", numframes);


//    	_u32 newChannel = 6; // range is 1-13
//    	sl_SetSockOpt(soc, SL_SOL_SOCKET, SL_SO_CHANGE_CHANNEL, &newChannel, sizeof(newChannel));

    	_u32 newChannel = 0;
    	optlen = sizeof(newChannel);
    	sl_GetSockOpt(soc, SL_SOL_SOCKET, SL_SO_CHANGE_CHANNEL, &newChannel, &optlen);
    	printf("Channel: %u\n", newChannel);

    	sl_Close(soc);
    }
//    RUN(sl_Stop(SL_STOP_TIMEOUT));
    return 0;
}
