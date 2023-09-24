#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

class URLValidator : public FieldValidatorSupport {
   private:
    std::string urlRegex;
    std::string urlRegexExpression;

   public:
    void validate(Object object) {
        std::string fieldName = getFieldName();
        auto [value, success] = getFieldValue(fieldName, object);

        // if there is no value - don't do comparison
        // if a value is required, a required validator should be added to the field
        if (!success || value.empty()) {
            return;
        }

        if (typeid(value) != typeid(std::string) ||
            !std::regex_match(value, std::regex(getUrlRegex(), std::regex_constants::icase))) {
            addFieldError(fieldName, object);
        }
    }

   private:
    std::string getUrlRegex() {
        if (!urlRegexExpression.empty()) {
            return parse(urlRegexExpression, std::string);
        } else if (!urlRegex.empty()) {
            return urlRegex;
        } else {
            return "^(https?|ftp):\\/\\/" +
                   "(([a-z0-9$_\\.\\+!\\*\\'\\(\\),;\\?&=-]|%[0-9a-f]{2})+" +
                   "(:([a-z0-9$_\\.\\+!\\*\\'\\(\\),;\\?&=-]|%[0-9a-f]{2})+)?" +
                   "@)?(#?" +
                   ")((([a-z0-9]\\.|[a-z0-9][a-z0-9-]*[a-z0-9]\\.)*" +
                   "[a-z][a-z0-9-]*[a-z0-9]" +
                   "|((\\d|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])\\.){3}" +
                   "(\\d|[1-9]\\d|1\\d{2}|2[0-4][0-9]|25[0-5])" +
                   ")(:\\d+)?" +
                   ")(((\\/{0,1}([a-z0-9$_\\.\\+!\\*\\'\\(\\),;:@&=-]|%[0-9a-f]{2})*)*" +
                   "(\\?([a-z0-9$_\\.\\+!\\*\\'\\(\\),;:@&=-]|%[0-9a-f]{2})*)" +
                   "?)?)?" +
                   "(#([a-z0-9$_\\.\\+!\\*\\'\\(\\),;:@&=-]|%[0-9a-f]{2})*)?" +
                   "$";
        }
    }
};
