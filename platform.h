#ifndef SNIPA_PLATFORM_H
#define SNIPA_PLATFORM_H

/* Must be defined before any GLUT header. MinGW GLUT otherwise emits
   __glutInitWithExit / __glutCreateWindowWithExit, which the stock
   glut32 import library does not provide. */
#if defined(_WIN32)
#  ifndef GLUT_DISABLE_ATEXIT_HACK
#    define GLUT_DISABLE_ATEXIT_HACK
#  endif
#  include <GL/glut.h>
#elif defined(__APPLE__)
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#endif
