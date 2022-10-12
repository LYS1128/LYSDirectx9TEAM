float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float	g_fPercent;

struct VS_IN {
	float3	 vPosition : POSITION;
	float2	 vTexUV : TEXCOORD;
};

struct VS_OUT {
	float4	 vPosition : POSITION;
	float2	 vTexUV : TEXCOORD0;
	float4 vLocalPos : TEXCOORD1;
};

texture g_Texture;

sampler DefaultSampler = sampler_state {
	texture = g_Texture;
	magfilter = linear;
	minfilter = linear;
	mipfilter = linear;
};

VS_OUT VS_MAIN(VS_IN In) {
	VS_OUT Out;

	float4	 vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	vPosition = mul(vPosition, g_ViewMatrix);
	vPosition = mul(vPosition, g_ProjMatrix);

	Out.vPosition = vPosition;
	Out.vTexUV = In.vTexUV;
	Out.vLocalPos = vector(In.vPosition, 1.f);

	return Out;
}

struct PS_IN {
	vector vPosition : POSITION;
	float2	 vTexUV : TEXCOORD0;
	float4 vLocalPos : TEXCOORD1;
};

struct PS_OUT {
	vector vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In) {
	PS_OUT Out;

	Out.vColor = tex2D(DefaultSampler, In.vTexUV);

	if (-0.5f + g_fPercent <= In.vLocalPos.y) {
		discard;
	}

	return Out;
}

technique DefaultTechnique {
	pass DefaultRendering {		
		VertexShader = compile vs_2_0 VS_MAIN();
		PixelShader = compile ps_2_0 PS_MAIN();
	}
}