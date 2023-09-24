#include <string>
#include "StringUtils.h"

using namespace std;

string getUrlRegex() {
    if (StringUtils::isNotEmpty(urlRegexExpression)) {
        return parse(urlRegexExpression, string);
    } else if (StringUtils::isNotEmpty(urlRegex)) {
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