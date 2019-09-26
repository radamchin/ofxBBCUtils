//
// Created by Adam Hinshaw on 2019-09-02.
//
// Utility to print opengl configuration
//
// Based on OF/examples/glInfoExample

#ifndef BBC_GLINFO_H
#define BBC_GLINFO_H

typedef struct {
    string version;
    string vendor;
    string renderer;

    bool bPointSpritesSupported;
    bool bVboSupported;
    bool bShadersSupported;
    int maxTextureSize;
    int maxDimensions[2];
    int maxLights;

} commonOpenGlInfo;

void ofGetGLInfo( commonOpenGlInfo & info ) {

    info.version = (char*)glGetString(GL_VERSION);
    info.vendor = (char*)glGetString(GL_VENDOR);
    info.renderer = (char*)glGetString(GL_RENDERER);
    info.bVboSupported = info.bShadersSupported = info.bPointSpritesSupported = false;

#ifndef TARGET_OPENGLES
    if(glewIsSupported("GL_VERSION_1_4  GL_ARB_point_sprite")) {
        info.bPointSpritesSupported = true;
    }

    if(glewIsSupported("GL_ARB_vertex_buffer_object")) {
        info.bVboSupported = true;
    }

    if(glewIsSupported("GL_ARB_vertex_shader")) {
        info.bShadersSupported = true;
    }

    glGetIntegerv(GL_MAX_VIEWPORT_DIMS, info.maxDimensions);

#else

    // TODO work out equiv. look ups in glm?

#endif

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &info.maxTextureSize);
    glGetIntegerv(GL_MAX_LIGHTS, &info.maxLights);

}

string ofGetGLInfoStringMin() {
    ostringstream out;

    commonOpenGlInfo info;
    ofGetGLInfo(info);

    out << "v=" << info.version << ", vendor=" << info.vendor <<  ", maxTex=" << info.maxTextureSize;

#ifndef TARGET_OPENGLES
    out << ", maxView=" << info.maxDimensions[0] << "," << info.maxDimensions[1];
#endif

    return out.str();
}


#endif //BBC_GLINFO_H
