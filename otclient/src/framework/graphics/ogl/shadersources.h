/*
 * Copyright (c) 2010-2017 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef PAINTEROGL2_SHADERSOURCES_H
#define PAINTEROGL2_SHADERSOURCES_H

static const std::string glslMainVertexShader = "\n\
    highp vec4 calculatePosition();\n\
    void main() {\n\
        gl_Position = calculatePosition();\n\
    }\n";

static const std::string glslMainWithTexCoordsVertexShader = "\n\
    attribute highp vec2 a_TexCoord;\n\
    uniform highp mat3 u_TextureMatrix;\n\
    varying highp vec2 v_TexCoord;\n\
    highp vec4 calculatePosition();\n\
    void main()\n\
    {\n\
        gl_Position = calculatePosition();\n\
        v_TexCoord = (u_TextureMatrix * vec3(a_TexCoord,1.0)).xy;\n\
    }\n";

static const std::string glslLightVertexShader = "\n\
    attribute highp vec4 a_Color;\n\
    varying highp vec4 v_Color;\n\
    attribute highp vec2 a_TexCoord;\n\
    uniform highp mat3 u_TextureMatrix;\n\
    uniform highp mat3 u_DepthTextureMatrix;\n\
    varying highp vec2 v_TexCoord;\n\
    varying highp vec2 v_DepthTexCoord;\n\
    highp vec4 calculatePosition();\n\
    void main() {\n\
        gl_Position = calculatePosition();\n\
        v_Color = a_Color;\n\
        v_TexCoord = (u_TextureMatrix * vec3(a_TexCoord,1.0)).xy;\n\
        v_DepthTexCoord = (u_DepthTextureMatrix * vec3(a_TexCoord,1.0)).xy;\n\
    }\n";

static std::string glslPositionOnlyVertexShader = "\n\
    attribute highp vec2 a_Vertex;\n\
    uniform highp mat3 u_TransformMatrix;\n\
    uniform highp mat3 u_ProjectionMatrix;\n\
    uniform highp float u_Depth;\n\
    highp vec4 calculatePosition() {\n\
        return vec4((u_ProjectionMatrix * u_TransformMatrix * vec3(a_Vertex.xy, 1.0)).xy, u_Depth / 16384.0, 1.0);\n\
    }\n";

static const std::string glslMainFragmentShader = "\n\
    uniform lowp float u_Opacity;\n\
    uniform lowp float u_GlobalOpacity;\n\
    uniform highp float u_Depth;\n\
    highp vec4 calculatePixel();\n\
    void main()\n\
    {\n\
        gl_FragColor = calculatePixel();\n\
        gl_FragColor.a *= u_Opacity;\n\
        gl_FragColor.a *= u_GlobalOpacity;\n\
        if(gl_FragColor.a < 0.01 && u_Depth > 0.0)\n\
	        discard;\n\
    }\n";

static const std::string glslTextureSrcFragmentShader = "\n\
    varying mediump vec2 v_TexCoord;\n\
    uniform highp vec4 u_Color;\n\
    uniform sampler2D u_Tex0;\n\
    highp vec4 calculatePixel() {\n\
        return texture2D(u_Tex0, v_TexCoord) * u_Color;\n\
    }\n";


static const std::string glslSolidColorFragmentShader = "\n\
    uniform lowp vec4 u_Color;\n\
    highp vec4 calculatePixel() {\n\
        return u_Color;\n\
    }\n";

static const std::string glslSolidColorOnTextureFragmentShader = "\n\
    uniform lowp vec4 u_Color;\n\
    varying mediump vec2 v_TexCoord;\n\
    uniform sampler2D u_Tex0;\n\
    highp vec4 calculatePixel() {\n\
        if(texture2D(u_Tex0, v_TexCoord).a > 0.01)\n\
            return u_Color;\n\
        return vec4(0,0,0,0);\n\
    }\n";

static const std::string glslLightFragmentShader = "\n\
    varying highp vec4 v_Color;\n\
    varying mediump vec2 v_TexCoord;\n\
    varying mediump vec2 v_DepthTexCoord;\n\
    uniform sampler2D u_Tex0;\n\
    uniform sampler2D u_TexDepth;\n\
    highp vec4 calculatePixel() {\n\
        //return texture2D(u_Tex0, vec2(v_TexCoord.xy) * v_Color;\n\
        //if(texture2D(u_TexDepth, v_TexCoord.xy).r >= u_Depth)\n\
        //    return texture2D(u_Tex0, v_TexCoord) * v_Color;\n\
        return texture2D(u_TexDepth, v_DepthTexCoord);\n\
    }\n";


#endif
