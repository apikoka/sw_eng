#include "stdafx.h"
#include "DIP_ProgrammingMyClass.h"


CDIP_ProgrammingMyClass::CDIP_ProgrammingMyClass(void)
	:m_pcBMP	(NULL)
	,m_pcImgBuf (NULL)
	,m_uiHeight (0)
	,m_uiWidth  (0)
{
	m_BMPHeader.biSize			= sizeof(BITMAPINFOHEADER);
	m_BMPHeader.biPlanes		= 1;
	m_BMPHeader.biBitCount		= 24;
	m_BMPHeader.biCompression	= BI_RGB;
	m_BMPHeader.biSizeImage		= 0;
	m_BMPHeader.biXPelsPerMeter	= 0;
	m_BMPHeader.biYPelsPerMeter	= 0;
	m_BMPHeader.biClrUsed		= 0;
	m_BMPHeader.biClrImportant	= 0;
}


CDIP_ProgrammingMyClass::~CDIP_ProgrammingMyClass(void)
{
}
