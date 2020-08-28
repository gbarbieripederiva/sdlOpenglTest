#version 300 es

in vec2 my_vpos;
in vec4  my_vcolor;

out vec4 my_fcolor;
void main() { 
    gl_Position = vec4( my_vpos.x, my_vpos.y, 0, 1 ); 
    my_fcolor = my_vcolor;
}