/*
 * SubOperation.cpp
 *
 *  Created on: 20 April 2015
 *      Author: cyosp
 */

#include "com/cyosp/mpa/po/MPAPO.hpp"

namespace mpapo
{
    void OperationDetail::setAmount(float amount)
    {
        this->amount = amount;
        setUpdated();
    }

    void OperationDetail::setNote(string note)
    {
        this->note = note;
        setUpdated();
    }
}
