/* TestNormal.cpp

First program test the Boost statistics library.

Look at the Normal distribution because it is important.
And gamma distribution

[including exponential and poisson distributions]

2008-6-27 DD initial code
2011-11-9 DD for QN course

(C) Datasim Education BV 2009-2011
*/

#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/gamma.hpp>
#include <boost/math/distributions.hpp> // For non-member functions of distributions

#include <vector>
#include <iostream>
using namespace std;


int main()
{
	// Don't forget to tell compiler which namespace
	using namespace boost::math;

	cout << "\n\n"
		<< "|=================================================|\n"
		<< "|      Normal and Exponential Distributions:      |\n"
		<< "|=================================================|\n\n";

	normal_distribution<> myNormal(1.0, 10.0); // Default type is 'double'
	cout << "Normal Mean: " << mean(myNormal) 
		<< ", Normal standard deviation: " << standard_deviation(myNormal) << endl;

	exponential_distribution<> myExponential(0.5); // Default type is 'double'
	cout << "Exponential Mean: " << mean(myExponential) 
		<< ", Exponential standard deviation: " 
		<< standard_deviation(myExponential) << endl;

	// Distributional properties
	double x = 10.25;
	double exp_x = 3;

	cout << "\nNormal pdf: " << pdf(myNormal, x) << endl;
	cout << "Normal cdf: " << cdf(myNormal, x) << endl;
	cout << "\nExponential pdf: " << pdf(myExponential, exp_x) << endl;
	cout << "Exponential cdf: " << cdf(myExponential, exp_x) << endl;

	// Choose another data type 
	float exp2_x = 3;
	exponential_distribution<float> myExponential2(1.5);
	cout << "\nExponential2 Mean: " << mean(myExponential2) 
		<< ", standard deviation: " << standard_deviation(myExponential2) << endl;
	cout << "Exponential2 pdf: " << pdf(myExponential2, exp2_x) << endl;
	cout << "Exponential2 cdf: " << cdf(myExponential2, exp2_x) << endl;

	// Other properties
	cout.precision(10);		// For normal and exponential distributions 

	cout << "\n\nOther properties\n\n";
	cout << "***normal distribution:\n";
	cout << "mean: " << mean(myNormal) << endl;
	cout << "variance: " << variance(myNormal) << endl;
	cout << "median: " << median(myNormal) << endl;
	cout << "mode: " << mode(myNormal) << endl;
	cout << "kurtosis excess: " << kurtosis_excess(myNormal) << endl;
	cout << "kurtosis: " << kurtosis(myNormal) << endl;
	cout << "characteristic function: " << chf(myNormal, x) << endl;
	cout << "hazard: " << hazard(myNormal, x) << endl;
	
	cout << "\n***exponential distribution: \n";
	cout << "mean: " << mean(myExponential) << endl;
	cout << "variance: " << variance(myExponential) << endl;
	cout << "median: " << median(myExponential) << endl;
	cout << "mode: " << mode(myExponential) << endl;
	cout << "kurtosis excess: " << kurtosis_excess(myExponential) << endl;
	cout << "kurtosis: " << kurtosis(myExponential) << endl;
	cout << "characteristic function: " << chf(myExponential, exp_x) << endl;
	cout << "hazard: " << hazard(myExponential, exp_x) << endl;

	cout.precision(7);		// For exponential2 distributions which uses floats
	cout << "\n***exponential2 distribution: \n";
	cout << "mean: " << mean(myExponential2) << endl;
	cout << "variance: " << variance(myExponential2) << endl;
	cout << "median: " << median(myExponential2) << endl;
	cout << "mode: " << mode(myExponential2) << endl;
	cout << "kurtosis excess: " << kurtosis_excess(myExponential2) << endl;
	cout << "kurtosis: " << kurtosis(myExponential2) << endl;
	cout << "characteristic function: " << chf(myExponential2, exp_x) << endl;
	cout << "hazard: " << hazard(myExponential2, exp_x) << endl;

	
	// Gamma and Poisson distributions
	cout << "\n\n"
		<< "|============================================|\n"
		<< "|      Gamma and Poisson Distributions:      |\n"
		<< "|============================================|\n\n";

	double alpha = 3.0; // Shape parameter, k
	double beta = 0.5;	// Scale parameter, theta
	double lambda = 5.0;	// mean rate for poisson distribution
	gamma_distribution<double> myGamma(alpha, beta);
	poisson_distribution<double> myPoisson(lambda);

	double val = 13.0;
	cout << "Gamma pdf: " << pdf(myGamma, val) << endl;
	cout << "Poisson pdf: " << pdf(myPoisson, val) << endl;
	cout << "Gamma cdf: " << cdf(myGamma, val) << endl;
	cout << "Poisson cdf: " << cdf(myPoisson, val) << endl;

	vector<double> gamma_pdfList;
	vector<double> gamma_cdfList;

	vector<double> poisson_pdfList;
	vector<double> poisson_cdfList;

	double start = 0.0;
	double end = 10.0;
	long N = 30;		// Number of subdivisions

	val = 0.0;
	double h = (end - start) / double(N);

	for (long j = 1; j <= N; ++j)
	{
		gamma_pdfList.push_back(pdf(myGamma, val));
		gamma_cdfList.push_back(cdf(myGamma, val));

		poisson_pdfList.push_back(pdf(myPoisson, val));
		poisson_cdfList.push_back(cdf(myPoisson, val));

		val += h;
	}

	cout << "\nGamma pdflist:\n";
	cout << gamma_pdfList[0];
	for (unsigned long j = 1; j < gamma_pdfList.size(); ++j)
	{
		cout << ", " << gamma_pdfList[j];
	}

	cout << "\n\nPoisson pdflist:\n";
	cout << poisson_pdfList[0];
	for (unsigned long j = 1; j < poisson_pdfList.size(); ++j)
	{
		cout << ", " << poisson_pdfList[j];
	}

	cout << "\n\n***" << endl;

	cout << "\nGamma cdflist:\n";
	cout << gamma_cdfList[0];
	for (unsigned long j = 1; j < gamma_cdfList.size(); ++j)
	{
		cout << ", " << gamma_cdfList[j];
	}

	cout << "\n\nPoisson cdflist:\n";
	cout << poisson_cdfList[0];
	for (unsigned long j = 1; j < poisson_cdfList.size(); ++j)
	{
		cout << ", " << poisson_cdfList[j];
	}

	cout << "\n\n***\n" << endl;
	
	return 0;
}