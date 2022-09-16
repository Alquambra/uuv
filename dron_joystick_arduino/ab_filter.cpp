
#include "ab_filter.h"

AB_Filter::AB_Filter(){
}

AB_Filter::AB_Filter(float _a, float _b){
	a = _a;
	b = _b;
}

void AB_Filter::SetAB(float _a, float _b)
{
	a = _a;
	b = _b;
}

float AB_Filter::Filter(float val){
	xm = val;

	float dt = 0.1;//(cur.tv_sec - prev_time.tv_sec)*1000 + (cur.tv_usec - prev_time.tv_usec)/1000;

	xk = xk_1 + ( vk_1 * dt );
	vk = vk_1;

	rk = xm - xk;

	xk += a * rk;
	vk += ( b * rk ) / dt;

	xk_1 = xk;
	vk_1 = vk;
	return xk_1;
}

AB_Filter_Int::AB_Filter_Int(){
}

AB_Filter_Int::AB_Filter_Int(float _a, float _b){
	a = _a*1000;
	b = _b*1000;
}

void AB_Filter_Int::SetAB(float _a, float _b)
{
	a = _a*1000;
	b = _b*1000;
 	//a = _a;
	//b = _b;
}

int AB_Filter_Int::Filter(int val){
	xm = val;

	xk = xk_1 + ( vk_1 / 10 );
	vk = vk_1;

	rk = xm - xk;

	xk += a * rk/1000;
	vk += ( b * rk ) / 10000;

	xk_1 = xk;
	vk_1 = vk;
	return xk_1;
}
