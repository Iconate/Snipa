#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#define NUM_BUFFERS 8
#define NUM_SOURCES 8

//buffer and source arrays
ALuint buffers[NUM_BUFFERS];
ALuint source[NUM_SOURCES];

void initSounds() {
    // Init openAL
    alutInit(0, NULL);
// Clear Error Code (so we can catch any new errors)
    alGetError();
  
    ALenum     format;
    ALsizei    size;
    ALsizei    freq;
    ALboolean  loop;
    ALvoid*    data;
    
    
    alGenBuffers(NUM_BUFFERS, buffers);
    buffers[0] = alutCreateBufferFromFile("wavdata/theme.wav");
    //alBufferData(buffers[0],format,data,size,freq);
    buffers[1] = alutCreateBufferFromFile("wavdata/beep.wav");
    //alBufferData(buffers[1],format,data,size,freq);
    buffers[2] = alutCreateBufferFromFile("wavdata/select.wav");
    buffers[3] = alutCreateBufferFromFile("wavdata/reload.wav");
    buffers[4] = alutCreateBufferFromFile("wavdata/shot.wav");
    buffers[5] = alutCreateBufferFromFile("wavdata/grass1.wav");
    // Generate the sources
    alGenSources(NUM_SOURCES, source);
    alSourcei(source[0], AL_BUFFER, buffers[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);
    
    alSourcei(source[1], AL_BUFFER, buffers[1]);
    alSourcei(source[2], AL_BUFFER, buffers[2]);
    alSourcei(source[3], AL_BUFFER, buffers[3]);
    alSourcei(source[4], AL_BUFFER, buffers[4]);
    alSourcei(source[5], AL_BUFFER, buffers[5]);

}

void playTheme() {
    alSourcePlay (source[0]);
}

void stopTheme() {
    alSourceStop (source[0]);
}

void playBeep() {
    alSourcePlay (source[1]);
}

void playSelectBeep() {
    alSourcePlay (source[2]);
}

void playReload() {
    alSourcePlay (source[3]);
}

void playShot() {
    alSourcePlay (source[4]);
}

void playWalk() {
    alSourcePlay (source[5]);
    alutSleep(2);
}
