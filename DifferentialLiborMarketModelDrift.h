#include "DifferentialDrift.h"
#include "Maturities.h"

class DifferentialLiborMarketModelDrift : public DifferentialDrift {
public:
    /**************************************************************************
     * Constructers and Destructer.
     **************************************************************************/
    DifferentialLiborMarketModelDrift(
        const boost::numeric::ublas::matrix<double>& volatilities,
        const boost::shared_ptr<const Maturities>& maturities,
        const std::size_t dimension);
    virtual ~DifferentialLiborMarketModelDrift();

    virtual void calculate(
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& result);
    
private:
    boost::numeric::ublas::matrix<double> _volatilities;
    const boost::shared_ptr<const Maturities> _maturities;
    const std::size_t _dimension;

    bool isBeforeMaturity(
        const double time,
        const std::size_t liborIndex) const;

    void calculateDifferentialElement( 
        const double time,
        const boost::numeric::ublas::vector<double>& states,
        boost::numeric::ublas::matrix<double>& result,
        const std::size_t rowIndex1);
    
};

