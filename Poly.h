
#include <iostream>
#include <cmath>

using namespace std;

class Poly
{
    private:
        double* coeffs;
        int size;

    public:
        // Konstruktor
        Poly(double val = 0)
        {
            coeffs = (double*) malloc(sizeof(double));

            if(!coeffs)
            {
                cout << "Allocation failed!" << endl;
                exit(1);
            }

            coeffs[0] = val;
            size = 1;
        }

		Poly(const Poly& p1)
		{
			coeffs = (double*) malloc(p1.size * sizeof(double));
			
			if(!coeffs)
            {
                cout << "Allocation failed!" << endl;
                exit(1);
            }
            
            for(int i=0; i<p1.size; i++)
				coeffs[i] = p1.coeffs[i];
				
			size = p1.size;
		}

        // Destruktor
        ~Poly()
        {
            free(this->coeffs);
        }

        // Negacja
        Poly operator-() const
        {
            Poly x;

            for(int i=0; i<this->size; i++)
                x[i] =  this->coeffs[i] * -1;

            x.size = this->size;

            return x;
        }

        // Operator przypisania Poly do Poly
        Poly& operator=(const Poly& p1)
        {

            // p0 = p1;

            double* wsk = (double*) realloc(this->coeffs, p1.size * sizeof(double));
            if(!wsk)
            {
                cout << "Allocation failed!\n";
                exit(1);
            }

            this->coeffs = wsk;
            this->size = p1.size;

            for(int i=0; i<this->size; i++)
                 this->coeffs[i] = p1.coeffs[i];

            return *this;
        };

        // Operator []
        double& operator[](const int deg)
        {
            if(deg >= size)
            {
                int temp = size;
                size = deg+1;
                double* wsk = (double*)realloc(coeffs, size * sizeof(double));

                if(!wsk)
                {
                    cout << "Allocation failed!" << endl;
                    exit(1);
                }

                coeffs = wsk;

                for(int i=temp; i<=deg; i++)
                    coeffs[i] = 0;
            }

            return coeffs[deg];
        }

        // cout
        friend ostream& operator<<(ostream& out, const Poly& polyval)
        {
            int zeros=0;

            for(int i = polyval.size-1; i >= 0; i--)
            {
                if(polyval.coeffs[i] == 0)
                {
                    zeros++;
                    continue;
                }

                double temp = polyval.coeffs[i];

                if(temp >= 0 && i != polyval.size-1)
                    out << "+ ";

                else if(temp < 0 && i != polyval.size-1)
                {
                    temp = abs(temp);
                    out << "- ";
                }

                if(temp == 1 && i == 1)
                {
                    out << "x" << " ";
                    continue;
                }

                if(temp == 1 && i != 0)
                {
                    out << "x^" << i << " ";
                    continue;
                }

                if(temp == -1 && i == 1)
                {
                    out << "-x" << " ";
                    continue;
                }

                if(temp == -1 && i != 0)
                {
                    out << "-x^" << i << " ";
                    continue;
                }

                switch(i)
                {
                    case 1:
                        out << temp << "x" << " ";
                        break;

                    case 0:
                        out << temp;
                        break;

                    default:
                        out << temp << "x^" << i << " ";
                        break;
                }
            }

            if(zeros == polyval.size)
                out << "0";

            return out;
        };

        // Liczenie wartości
        double operator()(double val) const
        {
            double result = 0;

            for(int i = this->size-1; i >= 0; i--)
                result += this->coeffs[i] * pow(val, i);

            return result;
        }

        // Dodawanie
        Poly operator+(const Poly& p1) const
        {
            Poly x;
            int i;

            if(this->size > p1.size)
            {
                for(i=0; i<p1.size; i++)
                    x[i] = this->coeffs[i] + p1.coeffs[i];

                for(; i<this->size; i++)
                    x[i] = this->coeffs[i];
            }

            else
            {
                for(i=0; i<this->size; i++)
                    x[i] = this->coeffs[i] + p1.coeffs[i];

                for(; i<p1.size; i++)
                    x[i] = p1.coeffs[i];
            }

            return x;
        }

        // Odejmowanie
        Poly operator-(const Poly& p1) const
        {
            Poly p2;
            int i;

            if(this->size > p1.size)
            {
                for(i=0; i<p1.size; i++)
                    p2[i] = this->coeffs[i] - p1.coeffs[i];

                for(; i<this->size; i++)
                    p2[i] = this->coeffs[i];
            }

            else
            {
                for(i=0; i<this->size; i++)
                    p2[i] = this->coeffs[i] - p1.coeffs[i];

                for(; i<p1.size; i++)
                    p2[i] = p1.coeffs[i] * -1;
            }

            return p2;
        }

        // Mnożenie
        Poly operator*(const Poly& p1) const
        {
            Poly x;

            for(int i=0; i<this->size; i++)
            {
                for(int j=0; j<p1.size; j++)
                {
                    x[i+j] += this->coeffs[i] * p1.coeffs[j];
                }
            }
            return x;
        }
};

inline Poly operator+(double val, const Poly& p1)
{
    Poly x = p1 + val;

    return x;
}

inline Poly operator-(double val, const Poly& p1)
{
    Poly x;

    x = -p1 + val;

    return x;
}

inline Poly operator*(double val, const Poly& p1)
{
	Poly x;
	
	x = p1 * val;

	return x;
}
