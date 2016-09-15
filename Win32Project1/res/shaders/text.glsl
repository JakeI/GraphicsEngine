
vec4 textureFontColor(sampler2D fontAtlas, vec2 textureUV, vec4 typeScalar,
		vec4 bodyColor, vec4 outlineColor, vec3 edges, vec4 shaddowColor, 
		vec4 shaddowParam, vec4 backgroundColor) {
		
	float dist = 1.0f - dot(typeScalar, texture2D(fontAtlas, textureUV)); // distance of the fragment from the center line of the character (0.0 -> on line, 1.0 -> max away)
	float bodyEnd = edges.x + edges.y; // distance form the ideal line at whitch the the character body ends
	float isBody = 1.0f - smoothstep(edges.x, bodyEnd, dist); // fragment is in the main body (0.0 -> outside, 1.0 -> inside)
	float isBodyOutline = 1.0f - smoothstep(bodyEnd, bodyEnd+edges.z, dist); // fragment is in Body or outline (0.0 -> outside, 1.0 -> inside)
	float isOutline = isBodyOutline - isBody; // fragment is in Outline (0.0 -> outlide, 1.0 -> inside)
	float shaddowDist = 1.0f - dot(typeScalar, texture2D(fontAtlas, textureUV + shaddowParam.xy)); // distance form the center line of the shaddow (0.0 -> on line, 1.0 -> max away)
	float isShadowOrOutlineBody = 1.0f - smoothstep(shaddowParam.z, shaddowParam.z+shaddowParam.w, shaddowDist); // fragment is Body, outline or shaddow (0.0 ->outside, 1.0 -> inside)
	float isShadow = clamp(isShadowOrOutlineBody - isOutline - isBody, 0.0f, 1.0f);  // fragment is in shaddow (0.0 -> outside, 1.0 -> inside)
	float isBackground = clamp(1.0f - isBody - isOutline, 0.0f, 1.0f); // fragment is in the Backgroundd (0.0 -> outside, 1.0 -> inside)
	
	return isBody*bodyColor + isOutline*outlineColor + 
		isShadow*shaddowColor + isBackground*backgroundColor;
}
