
#version 330
// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
// Output fragment color
out vec4 finalColor;

uniform vec2 resolution;
uniform vec3 camPos;
uniform vec3 displacements[100];
uniform int LENGTH;
//<***>

float sphere(vec3 p, float r){
    return length(p)-r;
}


float opSmoothUnion( float d1, float d2, float k )
{
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h);
}


float scene(vec3 p){
    float res = 1.0;
    //<**>
    return res;
}

vec3 calcNormal( in vec3 x, in float eps )
{
  vec2 e = vec2( eps, 0.0 );
  return normalize(vec3(scene(x+e.xyy) - scene(x-e.xyy),
                        scene(x+e.yxy) - scene(x-e.yxy),
                        scene(x+e.yyx) - scene(x-e.yyx)));
}

void main(){
    float aspectRatio = resolution.x/resolution.y;
    vec2 uv = vec2(gl_FragCoord.x/resolution.x*aspectRatio, gl_FragCoord.y/resolution.y);
    vec3 dir = normalize(vec3(uv, camPos.z+1.0)-camPos);
    float t = 0.0;
    float res = 0.0;
    bool use = false;
    for(int i = 0; i < 100; i++){
        res = scene(camPos+t*dir);
        t+=res;
        if(res < 0.005){
            use = true;
            break;
        }
    }
    if(use){
        finalColor = vec4(calcNormal(camPos+t*dir, 0.001), 1.0);
    }
    else{
        discard;
    }
}