
/*
	C++ interface(https://github.com/likev/natgrid.cpp)
	
	to NCAR natural neighbor gridding package(http://www.ncarg.ucar.edu/ngmath/natgrid/nnhome.html)
 */
#include<vector>
#include<iostream>

#ifndef _NAT_GRID
#define _NAT_GRID


namespace natgrid {

/*
 *  Function prototypes for the natgrid package.
 */
	void    c_nnseti(char *, int);
	void    c_nngeti(char *, int *);

	void    c_nnsetrd(char *, double);
	void    c_nngetrd(char *, double *);

	void    c_nnsetr(char *, float);
	void    c_nngetr(char *, float *);


	void    c_nnsetc(char *, char *);
	void    c_nngetc(char *, char *);


	float*  c_natgrids(int, float[], float[], float[],
		int, int, float[], float[], int *);

	double* c_natgridd(int, double[], double[], double[],
		int, int, double[], double[], int *);


	void    c_nngetslopes(int, int, float *, int *);
	void    c_nngetaspects(int, int, float *, int *);

	void    c_nngetsloped(int, int, double *, int *);
	void    c_nngetaspectd(int, int, double *, int *);

	void    c_nnpntinits(int, float[], float[], float[]);
	void    c_nnpntinitd(int, double[], double[], double[]);

	void    c_nnpnts(float, float, float *);
	void    c_nnpntd(double, double, double *);

	void    c_nnpntend();
	void    c_nnpntendd();

	void    c_nngetwts(int *, int *, float *, float *, float *, float *);
	void    c_nngetwtsd(int *, int *, double *, double *, double *, double *);

}

namespace natgrid {

	using std::vector;

	class natgrid
	{
		
	private:
		bool _ok = false;
		vector<double> _x,_y,_v, _xq, _yq;
		vector<vector<double> > _out;

	public:
		natgrid() {}

		natgrid(vector<double>& x,
			vector<double>& y,
			vector<double>& v) :_x(x), _y(y), _v(v) 
		{

		}

		natgrid(vector<double>& x, 
			vector<double>& y, 
			vector<double>& v, 
			
			vector<double>& xq,
			vector<double>& yq) 
			:_x(x), _y(y), _v(v), _xq(xq), _yq(yq) 
		{
		
			griddata(_x, _y, _v, _xq, _yq);
		}

		natgrid & griddata() 
		{

			return griddata(_x, _y, _v, _xq, _yq);
		}

		natgrid& x(vector<double>& ix)
		{
			_x = ix;

			return *this;
		}

		natgrid& y(vector<double>& iy)
		{
			_y = iy;

			return *this;
		}

		natgrid& v(vector<double>& iv)
		{
			_v = iv;

			return *this;
		}

		natgrid& xq(vector<double>& ixq)
		{
			_xq = ixq;

			return *this;
		}

		natgrid& yq(vector<double>& iyq)
		{
			_yq = iyq;

			return *this;
		}

		natgrid& xq(double start, double end, std::size_t count)
		{
			double span = (end - start) / (count - 1), length = 0;
			
			_xq.resize(count);

			for (auto& v : _xq)
			{
				v = start + length;
				
				length += span;
			}

			return *this;
		}

		natgrid& xq(double start, double span,  double end)
		{
			_xq.clear();

			double v = start;

			while (v <= end)
			{
				_xq.push_back(v);

				v += span;
			}

			return *this;
		}

		natgrid& yq(double start, double end, std::size_t count)
		{
			double span = (end - start) / (count - 1), length = 0;

			_yq.resize(count);

			for (auto& v : _yq)
			{
				v = start + length;

				length += span;
			}

			return *this;
		}

		natgrid& yq(double start, double span, double end)
		{
			_yq.clear();

			double v = start;

			while (v <= end)
			{
				_yq.push_back(v);

				v += span;
			}

			return *this;
		}

		const vector<double>& xq()const
		{
			return _xq;
		}

		const vector<double>& yq()const
		{
			return _yq;
		}

		const vector<vector<double> > & vq()const
		{
			return _out;
		}

		natgrid & griddata(vector<double>& x,
				vector<double>& y,
				vector<double>& v,

				vector<double>& xq,
				vector<double>& yq) 
		{
			_x = x;
			_y = y;
			_v = v;

			_xq = xq;
			_yq = yq;

			auto xqSize = xq.size(), yqSize = yq.size();
			int ier;
			
			double *out = c_natgridd(_x.size(), _x.data(), _y.data(), _v.data(), xqSize, yqSize, _xq.data(), _yq.data(), &ier);
			
			if (ier != 0) 
			{
				//printf(" Error return from c_natgrids = %d\n", ier);
				_ok = false;
				
			}
			else
			{
				_ok = true;
			}


			_out.resize(xqSize);

			
			for (auto i=0;i < xqSize; ++i)
			{
				_out[i].resize(yqSize);

				for (auto j=0; j< yqSize; ++j)
				{
					_out[i][j] = out[ i * yqSize + j];
				}
			}
			
			return *this;
		}

		operator bool() const
		{
			return _ok;
		}

		operator vector<vector<double> > () const
		{
			return _out;
		}
	};

	std::ostream& operator<<(std::ostream& os, const natgrid& m)
	{
		const vector<vector<double> > & vq = m.vq();
		for (auto& row : vq)
		{
			for (auto &v : row)
			{
				std::cout<< v <<' ';
			}
			std::cout << std::endl;
		}

		return os;
	}
}

#endif // !_NAT_GRID



 
