//
//  Random.h
//
//  Created by 鈴木 愛忠 on 2014/10/15.
//
//

#ifndef __ToothBrushGame__Random__
#define __ToothBrushGame__Random__

#include <random>
class RandomMT
{
public:
	RandomMT();
	~RandomMT();
	static void initRand();
	static int getRandomI(int min,int max);
	static double getRandomD(double min,double max);
	static float getRandomF(float min,float max);
private:
	static std::mt19937 m_mtRand;
};
#endif /* defined(__ToothBrushGame__Random__) */
