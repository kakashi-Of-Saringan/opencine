// Copyright (c) 2017 apertus° Association & contributors
// Project: OpenCine / ProcessingTest
// License: GNU GPL Version 3 (https://www.gnu.org/licenses/gpl-3.0.en.html)

#version 330 core
#extension GL_EXT_gpu_shader4 : enable

in highp vec4 vColor;
in vec2 vTexCoord;

out highp vec4 fColor;
uniform usampler2D texture1;
uniform usampler2D texture2;
uniform usampler2D texture3;

uniform float redEnabled;
uniform float greenEnabled;
uniform float blueEnabled;

void main()
{
   vec4 textureRed = uvec4(1.0,0.0,0.0,1.0) * texture(texture1, vTexCoord).r * redEnabled;
   vec4 textureGreen = uvec4(0.0,1.0,0.0,1.0) * texture(texture2, vTexCoord).r * greenEnabled;
   vec4 textureBlue = uvec4(0.0,0.0,1.0,1.0) * texture(texture3, vTexCoord).r  * blueEnabled;
   
   vec4 gamma = vec4(1.0 / 2.2, 1.0 / 2.2, 1.0 / 2.2, 1.0);
   vec4 pixel = (textureRed + textureGreen + textureBlue) / (3 * 4096);
   
   fColor = pow(pixel, gamma);
}
