unsigned short CRC16(unsigned char *pcBlock, unsigned short len)
{
    unsigned short crc = 0xFFFF;
    unsigned char i;

    while (len--)
    {
        crc ^= *pcBlock++ << 8;

        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

bool check_file_crc(File file)
{
	String fullfile,data,crc;
	int index;
	
	fullfile=file.readString();
	file.seek(0,SeekSet);
	index=fullfile.indexOf(String(CONFIG_PREFIX_CRC));
	if(index==-1)
	{
DBG_OUTPUT_PORT.printf("\tFile %s: CRC-record in file not found.\n",file.name());
		return false;
	}

	crc=fullfile.substring(index,fullfile.length());
	data=fullfile.substring(0,index);
	index=crc.indexOf(CONFIG_DIVIDER_CHAR);
	crc=crc.substring(index+1);

	if(CRC16((unsigned char *)(data.c_str()),data.length())==strtol(crc.c_str(),NULL,16))
	{
DBG_OUTPUT_PORT.printf("\tFile %s: CRC is OK\n",file.name());
		return true;
	}
	else
	{
DBG_OUTPUT_PORT.printf("\tDATA=[%s]\n",data.c_str());
DBG_OUTPUT_PORT.printf("\tCRC16=0x%X\n\tFile : 0x%X\n",CRC16((unsigned char *)(data.c_str()),data.length()),strtol(crc.c_str(),NULL,16));
DBG_OUTPUT_PORT.printf("\tCRC is FAIL\n");
		return false;
	}
}
