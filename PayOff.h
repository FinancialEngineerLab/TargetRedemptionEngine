class PayOff 
{
public:
    PayOff(const boost::shared_ptr<const PayOffFunction>& payOffFunction);
    ~PayOff();

    double operator()(const boost::numeri::ublas::vector<double>& underlyings);
    
private:
};

