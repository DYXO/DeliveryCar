#ifndef __PLAYSOUND_H
#define __PLAYSOUND_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

typedef struct {
    char chunkID[4];
    int chunkSize;
    char format[4];
    char subchunk1ID[4];
    int subchunk1Size;
    short audioFormat;
    short numChannels;
    unsigned int sampleRate;
    int byteRate;
    short blockAlign;
    short bitsPerSample;
    char subchunk2ID[4];
    int subchunk2Size;
} WAVHeader;

class soundplayer
{
public:
	/*
	 * Set the filename and init 
	 * when create an object
	 */
	soundplayer(const char* name);
	
	/*
	 * call the stop function 
	 * to clear memory space
	 */
	~soundplayer();
	
	/*
	 * play the audio file specified
	 * by the constuctor
	 */
	void play();
	
private:
	const char* filename;
	int rc;
    int size;
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *params;
    int dir;
    snd_pcm_uframes_t frames;
    char *buffer;
    FILE *fp;
    WAVHeader header;
    
    void init();
    void stop();
    void read_head(); 
};


#endif
