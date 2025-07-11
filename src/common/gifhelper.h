#ifndef GIFHELPER_H
#define GIFHELPER_H
#ifdef _WIN32
#pragma once
#endif

typedef struct GifFileType GifFileType;
typedef unsigned char GifByteType;

//-----------------------------------------------------------------------------
// Purpose: Simple utility for decoding GIFs
//-----------------------------------------------------------------------------
class CGIFHelper
{
public:
	CGIFHelper( void ) : m_pImage( NULL ), m_pPrevFrameBuffer( NULL ),
		m_iSelectedFrame( 0 ), m_dIterateTime( 0.0 )
	{}
	~CGIFHelper( void ) { CloseImage(); }

	bool OpenImage( CUtlBuffer* pBuf );
	void CloseImage( void );

	// iterates to the next frame, returns true if we have just looped
	bool NextFrame( void );
	int GetSelectedFrame( void ) const { return m_iSelectedFrame; }
	bool ShouldIterateFrame( void ) const { return m_dIterateTime < Plat_FloatTime(); }

	// retrieve data for the current frame
	void GetRGBA( uint8** ppOutFrameBuffer ); // size of the out frame buffer should be iScreenWide * iScreenTall * 4
	void GetFrameSize( int& iWide, int& iTall ) const;
	void GetScreenSize( int& iWide, int& iTall ) const;

private:
	static int ReadData( GifFileType* pFile, GifByteType* pBuffer, int cubBuffer );

	GifFileType* m_pImage;
	uint8* m_pPrevFrameBuffer;
	int m_iSelectedFrame;
	double m_dIterateTime;
};

#endif //GIFHELPER_H