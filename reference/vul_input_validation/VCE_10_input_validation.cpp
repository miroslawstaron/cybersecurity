void failureWithInvalidPatchContent() {
    Todo todo;
    todo.setDescription("Description");
    Patch patch = readJsonPatch("patch-failing-with-invalid-content.json");
    EXPECT_THROW_MSG(patch.apply(todo, Todo::class_type), PatchException, "content");
    EXPECT_THROW_MSG(patch.apply(todo, Todo::class_type), PatchException, "blabla");
    EXPECT_THROW_MSG(patch.apply(todo, Todo::class_type), PatchException, typeid(std::string).name());
}

Patch readJsonPatch(const std::string& jsonPatchFile) {
    ClassPathResource resource(jsonPatchFile, getClass());
    auto node = ObjectMapper().readValue(resource.getInputStream(), JsonNode::class_type);
    return JsonPatchPatchConverter(ObjectMapper()).convert(node);
}
