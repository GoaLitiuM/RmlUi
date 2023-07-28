#pragma once

#include "RmlUiHelpers.h"
#include "RmlUiProperty.h"

#include <Engine/Core/Config.h>
#include <Engine/Core/Types/BaseTypes.h>

#include <ThirdParty/RmlUi/Core/StyleSheetSpecification.h>
#include <ThirdParty/RmlUi/Core/PropertyParser.h>
#include <ThirdParty/RmlUi/Core/PropertyDefinition.h>
#include <ThirdParty/RmlUi/Core/PropertyDictionary.h>

#include <Engine/Core/Types/String.h>
#include <Engine/Core/Collections/Dictionary.h>
#include <Engine/Scripting/ScriptingObject.h>

API_CLASS(Static, Namespace = "RmlUi") class RMLUI_API RmlUiStyleSheetSpecification
{
    DECLARE_SCRIPTING_TYPE_NO_SPAWN(RmlUiStyleSheetSpecification);
public:
    /// Starts up the specification structure and registers default properties and type parsers.
    /// @return True if the specification started up successfully, false if not.
    API_FUNCTION(Static) static bool Initialise()
    {
        return Rml::StyleSheetSpecification::Initialise();
    }
    /// Destroys the specification structure and releases the parsers.
    API_FUNCTION(Static) static void Shutdown()
    {
        return Rml::StyleSheetSpecification::Shutdown();
    }
#if 0
    /// Registers a parser for use in property definitions.
    /// @param[in] parser_name The name to register the new parser under.
    /// @param[in] parser A non-owning pointer to the parser to register.
    /// @return True if the parser was registered successfully, false otherwise.
    /// @lifetime The parser must be kept alive until after the call to Rml::Shutdown.
    static bool RegisterParser(const Rml::String& parser_name, Rml::PropertyParser* parser);
    /// Returns the parser registered with a specific name.
    /// @param[in] parser_name The name of the desired parser.
    /// @return The parser registered under the given name, or nullptr if no such parser exists.
    static Rml::PropertyParser* GetParser(const Rml::String& parser_name);

    /// Registers a custom property with a new definition.
    /// @param[in] property_name The name to register the new property under.
    /// @param[in] default_value The default value to be used for an element if it has no other definition provided.
    /// @param[in] inherited True if this property is inherited from parent to child, false otherwise.
    /// @param[in] forces_layout True if a change in this property on an element will cause the element's layout to possibly change.
    /// @return The new property definition, ready to have parsers attached.
    static Rml::PropertyDefinition& RegisterProperty(const Rml::String& property_name, const Rml::String& default_value, bool inherited, bool forces_layout = false);
    /// Returns a property definition.
    /// @param[in] property_name The name of the desired property.
    /// @return The appropriate property definition if it could be found, nullptr otherwise.
    static const Rml::PropertyDefinition* GetProperty(const Rml::String& property_name);
    static const Rml::PropertyDefinition* GetProperty(Rml::PropertyId id);

    /// Returns the id set of all registered property definitions.
    static const Rml::PropertyIdSet& GetRegisteredProperties();
    /// Returns the id set of all registered inherited property definitions.
    static const Rml::PropertyIdSet& GetRegisteredInheritedProperties();
    /// Returns the id set of all registered property definitions that may dirty the layout.
    static const Rml::PropertyIdSet& GetRegisteredPropertiesForcingLayout();

    /// Registers a custom shorthand property definition.
    /// @param[in] shorthand_name The name to register the new shorthand property under.
    /// @param[in] properties A comma-separated list of the properties this definition is shorthand for. The order in which they are specified here is the order in which the values will be processed.
    /// @param[in] type The type of shorthand to declare.
    /// @param True if all the property names exist, false otherwise.
    static Rml::ShorthandId RegisterShorthand(const Rml::String& shorthand_name, const Rml::String& property_names, Rml::ShorthandType type);
    /// Returns a shorthand definition.
    /// @param[in] shorthand_name The name of the desired shorthand.
    /// @return The appropriate shorthand definition if it could be found, nullptr otherwise.
    static const Rml::ShorthandDefinition* GetShorthand(const Rml::String& shorthand_name);
    static const Rml::ShorthandDefinition* GetShorthand(Rml::ShorthandId id);
#endif

    /// 
    API_FUNCTION(Static) static Dictionary<RmlUiPropertyId, RmlUiProperty*> ParsePropertyDeclaration(const String& property_name, const String& property_value)
    {
        Rml::PropertyDictionary dict;
        Rml::StyleSheetSpecification::ParsePropertyDeclaration(dict, ToRmlString(property_name), ToRmlString(property_value));
        auto& map = dict.GetProperties();
        Dictionary<RmlUiPropertyId, RmlUiProperty*> dictionary(dict.GetNumProperties());
        for (auto iter = map.begin(); iter != map.end(); iter++)
            dictionary.Add((RmlUiPropertyId)iter->first, New<RmlUiProperty>(iter->second));
        return dictionary;
    }

    ///
    API_FUNCTION(Static) static bool TryParsePropertyDeclaration(API_PARAM(Out) Dictionary<RmlUiPropertyId, RmlUiProperty*>& dictionary, const String& property_name, const String& property_value)
    {
        Rml::PropertyDictionary dict;
        for (auto iter = dictionary.Begin(); iter.IsNotEnd(); iter++)
            dict.SetProperty((Rml::PropertyId)iter->Key, **iter->Value);
        bool ret = Rml::StyleSheetSpecification::ParsePropertyDeclaration(dict, ToRmlString(property_name), ToRmlString(property_value));
        auto& map = dict.GetProperties();
        for (auto iter = map.begin(); iter != map.end(); iter++)
            dictionary.Add((RmlUiPropertyId)iter->first, New<RmlUiProperty>(iter->second));
        return ret;
    }

    /// Parses a property declaration, setting any parsed and validated properties on the given dictionary.
    /// @param[in] dictionary The property dictionary which will hold all declared properties.
    /// @param[in] property_name The name of the declared property.
    /// @param[in] property_value The values the property is being set to.
    /// @param[in] source_file The file where this property was declared. Used for error reporting, debugging and relative paths for referenced assets.
    /// @param[in] line_number The location of the source file where this property was declared. Used for error reporting and debugging.
    /// @return True if all properties were parsed successfully, false otherwise.
    API_FUNCTION(Static) static bool ParsePropertyDeclaration(API_PARAM(Ref) Dictionary<RmlUiPropertyId, RmlUiProperty*>& dictionary, const String& property_name, const String& property_value)
    {
        Rml::PropertyDictionary dict;
        for (auto iter = dictionary.Begin(); iter.IsNotEnd(); iter++)
            dict.SetProperty((Rml::PropertyId)iter->Key, **iter->Value);
        bool ret = Rml::StyleSheetSpecification::ParsePropertyDeclaration(dict, ToRmlString(property_name), ToRmlString(property_value));
        auto& map = dict.GetProperties();
        for (auto iter = map.begin(); iter != map.end(); iter++)
            dictionary.Add((RmlUiPropertyId)iter->first, New<RmlUiProperty>(iter->second));
        return ret;
    }

#if 0
    static Rml::PropertyId GetPropertyId(const Rml::String& property_name);
    static Rml::ShorthandId GetShorthandId(const Rml::String& shorthand_name);
    static const Rml::String& GetPropertyName(Rml::PropertyId id);
    static const Rml::String& GetShorthandName(Rml::ShorthandId id);

    // Get the underlying property ids associated by a shorthand.
    static Rml::PropertyIdSet GetShorthandUnderlyingProperties(Rml::ShorthandId id);

    static const Rml::PropertySpecification& GetPropertySpecification();
#endif
private:
    RmlUiStyleSheetSpecification() {}
    ~RmlUiStyleSheetSpecification() {}

#if 0
    Rml::PropertyDefinition& RegisterProperty(Rml::PropertyId id, const Rml::String& property_name, const Rml::String& default_value, bool inherited, bool forces_layout = false);
    Rml::ShorthandId RegisterShorthand(Rml::ShorthandId id, const Rml::String& shorthand_name, const Rml::String& property_names, Rml::ShorthandType type);

    // Registers RmlUi's default parsers.
    void RegisterDefaultParsers();
    // Registers RmlUi's default style properties.
    void RegisterDefaultProperties();

    // Parsers used by all property definitions.
    typedef Rml::UnorderedMap< String, Rml::PropertyParser* > ParserMap;
    ParserMap parsers;

    // The properties defined in the style sheet specification.
    Rml::PropertySpecification properties;

    Rml::UniquePtr<Rml::DefaultStyleSheetParsers> default_parsers;
#endif
};