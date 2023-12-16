#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 fragNormal;

uniform mat4 mvp;
// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

void main()
{
    // Texel color fetching from texture sampler
    vec2 muv = vec2(mvp * vec4(normalize(fragNormal), 0.0))*0.5+vec2(0.5,0.5);



    // NOTE: Implement here your fragment shader code

    finalColor =  texture2D(texture0, vec2(muv.x, 1.0-muv.y));
}