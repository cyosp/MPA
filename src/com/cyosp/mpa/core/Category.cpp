/*
 * Category.cpp
 *
 *  Created on: 25 March 2015
 *      Author: cyosp
 */

#include <com/cyosp/mpa/core/Category.hpp>

namespace mpa
{
    // Return 0 if doesn't exist, Category ID otherwise
    int Category::getCategoryId(int accountId, string categoryName)
    {
        int ret = 0;

        vector<mpapo::Category> categories = all(accountId);
        // Get categories iterator
        vector<mpapo::Category>::iterator it = categories.begin();

        while( it != categories.end() && !ret )
        {
            mpapo::Category category = (*it);

            if( category.name == categoryName )
                ret = category.id;
            else
                it++;
        }

        return ret;
    }

    // Get category in all cases
    // Create one if no existing
    mpapo::Category Category::get(int accountId, string categoryName)
    {
        // Get category Id
        int categoryId = getCategoryId(accountId, categoryName);

        // Create because it doesn't exist
        if( categoryId == 0 )
        {
            mpapo::Category category(MPA::getInstance()->getMPAPO());
            category.initializeVersion();
            category.setName(accountId, categoryName);
            category.setAmount(0);

            mpapo::Account::CategoriesHandle categoriesHandle = mpa::Account::get(accountId).categories();

            // Transaction contains only database modification in order to reduce transaction time
            MPA::getInstance()->beginTransaction();
            try
            {
                category.update();
                categoriesHandle.link(category);
                MPA::getInstance()->commitTransaction();

                categoryId = category.id;
                MPA_LOG_TRIVIAL(trace, "Category ID added: " + categoryId);
            }
            catch( Except & e )
            {
                MPA::getInstance()->rollbackTransaction();
            }

        }

        return get(categoryId);
    }

    // Get categories following an account identified by ID
    vector<mpapo::Category> Category::all(int accountId)
    {
        return mpa::Account::get(accountId).categories().get().all();
    }

    mpapo::Category Category::get(int categoryId)
    {
        return select<mpapo::Category>(MPA::getInstance()->getMPAPO(), mpapo::Category::Id == categoryId).one();
    }

    void Category::del(int id, int version)
    {
        try
        {
            mpapo::Category category = Category::get(id);

            if( category.isCorrectVersion(version) )
            {
                if( category.operationDetails().get().all().size() > 0 )
                    throw mpa_exception::MsgNotTranslated(IMPOSSIBLE_REMOVE_THERE_ARE_AGAIN_OPERATIONS);

                if( category.account().get().all().size() > 0 )
                {
                    mpapo::Account account = category.account().get().one();

                    MPA::getInstance()->beginTransaction();
                    try
                    {
                        //mpa::Account::getAccount( accountId ).categories().unlink( category );
                        category.account().unlink(account);
                        category.del();
                        MPA::getInstance()->commitTransaction();
                    }
                    catch( Except & e )
                    {
                        MPA::getInstance()->rollbackTransaction();
                    }
                }
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
        }
    }

    // Rename category
    mpapo::Category Category::rename(int accountId, int categoryId, int categoryVersion, string newName)
    {
        //MPA_LOG_TRIVIAL( trace , "Start" );

        try
        {
            mpapo::Category category = get(categoryId);

            if( category.isCorrectVersion(categoryVersion) )
            {
                category.setName(accountId, newName);
                category.updateVersion();
                category.update();

                //MPA_LOG_TRIVIAL( trace , "End" );

                // Return is here because there is no empty constructor for mpapo::Category::Category()
                return category;
            }
            else
                throw mpa_exception::MsgNotTranslated(OPERATION_IMPOSSIBLE_BECAUSE_DATA_HAVE_CHANGED);
        }
        catch( NotFound & e )
        {
            throw mpa_exception::MsgNotTranslated(ACCOUNT_DOESNT_EXIST);
        }
    }

    Category::~Category()
    {
    }

}

