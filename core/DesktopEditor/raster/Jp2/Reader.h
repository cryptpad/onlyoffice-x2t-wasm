#pragma once

#include "../../common/File.h"

namespace Jpeg2000
{
	//-------------------------------------------------------------------------------------------------------------------------------
	// Byte input-output (Stream IO)
	//-------------------------------------------------------------------------------------------------------------------------------

#define STREAM_READ	 0x0001 // The stream is open for reading
#define STREAM_WRITE 0x0002 // The stream is open for writing

	typedef struct TByteIO
	{
		int            nMode;   // Read or Write ( STREAM_READ or OPJ_STREAM_WRITE )
		unsigned char *pBuffer; // Pointer to the beginning of the buffer
		int            nLength; // Buffer size in bytes

		unsigned char *pStart;  // Pointer to the beginning of the stream
		unsigned char *pEnd;    // Pointer to end of stream
		unsigned char *pCurPos; // Pointer to the current position in the stream
	} ByteIO;


	class CReader
	{
	public:
		virtual ~CReader(void){}

		virtual bool         Open(void* sStream, int nSizeStream){ return false; }
		virtual void         Close(){}
		virtual void         Read(BYTE* pData, int nSize){}
		virtual unsigned int Read(int nSize){ return 0; }
		virtual void         Skip(int nSize){}
		virtual void         Seek(int nPosition){}
		virtual unsigned int Write(unsigned int nValue, int nLen){ return 0; }
		virtual int          Tell(){ return 0; }
		virtual int          GetLeftSize(){ return 0; }
		virtual void*        GetOwner(){ return NULL; }
	};

	class CReaderStream : CReader
	{
	public:
		CReaderStream(void);
		CReaderStream(void* sStream, int nSizeStream);
		virtual ~CReaderStream(void);

		bool         Open(void* sStream, int nSizeStream);
		void         Close();
		void         Read(BYTE* pData, int nSize);
		unsigned int Read(int nSize);
		void         Skip(int nSize);
		void         Seek(int nPosition);
		unsigned int Write(unsigned int nValue, int nLen);
		int          Tell();
		int          GetLeftSize();
		void*        GetOwner();

	protected:
		ByteIO* m_pStream;
		int     m_nPosition;
		int     m_nSkiped;
		int     m_nSize;
	};

	class CReaderFile : CReader
	{
	public:
		CReaderFile(void);
		CReaderFile(const std::wstring& wsFileName, long lMode);
		virtual ~CReaderFile(void);

		bool         Open(const std::wstring& wsFileName, int nSizeStream);
		void         Close();
		void         Read(BYTE* pData, int nSize);
		unsigned int Read(int nSize);
		void         Skip(int nSize);
		void         Seek(int nPosition);
		unsigned int Write(unsigned int nValue, int nLen);
		int          Tell();
		int          GetLeftSize();
		void*        GetOwner();

	protected:

		NSFile::CFileBinary m_oFile;
		FILE*               m_pFile;
		int                 m_nPosition;
		int                 m_nSkiped;
		int                 m_nSize;
	};
}