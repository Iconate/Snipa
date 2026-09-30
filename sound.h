#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_BUFFERS 8
#define NUM_SOURCES 8

ALuint buffers[NUM_BUFFERS];
ALuint source[NUM_SOURCES];

static ALCdevice *snipaAlDevice = NULL;
static ALCcontext *snipaAlContext = NULL;

static unsigned int readLE32(const unsigned char *p) {
    return (unsigned int)p[0] | ((unsigned int)p[1] << 8) |
           ((unsigned int)p[2] << 16) | ((unsigned int)p[3] << 24);
}

static unsigned int readLE16(const unsigned char *p) {
    return (unsigned int)p[0] | ((unsigned int)p[1] << 8);
}

/* PCM WAV loader. Handles fmt chunks larger than 16 bytes and extra
   chunks (fact, LIST) so the bundled wavdata files load on both platforms. */
static int loadWavPcm(const char *path, ALenum *format, void **dataOut,
                      ALsizei *sizeOut, ALsizei *freqOut) {
    FILE *file = fopen(path, "rb");
    unsigned char header[12];
    unsigned short channels = 0;
    unsigned short bits = 0;
    unsigned int sampleRate = 0;
    int haveFmt = 0;
    unsigned char *data = NULL;
    unsigned int dataSize = 0;

    if (!file)
        return 0;
    if (fread(header, 1, 12, file) != 12 ||
        memcmp(header, "RIFF", 4) != 0 || memcmp(header + 8, "WAVE", 4) != 0) {
        fclose(file);
        return 0;
    }

    for (;;) {
        unsigned char chunk[8];
        unsigned int chunkSize;
        if (fread(chunk, 1, 8, file) != 8)
            break;
        chunkSize = readLE32(chunk + 4);
        if (memcmp(chunk, "fmt ", 4) == 0) {
            unsigned char fmt[64];
            unsigned int audioFormat;
            unsigned int toRead = chunkSize < sizeof(fmt) ? chunkSize : (unsigned int)sizeof(fmt);
            if (fread(fmt, 1, toRead, file) != toRead) {
                fclose(file);
                return 0;
            }
            if (chunkSize > toRead && fseek(file, (long)(chunkSize - toRead), SEEK_CUR) != 0) {
                fclose(file);
                return 0;
            }
            audioFormat = readLE16(fmt);
            channels = (unsigned short)readLE16(fmt + 2);
            sampleRate = readLE32(fmt + 4);
            bits = (unsigned short)readLE16(fmt + 14);
            if (audioFormat != 1) {
                fclose(file);
                return 0;
            }
            haveFmt = 1;
        } else if (memcmp(chunk, "data", 4) == 0) {
            data = (unsigned char *)malloc(chunkSize);
            if (!data || fread(data, 1, chunkSize, file) != chunkSize) {
                free(data);
                fclose(file);
                return 0;
            }
            dataSize = chunkSize;
            break;
        } else if (fseek(file, (long)chunkSize, SEEK_CUR) != 0) {
            fclose(file);
            return 0;
        }
        if (chunkSize & 1)
            fseek(file, 1, SEEK_CUR);
    }
    fclose(file);

    if (!haveFmt || !data) {
        free(data);
        return 0;
    }
    if (channels == 1 && bits == 8)
        *format = AL_FORMAT_MONO8;
    else if (channels == 1 && bits == 16)
        *format = AL_FORMAT_MONO16;
    else if (channels == 2 && bits == 8)
        *format = AL_FORMAT_STEREO8;
    else if (channels == 2 && bits == 16)
        *format = AL_FORMAT_STEREO16;
    else {
        free(data);
        return 0;
    }
    *dataOut = data;
    *sizeOut = (ALsizei)dataSize;
    *freqOut = (ALsizei)sampleRate;
    return 1;
}

static ALuint bufferFromWav(const char *path) {
    ALenum format;
    void *data = NULL;
    ALsizei size = 0;
    ALsizei freq = 0;
    ALuint buffer = 0;

    if (!loadWavPcm(path, &format, &data, &size, &freq)) {
        fprintf(stderr, "Snipa: could not load %s\n", path);
        return 0;
    }
    alGenBuffers(1, &buffer);
    alBufferData(buffer, format, data, size, freq);
    free(data);
    if (alGetError() != AL_NO_ERROR) {
        fprintf(stderr, "Snipa: OpenAL rejected %s\n", path);
        return 0;
    }
    return buffer;
}

void initSounds() {
    const char *files[6];
    int i;

    snipaAlDevice = alcOpenDevice(NULL);
    if (!snipaAlDevice) {
        fprintf(stderr, "Snipa: OpenAL device unavailable, continuing without sound\n");
        return;
    }
    snipaAlContext = alcCreateContext(snipaAlDevice, NULL);
    if (!snipaAlContext || !alcMakeContextCurrent(snipaAlContext)) {
        fprintf(stderr, "Snipa: OpenAL context unavailable, continuing without sound\n");
        return;
    }

    files[0] = "wavdata/theme.wav";
    files[1] = "wavdata/beep.wav";
    files[2] = "wavdata/select.wav";
    files[3] = "wavdata/reload.wav";
    files[4] = "wavdata/shot.wav";
    files[5] = "wavdata/grass1.wav";

    for (i = 0; i < 6; i++)
        buffers[i] = bufferFromWav(files[i]);

    alGenSources(NUM_SOURCES, source);
    for (i = 0; i < 6; i++) {
        if (buffers[i] != 0)
            alSourcei(source[i], AL_BUFFER, buffers[i]);
    }
    alSourcei(source[0], AL_LOOPING, AL_TRUE);
}

void playTheme() {
    alSourcePlay(source[0]);
}

void stopTheme() {
    alSourceStop(source[0]);
}

void playBeep() {
    alSourcePlay(source[1]);
}

void playSelectBeep() {
    alSourcePlay(source[2]);
}

void playReload() {
    alSourcePlay(source[3]);
}

void playShot() {
    alSourcePlay(source[4]);
}

void playWalk() {
    alSourcePlay(source[5]);
}
