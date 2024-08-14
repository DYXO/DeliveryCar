#include "playsound.h"

soundplayer::soundplayer(const char* name):filename(name),handle(nullptr),buffer(nullptr)
{
	read_head();
	init();
}

soundplayer::~soundplayer()
{
	stop();
}

void soundplayer::read_head()
{
    // open the audio file
    fp = fopen(filename, "rb");
    if (!fp) {
        perror("Failed to open file");
    }

    /* read WAV head to automatically set the sampling rate
       and other parameters
    */
    fread(&header, sizeof(WAVHeader), 1, fp);
}


void soundplayer::init()
{
	rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	
    if (rc < 0) 
    {
        fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
    }
    
    // allocate hardware parameter objects
    snd_pcm_hw_params_alloca(&params);

    // fill default
    snd_pcm_hw_params_any(handle, params);

    // set access type
    snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

    // set format
    snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

    // set the number of channels
    snd_pcm_hw_params_set_channels(handle, params, header.numChannels);

    // set sampling rate
    snd_pcm_hw_params_set_rate_near(handle, params, &header.sampleRate, &dir);

    // set parameter
    rc = snd_pcm_hw_params(handle, params);
    if (rc < 0) 
    {
        fprintf(stderr, "unable to set hw parameters: %s\n", snd_strerror(rc));
    }

    // get the size of frame
    snd_pcm_hw_params_get_period_size(params, &frames, &dir);
    size = frames * header.numChannels * (header.bitsPerSample / 8);
    buffer = (char *) malloc(size);
}

void soundplayer::stop()
{
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    free(buffer);
    fclose(fp);
}

void soundplayer::play()
{
	while (fread(buffer, 1, size, fp) == size) 
	{
        rc = snd_pcm_writei(handle, buffer, frames);
        if (rc == -EPIPE) 
        {
            // EPIPE means underrun
            fprintf(stderr, "underrun occurred\n");
            snd_pcm_prepare(handle);
        } 
        
        else if (rc < 0) 
        {
            fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
        } 
        
        else if (rc != (int)frames) 
        {
            fprintf(stderr, "short write, write %d frames\n", rc);
        }
    }
}
