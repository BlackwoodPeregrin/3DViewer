#extension GL_EXT_gpu_shader4 : require
uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower; // сила освещения
uniform highp bool u_shadding; // тип затенения

uniform highp float u_specularFactor;
uniform highp vec4 u_specularColor;
uniform highp float u_ambientFactor;
uniform highp vec4 u_lightColor;

uniform highp vec4 u_resultColor;
varying highp vec4 v_position;
varying highp vec2 v_texcoord;
varying highp vec3 v_normal;
flat varying vec3 v_normal_flat;

void main(void)
{
        vec3 final_normal = u_shadding ? v_normal : v_normal_flat;
        vec4 resultColor = u_resultColor;
        vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0); // позиция наблюдателя

        vec4 diffMatColor = texture2D(u_texture, v_texcoord); // диффузный цвет материала
        vec3 eyeVec = normalize(v_position.xyz - eyePosition.xyz); // направление взгляда

        vec3 lightVec = normalize(v_position.xyz - u_lightPosition.xyz); // вектор освещения

        vec3 reflectLight = normalize(reflect(lightVec, final_normal)); // отражённый свет


        float len = length(v_position.xyz - eyePosition.xyz); // расстояние от наблюдателя до точки

        vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(final_normal, -lightVec));
        resultColor += diffColor;
        vec4 ambientColor = u_ambientFactor * diffMatColor;
        resultColor += ambientColor;
        vec4 specularColor = u_specularColor * u_lightPower * pow(max(0.0, dot(reflectLight, -eyeVec)), u_specularFactor);

        resultColor += specularColor;

        resultColor *= u_lightColor;

        gl_FragColor = resultColor;
}
