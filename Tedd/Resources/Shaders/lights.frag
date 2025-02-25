uniform float uTime;
uniform vec2 uWinSize;
uniform sampler2D uTex;
uniform vec2 uPos;
uniform ivec4 uClr;
uniform float uRds;
uniform float uAtn;

float magnitude2(vec2 _v) {
	return _v.x * _v.x + _v.y * _v.y;
}

void main() {
	vec4 clrAdjusted = uClr / 255.;
	float uRdsAdjusted = uRds / uWinSize.y;
	uPos.y = uWinSize.y - uPos.y;

//	gl_FragColor = texture2D(uTex, fragPos);

//	vec2 fragPosAdjusted = vec2(fragPos.x, fragPos.y * uWinSize.x / uWinSize.y);

	float dist = magnitude2(gl_FragCoord.xy - uPos);
//	if (dist < uRds * uRds + sin(uTime * 10.) * .01) gl_FragColor += clrAdjusted;

	if (dist < uRds * uRds) {
	if (uAtn < .0001) uAtn = .0001;
		float fade = clamp((1. / uAtn) - (sqrt(dist) * (1. / uAtn) / uRds), 0., 1.);
		gl_FragColor = vec4(clrAdjusted.rgb, clrAdjusted.a * fade);
	}
}