#ifndef _CAD_MATRIX_VECTOR
#define _CAD_MATRIX_VECTOR

#include <iostream>
#include <array>
#include <algorithm>

namespace mv
{
	template <typename _type, std::size_t _dim> 
	class vector final
	{
	public:
		std::array<_type, _dim> _data;

		template <typename _elem, typename ..._args>
		void _fill(std::size_t index, const _elem& first, const _args&... other) noexcept
		{
			static_assert(sizeof...(other) < _dim, "list overflow");
			_data[index] = static_cast<_type>(first);
			_fill(index + 1, other...);
		}

		template <typename _elem>
		void _fill(std::size_t index, const _elem& last) noexcept { _data[index] = static_cast<_type>(last); }

		std::size_t _hash(const std::string& key) const noexcept
		{
			if (key == "x") return 0;
			if (key == "y") return 1;
			if (key == "z") return 2;
			if (key == "w") return 3;
			return _data.size();
		}

		friend class vector;
	public:
		using value_type				= _type;

		using iterator					= decltype(_data.begin());
		using const_iterator			= decltype(_data.cbegin());
		using reverse_iterator			= decltype(_data.rbegin());
		using const_reverse_iterator	= decltype(_data.crbegin());

		vector() noexcept : _data() {}

		explicit vector(const _type& value) noexcept 
		{ for (auto i = _data.begin(); i != _data.end(); *i = value, ++i); }

		template <typename ..._args>
		vector(const _args&... values) noexcept : _data() { _fill(0, values...); }

		template <typename _other_type>
		vector(const vector<_other_type, _dim>& other) noexcept 
		{ std::copy(other.cbegin(), other.cend(), _data.begin()); }

		template <typename _other_type>
		vector<_type, _dim>& operator=(const vector<_other_type, _dim>& other) noexcept
		{
			std::copy(other.cbegin(), other.cend(), _data.begin());
			return *this;
		}

		vector(const vector<_type, _dim>&) = default;
		vector<_type, _dim>& operator=(const vector<_type, _dim>&) = default;

		vector(vector<_type, _dim>&&) = default;
		vector& operator=(vector<_type, _dim>&&) = default;

		iterator				begin()		noexcept			{ return _data.begin();		}
		iterator				end()		noexcept			{ return _data.end();		}
		const_iterator			cbegin()	const noexcept		{ return _data.cbegin();	}
		const_iterator			cend()		const noexcept		{ return _data.cend();		}
		reverse_iterator		rbegin()	noexcept			{ return _data.rbegin();	}
		reverse_iterator		rend()		noexcept			{ return _data.rend();		}
		const_reverse_iterator	crbegin()	const noexcept		{ return _data.crbegin();	}
		const_reverse_iterator	crend()		const noexcept		{ return _data.crend();		}

		constexpr std::size_t dim() const noexcept { return _dim; }
		const _type* ptr() const noexcept { return _data.data(); }

		_type& operator[](std::size_t index) noexcept { return _data[index]; }
		const _type& operator[](std::size_t index) const noexcept { return _data[index]; }

		_type& operator[](const std::string& key) noexcept { return _data[_hash(key)]; }
		const _type& operator[](const std::string& key) const noexcept { return _data[_hash(key)]; }

		vector<_type, _dim>& operator+=(const vector<_type, _dim>& other) noexcept
		{
			for (std::size_t i = 0; i < _dim; ++i)
				_data[i] += other._data[i];
			return *this;
		}

		vector<_type, _dim>& operator-=(const vector<_type, _dim>& other) noexcept
		{
			for (std::size_t i = 0; i < _dim; ++i)
				_data[i] -= other._data[i];
			return *this;
		}
	};

	using vec2		= vector<double, 2>;
	using vec3		= vector<double, 3>;
	using vec4		= vector<double, 4>;
	
	using vec2f		= vector<float, 2>;
	using vec3f		= vector<float, 3>;
	using vec4f		= vector<float, 4>;

	using vec2i		= vector<int, 2>;
	using vec3i		= vector<int, 3>;
	using vec4i		= vector<int, 4>;

	using size2		= vector<std::size_t, 2>;
	using size3		= vector<std::size_t, 3>;

	template <typename _type, std::size_t _row, std::size_t _column>
	class matrix final
	{
	private:
		std::array<_type, _row * _column> _data;

		template <typename _elem, typename ..._args>
		void _fill(std::size_t index, const _elem& first, const _args&... other) noexcept
		{
			static_assert(sizeof...(other) < _row * _column, "list overflow");
			_data[index] = static_cast<_type>(first);
			_fill(index + 1, other...);
		}

		template <typename _elem>
		void _fill(std::size_t index, const _elem& last) noexcept { _data[index] = static_cast<_type>(last); }

		std::size_t _hash(const std::string& key) const noexcept
		{
			if (key == "x")  return 0;
			if (key == "xy") return 1;
			if (key == "xz") return 2;
			if (key == "xw") return 3;
			if (key == "yx") return 0 + _column;
			if (key == "y")  return 1 + _column;
			if (key == "yz") return 2 + _column;
			if (key == "yw") return 3 + _column;
			if (key == "zx") return 0 + 2 * _column;
			if (key == "zy") return 1 + 2 * _column;
			if (key == "z")  return 2 + 2 * _column;
			if (key == "zw") return 3 + 2 * _column;
			if (key == "wx") return 0 + 3 * _column;
			if (key == "wy") return 1 + 3 * _column;
			if (key == "wz") return 2 + 3 * _column;
			if (key == "w")  return 3 + 3 * _column;
			return _data.size();
		}

		friend class matrix;
	public:
		using value_type				= _type;

		using iterator					= decltype(_data.begin());
		using const_iterator			= decltype(_data.cbegin());
		using reverse_iterator			= decltype(_data.rbegin());
		using const_reverse_iterator	= decltype(_data.crbegin());

		matrix() noexcept : _data()
		{
			if constexpr (_row == _column)
				for (std::size_t i = 0; i < _row; _data[i + i * _column] = static_cast<_type>(1.0), ++i);
		}

		explicit matrix(const _type& value) noexcept : _data()
		{
			if constexpr (_row == _column)
				for (std::size_t i = 0; i < _row; _data[i + i * _column] = value, ++i);
			else
				for (std::size_t i = 0; i < _row * _column; _data[i] = value, ++i);
		}

		explicit matrix(const vector<_type, _row>& values) noexcept : _data()
		{
			static_assert(_row == _column, "matrix is not square");
			for (std::size_t i = 0; i < _row; ++i)
				_data[i + i * _column] = values[i];
		}

		template <typename ..._args>
		matrix(const _args&... values) noexcept : _data() { _fill(0, values...); }

		template <typename _other_type>
		matrix(const matrix<_other_type, _row, _column>& other) noexcept
		{ std::copy(other.cbegin(), other.cend(), _data.begin()); }

		template <typename _other_type>
		matrix<_type, _row, _column>& operator=(const matrix<_other_type, _row, _column>& other) noexcept
		{
			std::copy(other.cbegin(), other.cend(), _data.begin());
			return *this;
		}

		matrix(const matrix<_type, _row, _column>&) = default;
		matrix<_type, _row, _column>& operator=(const matrix<_type, _row, _column>&) = default;

		matrix(matrix<_type, _row, _column>&&) = default;
		matrix& operator=(matrix<_type, _row, _column>&&) = default;

		iterator				begin()		noexcept			{ return _data.begin();	  }
		iterator				end()		noexcept			{ return _data.end();	  }
		const_iterator			cbegin()	const noexcept		{ return _data.cbegin();  }
		const_iterator			cend()		const noexcept		{ return _data.cend();    }
		reverse_iterator		rbegin()	noexcept			{ return _data.rbegin();  }
		reverse_iterator		rend()		noexcept			{ return _data.rend();    }
		const_reverse_iterator	crbegin()	const noexcept		{ return _data.crbegin(); }
		const_reverse_iterator	crend()		const noexcept		{ return _data.crend();   }

		constexpr std::size_t row() const noexcept { return _row; }
		constexpr std::size_t column() const noexcept { return _column; }
		const _type* ptr() const noexcept { return _data.data(); }

		_type* operator[](std::size_t index) noexcept { return _data.data() + index * _column; }
		const _type* operator[](std::size_t index) const noexcept { return _data.data() + index * _column; }

		_type& operator[](const std::string& key) noexcept { return _data[_hash(key)]; }
		const _type& operator[](const std::string& key) const noexcept { return _data[_hash(key)]; }

		matrix<_type, _row, _column>& operator+=(const matrix<_type, _row, _column>& other) noexcept
		{
			for (std::size_t i = 0; i < _row * _column; ++i)
				_data[i] += other._data[i];
			return *this;
		}

		matrix<_type, _row, _column>& operator-=(const matrix<_type, _row, _column>& other) noexcept
		{
			for (std::size_t i = 0; i < _row * _column; ++i)
				_data[i] -= other._data[i];
			return *this;
		}
	};

	using mat2		= matrix<double, 2, 2>;
	using mat3		= matrix<double, 3, 3>;
	using mat4		= matrix<double, 4, 4>;

	using mat2f		= matrix<float, 2, 2>;
	using mat3f		= matrix<float, 3, 3>;
	using mat4f		= matrix<float, 4, 4>;

	using mat2i		= matrix<int, 2, 2>;
	using mat3i		= matrix<int, 3, 3>;
	using mat4i		= matrix<int, 4, 4>;

	template <typename _type, std::size_t _dim>
	std::istream& operator>>(std::istream& stream, vector<_type, _dim>& vec)
	{
		for (auto i = vec.begin(); i != vec.end(); ++i)
			stream >> *i;
		return stream;
	}

	template <typename _type, std::size_t _dim>
	std::ostream& operator<<(std::ostream& stream, const vector<_type, _dim>& vec)
	{
		for (auto i = vec.cbegin(); i != vec.cend(); ++i)
			stream << *i << "  ";
		return stream;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	std::istream& operator>>(std::istream& stream, matrix<_type, _row, _column>& mat)
	{
		for (auto i = mat.begin(); i != mat.end(); ++i)
			stream >> *i;
		return stream;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	std::ostream& operator<<(std::ostream& stream, const matrix<_type, _row, _column>& mat)
	{
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
				stream << mat[i][j] << "  ";
			stream << std::endl;
		}
		return stream;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> operator+(const vector<_type, _dim>& a, const vector<_type, _dim>& b) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; ++i)
			result[i] = a[i] + b[i];
		return result;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> operator-(const vector<_type, _dim>& a, const vector<_type, _dim>& b) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; ++i)
			result[i] = a[i] - b[i];
		return result;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> operator*(const vector<_type, _dim>& a, const _type& scalar) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; ++i)
			result[i] = a[i] * scalar;
		return result;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> operator*(const _type& scalar, const vector<_type, _dim>& a) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; ++i)
			result[i] = a[i] * scalar;
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	matrix<_type, _row, _column> operator+(
		const matrix<_type, _row, _column>& A, const matrix<_type, _row, _column>& B) noexcept
	{
		matrix<_type, _row, _column> result;
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
				result[i][j] = A[i][j] + B[i][j];
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	matrix<_type, _row, _column> operator-(
		const matrix<_type, _row, _column>& A, const matrix<_type, _row, _column>& B) noexcept
	{
		matrix<_type, _row, _column> result;
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
				result[i][j] = A[i][j] - B[i][j];
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column, std::size_t _other_column>
	matrix<_type, _row, _column> operator*(
		const matrix<_type, _row, _column>& A, const matrix<_type, _column, _other_column>& B) noexcept
	{
		matrix<_type, _row, _other_column> result(0.0);
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _other_column; ++j)
			{
				for (size_t k = 0; k < _column; ++k)
					result[i][j] += A[i][k] * B[k][j];
			}
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	vector<_type, _column> operator*(
		const matrix<_type, _row, _column>& A, const vector<_type, _column>& v) noexcept
	{
		vector<_type, _column> result(0.0);
		for (std::size_t j = 0; j < _column; ++j)
		{
			for (std::size_t i = 0; i < _row; ++i)
				result[i] += v[j] * A[i][j];
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	matrix<_type, _row, _column> operator*(
		const matrix<_type, _row, _column>& A, const _type& scalar) noexcept
	{
		matrix<_type, _row, _column> result;
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
				result[i][j] = A[i][j] * scalar;
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	matrix<_type, _row, _column> operator*(
		const _type& scalar, const matrix<_type, _row, _column>& A) noexcept
	{
		matrix<_type, _row, _column> result;
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
				result[i][j] = A[i][j] * scalar;
		}
		return result;
	}

	template <typename _type, std::size_t _dim>
	bool operator==(const vector<_type, _dim>& a, const vector<_type, _dim>& b) noexcept
	{
		for (std::size_t i = 0; i < _dim; ++i)
		{
			if (a[i] != b[i])
				return false;
		}
		return true;
	}

	template <typename _type, std::size_t _dim>
	bool operator!=(const vector<_type, _dim>& a, const vector<_type, _dim>& b) noexcept { return !(a == b); }

	template <typename _type, std::size_t _row, std::size_t _column>
	bool operator==(const matrix<_type, _row, _column>& A,
		const matrix<_type, _row, _column>& B) noexcept
	{
		for (std::size_t i = 0; i < _row; ++i)
		{
			for (std::size_t j = 0; j < _column; ++j)
			{
				if (A[i][j] != B[i][j])
					return false;
			}
		}
		return true;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	bool operator!=(const matrix<_type, _row, _column>& A,
		const matrix<_type, _row, _column>& B) noexcept { return !(A == B); }

	double rad(double deg_angle) noexcept { return deg_angle * (std::acos(-1.0) / 180.0); }
	double deg(double rad_angle) noexcept { return rad_angle * 180.0 / std::acos(-1.0);   }

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> rad(vector<_type, _dim> vec_of_deg_angle) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; result[i] = rad(vec_of_deg_angle[i]), ++i);
		return result;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> deg(vector<_type, _dim> vec_of_rad_angle) noexcept
	{
		vector<_type, _dim> result;
		for (std::size_t i = 0; i < _dim; result[i] = deg(vec_of_rad_angle[i]), ++i);
		return result;
	}

	template <typename _type, std::size_t _dim>
	double length(const vector<_type, _dim>& vec) noexcept
	{
		double result = 0.0;
		for (std::size_t i = 0; i < _dim; result += vec[i] * vec[i], ++i);
		return std::sqrt(result);
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim> normalize(const vector<_type, _dim>& vec) noexcept
	{
		vector<_type, _dim> result;
		double len = length(vec);
		for (std::size_t i = 0; i < _dim; result[i] = vec[i] / len, ++i);
		return result;
	}

	template <typename _type, size_t _current_row, size_t _current_column>
	double det(const matrix<_type, _current_row, _current_column>& mat) noexcept
	{
		if constexpr (_current_row != _current_column)
			return 0.0;
		constexpr std::size_t n = _current_row;
		if constexpr (n <= 1)
			return mat[0][0];
		else if constexpr (n == 2)
			return (mat["x"] * mat["y"]) - (mat["xy"] * mat["yx"]);
		else
		{
			double result = 0.0;
			for (std::size_t k = 0; k < n; k++)
			{
				matrix<_type, _current_row - 1, _current_column - 1> minor;
				for (std::size_t i = 0; i < n - 1; i++)
				{
					bool column = false;
					for (std::size_t j = 0; j < n - 1; j++)
					{
						if (j == k) column = true;
						minor[i][j] = column ? mat[i + 1][j + 1] : mat[i + 1][j];
					}
				}
				result += pow(-1.0, k) * det(minor) * mat[0][k];
			}
			return result;
		}
	}

	template <typename _type, std::size_t _dim>
	double dot(const vector<_type, _dim>& a, const vector<_type, _dim>& b) noexcept
	{
		double result;
		for (std::size_t i = 0; i < _dim; ++i)
			result += a[i] * b[i];
		return result;
	}

	template <typename _type>
	vector<_type, 3> cross(const vector<_type, 3>& a, const vector<_type, 3>& b) noexcept
	{
		matrix<_type, 2, 2> mat_i = {
			a["y"], b["y"],
			a["z"], b["z"]
		};
		matrix<_type, 2, 2> mat_j = {
			a["x"], b["x"],
			a["z"], b["z"]
		};
		matrix<_type, 2, 2> mat_k = {
			a["x"], b["x"],
			a["y"], b["y"]
		};
		return { det(mat_i), -det(mat_j), det(mat_k) };
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim - 1> low(const vector<_type, _dim>& v) noexcept
	{
		vector<_type, _dim - 1> result;
		for (std::size_t i = 0; i < _dim - 1; ++i)
			result[i] = v[i];
		return result;
	}

	template <typename _type, std::size_t _dim>
	matrix<_type, _dim - 1, _dim - 1> low(const matrix<_type, _dim, _dim>& M) noexcept
	{
		matrix<_type, _dim - 1, _dim - 1> result;
		for (std::size_t i = 0; i < _dim - 1; ++i)
		{
			for (std::size_t j = 0; j < _dim - 1; ++j)
				result[i][j] = M[i][j];
		}
		return result;
	}

	template <typename _type, std::size_t _dim>
	vector<_type, _dim + 1> high(const vector<_type, _dim>& v, const _type& lost) noexcept
	{
		vector<_type, _dim + 1> result;
		for (std::size_t i = 0; i < _dim; ++i)
			result[i] = v[i];
		result[_dim] = lost;
		return result;
	}

	template <typename _type, std::size_t _dim>
	matrix<_type, _dim + 1, _dim + 1> high(
		const matrix<_type, _dim, _dim>& M, const _type& lost) noexcept
	{
		matrix<_type, _dim + 1, _dim + 1> result(0.0);
		for (std::size_t i = 0; i < _dim; ++i)
		{
			for (std::size_t j = 0; j < _dim; ++j)
				result[i][j] = M[i][j];
		}
		result[_dim][_dim] = lost;
		return result;
	}

	template <typename _type, std::size_t _dim>
	matrix<_type, _dim, _dim> transpose(const matrix<_type, _dim, _dim>& M) noexcept
	{
		matrix<_type, _dim, _dim> result;
		for (std::size_t i = 0; i < _dim; ++i)
		{
			for (std::size_t j = 0; j < _dim; ++j)
				result[i][j] = M[j][i];
		}
		return result;
	}

	template <typename _type, std::size_t _row, std::size_t _column>
	matrix<_type, _row, _column> change(
		const matrix<_type, _row, _column>& M, const matrix<_type, _row, _column>& basis) noexcept
	{
		return tranpose(basis) * M * basis;
	}

	template <typename _type>
	matrix<_type, 3, 3> rotate_euler(const vector<_type, 3>& angles) noexcept
	{
		matrix<_type, 3, 3> psi = {
			std::cos(angles["x"]), 0.0, -std::sin(angles["x"]),
			0.0, 1.0, 0.0,
			std::sin(angles["x"]), 0.0, std::cos(angles["x"])
		};
		matrix<_type, 3, 3> theta = {
			std::cos(angles["y"]), std::sin(angles["y"]), 0.0,
			-std::sin(angles["y"]), std::cos(angles["y"]), 0.0,
			0.0, 0.0, 1.0
		};
		matrix<_type, 3, 3> gamma = {
			1.0, 0.0, 0.0,
			0.0, std::cos(angles["z"]), std::sin(angles["z"]),
			0.0, -std::sin(angles["z"]), std::cos(angles["z"])
		};
		matrix<_type, 3, 3> result = gamma * theta * psi;
		return transpose(result);
	}

	template <typename _type>
	matrix<_type, 3, 3> scale(const vector<_type, 3>& scalars) noexcept
	{
		return {
			scalars["x"], 0.0, 0.0,
			0.0, scalars["y"], 0.0,
			0.0, 0.0, scalars["z"]
		};
	}

	template <typename _type>
	matrix<_type, 4, 4> move(const vector<_type, 3>& radius) noexcept
	{
		return {
			1.0, 0.0, 0.0, radius["x"],
			0.0, 1.0, 0.0, radius["y"],
			0.0, 0.0, 1.0, radius["z"],
			0.0, 0.0, 0.0, 1.0
		};
	}
}

#endif
