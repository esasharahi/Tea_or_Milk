// esasharahi@gmail.com

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


enum type {tea, milk};

struct particle
{
	int type;
};


static const std::vector<particle> sampler (std::vector<particle>& in, const size_t& nelems)
{
	std::vector<particle> out;
	for (size_t i = 0; i < nelems; i++)
	{
		int index = rand() % in.size();
		out.push_back(in[index]);
		in.erase(in.begin() + index);
	}
	return out;
}

int main ()
{
	const size_t N = 1000;
	const size_t ITERS = 10000;
	const size_t epsilon = 1;
	
	std::vector<particle> tea_pot;
	std::vector<particle> milk_pot;
	
	tea_pot.resize(N);
	milk_pot.resize(N);
	
	for (size_t i = 0; i < N; i++)
	{
		tea_pot[i].type = tea;
		milk_pot[i].type = milk;
	}
	
	std::vector<particle> out;
	for (size_t i = 0; i < ITERS; i++)
	{
		out = sampler(tea_pot, epsilon);
		for (auto o : out)
		{
			milk_pot.push_back(o);
		}
		out = sampler(milk_pot, epsilon);
		for (auto o : out)
		{
			tea_pot.push_back(o);
		}
	}
	
	size_t tea_counter_tea_pot = 0;
	size_t milk_counter_tea_pot = 0;
	for (auto t : tea_pot)
	{
		(t.type == tea) ? (tea_counter_tea_pot++) : (milk_counter_tea_pot++); 
	}
	//
	size_t tea_counter_milk_pot = 0;
	size_t milk_counter_milk_pot = 0;
	for (auto m : milk_pot)
	{
		(m.type == tea) ? (tea_counter_milk_pot++) : (milk_counter_milk_pot++);
	}

	std::cout <<
				"teas in teapot: " << tea_counter_tea_pot  <<
				"\nmilks in teapot: " << milk_counter_tea_pot <<
				"\nteas in milkpot: " << tea_counter_milk_pot <<
				"\nmilks in milkpot: " << milk_counter_milk_pot <<
				"\n";	
}
