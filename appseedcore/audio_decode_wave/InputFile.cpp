#include "StdAfx.h"
#include "InputFile.h"

#define STANDARD_WAVEFORMAT_SIZE 16


namespace audio_decode_wave
{

InputFile::InputFile(void)
{
}

InputFile::~InputFile(void)
{
}


bool is_valid_riff_header(RIFF_HEADER * pRiffHeader)
{
	if(!SzEqual(pRiffHeader->chunkHeader.szChunkId, "RIFF", 4))
		return false;

	// Verify Wave in Riff
	if(!SzEqual(pRiffHeader->szRiffFormat, "WAVE", 4))
		return false;
	
	return true;
}

// verifies fmt chunk. checks for 'fmt '
bool is_valid_fmt_chunk(FMT_BLOCK* pFmtHeader)
{
	if(!SzEqual(pFmtHeader->chunkHeader.szChunkId, "fmt ", 4))
		return false;

	return true;
}

// checks for 'data' 
bool is_valid_data_block(DATA_BLOCK* pDataBlock)
{
   if(!SzEqual(pDataBlock->chunkHeader.szChunkId, "data", 4))	
		return false;

	return true;
}


bool InputFile::CheckRead(int & iPos, LPVOID lpdata, int iSize)
{
   int iPreviousPos = m_pfile->GetPosition();
   int iRead = m_pfile->read(lpdata, iSize);
   if(iRead == iSize)
   {
      iPos = iPreviousPos;
      return true;
   }
   else
   {
      return false;
   }
}

void InputFile::open(ex1::file * pfile)
{
   m_pfile = pfile;

   // Verify Riff
   int iRiffHeader;
   if(!CheckRead(iRiffHeader, &m_riffheader, sizeof(m_riffheader)))
      throw "CWaveFileHandler::OpenForRead, Invalid or corrupt Riff header. 'RIFF' or 'WAVE' missing.";
	if(!is_valid_riff_header(&m_riffheader))
		throw "CWaveFileHandler::OpenForRead, Invalid or corrupt Riff header. 'RIFF' or 'WAVE' missing.";
   
   // Verify Format
   int iFmtHeader;
   if(!CheckRead(iFmtHeader, &m_fmtheader, sizeof(m_fmtheader)))
      throw "CWaveFileHandler::OpenForRead, Invalid or corrupt fmt block. 'fmt ' missing.";
	if(!is_valid_fmt_chunk(&m_fmtheader))
		throw "CWaveFileHandler::OpenForRead, Invalid or corrupt fmt block. 'fmt ' missing.";
   int iFmtHeaderExSize = m_fmtheader.chunkHeader.dwChunkSize;

   if(iFmtHeaderExSize > STANDARD_WAVEFORMAT_SIZE)
	{
		m_pfile->seek(iFmtHeaderExSize - STANDARD_WAVEFORMAT_SIZE, ::ex1::seek_current);
	}

   CHUNK_HEADER hd;
   int iDataBlock;
   if(!CheckRead(iDataBlock, &hd, sizeof(hd)))
      throw "CWaveFileHandler::OpenForRead, Invalid or corrupt data block. 'data' missing.";

   CHAR sz5[5];

   hd.GetChunkId(sz5);

   while(strcmp(sz5, "data") != 0)
   {
		iDataBlock = m_pfile->seek(hd.dwChunkSize,
         ::ex1::seek_current);
      if(!CheckRead(iDataBlock, &hd, sizeof(hd)))
         throw "CWaveFileHandler::OpenForRead, Invalid or corrupt data block. 'data' missing.";
      hd.GetChunkId(sz5);
   }
   
   if(strcmp(sz5, "data") != 0)
      throw "CWaveFileHandler::OpenForRead, Invalid or corrupt data block. 'data' missing.";

   m_datablock.chunkHeader = hd;

   m_iRiffHeader        = iRiffHeader;
   m_iFmtHeader         = iFmtHeader;
   m_iFmtHeaderExSize   = iFmtHeaderExSize;
   m_iDataBlock         = iDataBlock;
   m_iStartOfData       = m_pfile->GetPosition();
}

void InputFile::Construct()
{
	m_iStartOfData	= -1;
	m_iRiffHeader	= -1;
	m_iFmtHeader	= -1;
	m_iDataBlock	= -1;
}

} // namespace audio_decode_wave