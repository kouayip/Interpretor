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
 * ADT
 * Symbol Table
 */
class SymbolTable
{
private:
    std::map<std::string, Symbol *> symbols_;

public:
    SymbolTable() //? Defined a default type
    {
        insert(new BuildTypeSymbol("auto"));
        insert(new BuildTypeSymbol("int"));
        insert(new BuildTypeSymbol("float"));
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
        std::cout << "Lookup: " << key << '\n'; //! Test look content
        return symbols_[key];
    }

    void print()
    {

        std::cout << '\n'
                  << "Symbol table contents" << '\n';
        std::cout << "---------------------" << '\n';
        for (auto pair : symbols_)
            std::cout << pair.second->toString() << '\n';
        std::cout << '\n';
    }

    ~SymbolTable()
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