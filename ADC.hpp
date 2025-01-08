namespace ADC
{
    using Voltage = double;
    class IADC
    {
    public:
        virtual Voltage Read() = 0;
    };
} // namespace ADC
