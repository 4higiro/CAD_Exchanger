#include "pch.h"
#include "curves.hpp"

curves::interface_curve::interface_curve() {}

curves::interface_curve::interface_curve(const mv::mat3& mat) noexcept 
	: _lin_op(mat) {}

curves::circle::circle(double R, const mv::mat3& linear_operator) noexcept
	: _R(R), interface_curve(linear_operator) {}

double curves::circle::get_radius() const noexcept { return _R; }

curves::curve_point curves::circle::get_value(double t) const noexcept
{ return _lin_op * mv::vec3(_R * std::cos(t), _R * std::sin(t), 0.0); }

curves::curve_point curves::circle::get_d_dt_value(double t) const noexcept
{ return _lin_op * mv::vec3(_R * (-std::sin(t)), _R * std::cos(t), 0.0); }

curves::ellipse::ellipse(double Rx, double Ry, const mv::mat3& linear_operator) noexcept
	: _Rx(Rx), _Ry(Ry), interface_curve(linear_operator) {}

curves::curve_point curves::ellipse::get_value(double t) const noexcept
{ return _lin_op * mv::vec3(_Rx * std::cos(t), _Ry * std::sin(t), 0.0); }

curves::curve_point curves::ellipse::get_d_dt_value(double t) const noexcept
{ return _lin_op * mv::vec3(_Rx * (-std::sin(t)), _Ry * std::cos(t), 0.0); }

curves::helix::helix(double R, double h, const mv::mat3& linear_operator) noexcept
	: _R(R), _h(h), interface_curve(linear_operator) {}

curves::curve_point curves::helix::get_value(double t) const noexcept
{ return _lin_op * mv::vec3(_R * std::cos(t), _R * std::sin(t), _h * t); }

curves::curve_point curves::helix::get_d_dt_value(double t) const noexcept
{ return _lin_op * mv::vec3(_R * (-std::sin(t)), _R * std::cos(t), _h); }

curves::curve_builder::build_exception::build_exception(const char* what) noexcept
	: what(what) {}
