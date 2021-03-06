#include "com/cyosp/mpa/po/MPAPO.hpp"
namespace mpapo {
using namespace litesql;
AccountCategoryRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : category(AccountCategoryRelation::Category), account(AccountCategoryRelation::Account) {
    switch(rec.size()) {
    case 2:
        category = rec[1];
    case 1:
        account = rec[0];
    }
}
const std::string AccountCategoryRelation::table__("Account_Category_");
const litesql::FieldType AccountCategoryRelation::Account("Account1_",A_field_type_integer,table__);
const litesql::FieldType AccountCategoryRelation::Category("Category2_",A_field_type_integer,table__);
void AccountCategoryRelation::link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Category& o1) {
    Record values;
    Split fields;
    fields.push_back(Account.name());
    values.push_back(o0.id);
    fields.push_back(Category.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void AccountCategoryRelation::unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Category& o1) {
    db.delete_(table__, (Account == o0.id && Category == o1.id));
}
void AccountCategoryRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<AccountCategoryRelation::Row> AccountCategoryRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Account.fullName());
    sel.result(Category.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<AccountCategoryRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Account> AccountCategoryRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Account.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Account>(db, mpapo::Account::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::Category> AccountCategoryRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Category.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Category>(db, mpapo::Category::Id.in(sel) && expr);
}
AccountProviderRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : provider(AccountProviderRelation::Provider), account(AccountProviderRelation::Account) {
    switch(rec.size()) {
    case 2:
        provider = rec[1];
    case 1:
        account = rec[0];
    }
}
const std::string AccountProviderRelation::table__("Account_Provider_");
const litesql::FieldType AccountProviderRelation::Account("Account1_",A_field_type_integer,table__);
const litesql::FieldType AccountProviderRelation::Provider("Provider2_",A_field_type_integer,table__);
void AccountProviderRelation::link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Provider& o1) {
    Record values;
    Split fields;
    fields.push_back(Account.name());
    values.push_back(o0.id);
    fields.push_back(Provider.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void AccountProviderRelation::unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Provider& o1) {
    db.delete_(table__, (Account == o0.id && Provider == o1.id));
}
void AccountProviderRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<AccountProviderRelation::Row> AccountProviderRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Account.fullName());
    sel.result(Provider.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<AccountProviderRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Account> AccountProviderRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Account.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Account>(db, mpapo::Account::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::Provider> AccountProviderRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Provider.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Provider>(db, mpapo::Provider::Id.in(sel) && expr);
}
AccountOperationRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : operation(AccountOperationRelation::Operation), account(AccountOperationRelation::Account) {
    switch(rec.size()) {
    case 2:
        operation = rec[1];
    case 1:
        account = rec[0];
    }
}
const std::string AccountOperationRelation::table__("Account_Operation_");
const litesql::FieldType AccountOperationRelation::Account("Account1_",A_field_type_integer,table__);
const litesql::FieldType AccountOperationRelation::Operation("Operation2_",A_field_type_integer,table__);
void AccountOperationRelation::link(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Operation& o1) {
    Record values;
    Split fields;
    fields.push_back(Account.name());
    values.push_back(o0.id);
    fields.push_back(Operation.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void AccountOperationRelation::unlink(const litesql::Database& db, const mpapo::Account& o0, const mpapo::Operation& o1) {
    db.delete_(table__, (Account == o0.id && Operation == o1.id));
}
void AccountOperationRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<AccountOperationRelation::Row> AccountOperationRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Account.fullName());
    sel.result(Operation.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<AccountOperationRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Account> AccountOperationRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Account.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Account>(db, mpapo::Account::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::Operation> AccountOperationRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Operation.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Operation>(db, mpapo::Operation::Id.in(sel) && expr);
}
OperationProviderRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : provider(OperationProviderRelation::Provider), operation(OperationProviderRelation::Operation) {
    switch(rec.size()) {
    case 2:
        provider = rec[1];
    case 1:
        operation = rec[0];
    }
}
const std::string OperationProviderRelation::table__("Operation_Provider_");
const litesql::FieldType OperationProviderRelation::Operation("Operation1_",A_field_type_integer,table__);
const litesql::FieldType OperationProviderRelation::Provider("Provider2_",A_field_type_integer,table__);
void OperationProviderRelation::link(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::Provider& o1) {
    Record values;
    Split fields;
    fields.push_back(Operation.name());
    values.push_back(o0.id);
    fields.push_back(Provider.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void OperationProviderRelation::unlink(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::Provider& o1) {
    db.delete_(table__, (Operation == o0.id && Provider == o1.id));
}
void OperationProviderRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<OperationProviderRelation::Row> OperationProviderRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Operation.fullName());
    sel.result(Provider.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<OperationProviderRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Operation> OperationProviderRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Operation.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Operation>(db, mpapo::Operation::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::Provider> OperationProviderRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Provider.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Provider>(db, mpapo::Provider::Id.in(sel) && expr);
}
OperationOperationDetailRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : operationDetail(OperationOperationDetailRelation::OperationDetail), operation(OperationOperationDetailRelation::Operation) {
    switch(rec.size()) {
    case 2:
        operationDetail = rec[1];
    case 1:
        operation = rec[0];
    }
}
const std::string OperationOperationDetailRelation::table__("Operation_OperationDetail_");
const litesql::FieldType OperationOperationDetailRelation::Operation("Operation1_",A_field_type_integer,table__);
const litesql::FieldType OperationOperationDetailRelation::OperationDetail("OperationDetail2_",A_field_type_integer,table__);
void OperationOperationDetailRelation::link(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::OperationDetail& o1) {
    Record values;
    Split fields;
    fields.push_back(Operation.name());
    values.push_back(o0.id);
    fields.push_back(OperationDetail.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void OperationOperationDetailRelation::unlink(const litesql::Database& db, const mpapo::Operation& o0, const mpapo::OperationDetail& o1) {
    db.delete_(table__, (Operation == o0.id && OperationDetail == o1.id));
}
void OperationOperationDetailRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<OperationOperationDetailRelation::Row> OperationOperationDetailRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Operation.fullName());
    sel.result(OperationDetail.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<OperationOperationDetailRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Operation> OperationOperationDetailRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Operation.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Operation>(db, mpapo::Operation::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::OperationDetail> OperationOperationDetailRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(OperationDetail.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::OperationDetail>(db, mpapo::OperationDetail::Id.in(sel) && expr);
}
CategoryOperationDetailRelation::Row::Row(const litesql::Database& db, const litesql::Record& rec)
         : operationDetail(CategoryOperationDetailRelation::OperationDetail), category(CategoryOperationDetailRelation::Category) {
    switch(rec.size()) {
    case 2:
        operationDetail = rec[1];
    case 1:
        category = rec[0];
    }
}
const std::string CategoryOperationDetailRelation::table__("Category_OperationDetail_");
const litesql::FieldType CategoryOperationDetailRelation::Category("Category1_",A_field_type_integer,table__);
const litesql::FieldType CategoryOperationDetailRelation::OperationDetail("OperationDetail2_",A_field_type_integer,table__);
void CategoryOperationDetailRelation::link(const litesql::Database& db, const mpapo::Category& o0, const mpapo::OperationDetail& o1) {
    Record values;
    Split fields;
    fields.push_back(Category.name());
    values.push_back(o0.id);
    fields.push_back(OperationDetail.name());
    values.push_back(o1.id);
    db.insert(table__, values, fields);
}
void CategoryOperationDetailRelation::unlink(const litesql::Database& db, const mpapo::Category& o0, const mpapo::OperationDetail& o1) {
    db.delete_(table__, (Category == o0.id && OperationDetail == o1.id));
}
void CategoryOperationDetailRelation::del(const litesql::Database& db, const litesql::Expr& expr) {
    db.delete_(table__, expr);
}
litesql::DataSource<CategoryOperationDetailRelation::Row> CategoryOperationDetailRelation::getRows(const litesql::Database& db, const litesql::Expr& expr) {
    SelectQuery sel;
    sel.result(Category.fullName());
    sel.result(OperationDetail.fullName());
    sel.source(table__);
    sel.where(expr);
    return DataSource<CategoryOperationDetailRelation::Row>(db, sel);
}
template <> litesql::DataSource<mpapo::Category> CategoryOperationDetailRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(Category.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::Category>(db, mpapo::Category::Id.in(sel) && expr);
}
template <> litesql::DataSource<mpapo::OperationDetail> CategoryOperationDetailRelation::get(const litesql::Database& db, const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    SelectQuery sel;
    sel.source(table__);
    sel.result(OperationDetail.fullName());
    sel.where(srcExpr);
    return DataSource<mpapo::OperationDetail>(db, mpapo::OperationDetail::Id.in(sel) && expr);
}
const litesql::FieldType MPAO::Own::Id("id_",A_field_type_integer,"MPAO_");
const std::string MPAO::type__("MPAO");
const std::string MPAO::table__("MPAO_");
const std::string MPAO::sequence__("MPAO_seq");
const litesql::FieldType MPAO::Id("id_",A_field_type_integer,table__);
const litesql::FieldType MPAO::Type("type_",A_field_type_string,table__);
const litesql::FieldType MPAO::Version("version_",A_field_type_integer,table__);
const litesql::FieldType MPAO::Updated("updated_",A_field_type_boolean,table__);
void MPAO::initValues() {
}
void MPAO::defaults() {
    id = 0;
    version = 0;
    updated = 0;
}
MPAO::MPAO(const litesql::Database& db)
     : litesql::Persistent(db), id(Id), type(Type), version(Version), updated(Updated) {
    defaults();
}
MPAO::MPAO(const litesql::Database& db, const litesql::Record& rec)
     : litesql::Persistent(db, rec), id(Id), type(Type), version(Version), updated(Updated) {
    defaults();
    size_t size = (rec.size() > 4) ? 4 : rec.size();
    switch(size) {
    case 4: updated = convert<const std::string&, bool>(rec[3]);
        updated.setModified(false);
    case 3: version = convert<const std::string&, int>(rec[2]);
        version.setModified(false);
    case 2: type = convert<const std::string&, std::string>(rec[1]);
        type.setModified(false);
    case 1: id = convert<const std::string&, int>(rec[0]);
        id.setModified(false);
    }
}
MPAO::MPAO(const MPAO& obj)
     : litesql::Persistent(obj), id(obj.id), type(obj.type), version(obj.version), updated(obj.updated) {
}
const MPAO& MPAO::operator=(const MPAO& obj) {
    if (this != &obj) {
        id = obj.id;
        type = obj.type;
        version = obj.version;
        updated = obj.updated;
    }
    litesql::Persistent::operator=(obj);
    return *this;
}
std::string MPAO::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back(id.name());
    values.push_back(id);
    id.setModified(false);
    fields.push_back(type.name());
    values.push_back(type);
    type.setModified(false);
    fields.push_back(version.name());
    values.push_back(version);
    version.setModified(false);
    fields.push_back(updated.name());
    values.push_back(updated);
    updated.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return litesql::Persistent::insert(tables, fieldRecs, valueRecs, sequence__);
}
void MPAO::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void MPAO::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
    updateField(updates, table__, type);
    updateField(updates, table__, version);
    updateField(updates, table__, updated);
}
void MPAO::addIDUpdates(Updates& updates) {
}
void MPAO::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    ftypes.push_back(Id);
    ftypes.push_back(Type);
    ftypes.push_back(Version);
    ftypes.push_back(Updated);
}
void MPAO::delRecord() {
    deleteFromTable(table__, id);
}
void MPAO::delRelations() {
}
void MPAO::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void MPAO::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<MPAO> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool MPAO::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<MPAO> MPAO::upcast() const {
    if (type == User::type__)
        return auto_ptr<MPAO>(new User(select<User>(*db, Id == id).one()));
    if (type == Account::type__)
        return auto_ptr<MPAO>(new Account(select<Account>(*db, Id == id).one()));
    if (type == Category::type__)
        return auto_ptr<MPAO>(new Category(select<Category>(*db, Id == id).one()));
    if (type == Provider::type__)
        return auto_ptr<MPAO>(new Provider(select<Provider>(*db, Id == id).one()));
    if (type == Operation::type__)
        return auto_ptr<MPAO>(new Operation(select<Operation>(*db, Id == id).one()));
    if (type == OperationDetail::type__)
        return auto_ptr<MPAO>(new OperationDetail(select<OperationDetail>(*db, Id == id).one()));
    return auto_ptr<MPAO>(new MPAO(*this));
}
std::auto_ptr<MPAO> MPAO::upcastCopy() const {
    MPAO* np = NULL;
    if (type == "User")
        np = new User(*db);
    if (type == "Account")
        np = new Account(*db);
    if (type == "Category")
        np = new Category(*db);
    if (type == "Provider")
        np = new Provider(*db);
    if (type == "Operation")
        np = new Operation(*db);
    if (type == "OperationDetail")
        np = new OperationDetail(*db);
    np->id = id;
    np->type = type;
    np->version = version;
    np->updated = updated;
    np->inDatabase = inDatabase;
    return auto_ptr<MPAO>(np);
}
std::ostream & operator<<(std::ostream& os, MPAO o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType User::Own::Id("id_",A_field_type_integer,"User_");
const std::string User::type__("User");
const std::string User::table__("User_");
const litesql::FieldType User::IsAdmin("isAdmin_",A_field_type_boolean,table__);
const litesql::FieldType User::Locale("locale_",A_field_type_string,table__);
const litesql::FieldType User::Login("login_",A_field_type_string,table__);
const litesql::FieldType User::Password("password_",A_field_type_string,table__);
const litesql::FieldType User::PwdErrNbr("pwdErrNbr_",A_field_type_integer,table__);
void User::initValues() {
}
void User::defaults() {
    isAdmin = 0;
    pwdErrNbr = 0;
}
User::User(const litesql::Database& db)
     : MPAO(db), isAdmin(IsAdmin), locale(Locale), login(Login), password(Password), pwdErrNbr(PwdErrNbr) {
    defaults();
}
User::User(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), isAdmin(IsAdmin), locale(Locale), login(Login), password(Password), pwdErrNbr(PwdErrNbr) {
    defaults();
    size_t size = (rec.size() > 9) ? 9 : rec.size();
    switch(size) {
    case 9: pwdErrNbr = convert<const std::string&, int>(rec[8]);
        pwdErrNbr.setModified(false);
    case 8: password = convert<const std::string&, std::string>(rec[7]);
        password.setModified(false);
    case 7: login = convert<const std::string&, std::string>(rec[6]);
        login.setModified(false);
    case 6: locale = convert<const std::string&, std::string>(rec[5]);
        locale.setModified(false);
    case 5: isAdmin = convert<const std::string&, bool>(rec[4]);
        isAdmin.setModified(false);
    }
}
User::User(const User& obj)
     : MPAO(obj), isAdmin(obj.isAdmin), locale(obj.locale), login(obj.login), password(obj.password), pwdErrNbr(obj.pwdErrNbr) {
}
const User& User::operator=(const User& obj) {
    if (this != &obj) {
        isAdmin = obj.isAdmin;
        locale = obj.locale;
        login = obj.login;
        password = obj.password;
        pwdErrNbr = obj.pwdErrNbr;
    }
    MPAO::operator=(obj);
    return *this;
}
std::string User::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(isAdmin.name());
    values.push_back(isAdmin);
    isAdmin.setModified(false);
    fields.push_back(locale.name());
    values.push_back(locale);
    locale.setModified(false);
    fields.push_back(login.name());
    values.push_back(login);
    login.setModified(false);
    fields.push_back(password.name());
    values.push_back(password);
    password.setModified(false);
    fields.push_back(pwdErrNbr.name());
    values.push_back(pwdErrNbr);
    pwdErrNbr.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void User::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void User::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, isAdmin);
    updateField(updates, table__, locale);
    updateField(updates, table__, login);
    updateField(updates, table__, password);
    updateField(updates, table__, pwdErrNbr);
    MPAO::addUpdates(updates);
}
void User::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void User::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(IsAdmin);
    ftypes.push_back(Locale);
    ftypes.push_back(Login);
    ftypes.push_back(Password);
    ftypes.push_back(PwdErrNbr);
}
void User::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void User::delRelations() {
}
void User::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void User::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<User> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool User::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<User> User::upcast() const {
    return auto_ptr<User>(new User(*this));
}
std::auto_ptr<User> User::upcastCopy() const {
    User* np = new User(*this);
    np->isAdmin = isAdmin;
    np->locale = locale;
    np->login = login;
    np->password = password;
    np->pwdErrNbr = pwdErrNbr;
    np->inDatabase = inDatabase;
    return auto_ptr<User>(np);
}
std::ostream & operator<<(std::ostream& os, User o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.isAdmin.name() << " = " << o.isAdmin << std::endl;
    os << o.locale.name() << " = " << o.locale << std::endl;
    os << o.login.name() << " = " << o.login << std::endl;
    os << o.password.name() << " = " << o.password << std::endl;
    os << o.pwdErrNbr.name() << " = " << o.pwdErrNbr << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Account::Own::Id("id_",A_field_type_integer,"Account_");
Account::CategoriesHandle::CategoriesHandle(const Account& owner)
         : litesql::RelationHandle<Account>(owner) {
}
void Account::CategoriesHandle::link(const Category& o0) {
    AccountCategoryRelation::link(owner->getDatabase(), *owner, o0);
}
void Account::CategoriesHandle::unlink(const Category& o0) {
    AccountCategoryRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Account::CategoriesHandle::del(const litesql::Expr& expr) {
    AccountCategoryRelation::del(owner->getDatabase(), expr && AccountCategoryRelation::Account == owner->id);
}
litesql::DataSource<Category> Account::CategoriesHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountCategoryRelation::get<Category>(owner->getDatabase(), expr, (AccountCategoryRelation::Account == owner->id) && srcExpr);
}
litesql::DataSource<AccountCategoryRelation::Row> Account::CategoriesHandle::getRows(const litesql::Expr& expr) {
    return AccountCategoryRelation::getRows(owner->getDatabase(), expr && (AccountCategoryRelation::Account == owner->id));
}
Account::ProvidersHandle::ProvidersHandle(const Account& owner)
         : litesql::RelationHandle<Account>(owner) {
}
void Account::ProvidersHandle::link(const Provider& o0) {
    AccountProviderRelation::link(owner->getDatabase(), *owner, o0);
}
void Account::ProvidersHandle::unlink(const Provider& o0) {
    AccountProviderRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Account::ProvidersHandle::del(const litesql::Expr& expr) {
    AccountProviderRelation::del(owner->getDatabase(), expr && AccountProviderRelation::Account == owner->id);
}
litesql::DataSource<Provider> Account::ProvidersHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountProviderRelation::get<Provider>(owner->getDatabase(), expr, (AccountProviderRelation::Account == owner->id) && srcExpr);
}
litesql::DataSource<AccountProviderRelation::Row> Account::ProvidersHandle::getRows(const litesql::Expr& expr) {
    return AccountProviderRelation::getRows(owner->getDatabase(), expr && (AccountProviderRelation::Account == owner->id));
}
Account::OperationsHandle::OperationsHandle(const Account& owner)
         : litesql::RelationHandle<Account>(owner) {
}
void Account::OperationsHandle::link(const Operation& o0) {
    AccountOperationRelation::link(owner->getDatabase(), *owner, o0);
}
void Account::OperationsHandle::unlink(const Operation& o0) {
    AccountOperationRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Account::OperationsHandle::del(const litesql::Expr& expr) {
    AccountOperationRelation::del(owner->getDatabase(), expr && AccountOperationRelation::Account == owner->id);
}
litesql::DataSource<Operation> Account::OperationsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountOperationRelation::get<Operation>(owner->getDatabase(), expr, (AccountOperationRelation::Account == owner->id) && srcExpr);
}
litesql::DataSource<AccountOperationRelation::Row> Account::OperationsHandle::getRows(const litesql::Expr& expr) {
    return AccountOperationRelation::getRows(owner->getDatabase(), expr && (AccountOperationRelation::Account == owner->id));
}
const std::string Account::type__("Account");
const std::string Account::table__("Account_");
const litesql::FieldType Account::Name("name_",A_field_type_string,table__);
const litesql::FieldType Account::Balance("balance_",A_field_type_float,table__);
void Account::initValues() {
}
void Account::defaults() {
    balance = 0.0;
}
Account::Account(const litesql::Database& db)
     : MPAO(db), name(Name), balance(Balance) {
    defaults();
}
Account::Account(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), name(Name), balance(Balance) {
    defaults();
    size_t size = (rec.size() > 6) ? 6 : rec.size();
    switch(size) {
    case 6: balance = convert<const std::string&, float>(rec[5]);
        balance.setModified(false);
    case 5: name = convert<const std::string&, std::string>(rec[4]);
        name.setModified(false);
    }
}
Account::Account(const Account& obj)
     : MPAO(obj), name(obj.name), balance(obj.balance) {
}
const Account& Account::operator=(const Account& obj) {
    if (this != &obj) {
        name = obj.name;
        balance = obj.balance;
    }
    MPAO::operator=(obj);
    return *this;
}
Account::CategoriesHandle Account::categories() {
    return Account::CategoriesHandle(*this);
}
Account::ProvidersHandle Account::providers() {
    return Account::ProvidersHandle(*this);
}
Account::OperationsHandle Account::operations() {
    return Account::OperationsHandle(*this);
}
std::string Account::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(balance.name());
    values.push_back(balance);
    balance.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void Account::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Account::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, name);
    updateField(updates, table__, balance);
    MPAO::addUpdates(updates);
}
void Account::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Account::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(Name);
    ftypes.push_back(Balance);
}
void Account::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void Account::delRelations() {
    AccountCategoryRelation::del(*db, (AccountCategoryRelation::Account == id));
    AccountProviderRelation::del(*db, (AccountProviderRelation::Account == id));
    AccountOperationRelation::del(*db, (AccountOperationRelation::Account == id));
}
void Account::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Account::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<Account> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Account::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<Account> Account::upcast() const {
    return auto_ptr<Account>(new Account(*this));
}
std::auto_ptr<Account> Account::upcastCopy() const {
    Account* np = new Account(*this);
    np->name = name;
    np->balance = balance;
    np->inDatabase = inDatabase;
    return auto_ptr<Account>(np);
}
std::ostream & operator<<(std::ostream& os, Account o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.balance.name() << " = " << o.balance << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Category::Own::Id("id_",A_field_type_integer,"Category_");
Category::AccountHandle::AccountHandle(const Category& owner)
         : litesql::RelationHandle<Category>(owner) {
}
void Category::AccountHandle::link(const Account& o0) {
    AccountCategoryRelation::link(owner->getDatabase(), o0, *owner);
}
void Category::AccountHandle::unlink(const Account& o0) {
    AccountCategoryRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Category::AccountHandle::del(const litesql::Expr& expr) {
    AccountCategoryRelation::del(owner->getDatabase(), expr && AccountCategoryRelation::Category == owner->id);
}
litesql::DataSource<Account> Category::AccountHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountCategoryRelation::get<Account>(owner->getDatabase(), expr, (AccountCategoryRelation::Category == owner->id) && srcExpr);
}
litesql::DataSource<AccountCategoryRelation::Row> Category::AccountHandle::getRows(const litesql::Expr& expr) {
    return AccountCategoryRelation::getRows(owner->getDatabase(), expr && (AccountCategoryRelation::Category == owner->id));
}
Category::OperationDetailsHandle::OperationDetailsHandle(const Category& owner)
         : litesql::RelationHandle<Category>(owner) {
}
void Category::OperationDetailsHandle::link(const OperationDetail& o0) {
    CategoryOperationDetailRelation::link(owner->getDatabase(), *owner, o0);
}
void Category::OperationDetailsHandle::unlink(const OperationDetail& o0) {
    CategoryOperationDetailRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Category::OperationDetailsHandle::del(const litesql::Expr& expr) {
    CategoryOperationDetailRelation::del(owner->getDatabase(), expr && CategoryOperationDetailRelation::Category == owner->id);
}
litesql::DataSource<OperationDetail> Category::OperationDetailsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return CategoryOperationDetailRelation::get<OperationDetail>(owner->getDatabase(), expr, (CategoryOperationDetailRelation::Category == owner->id) && srcExpr);
}
litesql::DataSource<CategoryOperationDetailRelation::Row> Category::OperationDetailsHandle::getRows(const litesql::Expr& expr) {
    return CategoryOperationDetailRelation::getRows(owner->getDatabase(), expr && (CategoryOperationDetailRelation::Category == owner->id));
}
const std::string Category::type__("Category");
const std::string Category::table__("Category_");
const litesql::FieldType Category::Name("name_",A_field_type_string,table__);
const litesql::FieldType Category::Amount("amount_",A_field_type_float,table__);
void Category::initValues() {
}
void Category::defaults() {
    amount = 0.0;
}
Category::Category(const litesql::Database& db)
     : MPAO(db), name(Name), amount(Amount) {
    defaults();
}
Category::Category(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), name(Name), amount(Amount) {
    defaults();
    size_t size = (rec.size() > 6) ? 6 : rec.size();
    switch(size) {
    case 6: amount = convert<const std::string&, float>(rec[5]);
        amount.setModified(false);
    case 5: name = convert<const std::string&, std::string>(rec[4]);
        name.setModified(false);
    }
}
Category::Category(const Category& obj)
     : MPAO(obj), name(obj.name), amount(obj.amount) {
}
const Category& Category::operator=(const Category& obj) {
    if (this != &obj) {
        name = obj.name;
        amount = obj.amount;
    }
    MPAO::operator=(obj);
    return *this;
}
Category::AccountHandle Category::account() {
    return Category::AccountHandle(*this);
}
Category::OperationDetailsHandle Category::operationDetails() {
    return Category::OperationDetailsHandle(*this);
}
std::string Category::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(amount.name());
    values.push_back(amount);
    amount.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void Category::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Category::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, name);
    updateField(updates, table__, amount);
    MPAO::addUpdates(updates);
}
void Category::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Category::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(Name);
    ftypes.push_back(Amount);
}
void Category::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void Category::delRelations() {
    AccountCategoryRelation::del(*db, (AccountCategoryRelation::Category == id));
    CategoryOperationDetailRelation::del(*db, (CategoryOperationDetailRelation::Category == id));
}
void Category::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Category::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<Category> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Category::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<Category> Category::upcast() const {
    return auto_ptr<Category>(new Category(*this));
}
std::auto_ptr<Category> Category::upcastCopy() const {
    Category* np = new Category(*this);
    np->name = name;
    np->amount = amount;
    np->inDatabase = inDatabase;
    return auto_ptr<Category>(np);
}
std::ostream & operator<<(std::ostream& os, Category o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.amount.name() << " = " << o.amount << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Provider::Own::Id("id_",A_field_type_integer,"Provider_");
Provider::AccountHandle::AccountHandle(const Provider& owner)
         : litesql::RelationHandle<Provider>(owner) {
}
void Provider::AccountHandle::link(const Account& o0) {
    AccountProviderRelation::link(owner->getDatabase(), o0, *owner);
}
void Provider::AccountHandle::unlink(const Account& o0) {
    AccountProviderRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Provider::AccountHandle::del(const litesql::Expr& expr) {
    AccountProviderRelation::del(owner->getDatabase(), expr && AccountProviderRelation::Provider == owner->id);
}
litesql::DataSource<Account> Provider::AccountHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountProviderRelation::get<Account>(owner->getDatabase(), expr, (AccountProviderRelation::Provider == owner->id) && srcExpr);
}
litesql::DataSource<AccountProviderRelation::Row> Provider::AccountHandle::getRows(const litesql::Expr& expr) {
    return AccountProviderRelation::getRows(owner->getDatabase(), expr && (AccountProviderRelation::Provider == owner->id));
}
Provider::OperationsHandle::OperationsHandle(const Provider& owner)
         : litesql::RelationHandle<Provider>(owner) {
}
void Provider::OperationsHandle::link(const Operation& o0) {
    OperationProviderRelation::link(owner->getDatabase(), o0, *owner);
}
void Provider::OperationsHandle::unlink(const Operation& o0) {
    OperationProviderRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Provider::OperationsHandle::del(const litesql::Expr& expr) {
    OperationProviderRelation::del(owner->getDatabase(), expr && OperationProviderRelation::Provider == owner->id);
}
litesql::DataSource<Operation> Provider::OperationsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return OperationProviderRelation::get<Operation>(owner->getDatabase(), expr, (OperationProviderRelation::Provider == owner->id) && srcExpr);
}
litesql::DataSource<OperationProviderRelation::Row> Provider::OperationsHandle::getRows(const litesql::Expr& expr) {
    return OperationProviderRelation::getRows(owner->getDatabase(), expr && (OperationProviderRelation::Provider == owner->id));
}
const std::string Provider::type__("Provider");
const std::string Provider::table__("Provider_");
const litesql::FieldType Provider::Name("name_",A_field_type_string,table__);
const litesql::FieldType Provider::Amount("amount_",A_field_type_float,table__);
void Provider::initValues() {
}
void Provider::defaults() {
    amount = 0.0;
}
Provider::Provider(const litesql::Database& db)
     : MPAO(db), name(Name), amount(Amount) {
    defaults();
}
Provider::Provider(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), name(Name), amount(Amount) {
    defaults();
    size_t size = (rec.size() > 6) ? 6 : rec.size();
    switch(size) {
    case 6: amount = convert<const std::string&, float>(rec[5]);
        amount.setModified(false);
    case 5: name = convert<const std::string&, std::string>(rec[4]);
        name.setModified(false);
    }
}
Provider::Provider(const Provider& obj)
     : MPAO(obj), name(obj.name), amount(obj.amount) {
}
const Provider& Provider::operator=(const Provider& obj) {
    if (this != &obj) {
        name = obj.name;
        amount = obj.amount;
    }
    MPAO::operator=(obj);
    return *this;
}
Provider::AccountHandle Provider::account() {
    return Provider::AccountHandle(*this);
}
Provider::OperationsHandle Provider::operations() {
    return Provider::OperationsHandle(*this);
}
std::string Provider::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(name.name());
    values.push_back(name);
    name.setModified(false);
    fields.push_back(amount.name());
    values.push_back(amount);
    amount.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void Provider::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Provider::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, name);
    updateField(updates, table__, amount);
    MPAO::addUpdates(updates);
}
void Provider::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Provider::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(Name);
    ftypes.push_back(Amount);
}
void Provider::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void Provider::delRelations() {
    AccountProviderRelation::del(*db, (AccountProviderRelation::Provider == id));
    OperationProviderRelation::del(*db, (OperationProviderRelation::Provider == id));
}
void Provider::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Provider::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<Provider> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Provider::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<Provider> Provider::upcast() const {
    return auto_ptr<Provider>(new Provider(*this));
}
std::auto_ptr<Provider> Provider::upcastCopy() const {
    Provider* np = new Provider(*this);
    np->name = name;
    np->amount = amount;
    np->inDatabase = inDatabase;
    return auto_ptr<Provider>(np);
}
std::ostream & operator<<(std::ostream& os, Provider o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.name.name() << " = " << o.name << std::endl;
    os << o.amount.name() << " = " << o.amount << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType Operation::Own::Id("id_",A_field_type_integer,"Operation_");
Operation::AccountHandle::AccountHandle(const Operation& owner)
         : litesql::RelationHandle<Operation>(owner) {
}
void Operation::AccountHandle::link(const Account& o0) {
    AccountOperationRelation::link(owner->getDatabase(), o0, *owner);
}
void Operation::AccountHandle::unlink(const Account& o0) {
    AccountOperationRelation::unlink(owner->getDatabase(), o0, *owner);
}
void Operation::AccountHandle::del(const litesql::Expr& expr) {
    AccountOperationRelation::del(owner->getDatabase(), expr && AccountOperationRelation::Operation == owner->id);
}
litesql::DataSource<Account> Operation::AccountHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return AccountOperationRelation::get<Account>(owner->getDatabase(), expr, (AccountOperationRelation::Operation == owner->id) && srcExpr);
}
litesql::DataSource<AccountOperationRelation::Row> Operation::AccountHandle::getRows(const litesql::Expr& expr) {
    return AccountOperationRelation::getRows(owner->getDatabase(), expr && (AccountOperationRelation::Operation == owner->id));
}
Operation::ProviderHandle::ProviderHandle(const Operation& owner)
         : litesql::RelationHandle<Operation>(owner) {
}
void Operation::ProviderHandle::link(const Provider& o0) {
    OperationProviderRelation::link(owner->getDatabase(), *owner, o0);
}
void Operation::ProviderHandle::unlink(const Provider& o0) {
    OperationProviderRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Operation::ProviderHandle::del(const litesql::Expr& expr) {
    OperationProviderRelation::del(owner->getDatabase(), expr && OperationProviderRelation::Operation == owner->id);
}
litesql::DataSource<Provider> Operation::ProviderHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return OperationProviderRelation::get<Provider>(owner->getDatabase(), expr, (OperationProviderRelation::Operation == owner->id) && srcExpr);
}
litesql::DataSource<OperationProviderRelation::Row> Operation::ProviderHandle::getRows(const litesql::Expr& expr) {
    return OperationProviderRelation::getRows(owner->getDatabase(), expr && (OperationProviderRelation::Operation == owner->id));
}
Operation::OperationDetailsHandle::OperationDetailsHandle(const Operation& owner)
         : litesql::RelationHandle<Operation>(owner) {
}
void Operation::OperationDetailsHandle::link(const OperationDetail& o0) {
    OperationOperationDetailRelation::link(owner->getDatabase(), *owner, o0);
}
void Operation::OperationDetailsHandle::unlink(const OperationDetail& o0) {
    OperationOperationDetailRelation::unlink(owner->getDatabase(), *owner, o0);
}
void Operation::OperationDetailsHandle::del(const litesql::Expr& expr) {
    OperationOperationDetailRelation::del(owner->getDatabase(), expr && OperationOperationDetailRelation::Operation == owner->id);
}
litesql::DataSource<OperationDetail> Operation::OperationDetailsHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return OperationOperationDetailRelation::get<OperationDetail>(owner->getDatabase(), expr, (OperationOperationDetailRelation::Operation == owner->id) && srcExpr);
}
litesql::DataSource<OperationOperationDetailRelation::Row> Operation::OperationDetailsHandle::getRows(const litesql::Expr& expr) {
    return OperationOperationDetailRelation::getRows(owner->getDatabase(), expr && (OperationOperationDetailRelation::Operation == owner->id));
}
const std::string Operation::type__("Operation");
const std::string Operation::table__("Operation_");
const litesql::FieldType Operation::Date("date_",A_field_type_string,table__);
const litesql::FieldType Operation::Amount("amount_",A_field_type_float,table__);
const litesql::FieldType Operation::AccountBalance("accountBalance_",A_field_type_float,table__);
void Operation::initValues() {
}
void Operation::defaults() {
    amount = 0.0;
    accountBalance = 0.0;
}
Operation::Operation(const litesql::Database& db)
     : MPAO(db), date(Date), amount(Amount), accountBalance(AccountBalance) {
    defaults();
}
Operation::Operation(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), date(Date), amount(Amount), accountBalance(AccountBalance) {
    defaults();
    size_t size = (rec.size() > 7) ? 7 : rec.size();
    switch(size) {
    case 7: accountBalance = convert<const std::string&, float>(rec[6]);
        accountBalance.setModified(false);
    case 6: amount = convert<const std::string&, float>(rec[5]);
        amount.setModified(false);
    case 5: date = convert<const std::string&, std::string>(rec[4]);
        date.setModified(false);
    }
}
Operation::Operation(const Operation& obj)
     : MPAO(obj), date(obj.date), amount(obj.amount), accountBalance(obj.accountBalance) {
}
const Operation& Operation::operator=(const Operation& obj) {
    if (this != &obj) {
        date = obj.date;
        amount = obj.amount;
        accountBalance = obj.accountBalance;
    }
    MPAO::operator=(obj);
    return *this;
}
Operation::AccountHandle Operation::account() {
    return Operation::AccountHandle(*this);
}
Operation::ProviderHandle Operation::provider() {
    return Operation::ProviderHandle(*this);
}
Operation::OperationDetailsHandle Operation::operationDetails() {
    return Operation::OperationDetailsHandle(*this);
}
std::string Operation::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(date.name());
    values.push_back(date);
    date.setModified(false);
    fields.push_back(amount.name());
    values.push_back(amount);
    amount.setModified(false);
    fields.push_back(accountBalance.name());
    values.push_back(accountBalance);
    accountBalance.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void Operation::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void Operation::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, date);
    updateField(updates, table__, amount);
    updateField(updates, table__, accountBalance);
    MPAO::addUpdates(updates);
}
void Operation::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void Operation::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(Date);
    ftypes.push_back(Amount);
    ftypes.push_back(AccountBalance);
}
void Operation::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void Operation::delRelations() {
    AccountOperationRelation::del(*db, (AccountOperationRelation::Operation == id));
    OperationProviderRelation::del(*db, (OperationProviderRelation::Operation == id));
    OperationOperationDetailRelation::del(*db, (OperationOperationDetailRelation::Operation == id));
}
void Operation::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void Operation::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<Operation> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool Operation::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<Operation> Operation::upcast() const {
    return auto_ptr<Operation>(new Operation(*this));
}
std::auto_ptr<Operation> Operation::upcastCopy() const {
    Operation* np = new Operation(*this);
    np->date = date;
    np->amount = amount;
    np->accountBalance = accountBalance;
    np->inDatabase = inDatabase;
    return auto_ptr<Operation>(np);
}
std::ostream & operator<<(std::ostream& os, Operation o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.date.name() << " = " << o.date << std::endl;
    os << o.amount.name() << " = " << o.amount << std::endl;
    os << o.accountBalance.name() << " = " << o.accountBalance << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
const litesql::FieldType OperationDetail::Own::Id("id_",A_field_type_integer,"OperationDetail_");
OperationDetail::OperationHandle::OperationHandle(const OperationDetail& owner)
         : litesql::RelationHandle<OperationDetail>(owner) {
}
void OperationDetail::OperationHandle::link(const Operation& o0) {
    OperationOperationDetailRelation::link(owner->getDatabase(), o0, *owner);
}
void OperationDetail::OperationHandle::unlink(const Operation& o0) {
    OperationOperationDetailRelation::unlink(owner->getDatabase(), o0, *owner);
}
void OperationDetail::OperationHandle::del(const litesql::Expr& expr) {
    OperationOperationDetailRelation::del(owner->getDatabase(), expr && OperationOperationDetailRelation::OperationDetail == owner->id);
}
litesql::DataSource<Operation> OperationDetail::OperationHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return OperationOperationDetailRelation::get<Operation>(owner->getDatabase(), expr, (OperationOperationDetailRelation::OperationDetail == owner->id) && srcExpr);
}
litesql::DataSource<OperationOperationDetailRelation::Row> OperationDetail::OperationHandle::getRows(const litesql::Expr& expr) {
    return OperationOperationDetailRelation::getRows(owner->getDatabase(), expr && (OperationOperationDetailRelation::OperationDetail == owner->id));
}
OperationDetail::CategoryHandle::CategoryHandle(const OperationDetail& owner)
         : litesql::RelationHandle<OperationDetail>(owner) {
}
void OperationDetail::CategoryHandle::link(const Category& o0) {
    CategoryOperationDetailRelation::link(owner->getDatabase(), o0, *owner);
}
void OperationDetail::CategoryHandle::unlink(const Category& o0) {
    CategoryOperationDetailRelation::unlink(owner->getDatabase(), o0, *owner);
}
void OperationDetail::CategoryHandle::del(const litesql::Expr& expr) {
    CategoryOperationDetailRelation::del(owner->getDatabase(), expr && CategoryOperationDetailRelation::OperationDetail == owner->id);
}
litesql::DataSource<Category> OperationDetail::CategoryHandle::get(const litesql::Expr& expr, const litesql::Expr& srcExpr) {
    return CategoryOperationDetailRelation::get<Category>(owner->getDatabase(), expr, (CategoryOperationDetailRelation::OperationDetail == owner->id) && srcExpr);
}
litesql::DataSource<CategoryOperationDetailRelation::Row> OperationDetail::CategoryHandle::getRows(const litesql::Expr& expr) {
    return CategoryOperationDetailRelation::getRows(owner->getDatabase(), expr && (CategoryOperationDetailRelation::OperationDetail == owner->id));
}
const std::string OperationDetail::type__("OperationDetail");
const std::string OperationDetail::table__("OperationDetail_");
const litesql::FieldType OperationDetail::Amount("amount_",A_field_type_float,table__);
const litesql::FieldType OperationDetail::Note("note_",A_field_type_string,table__);
void OperationDetail::initValues() {
}
void OperationDetail::defaults() {
    amount = 0.0;
}
OperationDetail::OperationDetail(const litesql::Database& db)
     : MPAO(db), amount(Amount), note(Note) {
    defaults();
}
OperationDetail::OperationDetail(const litesql::Database& db, const litesql::Record& rec)
     : MPAO(db, rec), amount(Amount), note(Note) {
    defaults();
    size_t size = (rec.size() > 6) ? 6 : rec.size();
    switch(size) {
    case 6: note = convert<const std::string&, std::string>(rec[5]);
        note.setModified(false);
    case 5: amount = convert<const std::string&, float>(rec[4]);
        amount.setModified(false);
    }
}
OperationDetail::OperationDetail(const OperationDetail& obj)
     : MPAO(obj), amount(obj.amount), note(obj.note) {
}
const OperationDetail& OperationDetail::operator=(const OperationDetail& obj) {
    if (this != &obj) {
        amount = obj.amount;
        note = obj.note;
    }
    MPAO::operator=(obj);
    return *this;
}
OperationDetail::OperationHandle OperationDetail::operation() {
    return OperationDetail::OperationHandle(*this);
}
OperationDetail::CategoryHandle OperationDetail::category() {
    return OperationDetail::CategoryHandle(*this);
}
std::string OperationDetail::insert(litesql::Record& tables, litesql::Records& fieldRecs, litesql::Records& valueRecs) {
    tables.push_back(table__);
    litesql::Record fields;
    litesql::Record values;
    fields.push_back("id_");
    values.push_back(id);
    fields.push_back(amount.name());
    values.push_back(amount);
    amount.setModified(false);
    fields.push_back(note.name());
    values.push_back(note);
    note.setModified(false);
    fieldRecs.push_back(fields);
    valueRecs.push_back(values);
    return MPAO::insert(tables, fieldRecs, valueRecs);
}
void OperationDetail::create() {
    litesql::Record tables;
    litesql::Records fieldRecs;
    litesql::Records valueRecs;
    type = type__;
    std::string newID = insert(tables, fieldRecs, valueRecs);
    if (id == 0)
        id = newID;
}
void OperationDetail::addUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, amount);
    updateField(updates, table__, note);
    MPAO::addUpdates(updates);
}
void OperationDetail::addIDUpdates(Updates& updates) {
    prepareUpdate(updates, table__);
    updateField(updates, table__, id);
}
void OperationDetail::getFieldTypes(std::vector<litesql::FieldType>& ftypes) {
    MPAO::getFieldTypes(ftypes);
    ftypes.push_back(Amount);
    ftypes.push_back(Note);
}
void OperationDetail::delRecord() {
    deleteFromTable(table__, id);
    MPAO::delRecord();
}
void OperationDetail::delRelations() {
    OperationOperationDetailRelation::del(*db, (OperationOperationDetailRelation::OperationDetail == id));
    CategoryOperationDetailRelation::del(*db, (CategoryOperationDetailRelation::OperationDetail == id));
}
void OperationDetail::update() {
    if (!inDatabase) {
        create();
        return;
    }
    Updates updates;
    addUpdates(updates);
    if (id != oldKey) {
        if (!typeIsCorrect()) 
            upcastCopy()->addIDUpdates(updates);
        else
            addIDUpdates(updates);
    }
    litesql::Persistent::update(updates);
    oldKey = id;
}
void OperationDetail::del() {
    if (!typeIsCorrect()) {
        std::auto_ptr<OperationDetail> p(upcastCopy());
        p->delRelations();
        p->onDelete();
        p->delRecord();
    } else {
        delRelations();
        onDelete();
        delRecord();
    }
    inDatabase = false;
}
bool OperationDetail::typeIsCorrect() const {
    return type == type__;
}
std::auto_ptr<OperationDetail> OperationDetail::upcast() const {
    return auto_ptr<OperationDetail>(new OperationDetail(*this));
}
std::auto_ptr<OperationDetail> OperationDetail::upcastCopy() const {
    OperationDetail* np = new OperationDetail(*this);
    np->amount = amount;
    np->note = note;
    np->inDatabase = inDatabase;
    return auto_ptr<OperationDetail>(np);
}
std::ostream & operator<<(std::ostream& os, OperationDetail o) {
    os << "-------------------------------------" << std::endl;
    os << o.id.name() << " = " << o.id << std::endl;
    os << o.type.name() << " = " << o.type << std::endl;
    os << o.version.name() << " = " << o.version << std::endl;
    os << o.updated.name() << " = " << o.updated << std::endl;
    os << o.amount.name() << " = " << o.amount << std::endl;
    os << o.note.name() << " = " << o.note << std::endl;
    os << "-------------------------------------" << std::endl;
    return os;
}
MPAPO::MPAPO(std::string backendType, std::string connInfo)
     : litesql::Database(backendType, connInfo) {
    initialize();
}
std::vector<litesql::Database::SchemaItem> MPAPO::getSchema() const {
    vector<Database::SchemaItem> res;
    string TEXT = backend->getSQLType(A_field_type_string);
    string rowIdType = backend->getRowIDType();
    res.push_back(Database::SchemaItem("schema_","table","CREATE TABLE schema_ (name_ "+TEXT+", type_ "+TEXT+", sql_ "+TEXT+")"));
    if (backend->supportsSequences()) {
        res.push_back(Database::SchemaItem("MPAO_seq","sequence",backend->getCreateSequenceSQL("MPAO_seq")));
    }
    res.push_back(Database::SchemaItem("MPAO_","table","CREATE TABLE MPAO_ (id_ " + rowIdType + ",type_ " + backend->getSQLType(A_field_type_string,"") + "" +",version_ " + backend->getSQLType(A_field_type_integer,"") + "" +",updated_ " + backend->getSQLType(A_field_type_boolean,"") + "" +")"));
    res.push_back(Database::SchemaItem("User_","table","CREATE TABLE User_ (id_ " + rowIdType + ",isAdmin_ " + backend->getSQLType(A_field_type_boolean,"") + "" +",locale_ " + backend->getSQLType(A_field_type_string,"5") + "" +",login_ " + backend->getSQLType(A_field_type_string,"32") + "" +",password_ " + backend->getSQLType(A_field_type_string,"32") + "" +",pwdErrNbr_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Account_","table","CREATE TABLE Account_ (id_ " + rowIdType + ",name_ " + backend->getSQLType(A_field_type_string,"256") + "" +",balance_ " + backend->getSQLType(A_field_type_float,"") + "" +")"));
    res.push_back(Database::SchemaItem("Category_","table","CREATE TABLE Category_ (id_ " + rowIdType + ",name_ " + backend->getSQLType(A_field_type_string,"64") + "" +",amount_ " + backend->getSQLType(A_field_type_float,"") + "" +")"));
    res.push_back(Database::SchemaItem("Provider_","table","CREATE TABLE Provider_ (id_ " + rowIdType + ",name_ " + backend->getSQLType(A_field_type_string,"64") + "" +",amount_ " + backend->getSQLType(A_field_type_float,"") + "" +")"));
    res.push_back(Database::SchemaItem("Operation_","table","CREATE TABLE Operation_ (id_ " + rowIdType + ",date_ " + backend->getSQLType(A_field_type_string,"23") + "" +",amount_ " + backend->getSQLType(A_field_type_float,"") + "" +",accountBalance_ " + backend->getSQLType(A_field_type_float,"") + "" +")"));
    res.push_back(Database::SchemaItem("OperationDetail_","table","CREATE TABLE OperationDetail_ (id_ " + rowIdType + ",amount_ " + backend->getSQLType(A_field_type_float,"") + "" +",note_ " + backend->getSQLType(A_field_type_string,"1024") + "" +")"));
    res.push_back(Database::SchemaItem("Account_Category_","table","CREATE TABLE Account_Category_ (Account1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",Category2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("Account_Provider_","table","CREATE TABLE Account_Provider_ (Account1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",Provider2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("Account_Operation_","table","CREATE TABLE Account_Operation_ (Account1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",Operation2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("Operation_Provider_","table","CREATE TABLE Operation_Provider_ (Operation1_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +",Provider2_ " + backend->getSQLType(A_field_type_integer,"") + "" +")"));
    res.push_back(Database::SchemaItem("Operation_OperationDetail_","table","CREATE TABLE Operation_OperationDetail_ (Operation1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",OperationDetail2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("Category_OperationDetail_","table","CREATE TABLE Category_OperationDetail_ (Category1_ " + backend->getSQLType(A_field_type_integer,"") + "" +",OperationDetail2_ " + backend->getSQLType(A_field_type_integer,"") + " UNIQUE" +")"));
    res.push_back(Database::SchemaItem("MPAO_id_idx","index","CREATE INDEX MPAO_id_idx ON MPAO_ (id_)"));
    res.push_back(Database::SchemaItem("Account_Category_Account1_idx","index","CREATE INDEX Account_Category_Account1_idx ON Account_Category_ (Account1_)"));
    res.push_back(Database::SchemaItem("Account_Category_Category2_idx","index","CREATE INDEX Account_Category_Category2_idx ON Account_Category_ (Category2_)"));
    res.push_back(Database::SchemaItem("Account_Category__all_idx","index","CREATE INDEX Account_Category__all_idx ON Account_Category_ (Account1_,Category2_)"));
    res.push_back(Database::SchemaItem("Account_Provider_Account1_idx","index","CREATE INDEX Account_Provider_Account1_idx ON Account_Provider_ (Account1_)"));
    res.push_back(Database::SchemaItem("Account_Provider_Provider2_idx","index","CREATE INDEX Account_Provider_Provider2_idx ON Account_Provider_ (Provider2_)"));
    res.push_back(Database::SchemaItem("Account_Provider__all_idx","index","CREATE INDEX Account_Provider__all_idx ON Account_Provider_ (Account1_,Provider2_)"));
    res.push_back(Database::SchemaItem("Account_Operation_Account1_idx","index","CREATE INDEX Account_Operation_Account1_idx ON Account_Operation_ (Account1_)"));
    res.push_back(Database::SchemaItem("O2086ca0062e7bc3c567180416fe58","index","CREATE INDEX O2086ca0062e7bc3c567180416fe58 ON Account_Operation_ (Operation2_)"));
    res.push_back(Database::SchemaItem("Account_Operation__all_idx","index","CREATE INDEX Account_Operation__all_idx ON Account_Operation_ (Account1_,Operation2_)"));
    res.push_back(Database::SchemaItem("O2a49bb6ee72af75814472e98bf5bd","index","CREATE INDEX O2a49bb6ee72af75814472e98bf5bd ON Operation_Provider_ (Operation1_)"));
    res.push_back(Database::SchemaItem("Ob3ed6a6b37220a19dca7dd9b86086","index","CREATE INDEX Ob3ed6a6b37220a19dca7dd9b86086 ON Operation_Provider_ (Provider2_)"));
    res.push_back(Database::SchemaItem("Operation_Provider__all_idx","index","CREATE INDEX Operation_Provider__all_idx ON Operation_Provider_ (Operation1_,Provider2_)"));
    res.push_back(Database::SchemaItem("O17daed388a001c4175aab7129fc16","index","CREATE INDEX O17daed388a001c4175aab7129fc16 ON Operation_OperationDetail_ (Operation1_)"));
    res.push_back(Database::SchemaItem("Ofd3201198b6c943ec28bc26733f91","index","CREATE INDEX Ofd3201198b6c943ec28bc26733f91 ON Operation_OperationDetail_ (OperationDetail2_)"));
    res.push_back(Database::SchemaItem("Oc2e4af7c5439ede28816d710a3615","index","CREATE INDEX Oc2e4af7c5439ede28816d710a3615 ON Operation_OperationDetail_ (Operation1_,OperationDetail2_)"));
    res.push_back(Database::SchemaItem("O639119dfce383e8c0f76c3aa164f5","index","CREATE INDEX O639119dfce383e8c0f76c3aa164f5 ON Category_OperationDetail_ (Category1_)"));
    res.push_back(Database::SchemaItem("O1fb877c5487f879a86efaf08818a1","index","CREATE INDEX O1fb877c5487f879a86efaf08818a1 ON Category_OperationDetail_ (OperationDetail2_)"));
    res.push_back(Database::SchemaItem("Odff0a593025aab379bda67558b279","index","CREATE INDEX Odff0a593025aab379bda67558b279 ON Category_OperationDetail_ (Category1_,OperationDetail2_)"));
    return res;
}
void MPAPO::initialize() {
    static bool initialized = false;
    if (initialized)
        return;
    initialized = true;
}
}
