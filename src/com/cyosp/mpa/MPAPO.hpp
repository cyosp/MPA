#ifndef mpapo_hpp
#define mpapo_hpp
#include "litesql.hpp"
#include "com/cyosp/mpa/MPAPOInclude.hpp"
namespace mpapo {
class MPAO;
class User;
class Account;
class Category;
class Provider;
class Operation;
class SubOperation;
class AccountCategoryRelation {
public:
    class Row {
    public:
        litesql::Field<int> category;
        litesql::Field<int> account;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Account;
    static const litesql::FieldType Category;
    static void link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Category& o1);
    static void unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Category& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<AccountCategoryRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class AccountProviderRelation {
public:
    class Row {
    public:
        litesql::Field<int> provider;
        litesql::Field<int> account;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Account;
    static const litesql::FieldType Provider;
    static void link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Provider& o1);
    static void unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Provider& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<AccountProviderRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class AccountOperationRelation {
public:
    class Row {
    public:
        litesql::Field<int> operation;
        litesql::Field<int> account;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Account;
    static const litesql::FieldType Operation;
    static void link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Operation& o1);
    static void unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Operation& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<AccountOperationRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class OperationProviderRelation {
public:
    class Row {
    public:
        litesql::Field<int> provider;
        litesql::Field<int> operation;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Operation;
    static const litesql::FieldType Provider;
    static void link(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::Provider& o1);
    static void unlink(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::Provider& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<OperationProviderRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class OperationSubOperationRelation {
public:
    class Row {
    public:
        litesql::Field<int> subOperation;
        litesql::Field<int> operation;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Operation;
    static const litesql::FieldType SubOperation;
    static void link(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::SubOperation& o1);
    static void unlink(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::SubOperation& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<OperationSubOperationRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class CategorySubOperationRelation {
public:
    class Row {
    public:
        litesql::Field<int> subOperation;
        litesql::Field<int> category;
        Row(const litesql::Database& db, const litesql::Record& rec=litesql::Record());
    };
    static const std::string table__;
    static const litesql::FieldType Category;
    static const litesql::FieldType SubOperation;
    static void link(const litesql::Database& db, const mpapo::Category& o0, const mpapo::SubOperation& o1);
    static void unlink(const litesql::Database& db, const mpapo::Category& o0, const mpapo::SubOperation& o1);
    static void del(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    static litesql::DataSource<CategorySubOperationRelation::Row> getRows(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr());
    template <class T> static litesql::DataSource<T> get(const litesql::Database& db, const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
;
;
};
class MPAO : public litesql::Persistent {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const std::string sequence__;
    static const litesql::FieldType Id;
    litesql::Field<int> id;
    static const litesql::FieldType Type;
    litesql::Field<std::string> type;
    static const litesql::FieldType Version;
    litesql::Field<int> version;
    static void initValues();
protected:
    void defaults();
public:
    MPAO(const litesql::Database& db);
    MPAO(const litesql::Database& db, const litesql::Record& rec);
    MPAO(const MPAO& obj);
    const MPAO& operator=(const MPAO& obj);
    virtual void initializeVersion();
    virtual void updateVersion();
    virtual bool isCorrectVersion(int versionToCheck);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<MPAO> upcast() const;
    std::auto_ptr<MPAO> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, MPAO o);
class User : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType IsAdmin;
    litesql::Field<bool> isAdmin;
    static const litesql::FieldType Login;
    litesql::Field<std::string> login;
    static const litesql::FieldType Password;
    litesql::Field<std::string> password;
    static const litesql::FieldType PwdErrNbr;
    litesql::Field<int> pwdErrNbr;
    static void initValues();
protected:
    void defaults();
public:
    User(const litesql::Database& db);
    User(const litesql::Database& db, const litesql::Record& rec);
    User(const User& obj);
    const User& operator=(const User& obj);
    virtual void setIsAdmin(bool isAdmin);
    virtual void setLogin(string login);
    virtual void setPassword(string password);
    virtual void addPwdErr();
    virtual void resetPwdErr();
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<User> upcast() const;
    std::auto_ptr<User> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, User o);
class Account : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class CategoriesHandle : public litesql::RelationHandle<Account> {
    public:
        CategoriesHandle(const Account& owner);
        void link(const Category& o0);
        void unlink(const Category& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Category> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountCategoryRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class ProvidersHandle : public litesql::RelationHandle<Account> {
    public:
        ProvidersHandle(const Account& owner);
        void link(const Provider& o0);
        void unlink(const Provider& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Provider> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountProviderRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class OperationsHandle : public litesql::RelationHandle<Account> {
    public:
        OperationsHandle(const Account& owner);
        void link(const Operation& o0);
        void unlink(const Operation& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Operation> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Balance;
    litesql::Field<float> balance;
    static void initValues();
protected:
    void defaults();
public:
    Account(const litesql::Database& db);
    Account(const litesql::Database& db, const litesql::Record& rec);
    Account(const Account& obj);
    const Account& operator=(const Account& obj);
    Account::CategoriesHandle categories();
    Account::ProvidersHandle providers();
    Account::OperationsHandle operations();
    virtual void setName(string name);
    virtual void addToBalance(float balance);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Account> upcast() const;
    std::auto_ptr<Account> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Account o);
class Category : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class AccountHandle : public litesql::RelationHandle<Category> {
    public:
        AccountHandle(const Category& owner);
        void link(const Account& o0);
        void unlink(const Account& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Account> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountCategoryRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class SubOperationsHandle : public litesql::RelationHandle<Category> {
    public:
        SubOperationsHandle(const Category& owner);
        void link(const SubOperation& o0);
        void unlink(const SubOperation& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<SubOperation> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<CategorySubOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Amount;
    litesql::Field<float> amount;
    static void initValues();
protected:
    void defaults();
public:
    Category(const litesql::Database& db);
    Category(const litesql::Database& db, const litesql::Record& rec);
    Category(const Category& obj);
    const Category& operator=(const Category& obj);
    Category::AccountHandle account();
    Category::SubOperationsHandle subOperations();
    virtual void setName(int accountId, string name);
    virtual void setAmount(float amount);
    virtual void addToAmount(float amount);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Category> upcast() const;
    std::auto_ptr<Category> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Category o);
class Provider : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class AccountHandle : public litesql::RelationHandle<Provider> {
    public:
        AccountHandle(const Provider& owner);
        void link(const Account& o0);
        void unlink(const Account& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Account> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountProviderRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class OperationsHandle : public litesql::RelationHandle<Provider> {
    public:
        OperationsHandle(const Provider& owner);
        void link(const Operation& o0);
        void unlink(const Operation& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Operation> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<OperationProviderRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType Name;
    litesql::Field<std::string> name;
    static const litesql::FieldType Amount;
    litesql::Field<float> amount;
    static void initValues();
protected:
    void defaults();
public:
    Provider(const litesql::Database& db);
    Provider(const litesql::Database& db, const litesql::Record& rec);
    Provider(const Provider& obj);
    const Provider& operator=(const Provider& obj);
    Provider::AccountHandle account();
    Provider::OperationsHandle operations();
    virtual void setName(int accountId, string name);
    virtual void setAmount(float amount);
    virtual void addToAmount(float amount);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Provider> upcast() const;
    std::auto_ptr<Provider> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Provider o);
class Operation : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class AccountHandle : public litesql::RelationHandle<Operation> {
    public:
        AccountHandle(const Operation& owner);
        void link(const Account& o0);
        void unlink(const Account& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Account> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<AccountOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class ProviderHandle : public litesql::RelationHandle<Operation> {
    public:
        ProviderHandle(const Operation& owner);
        void link(const Provider& o0);
        void unlink(const Provider& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Provider> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<OperationProviderRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class SubOperationsHandle : public litesql::RelationHandle<Operation> {
    public:
        SubOperationsHandle(const Operation& owner);
        void link(const SubOperation& o0);
        void unlink(const SubOperation& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<SubOperation> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<OperationSubOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType Date;
    litesql::Field<std::string> date;
    static const litesql::FieldType Amount;
    litesql::Field<float> amount;
    static const litesql::FieldType AccountBalance;
    litesql::Field<float> accountBalance;
    static void initValues();
protected:
    void defaults();
public:
    Operation(const litesql::Database& db);
    Operation(const litesql::Database& db, const litesql::Record& rec);
    Operation(const Operation& obj);
    const Operation& operator=(const Operation& obj);
    Operation::AccountHandle account();
    Operation::ProviderHandle provider();
    Operation::SubOperationsHandle subOperations();
    virtual void setDate(string date);
    virtual void setAmount(float amount);
    virtual void setAccountBalance(float amount);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<Operation> upcast() const;
    std::auto_ptr<Operation> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, Operation o);
class SubOperation : public MPAO {
public:
    class Own {
    public:
        static const litesql::FieldType Id;
    };
    class OperationHandle : public litesql::RelationHandle<SubOperation> {
    public:
        OperationHandle(const SubOperation& owner);
        void link(const Operation& o0);
        void unlink(const Operation& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Operation> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<OperationSubOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    class CategoryHandle : public litesql::RelationHandle<SubOperation> {
    public:
        CategoryHandle(const SubOperation& owner);
        void link(const Category& o0);
        void unlink(const Category& o0);
        void del(const litesql::Expr& expr=litesql::Expr());
        litesql::DataSource<Category> get(const litesql::Expr& expr=litesql::Expr(), const litesql::Expr& srcExpr=litesql::Expr());
        litesql::DataSource<CategorySubOperationRelation::Row> getRows(const litesql::Expr& expr=litesql::Expr());
    };
    static const std::string type__;
    static const std::string table__;
    static const litesql::FieldType Amount;
    litesql::Field<float> amount;
    static const litesql::FieldType Note;
    litesql::Field<std::string> note;
    static void initValues();
protected:
    void defaults();
public:
    SubOperation(const litesql::Database& db);
    SubOperation(const litesql::Database& db, const litesql::Record& rec);
    SubOperation(const SubOperation& obj);
    const SubOperation& operator=(const SubOperation& obj);
    SubOperation::OperationHandle operation();
    SubOperation::CategoryHandle category();
    virtual void setAmount(float amount);
    virtual void setNote(string name);
protected:
    std::string insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs);
    void create();
    virtual void addUpdates(Updates& updates);
    virtual void addIDUpdates(Updates& updates);
public:
    static void getFieldTypes(std::vector<litesql::FieldType>& ftypes);
protected:
    virtual void delRecord();
    virtual void delRelations();
public:
    virtual void update();
    virtual void del();
    virtual bool typeIsCorrect() const;
    std::auto_ptr<SubOperation> upcast() const;
    std::auto_ptr<SubOperation> upcastCopy() const;
};
std::ostream & operator<<(std::ostream& os, SubOperation o);
class MPAPO : public litesql::Database {
public:
    MPAPO(std::string backendType, std::string connInfo);
protected:
    virtual std::vector<litesql::Database::SchemaItem> getSchema() const;
    static void initialize();
};
}
#endif
