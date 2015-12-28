#version 120

attribute vec3 vVertex;
attribute vec3 vNormal;
attribute vec3 vColor;

uniform vec3 vLightPosition;
uniform vec3 vLightPosition1;
uniform mat4 vModel;
uniform mat4 vView;
uniform mat4 vProjection;

varying vec3 fColor;
varying vec3 fNormal;
varying vec3 fLightDir;
varying vec3 fLightDir1;

void main(void)
{
    gl_Position = vProjection * vView * vModel * vec4(vVertex, 1.0);

    fColor = vColor; //Interpolate color
    fNormal = normalize(vNormal);
    fLightDir = normalize(vVertex - vLightPosition);
    fLightDir1 = normalize(vVertex - vLightPosition1);
}
