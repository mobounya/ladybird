/*
 * Copyright (c) 2024, Sam Atkins <sam@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "StyleSheetIdentifier.h"
#include <LibIPC/Decoder.h>
#include <LibIPC/Encoder.h>

namespace Web::CSS {

StringView style_sheet_identifier_type_to_string(StyleSheetIdentifier::Type type)
{
    switch (type) {
    case StyleSheetIdentifier::Type::StyleElement:
        return "StyleElement"sv;
    case StyleSheetIdentifier::Type::LinkElement:
        return "LinkElement"sv;
    case StyleSheetIdentifier::Type::ImportRule:
        return "ImportRule"sv;
    case StyleSheetIdentifier::Type::UserAgent:
        return "UserAgent"sv;
    case StyleSheetIdentifier::Type::UserStyle:
        return "UserStyle"sv;
    }
    VERIFY_NOT_REACHED();
}

Optional<StyleSheetIdentifier::Type> style_sheet_identifier_type_from_string(StringView string)
{
    if (string == "StyleElement"sv)
        return StyleSheetIdentifier::Type::StyleElement;
    if (string == "LinkElement"sv)
        return StyleSheetIdentifier::Type::LinkElement;
    if (string == "ImportRule"sv)
        return StyleSheetIdentifier::Type::ImportRule;
    if (string == "UserAgent"sv)
        return StyleSheetIdentifier::Type::UserAgent;
    if (string == "UserStyle"sv)
        return StyleSheetIdentifier::Type::UserStyle;
    return {};
}

}

namespace IPC {

template<>
ErrorOr<void> encode(Encoder& encoder, Web::CSS::StyleSheetIdentifier const& style_sheet_source)
{
    TRY(encoder.encode(style_sheet_source.type));
    TRY(encoder.encode(style_sheet_source.dom_element_unique_id.map([](auto value) { return value.value(); })));
    TRY(encoder.encode(style_sheet_source.url));
    TRY(encoder.encode(style_sheet_source.rule_count));

    return {};
}

template<>
ErrorOr<Web::CSS::StyleSheetIdentifier> decode(Decoder& decoder)
{
    auto type = TRY(decoder.decode<Web::CSS::StyleSheetIdentifier::Type>());
    auto dom_element_unique_id = TRY(decoder.decode<Optional<Web::UniqueNodeID::Type>>());
    auto url = TRY(decoder.decode<Optional<String>>());
    auto rule_count = TRY(decoder.decode<size_t>());

    return Web::CSS::StyleSheetIdentifier {
        .type = type,
        .dom_element_unique_id = dom_element_unique_id.map([](auto value) -> Web::UniqueNodeID { return value; }),
        .url = move(url),
        .rule_count = rule_count,
    };
}

}
