#version 330 core

uniform sampler2D uTextureBindings0;
uniform sampler2D uTextureBindings1;
uniform sampler2D uTextureBindings2;
uniform sampler2D uTextureBindings3;
uniform sampler2D uTextureBindings4;
uniform sampler2D uTextureBindings5;
uniform sampler2D uTextureBindings6;
uniform sampler2D uTextureBindings7;
uniform sampler2D uTextureBindings8;
uniform sampler2D uTextureBindings9;
uniform sampler2D uTextureBindings10;
uniform sampler2D uTextureBindings11;
uniform sampler2D uTextureBindings12;
uniform sampler2D uTextureBindings13;
uniform sampler2D uTextureBindings14;
uniform sampler2D uTextureBindings15;
uniform sampler2D uTextureBindings16;
uniform sampler2D uTextureBindings17;
uniform sampler2D uTextureBindings18;
uniform sampler2D uTextureBindings19;
uniform sampler2D uTextureBindings20;
uniform sampler2D uTextureBindings21;
uniform sampler2D uTextureBindings22;
uniform sampler2D uTextureBindings23;
uniform sampler2D uTextureBindings24;
uniform sampler2D uTextureBindings25;
uniform sampler2D uTextureBindings26;
uniform sampler2D uTextureBindings27;
uniform sampler2D uTextureBindings28;
uniform sampler2D uTextureBindings29;
uniform sampler2D uTextureBindings30;
uniform sampler2D uTextureBindings31;

in vec4     vColor;
in vec2     vTextureCoordinates;
in float    vTextureSlot;

out vec4 oColor;

void main() {
    oColor = vColor;

    int texture_slot = int(vTextureSlot);
    switch (texture_slot) {
        case 1:
        oColor *= texture(uTextureBindings0, vTextureCoordinates);
        break;

        case 2:
        oColor *= texture(uTextureBindings1, vTextureCoordinates);
        break;

        case 3:
        oColor *= texture(uTextureBindings2, vTextureCoordinates);
        break;

        case 4:
        oColor *= texture(uTextureBindings3, vTextureCoordinates);
        break;

        case 5:
        oColor *= texture(uTextureBindings4, vTextureCoordinates);
        break;

        case 6:
        oColor *= texture(uTextureBindings5, vTextureCoordinates);
        break;

        case 7:
        oColor *= texture(uTextureBindings6, vTextureCoordinates);
        break;

        case 8:
        oColor *= texture(uTextureBindings7, vTextureCoordinates);
        break;

        case 9:
        oColor *= texture(uTextureBindings8, vTextureCoordinates);
        break;

        case 10:
        oColor *= texture(uTextureBindings9, vTextureCoordinates);
        break;

        case 11:
        oColor *= texture(uTextureBindings10, vTextureCoordinates);
        break;

        case 12:
        oColor *= texture(uTextureBindings11, vTextureCoordinates);
        break;

        case 13:
        oColor *= texture(uTextureBindings12, vTextureCoordinates);
        break;

        case 14:
        oColor *= texture(uTextureBindings13, vTextureCoordinates);
        break;

        case 15:
        oColor *= texture(uTextureBindings14, vTextureCoordinates);
        break;

        case 16:
        oColor *= texture(uTextureBindings15, vTextureCoordinates);
        break;

        case 17:
        oColor *= texture(uTextureBindings16, vTextureCoordinates);
        break;

        case 18:
        oColor *= texture(uTextureBindings17, vTextureCoordinates);
        break;

        case 19:
        oColor *= texture(uTextureBindings18, vTextureCoordinates);
        break;

        case 20:
        oColor *= texture(uTextureBindings19, vTextureCoordinates);
        break;

        case 21:
        oColor *= texture(uTextureBindings20, vTextureCoordinates);
        break;

        case 22:
        oColor *= texture(uTextureBindings21, vTextureCoordinates);
        break;

        case 23:
        oColor *= texture(uTextureBindings22, vTextureCoordinates);
        break;

        case 24:
        oColor *= texture(uTextureBindings23, vTextureCoordinates);
        break;

        case 25:
        oColor *= texture(uTextureBindings24, vTextureCoordinates);
        break;

        case 26:
        oColor *= texture(uTextureBindings25, vTextureCoordinates);
        break;

        case 27:
        oColor *= texture(uTextureBindings26, vTextureCoordinates);
        break;

        case 28:
        oColor *= texture(uTextureBindings27, vTextureCoordinates);
        break;

        case 29:
        oColor *= texture(uTextureBindings28, vTextureCoordinates);
        break;

        case 30:
        oColor *= texture(uTextureBindings29, vTextureCoordinates);
        break;

        case 31:
        oColor *= texture(uTextureBindings30, vTextureCoordinates);
        break;

        case 32:
        oColor *= texture(uTextureBindings31, vTextureCoordinates);
        break;
    }
}
