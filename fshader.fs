
uniform float red;
uniform float green;
uniform float blue;
varying vec3 f_color;
void main(void) {
    gl_FragColor = vec4(red, green, blue, 1.0);
   /* gl_FragColor[0] = gl_FragCoord.x/640.0;
                 gl_FragColor[1] = gl_FragCoord.y/480.0;
                 gl_FragColor[2] = 0.5;*/
}
