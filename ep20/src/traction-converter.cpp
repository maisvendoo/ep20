#include    "traction-converter.h"

//------------------------------------------------------------------------------
// Конструктор
//------------------------------------------------------------------------------
TractionConverter::TractionConverter(QObject *parent) : Device (parent)
  ,Udc_in(0)
  ,K4QS(0)
  ,U4(0)
{
    std::fill(Ut.begin(), Ut.end(), 0);
    std::fill(U4QS.begin(), U4QS.end(), 0);
    std::fill(Udc.begin(), Udc.end(), 0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
TractionConverter::~TractionConverter()
{

}

void TractionConverter::setUt(double Ut, size_t i)
{
    if (i < this->Ut.size())
        this->Ut[i] = Ut;
}

void TractionConverter::setUdcIn(double Udc_in)
{
    this->Udc_in = Udc_in;
}

double TractionConverter::getU4()
{
    return U4;
}

void TractionConverter::preStep(state_vector_t &Y, double t)
{

    for (size_t i = 0; i < U4QS.size(); ++i)
    {
        U4QS[i] = K4QS * Ut[i];
        Udc[i] = max(U4QS[i], Udc_in);
    }

    U4 = Udc[1];
}

void TractionConverter::ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t)
{

}

void TractionConverter::load_config(CfgReader &cfg)
{

}
