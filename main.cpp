#include <glad/egl.h>
#include <glad/gl.h>
#include <iostream>

static const EGLint configAttribs[] = {
          EGL_SURFACE_TYPE, EGL_PBUFFER_BIT,
          EGL_BLUE_SIZE, 8,
          EGL_GREEN_SIZE, 8,
          EGL_RED_SIZE, 8,
          EGL_DEPTH_SIZE, 8,
          EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
          EGL_NONE
  };

  static const int pbufferWidth = 800;
  static const int pbufferHeight = 600;

  static const EGLint pbufferAttribs[] = {
        EGL_WIDTH, pbufferWidth,
        EGL_HEIGHT, pbufferHeight,
        EGL_NONE,
  };

int main(int argc, char *argv[])
{
  // 0. Load egl-functions using glad (without egl-display first)
  int egl_version = gladLoaderLoadEGL( NULL );
  if ( !egl_version )
  {
    std::cout << "something went wrong while loading glad-egl functions  (no egl-display)" << std::endl;
    exit( 1 );
  }

  // 1. Initialize EGL
  EGLDisplay eglDpy = eglGetDisplay(EGL_DEFAULT_DISPLAY);

  EGLint major, minor;

  if ( !eglInitialize(eglDpy, &major, &minor) )
  {
    std::cout << "Unable to initialize EGL" << std::endl;
    exit( 2 );
  }

  // 1.1. Reload egl-functions using glad
  egl_version = gladLoaderLoadEGL( eglDpy );
  if ( !egl_version )
  {
    std::cout << "something went wrong while re-loading glad-egl functions" << std::endl;
    exit( 3 );
  }

  // 2. Select an appropriate configuration
  EGLint numConfigs;
  EGLConfig eglCfg;

  eglChooseConfig(eglDpy, configAttribs, &eglCfg, 1, &numConfigs);

  // 3. Create a surface
  EGLSurface eglSurf = eglCreatePbufferSurface(eglDpy, eglCfg, 
                                               pbufferAttribs);

  // 4. Bind the API
  eglBindAPI(EGL_OPENGL_API);

  // 5. Create a context and make it current
  EGLContext eglCtx = eglCreateContext(eglDpy, eglCfg, EGL_NO_CONTEXT, 
                                       NULL);

  eglMakeCurrent(eglDpy, eglSurf, eglSurf, eglCtx);

  // 5.1 Load gl using glad
  if ( !gladLoadGL((GLADloadfunc)eglGetProcAddress) )
  {
    std::cout << "Failed to load GL using glad in egl-context" << std::endl;
    exit( 4 );
  }

  std::cout << "Successfully initialized GLAD and EGL" << std::endl;

  // 6. Terminate EGL when finished
  eglTerminate(eglDpy);
  return 0;
}