﻿#include "stdafx.h"
#include <iostream>
#include  <sstream>
//#include "subwayMacro.h"
using namespace std;

/*
@ 获取基础票价, 即按进站点与出站点之间的最短里程分级计算
@ -1, 查询基础票价失败; 其他, 基础票价
*/
int GetBasePrice(unsigned int meters)
{
	if(meters<=3000)
		return 2;
	else if(meters>3000 && meters<=5000)
		return 3;
	else if(meters>5000 && meters<=10000)
		return 4;
	else
		return 5;
}