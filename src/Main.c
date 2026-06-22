#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"
#include "/home/codeleaded/System/Static/Library/PerlinNoise.h"
#include "/home/codeleaded/System/Static/Library/HydraulicErosion.h"


#define BUFFER_W    500
#define BUFFER_H    500
double* buffer = NULL;
u64 iterations = 0;
TransformedView tv;

void Setup(AlxWindow* w){
	tv = TransformedView_Make(
		(Vec2){ GetWidth(),GetHeight() },
		(Vec2){ 0.0f,0.0f },
		(Vec2){ 1.0f,1.0f },
		(float)GetWidth() / (float)GetHeight()
	);

    PerlinNoise_Permutations_Init();
    AlxFont_Resize(&window.font,50,50);

    buffer = (double*)malloc(sizeof(double) * BUFFER_W * BUFFER_H);
    memset(buffer,0,sizeof(double) * BUFFER_W * BUFFER_H);

    Random_Set(Time_Nano());

    PerlinNoise_Offset_Set(1);
    PerlinNoise_Persistance_Set(100.0f);

    for (unsigned int y = 0; y < BUFFER_H; y += 1U) {
        for (unsigned int x = 0; x < BUFFER_W; x += 1U) {
            const unsigned int i = y * BUFFER_W + x;
            buffer[i] = PerlinNoise_2D_Get(x,y);
        }
    }
}

void Update(AlxWindow* w){
    tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	TransformedView_Output(&tv,(Vec2){ GetWidth(),GetHeight() });

    if(Stroke(ALX_KEY_SPACE).DOWN){
        HydraulicErosion_2D_Iter(buffer,BUFFER_W,BUFFER_H,50,0.1,0.9,0.01);
    }

	Clear(BLACK);

    const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
	const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
	
	for(int i = (int)F32_Floor(tl.y) - 1;i<(int)F32_Ceil(br.y);i++){
		for(int j = (int)F32_Floor(tl.x) - 1;j<(int)F32_Ceil(br.x);j++){
			if(j<0 || j>=BUFFER_W || i<0 || i>=BUFFER_H) continue;
            
            const int ind = i * BUFFER_W + j;
			const Vec2 bg_p = TransformedView_WorldScreenPos(&tv,(Vec2){ j,i });
			const Vec2 bg_d = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
            const float l = (float)(0.5 * buffer[ind] + 0.5);
			RenderRect(bg_p.x,bg_p.y,bg_d.x + 1,bg_d.y + 1,Pixel_toRGBA(l,l,l,1.0f));
		}
	}
    
    CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,RED,"IT: %d",iterations);
}

void Delete(AlxWindow* w){
    if(buffer){
        free(buffer);
        buffer = NULL;
    }
}

int main(){
    if(Create("HydraulicErosion",1800,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}