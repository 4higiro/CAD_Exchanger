#include <iostream>
#include <vector>
#include <list>
#include <numeric>

#include "curves.hpp"

int main()
{
	std::srand(std::time(NULL));
	std::size_t count = std::rand() % 901 + 100;
	std::vector<curves::curve_builder::curve_ptr> first(count);
	for (auto i = first.begin(); i != first.end(); ++i)
		*i = curves::curve_builder::make_random_curve();
	std::cout << "Curve points:" << std::endl;
	const double t = PI / 4.0;
	for (auto curve : first)
		std::cout << "value(PI / 4) - {  " << curve->get_value(t) 
			<< "}\nderivative(PI/4) - {  " << curve->get_d_dt_value(t) << "}" << "\n\n";
	std::list<curves::circle*> second;
	for (auto curve : first)
	{
		curves::circle* temp = dynamic_cast<curves::circle*>(curve.get());
		if (temp != nullptr) second.push_back(temp);
	}
	second.sort([](const curves::circle* p1, const curves::circle* p2) 
		{ return p1->get_radius() < p2->get_radius(); });
	int sum_radius = 0;
	int size = second.size();
	auto it = second.begin();
	#pragma omp parallel
	{
		#pragma omp for
		for (int i = 0; i < size; ++i)
		{
			sum_radius += (*it)->get_radius();
			++it;
		}
	}
	std::cout << "Sum of circles radius: " << sum_radius << std::endl;

	return 0;
}