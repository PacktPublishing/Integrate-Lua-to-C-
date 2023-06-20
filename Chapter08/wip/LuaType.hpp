#ifndef _LUA_TYPE_HPP
#define _LUA_TYPE_HPP

#include <cstddef>
#include <string>
#include <variant>

enum class LuaType
{
    nil,
    boolean,
    number,
    string,
    function,
    table,
    lightuserdata,
};

/// @brief [inout]
struct LuaNil final
{
    const LuaType type = LuaType::nil;
    const std::nullptr_t value = nullptr;

    static LuaNil make() { return LuaNil(); }

private:
    LuaNil() = default;
};

/// @brief [inout]
struct LuaBoolean final
{
    const LuaType type = LuaType::boolean;
    const bool value;

    static LuaBoolean make(const bool value) { return LuaBoolean(value); }

private:
    LuaBoolean(const bool value) : value(value) {}
};

/// @brief [inout]
struct LuaNumber final
{
    const LuaType type = LuaType::number;
    const double value;

    static LuaNumber make(const double value) { return LuaNumber(value); }

private:
    LuaNumber(const double value) : value(value) {}
};

/// @brief [inout]
struct LuaString final
{
    const LuaType type = LuaType::string;
    const std::string value;

    static LuaString make(const std::string &value) { return LuaString(value); }

private:
    LuaString(const std::string &value) : value(value) {}
};

/// @brief [out]
struct LuaFunction final
{
    const LuaType type = LuaType::function;
    const std::nullptr_t value = nullptr;

    static LuaFunction make() { return LuaFunction(); }

private:
    LuaFunction() = default;
};

/// @brief [out]
struct LuaTable final
{
    const LuaType type = LuaType::table;
    const std::nullptr_t value = nullptr;

    static LuaTable make() { return LuaTable(); }

private:
    LuaTable() = default;
};

/// @brief [in]
struct LuaLightUserData final
{
    const LuaType type = LuaType::lightuserdata;
    void *value;

    static LuaLightUserData make(void *value) { return LuaLightUserData(value); }

private:
    LuaLightUserData(void *value) : value(value) {}
};

using LuaValue = std::variant<LuaNil, LuaBoolean, LuaNumber, LuaString, LuaFunction, LuaTable, LuaLightUserData>;

inline LuaType getLuaType(const LuaValue &value)
{
    return std::visit(
        [](const auto &v)
        { return v.type; },
        value);
}

inline std::string getLuaValueString(const LuaValue &value)
{
    switch (getLuaType(value))
    {
    case LuaType::nil:
        return "nil";
    case LuaType::boolean:
        return std::get<LuaBoolean>(value).value ? "true" : "false";
    case LuaType::number:
        return std::to_string(std::get<LuaNumber>(value).value);
    case LuaType::string:
        return std::get<LuaString>(value).value;
    case LuaType::function:
        return "function";
    case LuaType::table:
        return "table";
    case LuaType::lightuserdata:
        return "lightuserdata";
    }
}

#endif // _LUA_TYPE_HPP
