#pragma once

class BarbaVirtualIpManager
{
public:
	BarbaVirtualIpManager(IpRange* virtualIpRange)
	{
		memset(VirtualIps, 0, sizeof(VirtualIps));
		VirtualIpRange = virtualIpRange;
	}
	
	DWORD GetNewIp()
	{
		int maxIp = VirtualIpRange->EndIp - VirtualIpRange->StartIp + 1;
		for (int i=0; i<_countof(VirtualIps) && i<maxIp; i++)
		{
			if ( !VirtualIps[i] )
			{
				VirtualIps[i] = true;
				return VirtualIpRange->StartIp + i;
			}
		}
		return 0;
	}

	void ReleaseIp(DWORD Ip)
	{
		int index = VirtualIpRange->EndIp - Ip;
		if (index>0)
			VirtualIps[index] = false;
	}

private:
	bool VirtualIps[BARBA_MAX_VIRTUALIP];
	IpRange* VirtualIpRange;
};
