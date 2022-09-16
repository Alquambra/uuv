/* AB_FILTER_H_ */
                                                                                                                                                                                                                                                                                                                                                         #ifndef AB_FILTER_H_
#define AB_FILTER_H_

class AB_Filter{
public:
	AB_Filter();
	void SetAB(float _a, float _b);
	AB_Filter(float _a, float _b);
	float Filter(float val);
private:
	float xk_1 = 0, vk_1 = 0, a = 0.85, b = 0.005;
	float xk=0, vk=0, rk = 0;
	float xm;
};

class AB_Filter_Int{
public:
	AB_Filter_Int();
	AB_Filter_Int(float _a, float _b);
	void SetAB(float _a, float _b);
	int Filter(int val);
	void SetStart(int s){xk = s;}
private:
	int xk_1 = 0, vk_1 = 0;
	int a = 850, b = 5;
	int xk = 0, vk = 0, rk = 0;
	int xm;
};

#endif /* AB_FILTER_H_ */
