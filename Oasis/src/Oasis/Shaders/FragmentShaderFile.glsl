#version 460 core
uniform float t;
// uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    gl_FragColor = vec4(abs(sin(t)),abs(cos(t)),abs(tan(t)),1.0f);
}   