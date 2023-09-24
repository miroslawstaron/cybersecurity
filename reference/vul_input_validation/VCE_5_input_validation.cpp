#include <regex>
#include <string>

class URLValidator : public FieldValidatorSupport {
private:
std::string urlRegex;
std::string urlRegexExpression;
public:
void validate(Object object) override {
std::string fieldName = getFieldName();
Object value = this->getFieldValue(fieldName, object);

// if there is no value - don't do comparison
    // if a value is required, a required validator should be added to the field
    if (value == nullptr || value.toString().length() == 0) {
        return;
    }

    if (!(value.getClass().equals(String.class)) ||
        !std::regex_match(value.toString(), std::regex(getUrlRegex(), std::regex_constants::icase))) {
        addFieldError(fieldName, object);
    }
}

}