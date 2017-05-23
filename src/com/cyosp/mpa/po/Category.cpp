/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Category.hpp>

namespace mpapo
{

    // Check if a category exists with the same name before to set the category name
    // methode update() must be called manually after this method
    void Category::setName(int accountId, string name)
    {
        int categoryId = mpa::Category::getCategoryId(accountId, name);

        //MPA_LOG_TRIVIAL(trace,"setName1");
        //usleep( 10000000 );
        //MPA_LOG_TRIVIAL(trace,"setName2");

        if( categoryId == 0 )
        {
            this->name = name;
            updateVersion();
        }
        else
            throw mpa_exception::MsgNotTranslated(CATEGORY_SAME_NAME_ALREADY_EXIST);
    }

    void Category::setAmount(float amount)
    {
        this->amount = amount;
        updateVersion();
    }

    void Category::addToAmount(float amount)
    {
        this->amount = this->amount + amount;
        updateVersion();
    }

}

