#pragma once

class PresentValueCalculator 
{
public:
    /**************************************************************************
     * Constructers and Destructers.
     **************************************************************************/
    PresentValueCalculator(
        const boost::shared_ptr<const CashFlow>& cashFlow,
        const boost::numeric::ublas::vector<double>& discountFactors);
    virtual ~PresentValueCalculator();

    virtual double PresentValueCalculator::calculatePresentValue(
        const boost::numeric::ublas::matrix<double>& path) const;
private:
    const boost::shared_ptr<const CashFlow> _cashFlow;
    const boost::numeric::ublas::vector<double> _discountFactors;
            
};

