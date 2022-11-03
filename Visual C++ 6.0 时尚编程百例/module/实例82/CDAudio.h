// CDAudio.h

#ifndef __CDAUDIO_H__
#define __CDAUDIO_H__

class CCDAudio
{

public:
	CCDAudio();
	~CCDAudio();

	BOOL Open( void );
	void Close( void );
	BOOL Play( void );
	void Stop( void );
	void Pause( void );
	int GetTotalTracks( void );
	int GetCurrentTrack( void );
	void GetTotalLength( int *, int* );
	void GetTrackLength( int, int *, int * );
	int GetMinutes( void );
	int GetSeconds( void );
	int GetFrames( void );
	BOOL IsDriveReady( void );
	BOOL IsPlaying( BOOL * );
	BOOL IsAudioTrack( int );
	BOOL SeekTo( int, int, int, int );
	void SkipForward( int );
	void SkipBack( int );
	void CloseDrive( void );
	void OpenDrive( void );

private:
	BOOL m_bOpened, m_bPaused, m_bPlaying;
	WORD m_wDeviceID;

};


#endif
