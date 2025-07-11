#include "cbase.h"
#include "tier0/vprof.h"
#include "gifhelper.h"
#include "gif_lib.h"

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CGIFHelper::ReadData( GifFileType* pFile, GifByteType* pBuffer, int cubBuffer )
{
	auto pBuf = ( CUtlBuffer* )pFile->UserData;

	int nBytesToRead = MIN( cubBuffer, pBuf->GetBytesRemaining() );
	if( nBytesToRead > 0 )
		pBuf->Get( pBuffer, nBytesToRead );

	return nBytesToRead;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CGIFHelper::OpenImage( CUtlBuffer* pBuf )
{
	if( m_pImage )
	{
		CloseImage();
	}

	int nError;
	m_pImage = DGifOpen( pBuf, ReadData, &nError );
	if( !m_pImage )
	{
		DevWarning( "[CGIFHelper] Failed to open GIF image: %s\n", GifErrorString( nError ) );
		return false;
	}

	if( DGifSlurp( m_pImage ) != GIF_OK )
	{
		DevWarning( "[CGIFHelper] Failed to slurp GIF image: %s\n", GifErrorString( m_pImage->Error ) );
		CloseImage();
		return false;
	}

	int iWide, iTall;
	GetScreenSize( iWide, iTall );
	m_pPrevFrameBuffer = new uint8[ iWide * iTall * 4 ];
	GetRGBA( &m_pPrevFrameBuffer );

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CGIFHelper::CloseImage( void )
{
	if( !m_pImage )
		return;

	delete[] m_pPrevFrameBuffer;

	int nError;
	if( DGifCloseFile( m_pImage, &nError ) != GIF_OK )
	{
		DevWarning( "[CGIFHelper] Failed to close GIF image: %s\n", GifErrorString( nError ) );
	}
	m_pImage = NULL;
	m_pPrevFrameBuffer = NULL;
	m_iSelectedFrame = 0;
	m_dIterateTime = 0.0;
}

//-----------------------------------------------------------------------------
// Purpose: Iterates the current frame index
// Output : true - looped back to frame 0
//-----------------------------------------------------------------------------
bool CGIFHelper::NextFrame( void )
{
	if( !m_pImage )
		return false;

	m_iSelectedFrame++;

	if( m_iSelectedFrame >= m_pImage->ImageCount )
	{
		// Loop
		m_iSelectedFrame = 0;
	}

	GraphicsControlBlock gcb;
	if( DGifSavedExtensionToGCB( m_pImage, m_iSelectedFrame, &gcb ) == GIF_OK )
	{
		m_dIterateTime = ( gcb.DelayTime * 0.01 ) + Plat_FloatTime();
	}

	return m_iSelectedFrame == 0;
}

//-----------------------------------------------------------------------------
// Purpose: Gets the current frame as an RGBA buffer
// Input  :	ppOutFrameBuffer - where should the buffer be copied to, size
//							   needs to be iScreenWide * iScreenTall * 4
//-----------------------------------------------------------------------------
void CGIFHelper::GetRGBA( uint8** ppOutFrameBuffer )
{
	VPROF( "CGIFHelper::GetRGBA" );

	if( !m_pImage )
		return;

	SavedImage* pFrame = &m_pImage->SavedImages[ m_iSelectedFrame ];

	ColorMapObject* pColorMap = pFrame->ImageDesc.ColorMap ? pFrame->ImageDesc.ColorMap : m_pImage->SColorMap;
	GifByteType* pRasterBits = pFrame->RasterBits;

	int iScreenWide, iScreenTall;
	GetScreenSize( iScreenWide, iScreenTall );
	int iFrameWide, iFrameTall;
	GetFrameSize( iFrameWide, iFrameTall );

	int iFrameLeft = pFrame->ImageDesc.Left;
	int iFrameTop = pFrame->ImageDesc.Top;

	int nTransparentIndex = NO_TRANSPARENT_COLOR;
	int nDisposalMethod = DISPOSAL_UNSPECIFIED;

	GraphicsControlBlock gcb;
	if( DGifSavedExtensionToGCB( m_pImage, m_iSelectedFrame, &gcb ) == GIF_OK )
	{
		nTransparentIndex = gcb.TransparentColor;
		nDisposalMethod = gcb.DisposalMode;
	}

	// allocate buffer for current frame with prior framebuffer data for handling transparency and disposal
	uint8* pCurFrameBuffer = ( uint8* )stackalloc( iScreenWide * iScreenTall * 4 );
	Q_memcpy( pCurFrameBuffer, m_pPrevFrameBuffer, iScreenWide * iScreenTall * 4 );

	int iPixel = 0;
	if( pFrame->ImageDesc.Interlace )
	{
		// https://giflib.sourceforge.net/gifstandard/GIF89a.html#interlacedimages
		const int k_rowOffsets[] = { 0, 4, 2, 1 };
		const int k_rowIncrements[] = { 8, 8, 4, 2 };

		for( int nPass = 0; nPass < 4; nPass++ )
		{
			for( int y = k_rowOffsets[ nPass ]; y < iFrameTall; y += k_rowIncrements[ nPass ] )
			{
				if( y + iFrameTop >= iScreenTall ) continue;
				for( int x = 0; x < iFrameWide; x++ )
				{
					if( x + iFrameLeft >= iScreenWide ) continue;
					int iOut = ( ( y + iFrameTop ) * iScreenWide + ( x + iFrameLeft ) ) * 4;
					GifByteType colorIndex = pRasterBits[ iPixel ];
					if( colorIndex < pColorMap->ColorCount && colorIndex != nTransparentIndex )
					{
						GifColorType& color = pColorMap->Colors[ colorIndex ];
						pCurFrameBuffer[ iOut + 0 ] = color.Red;
						pCurFrameBuffer[ iOut + 1 ] = color.Green;
						pCurFrameBuffer[ iOut + 2 ] = color.Blue;
						pCurFrameBuffer[ iOut + 3 ] = 255;
					}
					// else retain prev frame buffer pixel data
					iPixel++;
				}
			}
		}
	}
	else
	{
		for( int y = 0; y < iFrameTall; y++ )
		{
			if( y + iFrameTop >= iScreenTall ) continue;
			for( int x = 0; x < iFrameWide; x++ )
			{
				if( x + iFrameLeft >= iScreenWide ) continue;
				int iOut = ( ( y + iFrameTop ) * iScreenWide + ( x + iFrameLeft ) ) * 4;
				GifByteType colorIndex = pRasterBits[ iPixel ];
				if( colorIndex < pColorMap->ColorCount && colorIndex != nTransparentIndex )
				{
					GifColorType& color = pColorMap->Colors[ colorIndex ];
					pCurFrameBuffer[ iOut + 0 ] = color.Red;
					pCurFrameBuffer[ iOut + 1 ] = color.Green;
					pCurFrameBuffer[ iOut + 2 ] = color.Blue;
					pCurFrameBuffer[ iOut + 3 ] = 255;
				}
				// else retain prev frame buffer pixel data
				iPixel++;
			}
		}
	}

	// copy to output
	Q_memcpy( *ppOutFrameBuffer, pCurFrameBuffer, iScreenWide * iScreenTall * 4 );

	// update prev frame buffer depending on disposal method
	switch( nDisposalMethod )
	{
	case DISPOSE_BACKGROUND:
	{
		for( int y = iFrameTop; y < iFrameTop + iFrameTall && y < iScreenTall; y++ )
		{
			for( int x = iFrameLeft; x < iFrameLeft + iFrameWide && x < iScreenWide; x++ )
			{
				int idx = ( y * iScreenWide + x ) * 4;
				if( m_pImage->SBackGroundColor < m_pImage->SColorMap->ColorCount )
				{
					GifColorType& color = m_pImage->SColorMap->Colors[ m_pImage->SBackGroundColor ];
					m_pPrevFrameBuffer[ idx + 0 ] = color.Red;
					m_pPrevFrameBuffer[ idx + 1 ] = color.Green;
					m_pPrevFrameBuffer[ idx + 2 ] = color.Blue;
					m_pPrevFrameBuffer[ idx + 3 ] = 255;
				}
			}
		}
		break;
	}
	case DISPOSE_PREVIOUS:
		break;
	case DISPOSAL_UNSPECIFIED:
	case DISPOSE_DO_NOT:
	default:
		Q_memcpy( m_pPrevFrameBuffer, pCurFrameBuffer, iScreenWide * iScreenTall * 4 );
		break;
	}

	stackfree( pCurFrameBuffer );
}

//-----------------------------------------------------------------------------
// Purpose: Gets the size of the current frame in pixels
//-----------------------------------------------------------------------------
void CGIFHelper::GetFrameSize( int& iWidth, int& iHeight ) const
{
	if( !m_pImage )
	{
		iWidth = iHeight = 0;
		return;
	}

	GifImageDesc& imageDesc = m_pImage->SavedImages[ m_iSelectedFrame ].ImageDesc;
	iWidth = imageDesc.Width;
	iHeight = imageDesc.Height;
}

//-----------------------------------------------------------------------------
// Purpose: Gets the size of the logical screen in pixels
//-----------------------------------------------------------------------------
void CGIFHelper::GetScreenSize( int& iWide, int& iTall ) const
{
	if( !m_pImage )
	{
		iWide = iTall = 0;
		return;
	}

	iWide = m_pImage->SWidth;
	iTall = m_pImage->SHeight;
}
