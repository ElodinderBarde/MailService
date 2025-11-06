#pragma once
enum class PersonType
{
    absender,
    empfaenger
};
inline const char* To_String(const PersonType e)
{
    switch (e)
    {
    case PersonType::absender:
        return R"(Absender)";
    case PersonType::empfaenger:
        return R"(Empfänger)";
    default:
        return "unknown";
    }
}
