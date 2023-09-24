// Evaluate the value from the target object
protected <T> Object evaluateValueFromTarget(Object targetObject, Class<T> entityType) {
verifyPath(entityType);
return evaluate(spelExpression.getValueType(targetObject));
}

// Evaluate the value based on the type
protected final <T> Object evaluate(Class<T> type) {
if (value instanceof LateObjectEvaluator) {
return ((LateObjectEvaluator) value).evaluate(type);
} else {
return value;
}
}

// Verify the path and return a PropertyPath representing the path
// Returns empty if the path only consists of index lookups or append characters
protected final Optional<PropertyPath> verifyPath(Class<?> type) {
// Split the path by "/"
std::vectorstd::string parts;
std::string delimiter = "/";
size_t pos = 0;
while ((pos = path.find(delimiter)) != std::string::npos) {
std::string part = path.substr(0, pos);
parts.push_back(part);
path.erase(0, pos + delimiter.length());
}
parts.push_back(path);

// Filter out the index lookups and append characters
std::vector<std::string> filteredParts;
for (const auto& part : parts) {
    if (!std::regex_match(part, std::regex("\\d"))) {
        if (part != "-") {
            filteredParts.push_back(part);
        }
    }
}

// Join the filtered parts using "."
std::string pathSource = std::accumulate(std::next(filteredParts.begin()), filteredParts.end(),
                                         filteredParts.front(), [](std::string& a, std::string& b) {
                                             return a + "." + b;
                                         });

if (pathSource.empty()) {
    return Optional.empty();
}

try {
    return Optional.of(PropertyPath::from(pathSource, type));
} catch (PropertyReferenceException& ex) {
    throw PatchException(String.format(INVALID_PATH_REFERENCE, pathSource, type, path), ex);
}


}