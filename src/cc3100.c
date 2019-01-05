#include "main.h"

int cc3100_read() {
	{
		printf("## Device API:\n\n");

		printf("### SL_DEVICE_GENERAL_CONFIGURATION\n");

		SlDateTime_t dateTime = { 0 };
		_u8 configLen = sizeof(SlDateTime_t);
		_u8 configOpt = SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME;
		_i32 retVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &configOpt,
				&configLen, (_u8 *) (&dateTime));
		if (retVal < 0) {
			DEBUG("Failed: sl_DevGet");
			return -1;
		}
		printf("#### SL_DEVICE_GENERAL_CONFIGURATION_DATE_TIME\n");
		printf("Day %d, Month %d, Year %d, %d:%d:%d\n", dateTime.sl_tm_day,
				dateTime.sl_tm_mon, dateTime.sl_tm_year, dateTime.sl_tm_hour,
				dateTime.sl_tm_min, dateTime.sl_tm_sec);

		SlVersionFull ver;
		configLen = sizeof(ver);
		configOpt = SL_DEVICE_GENERAL_VERSION;
		retVal = sl_DevGet(SL_DEVICE_GENERAL_CONFIGURATION, &configOpt,
				&configLen, (_u8 *) (&ver));
		if (retVal < 0) {
			DEBUG("Failed: sl_DevGet");
			return -1;
		}

		printf("#### SL_DEVICE_GENERAL_VERSION: \n");
		printf(
				"CHIP %d\nMAC %d.%d.%d.%d\nPHY %d.%d.%d.%d\nNWP %d.%d.%d.%d\nROM %d\nHOST %d.%d.%d.%d\n",
				ver.ChipFwAndPhyVersion.ChipId,
				ver.ChipFwAndPhyVersion.FwVersion[0],
				ver.ChipFwAndPhyVersion.FwVersion[1],
				ver.ChipFwAndPhyVersion.FwVersion[2],
				ver.ChipFwAndPhyVersion.FwVersion[3],
				ver.ChipFwAndPhyVersion.PhyVersion[0],
				ver.ChipFwAndPhyVersion.PhyVersion[1],
				ver.ChipFwAndPhyVersion.PhyVersion[2],
				ver.ChipFwAndPhyVersion.PhyVersion[3], ver.NwpVersion[0],
				ver.NwpVersion[1], ver.NwpVersion[2], ver.NwpVersion[3],
				ver.RomVersion,
				SL_MAJOR_VERSION_NUM, SL_MINOR_VERSION_NUM, SL_VERSION_NUM,
				SL_SUB_VERSION_NUM);

		printf("### SL_DEVICE_STATUS\n");

		_u32 classDevice;
		configOpt = SL_EVENT_CLASS_DEVICE;
		configLen = sizeof(classDevice);
		retVal = sl_DevGet(SL_DEVICE_STATUS, &configOpt, &configLen,
				(_u8 *) (&classDevice));
		if (retVal < 0) {
			DEBUG("Failed: sl_DevGet");
			return -1;
		}
		printf("#### SL_EVENT_CLASS_DEVICE\n");
		switch (classDevice) {
		case EVENT_DROPPED_DEVICE_ASYNC_GENERAL_ERROR:
			printf("- EVENT_DROPPED_DEVICE_ASYNC_GENERAL_ERROR\n");
			break;
		case STATUS_DEVICE_SMART_CONFIG_ACTIVE:
			printf("- STATUS_DEVICE_SMART_CONFIG_ACTIVE\n");
			break;
		default:
			printf("- UNKNOWN CLASS Device: %u\n", classDevice);
		}

		_u32 statusWlan;
		configOpt = SL_EVENT_CLASS_WLAN;
		configLen = sizeof(statusWlan);
		retVal = sl_DevGet(SL_DEVICE_STATUS, &configOpt, &configLen,
				(_u8 *) (&statusWlan));
		if (retVal < 0) {
			DEBUG("Failed: sl_DevGet");
			return -1;
		}
		printf("#### SL_EVENT_CLASS_WLAN\n");
		switch (statusWlan) {
		case EVENT_DROPPED_WLAN_WLANASYNCONNECTEDRESPONSE:
			printf("- EVENT_DROPPED_WLAN_WLANASYNCONNECTEDRESPONSE\n");
			break;
		case EVENT_DROPPED_WLAN_WLANASYNCDISCONNECTEDRESPONSE:
			printf("- EVENT_DROPPED_WLAN_WLANASYNCDISCONNECTEDRESPONSE\n");
			break;
		case EVENT_DROPPED_WLAN_STA_CONNECTED:
			printf("- EVENT_DROPPED_WLAN_STA_CONNECTED\n");
			break;
		case EVENT_DROPPED_WLAN_STA_DISCONNECTED:
			printf("- EVENT_DROPPED_WLAN_STA_DISCONNECTED\n");
			break;
		case STATUS_WLAN_STA_CONNECTED:
			printf("- STATUS_WLAN_STA_CONNECTED\n");
			break;
		default:
			printf("- Unknown CLASS WLAN: %u\n", statusWlan);
			break;
		}

	}

	{
		printf("\n## Device masked events: \n");
		_u32 maskWlan;
		_i16 retVal = sl_EventMaskGet(SL_EVENT_CLASS_WLAN, &maskWlan);
		if (retVal < 0) {
			DEBUG("Failed: sl_EventMaskGet");
			return -1;
		}

		printf("\n### SL_EVENT_CLASS_WLAN: %08X\n", maskWlan);

		printf("- SL_WLAN_CONNECT_EVENT: %d\n",
				maskWlan & SL_WLAN_CONNECT_EVENT);
		printf("- SL_WLAN_DISCONNECT_EVENT: %d\n",
				maskWlan & SL_WLAN_DISCONNECT_EVENT);
		printf("- SL_WLAN_STA_CONNECTED_EVENT: %d\n",
				maskWlan & SL_WLAN_STA_CONNECTED_EVENT);
		printf("- SL_WLAN_STA_DISCONNECTED_EVENT: %d\n",
				maskWlan & SL_WLAN_STA_DISCONNECTED_EVENT);
		printf("- SL_WLAN_SMART_CONFIG_COMPLETE_EVENT: %d\n",
				maskWlan & SL_WLAN_SMART_CONFIG_COMPLETE_EVENT);
		printf("- SL_WLAN_SMART_CONFIG_STOP_EVENT: %d\n",
				maskWlan & SL_WLAN_SMART_CONFIG_STOP_EVENT);
		printf("- SL_WLAN_P2P_DEV_FOUND_EVENT: %d\n",
				maskWlan & SL_WLAN_P2P_DEV_FOUND_EVENT);
		printf("- SL_WLAN_P2P_NEG_REQ_RECEIVED_EVENT: %d\n",
				maskWlan & SL_WLAN_P2P_NEG_REQ_RECEIVED_EVENT);
		printf("- SL_WLAN_CONNECTION_FAILED_EVENT: %d\n",
				maskWlan & SL_WLAN_CONNECTION_FAILED_EVENT);

		retVal = sl_EventMaskGet(SL_EVENT_CLASS_DEVICE, &maskWlan);
		if (retVal < 0) {
			DEBUG("Failed: sl_EventMaskGet");
			return -1;
		}

		printf("\n### SL_EVENT_CLASS_DEVICE: %08X\n", maskWlan);

		printf("- SL_DEVICE_FATAL_ERROR_EVENT: %d\n",
				maskWlan & SL_DEVICE_FATAL_ERROR_EVENT);
		printf("- SL_DEVICE_ABORT_ERROR_EVENT: %d\n",
				maskWlan & SL_DEVICE_ABORT_ERROR_EVENT);

		retVal = sl_EventMaskGet(SL_EVENT_CLASS_BSD, &maskWlan);
		if (retVal < 0) {
			DEBUG("Failed: sl_EventMaskGet");
			return -1;
		}
		printf("\n### SL_EVENT_CLASS_BSD: %08X\n", maskWlan);

		printf("- SL_SOCKET_TX_FAILED_EVENT: %d\n",
				maskWlan & SL_SOCKET_TX_FAILED_EVENT);
		printf("- SL_SOCKET_ASYNC_EVENT: %d\n",
				maskWlan & SL_SOCKET_ASYNC_EVENT);

		retVal = sl_EventMaskGet(SL_EVENT_CLASS_NETAPP, &maskWlan);
		if (retVal < 0) {
			DEBUG("Failed: sl_EventMaskGet");
			return -1;
		}

		printf("\n### SL_EVENT_CLASS_NETAPP: %08X\n", maskWlan);

		printf("- SL_NETAPP_IPV4_IPACQUIRED_EVENT: %d\n",
				maskWlan & SL_NETAPP_IPV4_IPACQUIRED_EVENT);
		printf("- SL_NETAPP_IPV6_IPACQUIRED_EVENT: %d\n",
				maskWlan & SL_NETAPP_IPV6_IPACQUIRED_EVENT);
		printf("- SL_NETAPP_IP_LEASED_EVENT: %d\n",
				maskWlan & SL_NETAPP_IP_LEASED_EVENT);
		printf("- SL_NETAPP_IP_RELEASED_EVENT: %d\n",
				maskWlan & SL_NETAPP_IP_RELEASED_EVENT);
		printf("- SL_NETAPP_HTTPGETTOKENVALUE_EVENT: %d\n",
				maskWlan & SL_NETAPP_HTTPGETTOKENVALUE_EVENT);
		printf("- SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT: %d\n",
				maskWlan & SL_NETAPP_HTTPPOSTTOKENVALUE_EVENT);

	}

	{
		printf("\n## Wlan configuration (sl_WlanGet): \n");

		slWlanScanParamCommand_t ScanParamConfig;
		_u16 Option = WLAN_GENERAL_PARAM_OPT_SCAN_PARAMS;
		_u16 OptionLen = sizeof(slWlanScanParamCommand_t);
		_i16 retVal = sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID, &Option,
				&OptionLen, (_u8 *) &ScanParamConfig);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf("\n## SL_WLAN_CFG_GENERAL_PARAM_ID\n");
		printf("### WLAN_GENERAL_PARAM_OPT_SCAN_PARAMS\n");
		printf(" - G_Channels_mask: %08X\n", ScanParamConfig.G_Channels_mask);
		printf(" - rssiThershold: %d\n", ScanParamConfig.rssiThershold);

		_i8 country[6];
		Option = WLAN_GENERAL_PARAM_OPT_COUNTRY_CODE;
		OptionLen = sizeof(country);
		retVal = sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID, &Option, &OptionLen,
				country);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf("\n### WLAN_GENERAL_PARAM_OPT_COUNTRY_CODE: %6s\n", country);

		_u32 TXPower = 0;
		Option = WLAN_GENERAL_PARAM_OPT_STA_TX_POWER;
		OptionLen = sizeof(TXPower);
		retVal = sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID, &Option, &OptionLen,
				&TXPower);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf("### WLAN_GENERAL_PARAM_OPT_STA_TX_POWER: %d\n", TXPower);

		Option = WLAN_GENERAL_PARAM_OPT_AP_TX_POWER;
		OptionLen = sizeof(TXPower);
		retVal = sl_WlanGet(SL_WLAN_CFG_GENERAL_PARAM_ID, &Option, &OptionLen,
				&TXPower);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}

		printf("### WLAN_GENERAL_PARAM_OPT_AP_TX_POWER: %d \n", TXPower);
		printf("\t0-15 as dB offset from max power, 0 - MAX power\n");

		printf("\n### SL_WLAN_CFG_AP_ID\n");
		_i8 ssid[32];
		Option = WLAN_AP_OPT_SSID;
		OptionLen = sizeof(ssid);
		retVal = sl_WlanGet(SL_WLAN_CFG_AP_ID, &Option, &OptionLen,
				(_u8*) ssid);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf(" - WLAN_AP_OPT_SSID:%*s\n", OptionLen, ssid);

		_u8 channel;
		Option = WLAN_AP_OPT_CHANNEL;
		OptionLen = sizeof(channel);
		retVal = sl_WlanGet(SL_WLAN_CFG_AP_ID, &Option, &OptionLen, &channel);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf(" - WLAN_AP_OPT_CHANNEL: %u\n", channel);

		_u8 hiddenSsid;
		Option = WLAN_AP_OPT_HIDDEN_SSID;
		OptionLen = sizeof(hiddenSsid);
		retVal = sl_WlanGet(SL_WLAN_CFG_AP_ID, &Option, &OptionLen,
				&hiddenSsid);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf(" - WLAN_AP_OPT_HIDDEN_SSID: %u\n", hiddenSsid);
		printf("\t 0(disabled), 1(length=0), 2(ASCII=0,length=original)\n");

		_u8 securityType;
		Option = WLAN_AP_OPT_SECURITY_TYPE;
		OptionLen = sizeof(securityType);
		retVal = sl_WlanGet(SL_WLAN_CFG_AP_ID, &Option, &OptionLen,
				&securityType);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf(" - WLAN_AP_OPT_SECURITY_TYPE: %u\n", securityType);
		printf("\t0 - OPEN, 1 - WEP, 2 - WPA/WPA2\n");

		_u8 password[64];
		Option = WLAN_AP_OPT_PASSWORD;
		OptionLen = sizeof(password);
		retVal = sl_WlanGet(SL_WLAN_CFG_AP_ID, &Option, &OptionLen, password);
		if (retVal < 0) {
			DEBUG("Failed: sl_WlanGet");
			return -1;
		}
		printf(" - WLAN_AP_OPT_PASSWORD:%*s\n", OptionLen, password);

		printf(
				"\n### SL_WLAN_CFG_P2P_PARAM_ID -> WLAN_P2P_OPT_CHANNEL_N_REGS\n");
		_u8 channel_n_regs[4];
		Option = WLAN_P2P_OPT_CHANNEL_N_REGS;
		OptionLen = sizeof(channel_n_regs);
		sl_WlanGet(SL_WLAN_CFG_P2P_PARAM_ID, &Option, &OptionLen,
				channel_n_regs);
		printf(" - listen channel: %u (either 1/6/11 for 2.4GHz)\n",
				channel_n_regs[0]);
		printf(" - listen regulatory class: %u (81 for 2.4GHz)\n",
				channel_n_regs[1]);
		printf(" - oper channel: %u (either 1/6/11 for 2.4GHz) \n",
				channel_n_regs[2]);
		printf(" - oper regulatory class: %u (81 for 2.4GHz)\n",
				channel_n_regs[3]);
	}

	{
		printf("\n## Wlan Policies (sl_WlanPolicyGet)\n");
		SlWlanGetPmPolicyParams_t PmParamGet;
		_u8 length = sizeof(PmParamGet);
		memset(&PmParamGet, 0, sizeof(PmParamGet));
		_i16 retVal = sl_WlanPolicyGet(SL_POLICY_PM, 0, (_u8 *) &PmParamGet,
				(_u8 *) &length);
		if (retVal < 0) {
			DEBUG("Failed sl_WlanPolicyGet: %d", retVal);
			return -1;
		}
		printf("### SL_POLICY_PM\n");
		printf(" - MaxSleepTimeMs: %u\n", PmParamGet.MaxSleepTimeMs);
		printf(" - Power management policy: ");
		switch (PmParamGet.PmPolicy) {
		case SL_NORMAL_POLICY:
			printf("SL_NORMAL_POLICY\n");
			break;
		case SL_LOW_LATENCY_POLICY:
			printf("SL_LOW_LATENCY_POLICY\n");
			break;
		case SL_LOW_POWER_POLICY:
			printf("SL_LOW_POWER_POLICY\n");
			break;
		case SL_ALWAYS_ON_POLICY:
			printf("SL_ALWAYS_ON_POLICY\n");
			break;
		case SL_LONG_SLEEP_INTERVAL_POLICY:
			printf("SL_LONG_SLEEP_INTERVAL_POLICY\n");
			break;
		default:
			printf("UNKNOWN POLICY\n");
			break;
		}

		SlWlanGetScanPolicyParams_t ScanParamsGet;
		length = sizeof(ScanParamsGet);
		memset(&ScanParamsGet, 0, sizeof(ScanParamsGet));
		retVal = sl_WlanPolicyGet(SL_POLICY_SCAN, 0, (_u8 *) &ScanParamsGet,
				&length);
		if (retVal < 0) {
			DEBUG("Failed sl_WlanPolicyGet: %d", retVal);
			return -1;
		}
		printf("### SL_POLICY_SCAN\n");
		printf(" - ScanInterval: %u\n", ScanParamsGet.ScanInterval);
		printf(" - Scan Policy: %08X\n", ScanParamsGet.ScanPolicy);

// TODO: find more clear example,
//		length = sizeof(policy);
//		sl_WlanPolicyGet(SL_POLICY_P2P, 0, (_u8 *) &policy, &length);
//
//		length = sizeof(policy);
//		sl_WlanPolicyGet(SL_POLICY_CONNECTION, 0, (_u8 *) &policy, &length);
	}

	{
		printf("\n## Rx Filters (sl_WlanRxFilterGet)\n");

		_WlanRxFilterRetrieveEnableStatusCommandResponseBuff_t buf;
		_i16 retVal = sl_WlanRxFilterGet(SL_FILTER_RETRIEVE_ENABLE_STATE, &buf,
				sizeof(buf));
		if (retVal < 0) {
			DEBUG("Failed sl_WlanRxFilterGet: %d", retVal);
			return -1;
		}

		printf("Enabled Filters: \n");
		printf("\t%08X\n", ((_u32*) &buf.FilterIdMask)[0]);
		printf("\t%08X\n", ((_u32*) &buf.FilterIdMask)[1]);
		printf("\t%08X\n", ((_u32*) &buf.FilterIdMask)[2]);
		printf("\t%08X\n", ((_u32*) &buf.FilterIdMask)[3]);
	}

	{
		printf("\nNetwork configuration (sl_NatCfgGet):\n");

		_u8 macAddressVal[SL_MAC_ADDR_LEN];
		_u8 macAddressLen = sizeof(macAddressVal);
		_i32 retVal = sl_NetCfgGet(SL_MAC_ADDRESS_GET, NULL, &macAddressLen,
				(_u8 *) macAddressVal);
		if (retVal < 0) {
			DEBUG("Failed sl_NetCfgGet: %d", retVal);
			return -1;
		}
		printf(" - MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n",
				macAddressVal[0], macAddressVal[1], macAddressVal[2],
				macAddressVal[3], macAddressVal[4], macAddressVal[5]);

		_u8 len = sizeof(SlNetCfgIpV4Args_t);
		_u8 dhcpIsOn = 0;
		SlNetCfgIpV4Args_t ipV4 = { 0 };
		retVal = sl_NetCfgGet(SL_IPV4_STA_P2P_CL_GET_INFO, &dhcpIsOn, &len,
				(_u8 *) &ipV4);
		if (retVal < 0) {
			DEBUG("Failed sl_NetCfgGet: %d", retVal);
			return -1;
		}

		printf("### STATION IPV4 configuration:\n");
		printf("\tDHCP is %s\n", (dhcpIsOn > 0) ? "ON" : "OFF");
		printf("\tIP %d.%d.%d.%d MASK %d.%d.%d.%d\n",
				SL_IPV4_BYTE(ipV4.ipV4, 3), SL_IPV4_BYTE(ipV4.ipV4, 2),
				SL_IPV4_BYTE(ipV4.ipV4, 1), SL_IPV4_BYTE(ipV4.ipV4, 0),
				SL_IPV4_BYTE(ipV4.ipV4Mask, 3), SL_IPV4_BYTE(ipV4.ipV4Mask, 2),
				SL_IPV4_BYTE(ipV4.ipV4Mask, 1), SL_IPV4_BYTE(ipV4.ipV4Mask, 0));
		printf("\tGW %d.%d.%d.%d \n", SL_IPV4_BYTE(ipV4.ipV4Gateway, 3),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 2),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 1),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 0));
		printf("\tDNS %d.%d.%d.%d\n", SL_IPV4_BYTE(ipV4.ipV4DnsServer, 3),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 2),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 1),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 0));

		len = sizeof(SlNetCfgIpV4Args_t);
		dhcpIsOn = 0; // this flag is meaningless on AP/P2P go.
		memset(&ipV4, 0, sizeof(ipV4));
		retVal = sl_NetCfgGet(SL_IPV4_AP_P2P_GO_GET_INFO, &dhcpIsOn, &len,
				(_u8 *) &ipV4);
		if (retVal < 0) {
			DEBUG("Failed sl_NetCfgGet: %d", retVal);
			return -1;
		}
		printf("### AP IPV4 configuration:\n");
		printf("\tIP %d.%d.%d.%d MASK %d.%d.%d.%d\n",
				SL_IPV4_BYTE(ipV4.ipV4, 3), SL_IPV4_BYTE(ipV4.ipV4, 2),
				SL_IPV4_BYTE(ipV4.ipV4, 1), SL_IPV4_BYTE(ipV4.ipV4, 0),
				SL_IPV4_BYTE(ipV4.ipV4Mask, 3), SL_IPV4_BYTE(ipV4.ipV4Mask, 2),
				SL_IPV4_BYTE(ipV4.ipV4Mask, 1), SL_IPV4_BYTE(ipV4.ipV4Mask, 0));
		printf("\tGW %d.%d.%d.%d\n", SL_IPV4_BYTE(ipV4.ipV4Gateway, 3),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 2),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 1),
				SL_IPV4_BYTE(ipV4.ipV4Gateway, 0));
		printf("\tDNS %d.%d.%d.%d\n", SL_IPV4_BYTE(ipV4.ipV4DnsServer, 3),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 2),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 1),
				SL_IPV4_BYTE(ipV4.ipV4DnsServer, 0));

		// TODO:
//		Get DHCP client inforamtion, when DhcpState is SL_NETCFG_DHCP_CLIENT_BOUND,  SL_NETCFG_DHCP_CLIENT_RENEW or SL_NETCFG_DHCP_CLIENT_REBIND, dhcp inforamtion is not zeroed
//		_u8 ConfigOpt = 0, ConfigLen = sizeof(SlNetCfgIpV4DhcpClientArgs_t);
//		_i32 Status;
//		SlNetCfgIpV4DhcpClientArgs_t Dhcp;
//		Status = sl_NetCfgGet(SL_IPV4_DHCP_CLIENT, &ConfigOpt, &ConfigLen,
//				(_u8 *) &Dhcp);
//		if (Status) {
//			// error
//		}

//		Get DNS max retries and secondary DNS address (DHCP and static configuration)
//		_u8 pConfigLen = sizeof(SlNetCfgIpV4DnsClientArgs_t);
//		SlNetCfgIpV4DnsClientArgs_t DnsOpt;
//		Status = sl_NetCfgGet(SL_IPV4_DNS_CLIENT, &ConfigOpt, &pConfigLen,
//				&DnsOpt);
//		if (Status) {
//			// error
//		}

//		SL_IPV4_STA_P2P_CL_DHCP_ENABLE        = 4,
//		SL_IPV4_STA_P2P_CL_STATIC_ENABLE      = 5,
//		SL_IPV4_AP_P2P_GO_STATIC_ENABLE       = 7,
//		SL_SET_HOST_RX_AGGR                   = 8,
//		SL_IPV4_ARP_FLUSH                     = 11,
	}

	return 0;
}

int cc3100_write() {
	DEBUG("Not implemented");
	return -1;
}
