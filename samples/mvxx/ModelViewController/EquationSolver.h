#pragma once

#include "Signals.h"

struct NoRealRoots {};
struct InfiniteNumberOfRoots {};

typedef boost::variant<NoRealRoots, InfiniteNumberOfRoots, double, std::pair<double, double>> EquationRoots;


class CEquationSolver
{
public:
	CEquationSolver();
	~CEquationSolver();

	
	sig::connection DoOnSolutionChange(const sig::signal<void()>::slot_type & handler);

	EquationRoots GetEquationRoots()const;

	double GetQuadraticCoeff()const;
	void SetQuadraticCoeff(double a);

	double GetLinearCoeff()const;
	void SetLinearCoeff(double b);

	double GetConstantCoeff()const;
	void SetConstantCoeff(double c);
private:
	double m_a = 0;
	double m_b = 0;
	double m_c = 0;

	sig::signal<void()> m_solutionChanged;
};

