template <typename T>
Object evaluateValueFromTarget(Object targetObject, Class<T> entityType) {
if (path.find_last_of("-") != path.length() - 1) {
return super.evaluateValueFromTarget(targetObject, entityType);
}

std::vector<std::string> splitPath;
std::stringstream ss(path);
std::string item;
while (std::getline(ss, item, '/')) {
    if (std::regex_match(item, std::regex("\\d"))) {
        continue;
    }
    if (item == "-") {
        continue;
    }
    if (item.empty()) {
        continue;
    }
    splitPath.push_back(item);
}

std::string pathSource = boost::algorithm::join(splitPath, ".");

PropertyPath propertyPath = PropertyPath::from(pathSource, entityType);

if (typeid(value) == typeid(LateObjectEvaluator)) {
    return static_cast<LateObjectEvaluator*>(value)->evaluate(propertyPath.getType());
} else {
    return value;
}


}