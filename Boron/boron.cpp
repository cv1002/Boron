﻿#include "boron.h"

namespace boron
{

Boron::Boron()
{
	sign = 0;
	data = { 0 };
}

Boron::Boron(const Boron& b)
{
	sign = b.sign;
	data = std::move(b).data;
}
              
Boron::Boron(signed char n)
{
	sign = n < 0;
	data = { static_cast<unsigned>(std::abs(n)) };
}

Boron::Boron(unsigned char n)
{
	sign = 0;
	data = { static_cast<unsigned>(n) };
}

Boron::Boron(signed short n)
{
	sign = n < 0;
	data = { static_cast<unsigned>(std::abs(n)) };
}

Boron::Boron(unsigned short n)
{
	sign = 0;
	data = { static_cast<unsigned>(n) };
}

Boron::Boron(signed int n)
{
	sign = n < 0;
	data = { (unsigned)std::abs(n) };
}

Boron::Boron(unsigned int n)
{
	sign = 0;
	data = { n };
}

Boron::Boron(const char* s, int base)
{
}

Boron::Boron(std::string s, int base)
{
}

Boron::~Boron()
{
}

Boron Boron::operator-()
{
	Boron& b = *this;
	b.sign = !b.sign;
	return b;
}

Boron Boron::operator+(const Boron& rhs)
{
	const Boron& lhs = *this;
	Boron& b{};

	const std::vector<unsigned>& lhs_data = std::move(lhs.data);
	const std::vector<unsigned>& rhs_data = std::move(rhs.data);
	std::vector<unsigned> result_data = { 0 };
	size_t lhs_size = lhs_data.size();
	size_t rhs_size = rhs_data.size();

	if (lhs.sign == rhs.sign)
	{

		for (int i = 1; i <= std::min(lhs_size, rhs_size); i += 1)
		{
			unsigned lhs_section = lhs_data.at(lhs_size - i);
			unsigned rhs_section = rhs_data.at(rhs_size - i);
			unsigned result_section = result_data.at(result_data.size() - 1);

			// 预测两 section 直接相加是否溢出
			if (UINT_MAX - lhs_section > rhs_section)
			{
				// 最大值减去 lhs 段的差大于 rhs 段，则两段相加不会溢出
				result_data.emplace_back(lhs_section + rhs_section + result_section);
			}
			else
			{
				// 将两段的最左位清零，以完成其余位的加法
				unsigned lhs_temp = lhs_section & (~(1 << 1)),
					rhs_temp = rhs_section & (~(1 << 1)),
					result_temp = lhs_temp + rhs_temp;

				// 向 result 的高位段进 1 位
				result_data.emplace_back(1);
				result_data.emplace_back(result_temp);

			}
		}
		
		b.sign == b.sign || POS;

	}
	else
	{
		// TODO...
	}

	b.data = std::move(result_data);
	return b;
}

Boron Boron::operator+=(const Boron& rhs)
{
	return Boron();
}

}