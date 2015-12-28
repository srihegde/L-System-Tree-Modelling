#version 120

varying vec3 fColor;
varying vec3 fNormal;
varying vec3 fLightDir;
varying vec3 fLightDir1;

void main(void)
{
    float tmp,tmp1;
    tmp = max(0,dot(fNormal, fLightDir));
    tmp1 = max(0,dot(fNormal, fLightDir1));
    gl_FragColor = vec4((tmp+tmp1) * fColor, 1.0);
}
