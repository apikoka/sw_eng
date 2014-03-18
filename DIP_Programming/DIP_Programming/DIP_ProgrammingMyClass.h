#pragma once
#pragma warning (disable:4996 )
class CDIP_ProgrammingMyClass
{
public:
	CDIP_ProgrammingMyClass(void);
	~CDIP_ProgrammingMyClass(void);



	BITMAPINFOHEADER m_BMPHeader;
	UCHAR**			 m_pcBMP;
	UCHAR**			 m_pcImgBuf;
	UINT			 m_uiHeight;
	UINT			 m_uiWidth;


	FILE*           m_fp;
	UINT32          m_uiFileTotalSize;
};

