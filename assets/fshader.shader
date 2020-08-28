#version 300 es
precision mediump float;

in vec4 my_fcolor;

out vec4 my_fragment;
void main() {
    my_fragment = my_fcolor; 
}