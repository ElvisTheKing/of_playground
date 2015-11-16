// fragment shader

#version 150

uniform int init_flag;
uniform float time;
uniform sampler2DRect tex0, tex1;
out vec4 outputColor;
//layout(origin_upper_left) in vec4 gl_FragCoord;

precision highp float;
float snoise(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233*time))) * 43758.5453);
}

int get(int x, int y) {
    return int(texture2DRect(tex0, (gl_FragCoord.xy + vec2(x, y))).r);
}


void main()
{
    float c = 0;
    if (init_flag == 1) {
        c = float(int(snoise(gl_FragCoord.xy)+0.3));
    } else {
        float sum = 0;
        for (int i=-1;i<2; i++) {
            for (int j=-1;j<2; j++) {
                sum = sum + get(i,j);
            }
        }

        sum = sum - get(0,0);

        if (sum!=3) {
            c=0;
        } else {
            c=1;
        }
    }
    outputColor = vec4(c, c, c, 1.0);
}
