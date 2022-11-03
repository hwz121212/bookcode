// CDAudio.cpp

#include "stdafx.h"
#include <mmsystem.h>
#include "CDAudio.h"

CCDAudio::CCDAudio()
{

	m_bOpened = m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;

}

CCDAudio::~CCDAudio()
{

	Close();

}

BOOL CCDAudio::Open( void )
{

	if( m_bOpened )
		return( TRUE );

	m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;

	MCI_OPEN_PARMS OpenParms;
	OpenParms.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
	OpenParms.wDeviceID = 0;

	if( mciSendCommand( NULL, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE, (DWORD)(LPVOID) &OpenParms ) )
		return( FALSE );

	m_wDeviceID = OpenParms.wDeviceID;
	m_bOpened = TRUE;

	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_TMSF;

	if( mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ){
		Close ();
		return( FALSE );
		}

	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );

	return( TRUE );

}

void CCDAudio::Close( void )
{

	if( !m_bOpened )
		return;

	if( m_bPlaying || m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_STOP, NULL, NULL );

	mciSendCommand( m_wDeviceID, MCI_CLOSE, MCI_WAIT, NULL );

	m_bOpened = m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;

}

BOOL CCDAudio::Play (void)
{

	if( !Open() )
		return( FALSE );

	if( !IsAudioTrack( GetCurrentTrack() ) )
		return( FALSE );

	MCI_PLAY_PARMS PlayParms;
	PlayParms.dwCallback = NULL;
	PlayParms.dwFrom = MCI_MAKE_TMSF( GetCurrentTrack(), GetMinutes(), GetSeconds(), GetFrames() );

	if( mciSendCommand( m_wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &PlayParms ) )
		return( FALSE );

	m_bPaused = FALSE;
	m_bPlaying = TRUE;

	return( TRUE );

}

void CCDAudio::Stop( void )
{

	if( !m_bOpened || !m_bPlaying )
		return;

	mciSendCommand( m_wDeviceID, MCI_STOP, MCI_WAIT, NULL );
	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
	m_bPlaying = FALSE;
	m_bPaused = FALSE;

}

void CCDAudio::Pause( void )
{

	if( !m_bOpened || !m_bPlaying )
		return;

	MCI_PLAY_PARMS PlayParms;

	if( mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, (DWORD)(LPVOID) &PlayParms ) )
		return;

	m_bPaused = TRUE;

}

int CCDAudio::GetTotalTracks( void )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( (int) StatusParms.dwReturn );

}

void CCDAudio::GetTotalLength( int *pnMinutes, int *pnSeconds )
{

	*pnMinutes = -1;
	*pnSeconds = -1;

	if( !m_bOpened )
		return;

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_LENGTH;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return;

	*pnMinutes = MCI_MSF_MINUTE( StatusParms.dwReturn );
	*pnSeconds = MCI_MSF_SECOND( StatusParms.dwReturn );

}

void CCDAudio::GetTrackLength( int nTrack, int *pnMinutes, int *pnSeconds )
{

	*pnMinutes = -1;
	*pnSeconds = -1;

	if( !m_bOpened )
		return;

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	StatusParms.dwTrack = (DWORD) nTrack;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms ) )
			return;

	*pnMinutes = MCI_MSF_MINUTE( StatusParms.dwReturn );
	*pnSeconds = MCI_MSF_SECOND( StatusParms.dwReturn );

}

int CCDAudio::GetCurrentTrack( void )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_TRACK( StatusParms.dwReturn ) );

}

int CCDAudio::GetMinutes( void )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_MINUTE( StatusParms.dwReturn ) );

}

int CCDAudio::GetSeconds( void )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_SECOND( StatusParms.dwReturn ) );

}

int CCDAudio::GetFrames( void )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_FRAME( StatusParms.dwReturn ) );

}

BOOL CCDAudio::IsDriveReady( void )
{

	if( !m_bOpened )
		return( FALSE );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_MODE;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( FALSE );

	if( StatusParms.dwReturn == MCI_MODE_NOT_READY || StatusParms.dwReturn == MCI_MODE_OPEN )
		return( FALSE );

	StatusParms.dwItem = MCI_STATUS_MEDIA_PRESENT;
	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( FALSE );

	return( (BOOL) StatusParms.dwReturn );

}

BOOL CCDAudio::IsAudioTrack( int nTrack )
{

	if( !m_bOpened )
		return( FALSE );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_CDA_STATUS_TYPE_TRACK;
	StatusParms.dwTrack = nTrack;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms ) )
		return( FALSE );

	if( StatusParms.dwReturn == MCI_CDA_TRACK_AUDIO )
		return( TRUE );

	return( FALSE );

}

BOOL CCDAudio::IsPlaying( BOOL *pbPaused )
{

	*pbPaused = m_bPaused;

	return( m_bPlaying );

}

BOOL CCDAudio::SeekTo( int nTrack, int nMinute, int nSecond, int nFrame )
{

	if( !m_bOpened )
		return( FALSE );

	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = MCI_MAKE_TMSF( nTrack, nMinute, nSecond, nFrame );

	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );

	if( mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms ) )
		return( FALSE );

	if( m_bPlaying && !m_bPaused )
		Play();

	return( TRUE );

}

void CCDAudio::SkipForward( int nSeconds )
{

	if( !m_bOpened )
		return;

	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;

	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	MCI_STATUS_PARMS StatusParms;
	DWORD dwPos;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );

	dwPos = StatusParms.dwReturn;
	dwPos += (DWORD) nSeconds * 1000;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = dwPos;

	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );

	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms );
	SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	if( m_bPlaying && !m_bPaused )
		Play();

}

void CCDAudio::SkipBack( int nSeconds )
{

	if( !m_bOpened )
		return;

	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	MCI_STATUS_PARMS StatusParms;
	DWORD dwPos;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );

	dwPos = StatusParms.dwReturn;
	dwPos -= (DWORD) nSeconds * 1000;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = dwPos;

	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );

	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms );
	SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	if( m_bPlaying && !m_bPaused )
		Play();

}

void CCDAudio::OpenDrive( void )
{

	if( m_bOpened ){
		Stop();
		mciSendCommand( m_wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, NULL );
		}

}

void CCDAudio::CloseDrive( void )
{

	if( m_bOpened ){
		mciSendCommand( m_wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, NULL );
		Stop();
		}	

}

