#ifndef _CAD_CURVES
#define _CAD_CURVES

#include <random>
#include <memory>

#include "matvec.hpp"

#define PI std::acos(-1)

namespace curves
{
	using curve_point = mv::vec3;

	class interface_curve
	{
	protected:
		mv::mat3 _lin_op;
		interface_curve() {}
		explicit interface_curve(const mv::mat3& mat) noexcept : _lin_op(mat) {}
	public:
		curve_point virtual get_value(double) const noexcept = 0;
		curve_point virtual get_d_dt_value(double) const noexcept = 0;
	};

	class circle : public interface_curve
	{
	private:
		double _R;

		explicit circle(double R, const mv::mat3& linear_operator = mv::mat3()) noexcept
			: _R(R), interface_curve(linear_operator) {}

		friend class curve_builder;
	public:
		double get_radius() const noexcept { return _R; }

		curve_point get_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_R * std::cos(t), _R * std::sin(t), 0.0); }

		curve_point get_d_dt_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_R * (-std::sin(t)), _R * std::cos(t), 0.0); }
	};

	class ellipse : public interface_curve
	{
	private:
		double _Rx, _Ry;

		ellipse(double Rx, double Ry, const mv::mat3& linear_operator = mv::mat3()) noexcept
			: _Rx(Rx), _Ry(Ry), interface_curve(linear_operator) {}

		friend class curve_builder;
	public:
		curve_point get_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_Rx * std::cos(t), _Ry * std::sin(t), 0.0); }

		curve_point get_d_dt_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_Rx * (-std::sin(t)), _Ry * std::cos(t), 0.0); }
	};

	class helix : public interface_curve
	{
	private:
		double _R, _h;

		helix(double R, double h, const mv::mat3& linear_operator = mv::mat3()) noexcept
			: _R(R), _h(h), interface_curve(linear_operator) {}

		friend class curve_builder;
	public:
		curve_point get_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_R * std::cos(t), _R * std::sin(t), _h * t); }

		curve_point get_d_dt_value(double t) const noexcept override
		{ return _lin_op * mv::vec3(_R * (-std::sin(t)), _R * std::cos(t), _h); }
	};

	enum curve_t { CIRCLE = 0, ELLIPSE = 1, HELIX = 2 };

	class curve_builder final
	{
	private:
		template <typename ..._args>
		static bool _valid(double arg, const _args&... data) noexcept
		{ return static_cast<double>(arg) >= 0.0 && _valid(data...); }

		static bool _valid(const mv::mat3& linear_operator) noexcept { return true; }
		static bool _valid() noexcept { return true; }

#define RAND_GEN std::rand() % 50 + 1
	public:
		using curve_ptr = std::shared_ptr<interface_curve>;

		struct build_exception
		{
			const char* what;
			explicit build_exception(const char* what) noexcept : what(what) {}
		};

		template <curve_t curve, typename ..._args>
		static curve_ptr make_curve(_args... construct_data)
		{
			if (!_valid(construct_data...))
				throw build_exception("Curve is not physically correct");
			if constexpr (curve == CIRCLE)
				return curve_ptr(new circle(construct_data...));
			if constexpr (curve == ELLIPSE)
				return curve_ptr(new ellipse(construct_data...));
			if constexpr (curve == HELIX)
				return curve_ptr(new helix(construct_data...));
			static_assert(curve < 3, "Uncorrect curve type");
		}

		static curve_ptr make_random_curve() noexcept
		{
			curve_t curve = static_cast<curve_t>(std::rand() % 3);
			switch (curve)
			{
			case CIRCLE:
				return curve_ptr(new circle(RAND_GEN));
			case ELLIPSE:
				return curve_ptr(new ellipse(RAND_GEN, RAND_GEN));
			case HELIX:
				return curve_ptr(new helix(RAND_GEN, RAND_GEN));
			}
		}

		static curve_ptr make_random_curve_with_random_linear_operator() noexcept
		{ 
			curve_t curve = static_cast<curve_t>(std::rand() % 3);
			mv::mat3 random_linear_operator;
			for (auto i = random_linear_operator.begin();
				i != random_linear_operator.end(); *i = RAND_GEN, ++i);
			switch (curve)
			{
			case CIRCLE:
				return curve_ptr(new circle(RAND_GEN, random_linear_operator));
			case ELLIPSE:
				return curve_ptr(new ellipse(RAND_GEN, RAND_GEN, random_linear_operator));
			case HELIX:
				return curve_ptr(new helix(RAND_GEN, RAND_GEN, random_linear_operator));
			}
		}
	};
}

#endif
