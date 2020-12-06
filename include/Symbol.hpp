#ifndef __SYMBOL__
#define __SYMBOL__

#include <iostream>
#include <map>

/**
 * Symbol
 */
class Symbol
{
protected:
    std::string name_;
    Symbol *type_;

public:
    Symbol(std::string const(&name), Symbol *(&type)) : name_(name), type_(type) {}

    Symbol(std::string const(&name)) : name_(name), type_(nullptr) {}

    const auto name() const
    {
        return name_;
    }

    const auto type() const
    {
        return type_;
    }

    virtual std::string print() = 0;

    virtual std::string toString() = 0;
};

/**
 * Builtin type symbol
 */
class BuildTypeSymbol : public Symbol
{
public:
    BuildTypeSymbol(std::string const(&name)) : Symbol(name) {}

    std::string print()
    {
        return name_;
    }

    virtual std::string toString()
    {
        return "<BuildTypeSymbol (name = '" + name_ + "')>";
    }
};

/**
 * Builtin val symbol
 */
class ValSymbol : public Symbol
{
public:
    ValSymbol(std::string const(&name), Symbol *type) : Symbol(name, type) {}

    virtual std::string print()
    {
        return std::string("<" + name_ + ":" + type_->name() + ">");
    }

    virtual std::string toString()
    {
        return "<ValSymbol (name = '" + name_ + "', " + "type = '" + type_->name() + "')>";
    }
};

/**
 * Builtin Func symbol
 */
class FuncSymbol : public Symbol
{
private:
    std::map<std::string, Symbol *> params_;

public:
    FuncSymbol(std::string const(&name), Symbol *type) : Symbol(name, type) {}

    void append(Symbol *symbol)
    {
        // Utils::print(symbol->toString());
        // params_[symbol->name()] = symbol; //!Erreur lors de l'ajour du symbol
    }

    virtual std::string print()
    {
        return std::string("<" + name_ + ":" + type_->name() + ">");
    }

    virtual std::string toString()
    {
        auto result = std::string("");
        for (auto pair : params_)
            result += pair.second->toString() + ", ";

        return "<FuncSymbol (name = '" + name_ + "', " + "return_type = '" + type_->name() + "', parameters = [" + result + "])>";
    }

    ~FuncSymbol()
    {
        // Utils::print("DELELELELELELLEELELELELELELE");
        // for (auto it = params_.begin(); it != params_.end(); ++it)
        // {
        //     delete it->second;
        //     it->second = nullptr;
        // }
        // params_.clear();
    }
};

/**
 * ADT
 * Symbol Table
 */
class ScopedSymbolTable
{
private:
    std::map<std::string, Symbol *> symbols_;
    std::string name_;
    // ScopedSymbolTable *enclosingScope_;
    int level_;

    Symbol *nullSymbol;

public:
    ScopedSymbolTable(std::string const(&scopeName), int scopeLevel, ScopedSymbolTable *enclosingScope = nullptr) : name_(scopeName), level_(scopeLevel), enclosingScope_(enclosingScope)
    {
        //? Defined a default type
        insert(new BuildTypeSymbol("auto"));
        insert(new BuildTypeSymbol("int"));
        insert(new BuildTypeSymbol("float"));

        //?
        nullSymbol = nullptr;
    }

    ScopedSymbolTable *enclosingScope_;

    auto getEnclosingScope()
    {
        return enclosingScope_;
    }

    auto getLevel()
    {
        return level_;
    }

    void insert(Symbol *symbol) noexcept
    {
        std::cout << "Insert: " << symbol->name() << '\n'; //! Test look content
        symbols_[symbol->name()] = symbol;
    }

    bool hasKey(std::string const(&key)) noexcept
    {
        return symbols_.count(key) == 1;
    }

    const auto lookup(std::string const(&key))
    {
        std::cout << "Lookup: " << key << ". (Scope name: " << (enclosingScope_ ? enclosingScope_->name_ : "None") << ")" << '\n'; //! Test look content

        if (hasKey(key)) //? Check is key existe
            return symbols_[key];

        if (enclosingScope_)
            return enclosingScope_->lookup(key);

        return nullSymbol;
    }

    void print()
    {

        std::cout << '\n'
                  << "SCOPE (SCOPED SYMBOL TABLE)" << '\n';
        std::cout << "---------------------------" << '\n';
        std::cout << "Scope name  :  " << name_ << '\n';
        std::cout << "Scope level :  " << level_ << '\n';
        std::cout << "Enclosing scope :  " << (enclosingScope_ ? enclosingScope_->name_ : "None") << '\n';
        std::cout << "---------------------------" << '\n';
        for (auto pair : symbols_)
            std::cout << pair.first << ": " << pair.second->toString() << '\n';
        std::cout << '\n';
    }

    ~ScopedSymbolTable()
    {
        for (auto it = symbols_.begin(); it != symbols_.end(); ++it)
        {
            delete it->second;
            it->second = nullptr;
        }
        symbols_.clear();
    }
};

#endif