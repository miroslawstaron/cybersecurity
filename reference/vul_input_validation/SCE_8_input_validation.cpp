template<typename T>
Object MyClass::evaluateValueFromTarget(Object targetObject, Class<T> entityType) {
if (!path.endsWith("-")) {
return MyClassBase::evaluateValueFromTarget(targetObject, entityType);
}

return evaluate(verifyPath(entityType).map([](auto it) -> Class<T> { return it.getType(); }).orElse(entityType));

}