template<typename T>
Object evaluateValueFromTarget(Object targetObject, Class<T> entityType) {
if (!path.endsWith("-")) {
return super.evaluateValueFromTarget(targetObject, entityType);
}

std::string pathSource = stream(path.split("/"))
                            .filter([](const std::string& it) { return !std::regex_match(it, std::regex("\\d")); })
                            .filter([](const std::string& it) { return it != "-"; })
                            .filter([](const std::string& it) { return !it.empty(); })
                            .collect(Collectors.joining("."));

PropertyPath propertyPath = PropertyPath::from(pathSource, entityType);

return value instanceof LateObjectEvaluator ? ((LateObjectEvaluator*)value)->evaluate(propertyPath.getType())
                                             : value;
}